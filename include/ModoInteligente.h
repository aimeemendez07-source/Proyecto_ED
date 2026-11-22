#ifndef MODOINTELIGENTE_H
#define MODOINTELIGENTE_H

#include <vector>
#include <string>
#include "Tablero.h"
#include "Solucionador.h"

// Pantalla del modo inteligente: el usuario define inicio y meta,
// el programa resuelve con A* y muestra la solucion paso a paso.
class ModoInteligente {
private:
    Tablero inicio;                 // Punto de inicio elegido
    Tablero meta;                   // Meta elegida por el usuario
    std::vector<Tablero> camino;    // Traza de la solucion (inicio -> meta)
    Solucionador solucionador;      // Algoritmo A*
    int pasoActual;                 // Paso que se esta mostrando
    bool enSolucion;                // true: mostrando solucion, false: configurando
    bool reproduccionAutomatica;    // true si avanza sola
    float temporizador;             // Tiempo acumulado para la reproduccion automatica
    std::string mensaje;            // Mensaje informativo para el usuario
    bool mensajeEsError;            // Define el color del mensaje

    // Mezcla un tablero aplicando movimientos legales aleatorios (siempre resoluble)
    void mezclarTablero(Tablero& tablero, int movimientos);

    // Si hay clic sobre una ficha del tablero dibujado en (x, y), intenta moverla
    void procesarClicTablero(Tablero& tablero, int x, int y, int tamCelda);

    // Dibuja un tablero con fichas rellenas
    void dibujarTablero(const Tablero& tablero, int x, int y, int tamCelda) const;

    // Ejecuta A* con el inicio y la meta actuales
    void resolver();

    // Pantallas de cada fase
    void actualizarConfiguracion();
    void actualizarSolucion();
    void dibujarConfiguracion() const;
    void dibujarSolucion() const;

public:
    ModoInteligente();
    void reiniciar();   // Prepara una nueva sesion (meta estandar, inicio aleatorio)
    void actualizar();  // Procesa la entrada del usuario
    void dibujar() const; // Dibuja la pantalla actual
};

#endif
