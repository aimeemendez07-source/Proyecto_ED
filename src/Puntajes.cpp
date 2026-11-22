#include <Puntajes.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>

//fecha actual
std::string fechaActual(){
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return std::to_string(1 + ltm->tm_mday) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(1900 + ltm->tm_year);
}

void Puntajes::guardar(const std::string& alias, int puntaje){
    std::ofstream archivo("../Puntajes.txt", std::ios::app);
    if(archivo.is_open()){
        archivo << alias << ", " << puntaje << ", " << fechaActual() << "\n";
        archivo.close();
    }
}

std::vector<RegistroPuntaje> Puntajes::mejoresPuntajes(){
    std::vector<RegistroPuntaje> lista;
    std::ifstream archivo("../Puntajes.txt");
    std::string linea;

    if(archivo.is_open()){
        while(std::getline(archivo, linea)){
            size_t pos1 = linea.find(',');
            size_t pos2 = linea.find(',', pos1 + 1);

            if(pos1 != std::string::npos && pos2 != std::string::npos){
                RegistroPuntaje reg;
                reg.alias = linea.substr(0, pos1);
                reg.puntaje = std::stoi(linea.substr(pos1 + 1, pos2 - pos1 - 1));
                reg.fecha = linea.substr(pos2 + 1);
                lista.push_back(reg);
            }
        }
        archivo.close();
    }

    //orden de mayor a menor
    std::sort(lista.begin(), lista.end(), [](const RegistroPuntaje& a, const RegistroPuntaje& b){return a.puntaje > b.puntaje;});

    return lista;
}
