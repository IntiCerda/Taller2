using namespace std;

#include "board.h"

Board::Board()
{
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 7; x++)
        {
            _board[y][x] = 0;
        }
    }
}

void Board::printBoard()
{
    cout << "\n";
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 7; x++)
        {
            cout << " ";

            if (_board[y][x] == HUMAN)
            {
                cout << "x" << RESET;
            }
            else if (_board[y][x] == COMP)
            {
                cout << "o" << RESET;
            }
            else
            {
                cout << "-";
            }
        }
        cout << endl;
    }

    for (int x = 1; x <= WIDTH; x++)
    {
        cout << " " << x<<endl;
    }
    cout << "\n\n" << endl;
}

int Board::dropDisk(int column, int player)
{
    for (int y = 6 - 1; y >= 0; y--)
    {
        if (_board[y][column] == 0)
        {
            _board[y][column] = player;
            return y;
        }
    }
    return -1;
}

void Board::removeDisk(int row, int column)
{
    _board[row][column] = 0;
}

bool Board::boardFull()
{
    for (int x = 0; x < 7; x++)
    {
        if (_board[0][x] == 0)
        {
            return false;
        }
    }
    return true;
}

bool Board::columnFull(int column)
{
    return _board[0][column] != 0;
}

long Board::scoreBoard()
{
    int counters[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    typedef int grid[6][7];
    const grid &scores = _board;

    // Horizontal spans
    for (int y = 0; y < 6; y++)
    {
        int score = scores[y][0] + scores[y][1] + scores[y][2];
        for (int x = 3; x < 7; x++)
        {
            score += scores[y][x];
            counters[score + 4]++;
            score -= scores[y][x - 3];
        }
    }
    // Vertical spans
    for (int x = 0; x < 7; x++)
    {
        int score = scores[0][x] + scores[1][x] + scores[2][x];
        for (int y = 3; y < 6; y++)
        {
            score += scores[y][x];
            counters[score + 4]++;
            score -= scores[y - 3][x];
        }
    }
    // Down-right (and up-left) diagonals
    for (int y = 0; y < 6 - 3; y++)
    {
        for (int x = 0; x < 7 - 3; x++)
        {
            int score = 0;
            for (int idx = 0; idx < 4; idx++)
            {
                int yy = y + idx;
                int xx = x + idx;
                score += scores[yy][xx];
            }
            counters[score + 4]++;
        }
    }
    // up-right (and down-left) diagonals
    for (int y = 3; y < 6; y++)
    {
        for (int x = 0; x < 7 - 3; x++)
        {
            int score = 0;
            for (int idx = 0; idx < 4; idx++)
            {
                int yy = y - idx;
                int xx = x + idx;
                score += scores[yy][xx];
            }
            counters[score + 4]++;
        }
    }
    if (counters[0] != 0)
        return HUMAN_WIN;
    else if (counters[8] != 0)
        return COMP_WIN;
    else // heuristic function
        return counters[5] + 2 * counters[6] + 5 * counters[7] -
               counters[3] - 4 * counters[2] - 10 * counters[1];
}