#pragma once
#define AI_H

#include <algorithm>
#include "board.h"
#include "define.h"

class AI{
    int maxDepth;

public:
    struct NewMove{
        int move;
        int score;
        NewMove(int score){
            this->score = score;
        }
    };

    NewMove minimax(
        Board &board,
        bool isMaximizing,
        int depth,
        int player,
        int alpha,
        int beta
    );
};
