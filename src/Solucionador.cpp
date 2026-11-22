#include "Solucionador.h"
#include <queue>
#include <unordered_map>
#include <algorithm>

// Elemento de la cola de prioridad: guarda f(n) y el indice del nodo
struct ElementoCola {
    int f;        // f(n) = g(n) + h(n)
    int g;        // Se usa para desempatar (se prefiere el mas profundo)
    int indice;   // Posicion del nodo en el vector de nodos
};

// Comparador: saca primero el menor f(n)
struct ComparadorCola {
    bool operator()(const ElementoCola& A, const ElementoCola& B) const {
        if (A.f != B.f) return A.f > B.f;
        return A.g < B.g;
    }
};

Solucionador::Solucionador() {
    nodosExpandidos = 0;
}

int Solucionador::getNodosExpandidos() const {
    return nodosExpandidos;
}

// Codifica el tablero como un numero en base 9
int Solucionador::codificarEstado(const Tablero& tablero) {
    int codigo = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            codigo = codigo * 9 + tablero.getCelda(i, j);
        }
    }
    return codigo;
}

// Sigue los padres desde el nodo final hasta la raiz y luego invierte el orden
std::vector<Tablero> Solucionador::reconstruirCamino(const std::vector<NodoBusqueda>& nodos, int indiceFinal) const {
    std::vector<Tablero> camino;
    int indice = indiceFinal;
    while (indice != -1) {
        camino.push_back(nodos[indice].estado);
        indice = nodos[indice].padre;
    }
    std::reverse(camino.begin(), camino.end());
    return camino;
}

// Algoritmo A*: expande siempre el estado con menor f(n) = g(n) + h(n)
std::vector<Tablero> Solucionador::resolver(const Tablero& inicio, const Tablero& meta) {
    nodosExpandidos = 0;

    // Si la paridad no coincide, no hay solucion
    if (!inicio.tieneSolucion(meta)) return std::vector<Tablero>();

    std::vector<NodoBusqueda> nodos;                               // Todos los nodos generados
    std::priority_queue<ElementoCola, std::vector<ElementoCola>, ComparadorCola> abiertos; // Cola de prioridad
    std::unordered_map<int, int> mejorG;                           // Mejor g conocido por estado

    // Nodo raiz
    NodoBusqueda raiz;
    raiz.estado = inicio;
    raiz.g = 0;
    raiz.h = inicio.calcularDistanciaManhattan(meta);
    raiz.padre = -1;
    nodos.push_back(raiz);
    mejorG[codificarEstado(inicio)] = 0;
    abiertos.push({raiz.g + raiz.h, raiz.g, 0});

    while (!abiertos.empty()) {
        // sacar el estado con menor f(n)
        ElementoCola actual = abiertos.top();
        abiertos.pop();
        NodoBusqueda nodoActual = nodos[actual.indice];

        // Descartar entradas obsoletas (se encontro un camino mejor despues)
        if (nodoActual.g > mejorG[codificarEstado(nodoActual.estado)]) continue;

        // Si llegamos a la meta, reconstruimos la traza
        if (nodoActual.estado.esMeta(meta)) {
            return reconstruirCamino(nodos, actual.indice);
        }

        nodosExpandidos++;

        //generar sucesores (movimientos legales del espacio vacio)
        std::vector<Tablero> sucesores = nodoActual.estado.generarSucesores();
        for (size_t k = 0; k < sucesores.size(); k++) {
            int codigo = codificarEstado(sucesores[k]);
            int nuevoG = nodoActual.g + 1;

            // Solo se agrega si el estado es nuevo o se llego a el con menor costo
            std::unordered_map<int, int>::iterator it = mejorG.find(codigo);
            if (it != mejorG.end() && it->second <= nuevoG) continue;

            mejorG[codigo] = nuevoG;

            NodoBusqueda hijo;
            hijo.estado = sucesores[k];
            hijo.g = nuevoG;
            hijo.h = sucesores[k].calcularDistanciaManhattan(meta);
            hijo.padre = actual.indice;
            nodos.push_back(hijo);

            //Insertar en la cola usando f(n) como prioridad
            abiertos.push({hijo.g + hijo.h, hijo.g, (int)nodos.size() - 1});
        }
    }

    return std::vector<Tablero>(); // No se encontro solucion
}
