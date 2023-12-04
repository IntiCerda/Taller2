#include "board.h"
#include "ai.h"
#include <iostream>
#include <fstream>  
using namespace std;

//Funcion que agrega el ganador al archivo .csv
void guardar_ganador(const std::string& ganador) {
    std::ofstream archivo("partidas.csv", std::ios::app);
    archivo << ganador << endl;
    archivo.close();
}

//Imprime el archivo CSV, 
void mostrar_historial() {
    cout<<endl;
    cout<<"Historial: "<<endl;
    cout<<endl;
    std::ifstream archivo("partidas.csv");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            cout <<"-> "<< linea << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." <<endl;
    }
}
//Limpia el archivo.csv
void limpiar_archivo() {
    std::ofstream archivo("partidas.csv", std::ofstream::out | std::ofstream::trunc); //Sincermaente ni idea de como funciona esto, es la forma que encontre para poder limpiar el .csv
    cout<<"Archivo limpiado. "<<endl;
    cout<<endl;
    archivo.close();
}

int main() {
    string respuesta;
    do {
        Board board;
        AI ai;
        cout << "\nConnecta 4\n" << endl;
        cout << "El programa contiene un autoguardado despues de cada movimiento del Jugador. " <<endl;
        int profMaxima; // profundidad 
        string dificultad;

        while (1) {
            cout << "Dificultad:  [d]: dificil                | [m]: medio            | [f]: facil         | [i]: imposible   " << endl;
            cout << "Extras:      [h]: historial de victorias | [l] Limpiar Historial | [c] Cargar partida | [s]: salir" << endl;
            cin >> dificultad;
            if (dificultad == "d") {
                profMaxima = 7;
                break;
            } else if (dificultad == "m") {
                profMaxima = 5;
                break;
            } else if (dificultad == "f") {
                profMaxima = 3;
                break;
            } else if (dificultad == "i") {
                profMaxima = 9; //Mientras mas mas dificil, pero toma mas tiempo en cargar cada jugada de la IA
                break;
            } else if(dificultad == "h"){
                mostrar_historial();
                
            }else if(dificultad == "l"){
                limpiar_archivo();

            }else if (dificultad == "c") {
                board.cargarPartida("partidaGuardada");
                break;
            }else if (dificultad == "s") {
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
            board.guardarPartida("partidaGuardada");

            board.imprimirTablero();
            if (board.puntajeTablero() == HUMAN_WIN){
                cout << "Victoria! " << endl;
                guardar_ganador("Jugador");
                break;
            }

            cout << "IA: "<<endl;
            AI::NewMove compMove = ai.minimax(board, true, profMaxima, COMP, ALPHA, BETA);
            board.dejarDisco(compMove.move, COMP);

            if (board.puntajeTablero() == COMP_WIN){
                board.imprimirTablero();
                cout << "IA Win..." << endl;
                guardar_ganador("IA");
                break;
            }
        }

        // Verificar si el jugador desea volver a jugars
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
  






