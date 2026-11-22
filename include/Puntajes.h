#ifndef PUNTAJES_H
#define PUNTAJES_H

#include <string>
#include <vector>

struct RegistroPuntaje{
    std::string alias;
    int puntaje;
    std::string fecha;
};

class Puntajes{
public:
    static void guardar(const std::string& alias, int puntaje);
    static std::vector<RegistroPuntaje> mejoresPuntajes();
};

#endif
