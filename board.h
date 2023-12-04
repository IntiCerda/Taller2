#pragma once
#define BOARD_H
#include <fstream>
#include <string>
#include <iostream>
#include "define.h"

class Board{
    int tablero[ALTO][ANCHO];

public:
    Board();
    void imprimirTablero();
    bool tableroFull();
    bool columnaFull(int columna);
    long puntajeTablero();
    int dejarDisco(int columna, int player);
    void eliminarDisco(int fila, int columna);
    void guardarPartida(std::string nombreArchivo);
    void cargarPartida(std::string nombreArchivo);
};
