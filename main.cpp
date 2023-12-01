#include "board.h"
#include "ai.h"
#include <iostream>
using namespace std;



int main() {
    string respuesta;
    do {
        Board board;
        AI ai;
        cout << "\nConnecta 4\n" << endl;
        int maxDepth; // profundidad 
        string dificultad;

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
                maxDepth = 11; //Mientras mas mas dificil, pero toma mas tiempo por las ramificaciones
                break;
            } else if (dificultad == "s") {
                cout << "Gracias por jugar... " << endl;
                return 0;  // Salir del programa
            }
        }

        while (1) {
            board.imprimirTablero();

            int movimiento;
            cout << "Ingresar movimiento: "<<endl;
            cin >> movimiento;

            while(movimiento <1 || movimiento > 7){
                cout << "Invalido... Ingresa movimiento: "<<endl;
                cin >> movimiento;
            }

            while(board.dejarDisco(movimiento - 1, HUMAN) == -1){
                cout << "Invalido columna llena... Ingresa movimiento: "<<endl;
                cin >> movimiento;
            }

            board.imprimirTablero();

            if (board.puntajeTablero() == HUMAN_WIN){
                cout << "Victoria! " << endl;
                break;
            }

            cout << "IA: "<<endl;
            AI::NewMove compMove = ai.minimax(board, true, maxDepth, COMP, ALPHA, BETA);
            board.dejarDisco(compMove.move, COMP);

            if (board.puntajeTablero() == COMP_WIN){
                board.imprimirTablero();
                cout << "IA Win..." << endl;
                break;
            }
        }

        // Verificar si el jugador desea volver a jugar
        string respuesta = "";
        while(respuesta != "s" && respuesta != "n"){
            cout << "Desea volver a jagur? [s/n]: ";
            cin >> respuesta;
        }

        if (respuesta == "n") {
            cout << "Gracias por jugar... " << endl;
            break;
        } 
    } while (respuesta == "s");

    return 0;
}
  






