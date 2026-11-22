#include "Menu.h"

Menu::Menu(){
    opc = 0;
}

void Menu::dibujar(){
    DrawText("8-PUZZLE", 300, 100, 40, BLACK);

    DrawRectangleRounded(Rectangle{ 230, 190, 340, 40 }, 0.4f, 10, PURPLE);
    DrawText("1. Ver puntuaciones", 250, 200, 25, BLACK);

    DrawRectangleRounded(Rectangle{ 230, 240, 340, 40 }, 0.4f, 10, PURPLE);
    DrawText("2. Modo Manual", 250, 250, 25, BLACK);

    DrawRectangleRounded(Rectangle{ 230, 290, 340, 40 }, 0.4f, 10, PURPLE);
    DrawText("3. Modo Inteligente", 250, 300, 25, BLACK);
}

int Menu::seleccion(){
    Vector2 mouse = GetMousePosition();
    if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(mouse.x >= 250 && mouse.x <= 550 && mouse.y >= 200 && mouse.y <= 230){
            opc = 1;
        }else if(mouse.x >= 250 && mouse.x <= 550 && mouse.y >= 250 && mouse.y <= 280){
            opc = 2;
        }else if(mouse.x >= 250 && mouse.x <= 550 && mouse.y >= 300 && mouse.y <= 330){
            opc = 3;
        }
    }
    return opc;
}

void Menu::reiniciar(){
    opc = 0;
}

bool Menu::botonVolver(){
    DrawRectangleRounded(Rectangle{ 20, 540, 60, 40 }, 0.2f, 10, LIGHTGRAY);
    DrawText("<-", 38, 550, 20, BLACK);
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mouse.x >= 20 && mouse.x <= 80 && mouse.y >= 540 && mouse.y <= 580) {
            return true; // Se hizo clic
        }
    }
    return false;
}