#pragma once
#include "Persona.h"


class Cliente : public Persona {

private:
    char _telefono[20];
    int _puntosFidelidad;

public:
    // Constructor

    Cliente(int id = 0,
            const char* nombre = "Sin nombre",
            const char* apellido = "Sin apellido",
            bool eliminado = false,
            const char* telefono = "Sin numero",
            int puntosFidelidad = 0);

    // Getters
    const char* getTelefono();
    int getPuntosFidelidad();

    // Setters
    void setTelefono(const char* telefono);
    void setPuntosFidelidad(int puntos);

    // Métodos
    void Mostrar();
    void Cargar(int id);
};
