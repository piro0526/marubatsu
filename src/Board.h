#pragma once
#include "Disc.h"
#include <utility>
#include <vector>

static const int BOARD_ROW_SIZE = 3;
static const int BOARD_COL_SIZE = 3;
static const int K_IN_A_ROW = 3;
static const int MAX_TURNS = BOARD_ROW_SIZE*BOARD_COL_SIZE;


class Board
{
public:
    Board();

    void init();
    bool place(const Point point);
    bool undo();
    bool checkLine() const;
    bool isGameOver() const;
    void switchMark();

    const Mark getMark(const Point& point) const;
    std::vector<Point> getPlaceablePosition() const;
    Disc getUpdate() const;
    Mark getCurrentMark() const;
    unsigned int getTurns() const;

private:
    void initMovable();

    // ボード上の石. 
    Mark _rawBoard[BOARD_ROW_SIZE + 2][BOARD_COL_SIZE + 2];

    // 手数. 
    unsigned int _turns;

    // 現在のプレイヤー. 
    Mark _currentPlayerMark;

    // 打ち手の履歴. 
    std::vector<Disc> _updateLog;

    // 石を置ける位置. 
    std::vector<Point> _placeablePosition[MAX_TURNS + 1];
};