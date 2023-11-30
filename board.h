#pragma once
#define BOARD_H

#include <iostream>
#include "global.h"

class Board
{
    int _board[ALTO][ANCHO];

public:
    Board();
    void printBoard();
    int dropDisk(int column, int player);
    void removeDisk(int row, int column);
    bool boardFull();
    bool columnFull(int column);
    long scoreBoard();
};
