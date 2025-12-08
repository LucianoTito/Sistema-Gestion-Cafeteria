#pragma once
#include <string>
#include "../../Headers/Entities/Pagos.h"

class ArchivoPagos {
private:
    std::string _nombreArchivo;

public:
    // Constructor
    ArchivoPagos(std::string nombreArchivo = "Pagos.dat");

    // Métodos
    bool grabarRegistro(Pagos reg);
    Pagos leerRegistro(int posicion);
    int contarRegistros();
    int buscarRegistro(int idPago);
    bool modificarRegistro(Pagos reg, int posicion);
    void listar();
};
