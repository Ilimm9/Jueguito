#include <ncurses.h>

void dibujarJugador(int x, int y) {
    mvprintw(y, x, "X"); // Dibuja el jugador en la posición (x, y)
    refresh(); // Actualiza la pantalla
}

void eliminarJugador(int x, int y) {
    mvprintw(y, x, " "); // Borra el jugador en la posición (x, y)
    refresh(); // Actualiza la pantalla
}

void hacerJugador(int x, int y) {
    int tecla = -1;
    dibujarJugador(x, y);
    while (true) {
        if ((tecla = getch()) != ERR) { // Captura una tecla (ERR indica que no se presionó ninguna tecla)
            eliminarJugador(x, y);
            switch (tecla) {
                case 'S': x--; break;
                case 'A': x++; break;
            }
            dibujarJugador(x, y);
        }
    }
}

int main() {
    int x = 41;
    int y = 15;

    initscr(); // Inicializa la pantalla de ncurses
    noecho(); // No muestra las teclas presionadas
    curs_set(0); // Oculta el cursor

    hacerJugador(x, y);

    endwin(); // Finaliza la pantalla de ncurses
    return 0;
}