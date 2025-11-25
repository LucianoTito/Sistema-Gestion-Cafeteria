#pragma once
#include "Persona.h"


class Cliente : public Persona {

private:

    int _puntosFidelidad;

public:
    // Constructor

    Cliente(int id = 0,
            const char* nombre = "Sin nombre",
            const char* apellido = "Sin apellido",
            const char* telefono = "Sin numero",
            const char* mail = "Sin mail",
            bool eliminado = false,
            int puntosFidelidad = 0);

    // Getters
    int getPuntosFidelidad();

    // Setters
    void setPuntosFidelidad(int puntos);

    // Métodos
    void Mostrar();
    void Cargar(int id);
};
