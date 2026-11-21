#include "raylib.h"
#include "Menu.h"

int main(){
    InitWindow(880, 600, "8-Puzzle");
    SetTargetFPS(60);
    Menu menu;

    //variable para saber en q pantalla se esta
    int estadoActual = 0;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //menu
        if(estadoActual == 0){
            menu.dibujar();
            int opcionElegida = menu.seleccion();
            if (opcionElegida != 0){
                estadoActual = opcionElegida; 
                menu.reiniciar();
            }
        }
        //puntuaciones
        else if(estadoActual == 1){
            DrawText("PANTALLA DE PUNTUACIONES", 200, 200, 30, BLACK);
            if(Menu::botonVolver()){
                estadoActual = 0; // Volver al menú
            }
        }
        //modo manual
        else if(estadoActual == 2){
            DrawText("MODO MANUAL - JUGANDO", 200, 200, 30, BLACK);
            if(Menu::botonVolver()){
                estadoActual = 0; // Volver al menú
            }
        }
        //modo inteligente
        else if(estadoActual == 3){
            DrawText("MODO INTELIGENTE - A*", 200, 200, 30, BLACK);
            if(Menu::botonVolver()){
                estadoActual = 0; // Volver al menú
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
