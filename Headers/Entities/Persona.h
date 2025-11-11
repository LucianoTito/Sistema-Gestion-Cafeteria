#pragma once

class Persona {

protected://Se usa esto para que Cliente y Empleado puedan acceder.
    int _id;
    char _nombre [30];
    char _apellido [30];
    bool _eliminado;

public:
    //Constructor
    Persona (int id = 0,
             const char* nombre = "Sin nombre",
             const char* apellido = "Sin apellido",
             bool eliminado = false);

    //Getters
    int getId();
    const char* getNombre();
    const char* getApellido();
    bool getEliminado();

    //Setters
    void setId(int id);
    void setNombre (const char* nombre);
    void setApellido (const char* apellido);
    void setEliminado (bool eliminado);

    //Métodos
    void Mostrar();
    void Cargar(int id);
};
