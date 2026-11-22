#include "ModoInteligente.h"
#include "raylib.h"
#include <cstdlib>

namespace {
    // Medidas de la fase de configuracion
    const int CELDA_CONFIG = 80;
    const int INICIO_X = 100;
    const int META_X = 540;
    const int TABLERO_Y = 110;

    // Medidas de la fase de solucion
    const int CELDA_SOLUCION = 90;
    const int SOLUCION_X = 305;
    const int SOLUCION_Y = 105;

    // Botones de configuracion
    const Rectangle BTN_INICIO_ALEATORIO = {100, 370, 240, 40};
    const Rectangle BTN_RESTABLECER_META = {540, 370, 240, 40};
    const Rectangle BTN_RESOLVER         = {320, 470, 240, 45};

    // Botones de solucion
    const Rectangle BTN_ANTERIOR  = {180, 430, 160, 40};
    const Rectangle BTN_SIGUIENTE = {540, 430, 160, 40};
    const Rectangle BTN_NUEVA     = {290, 485, 300, 40};

    // Indica si se hizo clic izquierdo dentro del rectangulo
    bool clicEn(Rectangle r) {
        return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), r);
    }

    // Dibuja un boton con texto centrado
    void dibujarBoton(Rectangle r, const char* texto) {
        DrawRectangleRounded(r, 0.2f, 10, PURPLE);
        int ancho = MeasureText(texto, 20);
        DrawText(texto, (int)(r.x + (r.width - ancho) / 2), (int)(r.y + 10), 20, BLACK);
    }

    // Dibuja un texto centrado horizontalmente en la ventana
    void dibujarTextoCentrado(const char* texto, int y, int tam, Color color) {
        int ancho = MeasureText(texto, tam);
        DrawText(texto, (GetScreenWidth() - ancho) / 2, y, tam, color);
    }
}

ModoInteligente::ModoInteligente() {
    pasoActual = 0;
    enSolucion = false;
    reiniciar();
}

// Meta estandar, inicio aleatorio y fase de configuracion
void ModoInteligente::reiniciar() {
    meta = Tablero();
    inicio = meta;
    mezclarTablero(inicio, 80);
    camino.clear();
    pasoActual = 0;
    enSolucion = false;
    mensaje = "Haz clic en las fichas para editar el inicio y la meta";
}

//  el resultado siempre es resoluble
void ModoInteligente::mezclarTablero(Tablero& tablero, int movimientos) {
    for (int i = 0; i < movimientos; i++) {
        std::vector<Tablero> sucesores = tablero.generarSucesores();
        tablero = sucesores[rand() % sucesores.size()];
    }
}

// Convierte el clic en fila/columna y mueve la ficha si es adyacente al espacio vacio
void ModoInteligente::procesarClicTablero(Tablero& tablero, int x, int y, int tamCelda) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
    Vector2 mouse = GetMousePosition();
    if (mouse.x < x || mouse.y < y) return;
    int col = (int)(mouse.x - x) / tamCelda;
    int fila = (int)(mouse.y - y) / tamCelda;
    if (fila >= 0 && fila < 3 && col >= 0 && col < 3) {
        tablero.mover(fila, col);
    }
}

// Ejecuta A* y cambia a la fase de solucion si existe una traza
void ModoInteligente::resolver() {
    if (inicio.esIgual(meta)) {
        mensaje = "El inicio y la meta son iguales";
        return;
    }
    if (!inicio.tieneSolucion(meta)) {
        mensaje = "Sin solucion: esa meta no se puede alcanzar desde ese inicio";
        return;
    }
    camino = solucionador.resolver(inicio, meta);
    if (camino.empty()) {
        mensaje = "No se encontro una solucion";
        return;
    }
    enSolucion = true;
    pasoActual = 0;
}

// Entrada de la fase de configuracion
void ModoInteligente::actualizarConfiguracion() {
    procesarClicTablero(inicio, INICIO_X, TABLERO_Y, CELDA_CONFIG);
    procesarClicTablero(meta, META_X, TABLERO_Y, CELDA_CONFIG);

    if (clicEn(BTN_INICIO_ALEATORIO)) {
        inicio = meta;
        mezclarTablero(inicio, 80);
        mensaje = "Nuevo inicio aleatorio generado";
    }
    if (clicEn(BTN_RESTABLECER_META)) {
        meta = Tablero();
        mensaje = "Meta restablecida al orden 1-8";
    }
    if (clicEn(BTN_RESOLVER)) {
        resolver();
    }
}

// Entrada de la fase de solucion
void ModoInteligente::actualizarSolucion() {
    int ultimoPaso = (int)camino.size() - 1;

    if (clicEn(BTN_ANTERIOR) && pasoActual > 0) {
        pasoActual--;
    }
    if (clicEn(BTN_SIGUIENTE) && pasoActual < ultimoPaso) {
        pasoActual++;
    }
    if (clicEn(BTN_NUEVA)) {
        enSolucion = false;
        mensaje = "Edita el inicio y la meta, o genera un inicio aleatorio";
        return;
    }
}

void ModoInteligente::actualizar() {
    if (enSolucion) actualizarSolucion();
    else actualizarConfiguracion();
}

// Dibuja un tablero con fichas rellenas; el espacio vacio queda gris
void ModoInteligente::dibujarTablero(const Tablero& tablero, int x, int y, int tamCelda) const {
    int tamFuente = tamCelda / 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = tablero.getCelda(i, j);
            Rectangle rect = {(float)(x + j * tamCelda), (float)(y + i * tamCelda), (float)tamCelda, (float)tamCelda};
            if (num != 0) {
                DrawRectangleRec(rect, SKYBLUE);
                const char* texto = TextFormat("%d", num);
                int ancho = MeasureText(texto, tamFuente);
                DrawText(texto, x + j * tamCelda + (tamCelda - ancho) / 2,
                         y + i * tamCelda + (tamCelda - tamFuente) / 2, tamFuente, BLACK);
            } else {
                DrawRectangleRec(rect, LIGHTGRAY);
            }
            DrawRectangleLinesEx(rect, 2, BLACK);
        }
    }
}

void ModoInteligente::dibujarConfiguracion() const {
    dibujarTextoCentrado("MODO INTELIGENTE - A*", 20, 30, BLACK);

    DrawText("Inicio", INICIO_X + 90, TABLERO_Y - 30, 22, DARKGRAY);
    DrawText("Meta", META_X + 95, TABLERO_Y - 30, 22, DARKGRAY);
    dibujarTablero(inicio, INICIO_X, TABLERO_Y, CELDA_CONFIG);
    dibujarTablero(meta, META_X, TABLERO_Y, CELDA_CONFIG);

    dibujarBoton(BTN_INICIO_ALEATORIO, "Inicio aleatorio");
    dibujarBoton(BTN_RESTABLECER_META, "Restablecer meta");
    dibujarBoton(BTN_RESOLVER, "Resolver con A*");

    dibujarTextoCentrado(mensaje.c_str(), 430, 20, RED);
}

void ModoInteligente::dibujarSolucion() const {
    int ultimoPaso = (int)camino.size() - 1;

    dibujarTextoCentrado("SOLUCION PASO A PASO", 20, 30, BLACK);
    dibujarTextoCentrado(TextFormat("Paso %d de %d", pasoActual, ultimoPaso), 70, 24, DARKGRAY);

    dibujarTablero(camino[pasoActual], SOLUCION_X, SOLUCION_Y, CELDA_SOLUCION);

    dibujarTextoCentrado(TextFormat("Movimientos: %d  |  Nodos expandidos: %d",
    ultimoPaso, solucionador.getNodosExpandidos()), 390, 20, DARKGRAY);

    dibujarBoton(BTN_ANTERIOR, "Anterior");
    dibujarBoton(BTN_AUTO, reproduccionAutomatica ? "Pausar" : "Auto");
    dibujarBoton(BTN_SIGUIENTE, "Siguiente");
    dibujarBoton(BTN_NUEVA, "Nueva configuracion");
}

void ModoInteligente::dibujar() const {
    if (enSolucion) dibujarSolucion();
    else dibujarConfiguracion();
}
