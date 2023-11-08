#include "Board.h"

Board::Board()
{
    init();
}

void Board::init()
{
    // ボード上の全マスを空きマスに設定する. 
    for (int y = 1; y <= BOARD_COL_SIZE; ++y)
    {
        for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
        {
            _rawBoard[x][y] = EMPTY;
        }
    }

    // 壁を設定する. 
    for (int y = 0; y < BOARD_COL_SIZE + 2; ++y)
    {
        _rawBoard[0][y] = WALL;
        _rawBoard[BOARD_COL_SIZE + 1][y] = WALL;
    }

    for (int x = 0; x < BOARD_ROW_SIZE + 2; ++x)
    {
        _rawBoard[x][0] = WALL;
        _rawBoard[x][BOARD_ROW_SIZE + 1] = WALL;
    }

    // 手数は0から数える. 
    _turns = 0;

    // 先手は黒. 
    _currentPlayerMark = O;

    // updateは全て削除する. 
    _updateLog.clear();

    // 石を置ける位置を初期化する. 
    initMovable();
}

bool Board::place(const Point& point)
{
    // ボード外に石は置けない. 
    if (point.getX() < 0 || point.getX() > BOARD_ROW_SIZE)
    {
        return false;
    }

    if (point.getY() < 0 || point.getY() > BOARD_COL_SIZE)
    {
        return false;
    }

    if (_rawBoard[point.getX()][point.getY()] != EMPTY)
    {
        return false;
    }

    _rawBoard[point.getX()][point.getY()] = _currentPlayerMark;


    return true;
}

bool Board::undo()
{
    // ゲーム開始時の場合、戻すことはできない. 
    if (0 == _turns)
    {
        return false;
    }

    // 一手前に戻す. 
    _currentPlayerMark = -_currentPlayerMark;
    const Disc& update = _updateLog.back();


    --_turns;

    // ボード上の石を前の状態に戻す. 
    _rawBoard[update.getX()][update.getY()] = EMPTY;
    

    // 不要になったupdateを1つ削除する. 
    _updateLog.pop_back();

    return true;
}

bool Board::isGameOver() const
{
    // ラインが完成してたらゲーム終了
    if (checkLine())
    {
        return true;
    }

    // 最大の手数に達していたらゲーム終了. 
    if (MAX_TURNS == _turns)
    {
        return true;
    }

    // 打ち手がある場合はゲーム終了ではない. 
    if (!_placeablePosition[_turns].empty())
    {
        return false;
    }

    
    return true;
}

void Board::switchMark()
{
    // 相手のターンに移る. 
    ++_turns;
    _currentPlayerMark = -_currentPlayerMark;

    // データ更新処理. 
    initMovable();
}

Mark Board::getMark(const Point& point) const
{
    return _rawBoard[point.getX()][point.getY()];
}

const std::vector<Point>& Board::getMovablePosition() const
{
    return _placeablePosition[_turns];
}

Disc Board::getUpdate() const
{
    if (_updateLog.empty())
    {
        return Disc();
    }
    else
    {
        return _updateLog.back();
    }
}

Mark Board::getCurrentMark() const
{
    return _currentPlayerMark;
}

unsigned int Board::getTurns() const
{
    return _turns;
}

void Board::initMovable()
{
    Disc disc(0, 0, _currentPlayerMark);

    _placeablePosition[_turns].clear();

    // ボード上の1マス1マスに対して石が置けるか判定する. 
    for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
    {
        disc.setX(x);

        for (int y = 1; y <= BOARD_COL_SIZE; ++y)
        {
            disc.setY(y);

            if (_rawBoard[x][y] == EMPTY)
            {
                _placeablePosition[_turns].push_back(disc);
            }
        }
    }
}

bool Board::checkLine() const
{
    //右
    for (int y = 1; y <= BOARD_COL_SIZE; ++y)
    {
        int cnt = 0;
        for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
        {
            if(_rawBoard[x][y] == _currentPlayerMark)
            {
                cnt++;
            }else{
                cnt = 0;
            }
            if(cnt >= K_IN_A_ROW)
            {
                return true;
            }
        }
    }

    //下
    for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
    {
        int cnt = 0;
        for (int y = 1; y <= BOARD_COL_SIZE; ++y)
        {
            if(_rawBoard[x][y] == _currentPlayerMark)
            {
                cnt++;
            }else{
                cnt = 0;
            }
            if(cnt >= K_IN_A_ROW)
            {
                return true;
            }
        }
    }

    //左下
    for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
    {
        int cnt = 0;
        int y = 1;
        for(int k = 0, l = 0; x + k >= 1 || y + l <= BOARD_COL_SIZE; --k, ++l)
        {
            if(_rawBoard[x + k][y + l] == _currentPlayerMark)
            {
                cnt++;
            }else{
                cnt = 0;
            }
            if(cnt >= K_IN_A_ROW)
            {
                return true;
            }
        }
    }
    for (int y = 1; y <= BOARD_COL_SIZE; ++y)
    {
        int cnt = 0;
        int x = BOARD_ROW_SIZE;
        for(int k = 0, l = 0; x + k >= 1 || y + l <= BOARD_COL_SIZE; --k, ++l)
        {
            if(_rawBoard[x + k][y + l] == _currentPlayerMark)
            {
                cnt++;
            }else{
                cnt = 0;
            }
            if(cnt >= K_IN_A_ROW)
            {
                return true;
            }
        }
    }
    
    //右下
    for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
    {
        int cnt = 0;
        int y = 1;
        for(int k = 0, l = 0; x + k <= BOARD_ROW_SIZE || y + l <= BOARD_COL_SIZE; ++k, ++l)
        {
            if(_rawBoard[x + k][y + l] == _currentPlayerMark)
            {
                cnt++;
            }else{
                cnt = 0;
            }
            if(cnt >= K_IN_A_ROW)
            {
                return true;
            }
        }
    }
    for (int y = 1; y <= BOARD_ROW_SIZE; ++y)
    {
        int cnt = 0;
        int x = 1;
        for(int k = 0, l = 0; x + k <= BOARD_ROW_SIZE || y + l <= BOARD_COL_SIZE; ++k, ++l)
        {
            if(_rawBoard[x + k][y + l] == _currentPlayerMark)
            {
                cnt++;
            }else{
                cnt = 0;
            }
            if(cnt >= K_IN_A_ROW)
            {
                return true;
            }
        }
    }

    return false;
}