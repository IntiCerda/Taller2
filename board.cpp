#include "board.h"
using namespace std;


Board::Board(){
    for (int y = 0; y < 6; y++){
        for (int x = 0; x < 7; x++){
            _board[y][x] = 0;
        }
    }
}

int Board::dropDisk(int column, int player){
    for (int y = ALTO - 1; y >= 0; y--){
        if (_board[y][column] == EMPTY){
            _board[y][column] = player;
            return y;
        }
    }
    return -1;
}

long Board::scoreBoard(){
    int counters[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    typedef int grid[ALTO][ANCHO];
    const grid &scores = _board;

    // Horizontales
    for (int y = 0; y < ALTO; y++){
        int score = scores[y][0] + scores[y][1] + scores[y][2];
        for (int x = 3; x < ANCHO; x++){
            score += scores[y][x];
            counters[score + 4]++;
            score -= scores[y][x - 3];
        }
    }
    // Vertical 
    for (int x = 0; x < ANCHO; x++){
        int score = scores[0][x] + scores[1][x] + scores[2][x];
        for (int y = 3; y < ALTO; y++)
        {
            score += scores[y][x];
            counters[score + 4]++;
            score -= scores[y - 3][x];
        }
    }
    // Diagonales abajo derecha
    for (int y = 0; y < ALTO - 3; y++){
        for (int x = 0; x < ANCHO - 3; x++){
            int score = 0;
            for (int idx = 0; idx < 4; idx++){
                int yy = y + idx;
                int xx = x + idx;
                score += scores[yy][xx];
            }
            counters[score + 4]++;
        }
    }
    // diagonales arriba derecha
    for (int y = 3; y < ALTO; y++){
        for (int x = 0; x < ANCHO - 3; x++){
            int score = 0;
            for (int idx = 0; idx < 4; idx++){
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
    else 
        return counters[5] + 2 * counters[6] + 5 * counters[7] -
               counters[3] - 4 * counters[2] - 10 * counters[1];
}

bool Board::boardFull(){
    for (int x = 0; x < ANCHO; x++)
    {
        if (_board[0][x] == EMPTY){
            return false;
        }
    }
    return true;
}

void Board::removeDisk(int fila, int column){
    _board[fila][column] = EMPTY;
}

bool Board::columnFull(int column){
    return _board[0][column] != EMPTY;
}

void Board::printBoard(){
    cout << "\n";
    for (int y = 0; y < 6; y++){
        for (int x = 0; x < 7; x++){
            cout << " ";

            if (_board[y][x] == HUMAN){
                cout << "x";
            }
            else if (_board[y][x] == COMP){
                cout << "o";
            }
            else{
                cout << "-";
            }
        }
        cout << endl;
    }

    for (int x = 1; x <= 7; x++){
        cout << " " << x;
    }
    cout << "\n\n";
}