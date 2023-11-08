#include "ConsoleBoard.h"
#include <stdlib.h>

void ConsoleBoard::display()
{
    system("clear");

    for (int y = 1; y <= BOARD_COL_SIZE; ++y)
    {
        std::cout << " ";

        for (int x = 1; x <= BOARD_ROW_SIZE; ++x)
        {
            switch (getMark(Point(x, y)))
            {
            case O:
                std::cout << "O";
                break;
            case X:
                std::cout << "X";
                break;
            default:
                std::cout << " ";
                break;
            }
            if(x != BOARD_ROW_SIZE)
            {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        if(y != BOARD_COL_SIZE)
        {
            std::cout << "-------";
        }
        std::cout << std::endl;
    }
}
