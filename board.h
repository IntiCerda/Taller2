#pragma once
#define BOARD_H

#include <iostream>
#include "define.h"

class Board
{
    int _board[ALTO][ANCHO];

public:
    Board();
    void printBoard();
    int dropDisk(int column, int player);
    void removeDisk(int fila, int column);
    bool boardFull();
    bool columnFull(int column);
    long scoreBoard();
};
