#include "raylib.h"

int main() {
    // Inicializa la ventana
    InitWindow(800, 600, "Prueba de Raylib - 8 Puzzle");

    // Bucle principal del juego
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("¡Raylib esta funcionando correctamente!", 150, 280, 20, DARKGRAY);
        EndDrawing();
    }

    // Cierra la ventana
    CloseWindow();
    return 0;
}