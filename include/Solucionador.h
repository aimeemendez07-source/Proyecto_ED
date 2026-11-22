#ifndef SOLUCIONADOR_H
#define SOLUCIONADOR_H

#include <vector>
#include "Tablero.h"

// Nodo del arbol de busqueda de A*
struct NodoBusqueda {
    Tablero estado;   // Configuracion del tablero en este nodo
    int g;            // movimientos desde el inicio
    int h;            // Heuristica (distancia Manhattan)
    int padre;        // Indice del nodo padre en el vector de nodos (-1 si es la raiz)
};

// Resuelve el 8-puzzle con A* usando la distancia Manhattan como heuristica
class Solucionador {
private:
    int nodosExpandidos;

    // Convierte un tablero en un entero unico
    static int codificarEstado(const Tablero& tablero);

    // devuelve el camino inicio -> nodo
    std::vector<Tablero> reconstruirCamino(const std::vector<NodoBusqueda>& nodos, int indiceFinal) const;

public:
    Solucionador();

    // Devuelve la traza de estados desde inicio hasta meta (ambos incluidos).
    // Si no existe solucion devuelve un vector vacio.
    std::vector<Tablero> resolver(const Tablero& inicio, const Tablero& meta);

    // Cantidad de nodos expandidos en la ultima busqueda
    int getNodosExpandidos() const;
};

#endif
