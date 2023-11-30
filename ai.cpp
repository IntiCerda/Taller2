#include "ai.h"

AI::NewMove AI::minimax(Board &board, bool isMaximizing, int depth, int player, int alpha, int beta)
{
    int initialScore = board.scoreBoard();
    if (board.boardFull())
    {
        return NewMove(0);
    }
    else if (initialScore == COMP_WIN)
    {
        return NewMove(COMP_WIN);
    }
    else if (initialScore == HUMAN_WIN)
    {
        return NewMove(HUMAN_WIN);
    }
    else if (depth == 0)
    {
        return NewMove(initialScore);
    }

    if (isMaximizing)
    {
        NewMove bestMove(-100000000);
        bestMove.move = -1;

        for (int x = 0; x < ANCHO; x++)
        {
            int row = board.dropDisk(x, COMP);
            if (row == -1)
            {
                continue;
            }
            int score = minimax(board, !isMaximizing, depth - 1, HUMAN, alpha, beta).score;

            board.removeDisk(row, x);

            if (score > bestMove.score)
            {
                bestMove.move = x;
                bestMove.score = score;
            }

            alpha = std::max(bestMove.score, alpha);
            if (beta <= alpha)
                break;
        }
        return bestMove;
    }
    else
    {
        NewMove bestMove(100000000);
        bestMove.move = -1;

        for (int x = 0; x < ANCHO; x++)
        {
            int row = board.dropDisk(x, HUMAN);
            if (row == -1)
            {
                continue;
            }
            int score = minimax(board, !isMaximizing, depth - 1, COMP, alpha, beta).score;
            board.removeDisk(row, x);

            if (score < bestMove.score)
            {
                bestMove.move = x;
                bestMove.score = score;
            }

            beta = std::min(bestMove.score, beta);
            if (beta <= alpha)
                break;
        }
        return bestMove;
    }
}