#include "ai.h"
using namespace std;

AI::NewMove AI::minimax(Board &board, bool isMaximizing, int depth, int player, int alpha, int beta) {
    // Obtiene el puntaje inicial del tablero
    int puntajeInicial = board.puntajeTablero();

    // Verifica si el tablero está lleno
    if (board.tableroFull()) {
        return NewMove(0);
    }
    // Verifica si el jugador actual ha ganado
    else if (puntajeInicial == COMP_WIN) {
        return NewMove(COMP_WIN);
    }
    // Verifica si el oponente ha ganado
    else if (puntajeInicial == HUMAN_WIN) {
        return NewMove(HUMAN_WIN);
    }
    // Verifica si se ha alcanzado la profundidad máxima de búsqueda
    else if (depth == 0) {
        return NewMove(puntajeInicial);
    }

    // Si es el turno del jugador maximizador
    if (isMaximizing) {
        // Inicializa el mejor movimiento con un puntaje muy bajo
        NewMove bestMove(-100000000);
        bestMove.move = -1;

        // Itera sobre todas las columnas del tablero
        for (int x = 0; x < ANCHO; x++) {
            // Deja caer un disco en la columna actual
            int fila = board.dejarDisco(x, COMP);
            // Si la columna está llena, continúa con la siguiente columna
            if (fila == -1) {
                continue;
            }
            // Calcula el puntaje para el movimiento actual utilizando la recursión
            int puntaje = minimax(board, !isMaximizing, depth - 1, HUMAN, alpha, beta).score;
            // Elimina el disco para deshacer el movimiento
            board.eliminarDisco(fila, x);

            // Actualiza el mejor movimiento y el valor de alpha
            if (puntaje > bestMove.score) {
                bestMove.move = x;
                bestMove.score = puntaje;
            }
            alpha = std::max(bestMove.score, alpha);
            // Realiza la poda alfa-beta
            if (beta <= alpha) {
                break;
            }
        }
        return bestMove;
    }
    // Si es el turno del jugador minimizador
    else {
        // Inicializa el mejor movimiento con un puntaje muy alto
        NewMove bestMove(100000000);
        bestMove.move = -1;

        // Itera sobre todas las columnas del tablero
        for (int x = 0; x < ANCHO; x++) {
            // Deja caer un disco en la columna actual
            int fila = board.dejarDisco(x, HUMAN);
            // Si la columna está llena, continúa con la siguiente columna
            if (fila == -1) {
                continue;
            }
            // Calcula el puntaje para el movimiento actual utilizando la recursión
            int puntaje = minimax(board, !isMaximizing, depth - 1, COMP, alpha, beta).score;
            // Elimina el disco para deshacer el movimiento
            board.eliminarDisco(fila, x);

            // Actualiza el mejor movimiento y el valor de beta
            if (puntaje < bestMove.score) {
                bestMove.move = x;
                bestMove.score = puntaje;
            }
            beta = std::min(bestMove.score, beta);
            // Realiza la poda alfa-beta
            if (beta <= alpha) {
                break;
            }
        }
        return bestMove;
    }
}