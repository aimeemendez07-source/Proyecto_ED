//Menu
#ifndef MENU_H
#define MENU_H
#include "raylib.h"

class Menu{
    private:
        int opc;
    public:
        Menu();
        void dibujar();
        int seleccion();
};

#endif
