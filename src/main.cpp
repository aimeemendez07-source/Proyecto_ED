#include "raylib.h"
#include "Menu.h"
#include "Tablero.h"
#include "ModoInteligente.h"
#include "Puntajes.h"

void DibujarTablero(const Tablero& tablero, int offsetX, int offsetY) {
    int tamCelda = 100;
    int margen = 2;  //espacio entre las celdas
    int margenExterior = 6;
    
    //borde exterior
    Rectangle bordeRect = {(float)(offsetX - margenExterior), (float)(offsetY - margenExterior), (float)(tamCelda * 3 + margenExterior *2), (float)(tamCelda * 3 + margenExterior * 2)};
    DrawRectangleRounded(bordeRect, 0.1f, 10, DARKPURPLE);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = tablero.getCelda(i, j);
            
            Rectangle rect = {(float)(offsetX + j * tamCelda + margen), (float)(offsetY + i * tamCelda + margen), (float)(tamCelda - margen * 2), (float)(tamCelda - margen * 2)};
            
            if (num != 0) {
                DrawRectangleRounded(rect, 0.2f, 10, PURPLE);
                const char* texto = TextFormat("%d", num);
                int anchoTexto = MeasureText(texto, 40);
                DrawText(texto, rect.x + (rect.width - anchoTexto) / 2, rect.y + (rect.height - 40) / 2, 40, BLACK);
            }
        }
    }
}

int main(){
    InitWindow(880, 600, "8-Puzzle");
    SetTargetFPS(60);
    
    Menu menu;
    Tablero tablero;
    ModoInteligente modoInteligente;
    tablero.inicializarAleatorio();

    int estadoActual = 0;  //variable para saber la pantalla
    bool juegoTerminado = false; 

    bool pidiendoAlias = false;
    std::string aliasJugador = "";

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
                
                if(estadoActual == 2){
                    tablero.inicializarAleatorio();
                }

                if(estadoActual == 3){
                    modoInteligente.reiniciar();
                }
            }
        }
        //puntuaciones
        else if(estadoActual == 1){
            DrawText("MEJORES PUNTAJES", 300, 50, 30, BLACK);
            std::vector<RegistroPuntaje> lista = Puntajes::mejoresPuntajes();
            int y =120;

            for(int i = 0; i < lista.size() && i < 10; i++){
                std::string texto = std::to_string(i + 1) + ". " + lista[i].alias +  " - " + std::to_string(lista[i].puntaje) + " pts - " + lista[i].fecha;
                DrawText(texto.c_str(), 200, y, 25, BLACK);
                y += 35;
            }

            if(Menu::botonVolver()){
                estadoActual = 0; 
            }
        }
        //modo manual
        else if(estadoActual == 2){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();
                
                if (mouse.x >= 290 && mouse.x <= 590 && mouse.y >= 500 && mouse.y <= 540) {
                    tablero.inicializarAleatorio();
                    juegoTerminado = false;
                }
                else if (!juegoTerminado){ 
                    int offsetX = 290, offsetY = 150;
                    int tamCelda = 100;
                
                    int col = (mouse.x - offsetX) / tamCelda;
                    int fila = (mouse.y - offsetY) / tamCelda;
                
                    if (fila >= 0 && fila < 3 && col >= 0 && col < 3) {
                        if(tablero.mover(fila, col)){
                            Tablero meta;
                            if(tablero.esMeta(meta)){
                                juegoTerminado = true;
                            }
                        }
                    }
                }
            }

            if(IsKeyPressed(KEY_ESCAPE) || Menu::botonVolver()){
                estadoActual = 0;
            }

            DrawText("Modo Manual - Mueve las fichas con el ratón", 200, 50, 20, DARKGRAY);
            DibujarTablero(tablero, 290, 150);

            //mensaje de victoria
            if(juegoTerminado){
                DrawRectangle(0, 0, 880, 600, Fade(BLACK, 0.6f));

                if(!pidiendoAlias){
                    DrawText("Felicidades Pequeño Estupido", 250, 300, 30, GOLD);
                    DrawText("Presiona ENTER para guardar tu record", 230, 350, 20, WHITE);

                    if(IsKeyPressed(KEY_ENTER)){
                        pidiendoAlias = true;
                    }
                }else{
                    DrawText("Ingresa tu alias y presiona ENTER", 200, 200, 25, WHITE);
                    DrawText(aliasJugador.c_str(), 300, 260, 40, GOLD);

                    //captura del alias
                    int key = GetCharPressed();
                    while(key > 0){
                        if((key >=32) && (key <=125) && (aliasJugador.length() < 15)){
                            aliasJugador += (char)key;
                        }
                        key = GetCharPressed();
                    }
                    if(IsKeyPressed(KEY_BACKSPACE) && !aliasJugador.empty()){
                        aliasJugador.pop_back();
                    }
                    if(IsKeyPressed(KEY_ENTER) && !aliasJugador.empty()){
                        Puntajes::guardar(aliasJugador, 100); //100 pts por ganar
                        pidiendoAlias = false;
                        juegoTerminado = false; //quitar el mensaje
                        aliasJugador = "";
                        estadoActual = 1; //mandar a la pantalla de puntuaciones
                    }
                }
                
            }
            
            DrawRectangle(290, 500, 300, 40, LIGHTGRAY);
            DrawText("Generar Nuevo Juego", 340, 510, 20, BLACK);
        }       
        //modo inteligente
        else if(estadoActual == 3){
            modoInteligente.actualizar();   // procesa clics (tableros y botones)
            modoInteligente.dibujar();      // dibuja la pantalla actual
            if(Menu::botonVolver()){
                estadoActual = 0; 
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
