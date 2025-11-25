#pragma once

class Persona {

protected://Se usa esto para que Cliente y Empleado puedan acceder.
    int _id;
    char _nombre [30];
    char _apellido [30];
    char _telefono [20];
    char _mail [40];
    bool _eliminado;

public:
    //Constructor
    Persona (int id = 0,
             const char* nombre = "Sin nombre",
             const char* apellido = "Sin apellido",
             const char* telefono = "Sin telefono",
             const char* mail = "Sin mail",
             bool eliminado = false);

    //Getters
    int getId();
    const char* getNombre();
    const char* getApellido();
    const char* getTelefono();
    const char* getMail();
    bool getEliminado();

    //Setters
    void setId(int id);
    void setNombre (const char* nombre);
    void setApellido (const char* apellido);
    void setTelefono (const char* telefono);
    void setMail(const char* mail);
    void setEliminado (bool eliminado);

    //Métodos
    void Mostrar();
    void Cargar(int id);
};
