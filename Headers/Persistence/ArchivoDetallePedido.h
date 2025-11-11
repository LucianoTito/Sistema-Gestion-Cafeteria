#pragma once
#include <string>
#include "../Entities/DetallePedido.h"

class ArchivoDetallePedido{

private:
    std::string _nombreArchivo;

public:

    //Constructor

    ArchivoDetallePedido(std::string nombreArchivo = "DetallesPedidos.dat");

    //Métodos

    //Crear
    bool grabarRegistro(DetallePedido reg);

    //Leer por posición
    DetallePedido leerRegistro(int posicion);

    //Numero total de registros
    int contarRegistros();

    //Buscar la posición de un registro
    int buscarRegistro(int idDetallePedido);

    //Sobreescribir un registro
    bool modificarRegistro (DetallePedido reg, int posicion);

    //Listar
    void listar();

};
