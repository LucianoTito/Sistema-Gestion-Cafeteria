#pragma once

#include <string>

#include "../Entities/Pedido.h"


class ArchivoPedido{

private:
    std::string _nombreArchivo;

public:

    ArchivoPedido(std::string nombreArchivo = "Pedidos.dat");

    //Métodos CRUD

    //Crear registro
    bool grabarRegistro(Pedido reg);

    //Leer
    Pedido leerRegistro(int posicion);

    //Contar
    int contarRegistros();

    //Buscar
    int buscarRegistro(int idPedido);

    //Update
    bool modificarRegistro(Pedido reg, int posicion);

    //Listar
    void listar();




};
