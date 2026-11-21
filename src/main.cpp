#include "raylib.h"
#include "Menu.h"
#include "Tablero.h" 

void DibujarTablero(const Tablero& tablero, int offsetX, int offsetY) {
    int tamCelda = 100;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = tablero.getCelda(i, j);
            
            
            Rectangle rect = {(float)(offsetX + j * tamCelda), (float)(offsetY + i * tamCelda), (float)tamCelda, (float)tamCelda};
            DrawRectangleLinesEx(rect, 2, BLACK);
            
            
            if (num != 0) {
                const char* texto = TextFormat("%d", num);
                int anchoTexto = MeasureText(texto, 40);
                DrawText(texto, offsetX + j * tamCelda + (tamCelda - anchoTexto) / 2, 
                         offsetY + i * tamCelda + (tamCelda - 40) / 2, 40, BLACK);
            }
        }
    }
}

int main(){
    InitWindow(880, 600, "8-Puzzle");
    SetTargetFPS(60);
    
    Menu menu;
    Tablero tablero;
    tablero.inicializarAleatorio();


    int estadoActual = 0;

    while(!WindowShouldClose()){
        
        if(estadoActual == 0){
            int opcionElegida = menu.seleccion();
            if (opcionElegida != 0){
                estadoActual = opcionElegida; 
                menu.reiniciar(); 
                
                
                if(estadoActual == 2){
                    tablero.inicializarAleatorio();
                }
            }
        }
    
        else if(estadoActual == 2){
            
            if(IsKeyPressed(KEY_ESCAPE) || Menu::botonVolver()){
                estadoActual = 0;
            }

            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();
                int offsetX = 290, offsetY = 150;
                int tamCelda = 100;
                
                int col = (mouse.x - offsetX) / tamCelda;
                int fila = (mouse.y - offsetY) / tamCelda;
                
                
                if (fila >= 0 && fila < 3 && col >= 0 && col < 3) {
                    tablero.mover(fila, col);
                }
            }

            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();
                
                if (mouse.x >= 290 && mouse.x <= 590 && mouse.y >= 500 && mouse.y <= 540) {
                    tablero.inicializarAleatorio();
                }
            }
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

    
        if(estadoActual == 0){
            menu.dibujar();
        }
        
    
        else if(estadoActual == 1){
            DrawText("PANTALLA DE PUNTUACIONES", 200, 200, 30, BLACK);
            if(Menu::botonVolver()){
                estadoActual = 0; 
            }
        }
        
        
        else if(estadoActual == 2){
            DrawText("Modo Manual - Mueve las fichas con el ratón", 200, 50, 20, DARKGRAY);
            DrawText("Presiona ESC para volver al menú", 280, 80, 20, GRAY);
            
            
            DibujarTablero(tablero, 290, 150);
            
            
            DrawRectangle(290, 500, 300, 40, LIGHTGRAY);
            DrawText("Generar Nuevo Juego", 340, 510, 20, BLACK);
        }
        
        
        else if(estadoActual == 3){
            DrawText("MODO INTELIGENTE - A* (En construcción)", 200, 200, 30, BLACK);
            if(Menu::botonVolver()){
                estadoActual = 0; 
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
