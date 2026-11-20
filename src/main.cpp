#include "raylib.h"
#include "Menu.h"

int main(){
    InitWindow(880, 600, "8-Puzzle");
    SetTargetFPS(60);
    Menu menu;

    while(!WindowShouldClose()){
        int opc = menu.seleccion();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        menu.dibujar();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
