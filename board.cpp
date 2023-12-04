#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//inicializa el tablero con celdas vacías y se llama automáticamente cuando se crea un objeto de la clase "Board"
Board::Board(){
    for (int y = 0; y < 6; y++){
        for (int x = 0; x < 7; x++){
            tablero[y][x] = 0;
        }
    }
}
//simula el proceso de dejar caer un disco, verifica si la celda está vacía. Si encuentra una celda vacía, 
//coloca el disco del jugador en esa celda y devuelve el número de fila en la que se dejó caer el disco. Si la columna está llena, la función devuelve -1 para indicar que no se puede dejar caer el disco en esa columna.
int Board::dejarDisco(int columna, int player){
    for (int y = ALTO - 1; y >= 0; y--){
        if (tablero[y][columna] == EMPTY){
            tablero[y][columna] = player;
            return y;
        }
    }
    return -1;
}

//calcula el puntaje total para cada jugador en el tablero de juego y devuelve el resultado según quién tenga más puntaje,
//sumando las posiciones de los contadores que corresponden a las filas y columnas ganadas, así como las posiciones de los contadores en las diagonales.
long Board::puntajeTablero(){
    int contador[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int puntajes[6][7];

    // Copiar los valores de tablero a puntajes
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 7; x++) {
            puntajes[y][x] = tablero[y][x];
        }
    }

    //  calcular los puntajes horizontales, recorre cada fila de la matriz "puntajes" y calcula la suma de los valores en las primeras tres columnas.
    // Luego, utiliza otro bucle for para recorrer las columnas restantes y calcular la suma de los valores en cada grupo de cuatro columnas
    for (int y = 0; y < ALTO; y++){
        int valor = puntajes[y][0] + puntajes[y][1] + puntajes[y][2];
        for (int x = 3; x < ANCHO; x++){
            valor += puntajes[y][x];
            contador[valor + 4]++;
            valor -= puntajes[y][x - 3];
        }
    }

    // Lo mismo de arriba pero en vertical 
    for (int x = 0; x < ANCHO; x++){
        int valor = puntajes[0][x] + puntajes[1][x] + puntajes[2][x];
        for (int y = 3; y < ALTO; y++)
        {
            valor += puntajes[y][x];
            contador[valor + 4]++;
            valor -= puntajes[y - 3][x];
        }
    }

    // recorre cada fila de la matriz "puntajes" y cada columna de la matriz "puntajes" para calcular los puntajes diagonales hacia abajo y hacia la derecha
    for (int y = 0; y < ALTO - 3; y++){
        for (int x = 0; x < ANCHO - 3; x++){
            int valor = 0;
            for (int idx = 0; idx < 4; idx++){
                int yy = y + idx;
                int xx = x + idx;
                valor += puntajes[yy][xx];
            }
            contador[valor + 4]++;
        }
    }

    // calcular los puntajes diagonales hacia arriba y hacia la derecha.
    for (int y = 3; y < ALTO; y++){
        for (int x = 0; x < ANCHO - 3; x++){
            int valor = 0;
            for (int idx = 0; idx < 4; idx++){
                int yy = y - idx;
                int xx = x + idx;
                valor += puntajes[yy][xx];
            }
            contador[valor + 4]++;
        }
    }
    if (contador[0] != 0)
        return HUMAN_WIN;

    else if (contador[8] != 0)
        return COMP_WIN;

    else //se calcula un puntaje basado en los contadores en diferentes posiciones y se devuelve ese puntaje
        return contador[5] + 2 * contador[6] + 5 * contador[7] -
               contador[3] - 4 * contador[2] - 10 * contador[1];
}

//true si el tablero está completo y false en caso contrario.
bool Board::tableroFull(){
    for (int x = 0; x < ANCHO; x++)
    {
        if (tablero[0][x] == EMPTY){
            return false;
        }
    }
    return true;
}

// "fila" y "columna", que representan las coordenadas de una celda en el tablero. La función entonces asigna el valor de "EMPTY" (0) a la celda en la posición especificada
void Board::eliminarDisco(int fila, int columna){
    tablero[fila][columna] = EMPTY;
}

//verifica si una columna específica del tablero está llena y devuelve un valor booleano en función de esa verificación.
bool Board::columnaFull(int columna){
    return tablero[0][columna] != EMPTY;
}

//imprime por pantalla el tablero, cuando se encuantra con "HUMAN" (= -1) se reemplaza con una X, y en caso de COMP con una o
void Board::imprimirTablero(){
    cout << "\n";
    for (int y = 0; y < 6; y++){
        for (int x = 0; x < 7; x++){
            cout << " ";

            if (tablero[y][x] == HUMAN){
                cout << "x";
            }
            else if (tablero[y][x] == COMP){
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

//guarda la partida en un csv.
void Board:: guardarPartida(std::string nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int y = 0; y < 6; y++) {
            for (int x = 0; x < 7; x++) {
                archivo << tablero[y][x];
                if (x < 6) {
                    archivo << ",";  // Separador de columnas
                }
            }
            archivo << std::endl;  // Nueva fila
        }
        archivo.close();
    } 
}

//Carga la partida sdkla
void Board:: cargarPartida(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int y = 0; y < 6; y++) {
            for (int x = 0; x < 7; x++) {
                char valor;
                archivo >> valor;
                tablero[y][x] = valor - '0';
                archivo.ignore(); 
            }
        }
        archivo.close();
        cout << "Partida cargada "<< endl;
    } else {
        cout << "Error al cargar partida... " << endl;
    }
    archivo.close();
}
