#include "ConsoleBoard.h"
#include <string>

int main()
{
    ConsoleBoard board;

    while (true)
    {
        board.display();

        std::cout << std::endl;

        std::cout << "input..." << std::endl;

        Point p;
        std::string in;
        std::cin >> in;

        if ("u" == in)
        {
            board.undo();
            continue;
        }

        if (in.length() >= 2)
        {
            p.setX(in[0] - 'a' + 1);
            p.setY(in[1] - '1' + 1);
        }
        else
        {
            std::cerr << "invalid input!!" << std::endl;
            continue;
        }

        if (false == board.place(p))
        {
            std::cerr << "can't put the disc there!!" << std::endl;
            continue;
        }

        if (board.isGameOver())
        {
            std::cout << "Game Over..." << std::endl;
            if(board.getCurrentMark() == O)
            {
                std::cout << "!!! O win !!!" << std::endl;
            }else if(board.getCurrentMark() == X)
            {
                std::cout << "!!! X win !!!" << std::endl;
            }
            
            return 0;
        }

        board.switchMark();
    }

    return 0;
}