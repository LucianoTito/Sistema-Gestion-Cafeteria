#pragma once
#include <string>
#include"../Entities/Pagos.h"


class ArchivoPagos{

private:
    std::string _nombreArchivo;

public:

    //Constructor

ArchivoPagos(std::string nombreArchivo = "Pagos.dat");

//Métodos

//Crear registro
bool grabarRegistro(Pagos reg);

//Leer registro
Pagos leerRegistro (int posicion);

//Numero total de registros
int contarRegistros();

//Buscar la posicion de un registro usando su ID
int buscarRegistro(int idPago);

//Modificar registro
bool modificarRegistro (Pagos reg, int posicion);

//Listar
void listar ();

};
