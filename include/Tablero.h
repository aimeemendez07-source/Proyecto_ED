#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>

class Tablero {
private:
    int celdas[3][3]; 
    int filaVacia, colVacia;
    
public:
    
    Tablero();
    void inicializarAleatorio();
    void setEstado(const int nuevoEstado[3][3]);
    void getEstado(int estado[3][3]) const;
    
    
    int getFilaVacia() const;
    int getColVacia() const;
    int getCelda(int fila, int col) const;
    
    
    bool mover(int fila, int col);
    bool esMeta(const Tablero& meta) const;
    bool esIgual(const Tablero& otro) const;
    bool esValido() const;
    bool tieneSolucion(const Tablero& meta) const;
    
    int calcularDistanciaManhattan(const Tablero& meta) const;
    int calcularPiezasMalColocadas(const Tablero& meta) const;
    

    std::vector<Tablero> generarSucesores() const;
    
    
    std::string toString() const;
};

#endif
