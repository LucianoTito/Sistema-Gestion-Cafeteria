#pragma once

#include <string>

#include "../Entities/Empleado.h"


class ArchivoEmpleado {

private:

    std::string _nombreArchivo;

public:
    //Constructor

    ArchivoEmpleado(std::string nombreArchivo = "Empleados.dat");

    //Métodos CRUD

    //Grabar
    bool grabarRegistro(Empleado reg);

    //Leer
    Empleado leerRegistro (int posicion);

    //Contar registro
    int contarRegistros();

    //Buscar registro:
    int buscarRegistro(int idEmpleado);

    //Update
    bool modificarRegistro(Empleado reg, int posicion);

    //Listar
    void listar();
    void listarEliminados();
    bool hayEmpleadosConEstadoEliminado(bool eliminado);
    int leerRegistros(Empleado registros[], int cantidadMaxima);

};
