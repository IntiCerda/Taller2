#include "board.h"
#include "ai.h"
#include <iostream>
using namespace std;


int main()
{
    Board board;
    AI ai;
    cout << "\nConnecta 4\n"<<endl;
    int maxDepth; // profundidad 
    string dificultad = "";
    while (1) {
        cout << "Dificultad:  [d]: dificil | [m]: medio | [f]: facil | [i]: imposible: | [s]: salir  " << endl;
        cin >> dificultad;
        if (dificultad == "d") {
            maxDepth = 9;
            break;
        } else if (dificultad == "m") {
            maxDepth = 5;
            break;
        } else if (dificultad == "f") {
            maxDepth = 3;
            break;
        } else if (dificultad == "i") {
            maxDepth = 40;
            break;
        } else if (dificultad == "s") {
            cout << "Gracias por jugar... " << endl;
            return 0;  // Salir del programa
        }
    }

    while (1){
        board.printBoard();

        int movimiento;
        cout << "Ingresar movimiento: "<<endl;
        cin >> movimiento;
        board.dropDisk(movimiento - 1, HUMAN);
        board.printBoard();

        if (board.scoreBoard() == HUMAN_WIN){
            cout << "Victoria! " << endl;
            break;
        }

        cout << "IA: "<<endl;
        AI::NewMove compMove = ai.minimax(board, true, maxDepth, COMP, ALPHA, BETA);
        board.dropDisk(compMove.move, COMP);

        if (board.scoreBoard() == COMP_WIN){
            board.printBoard();
            cout << "IA Win..." << endl;
            break;
        }
    }

    return 0;
}