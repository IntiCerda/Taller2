#include "board.h"
#include "ai.h"
#include <iostream>
using namespace std;


int main()
{
    Board board;
    AI ai;
    cout << "--------------------\n\nConnecta 4\n\n--------------------\n\n"<<endl;
    int maxDepth;

    while (1)
    {
        string dificultad;
        cout << "Dificultad  [d]: dificil | [m]: medio | [f]: facil | [i]: imposible: "<<endl;
        cin >> dificultad;

        if (dificultad == "d")
        {
            maxDepth = 9;
            break;
        }
        else if (dificultad == "m")
        {
            maxDepth = 5;
            break;
        }
        else if (dificultad == "f")
        {
            maxDepth = 3;
            break;
        }
        else if (dificultad == "i")
        {
            maxDepth = 41;
            break;
        }
    }

    while (1)
    {
        board.printBoard();

        int move;
        cout << "Enter Move: "<<endl;
        cin >> move;
        board.dropDisk(move - 1, HUMAN);
        board.printBoard();

        if (board.scoreBoard() == HUMAN_WIN)
        {
            cout << "Victoria! " << endl;
            break;
        }

        cout << "IA: "<<endl;
        AI::NewMove compMove = ai.minimax(board, true, maxDepth, COMP, ALPHA, BETA);
        board.dropDisk(compMove.move, COMP);

        if (board.scoreBoard() == COMP_WIN)
        {
            board.printBoard();
            cout << "IA Win..." << endl;
            break;
        }
    }

    return 0;
}