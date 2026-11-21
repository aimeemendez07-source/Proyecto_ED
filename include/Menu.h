//Menu
#ifndef MENU_H
#define MENU_H
#include "raylib.h"

class Menu{
    private:
        int opc;
        const Color colorfondo=RAYWHITE;

    public:
        Menu();
        void dibujar();
        int seleccion();
        void reiniciar();
        static bool botonVolver(); 
};

#endif