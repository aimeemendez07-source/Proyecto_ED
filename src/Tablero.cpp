#include "Tablero.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

Tablero::Tablero(){
    int metaInicial[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    setEstado(metaInicial);
}

void Tablero::setEstado(const int nuevoEstado[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            celdas[i][j] = nuevoEstado[i][j];
            if (celdas[i][j] == 0) {
                filaVacia = i;
                colVacia = j;
            }
        }
    }
}

void Tablero::getEstado(int estado[3][3]) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            estado[i][j] = celdas[i][j];
        }
    }
}

int Tablero::getFilaVacia() const { return filaVacia; }
int Tablero::getColVacia() const { return colVacia; }
int Tablero::getCelda(int fila, int col) const { return celdas[fila][col]; }

bool Tablero::mover(int fila, int col) {
    if(fila < 0 || fila > 2 || col < 0 || col > 2)return false;
    int distancia = abs(fila - filaVacia) + abs(col - colVacia);
    if (distancia != 1) return false;
    celdas[filaVacia][colVacia] = celdas[fila][col];
    celdas[fila][col] = 0;
    filaVacia = fila;
    colVacia = col;
    return true;
}

void Tablero::inicializarAleatorio() {
    srand(time(0));
    int nuevoEstado[3][3];
    int meta[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    Tablero metaTablero;
    metaTablero.setEstado(meta);
    do {
        int numeros[9] = {0,1,2,3,4,5,6,7,8};
        
        for (int i = 8; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = numeros[i];
            numeros[i] = numeros[j];
            numeros[j] = temp;
        }
         int k = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                nuevoEstado[i][j] = numeros[k++];
            }
        }
        setEstado(nuevoEstado);
    } while (!tieneSolucion(metaTablero));
}

bool Tablero::esMeta(const Tablero& meta) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (celdas[i][j] != meta.getCelda(i, j)) return false;
        }
    }
    return true;
}

bool Tablero::esIgual(const Tablero& otro) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (celdas[i][j] != otro.getCelda(i, j)) return false;
        }
    }
    return true;
}

bool Tablero::esValido() const {
    bool vistos[9] = {false};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = celdas[i][j];
            if (num < 0 || num > 8 || vistos[num]) return false;
            vistos[num] = true;
        }
    }
    return true;
}

bool Tablero::tieneSolucion(const Tablero& meta) const {

    int actual[8], objetivo[8];
    int k1 = 0, k2 = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (celdas[i][j] != 0) actual[k1++] = celdas[i][j];
            if (meta.getCelda(i, j) != 0) objetivo[k2++] = meta.getCelda(i, j);
        }
    }
    int invActual = 0, invMeta = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (actual[i] > actual[j]) invActual++;
            if (objetivo[i] > objetivo[j]) invMeta++;
        }
    }
     return (invActual % 2) == (invMeta % 2);
}

int Tablero::calcularDistanciaManhattan(const Tablero& meta) const {
    int distancia = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int ficha = celdas[i][j];
            if (ficha != 0) {
                for (int mi = 0; mi < 3; mi++) {
                    for (int mj = 0; mj < 3; mj++) {
                        if (meta.getCelda(mi, mj) == ficha) {
                            distancia += abs(i - mi) + abs(j - mj);
                        }
                    }
                }
            }
        }
    }
    return distancia;
}

std::vector<Tablero> Tablero::generarSucesores() const {
    std::vector<Tablero> sucesores;
    int df[] = {-1, 1, 0, 0}; 
    int dc[] = {0, 0, -1, 1}; 
    
    for (int k = 0; k < 4; k++) {
        int nf = filaVacia + df[k];
        int nc = colVacia + dc[k];
        
        if (nf >= 0 && nf < 3 && nc >= 0 && nc < 3) {
            Tablero nuevo = *this;
            nuevo.mover(nf, nc);
            sucesores.push_back(nuevo);
        }
    }
    return sucesores;
}

