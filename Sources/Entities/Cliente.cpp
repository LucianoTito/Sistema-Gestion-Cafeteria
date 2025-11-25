#include <iostream>
#include <cstring>
#include <cstdio>
#include "../../Headers/Entities/Cliente.h"

#include "../../Headers/Utilidades/Validaciones.h"

using namespace std;

//Constructor

Cliente::Cliente(int id,
                 const char* nombre,
                 const char* apellido,
                 const char* telefono,
                 const char* mail,
                 bool eliminado,
                 int puntosFidelidad)
    : Persona(id, nombre, apellido, telefono, mail, eliminado)
{
    setPuntosFidelidad(puntosFidelidad);
}

//Getters ESPECÍFICOS de Cliente

int Cliente::getPuntosFidelidad() {
    return _puntosFidelidad;
}

// --- Setters ESPECÍFICOS de Cliente ---

void Cliente::setPuntosFidelidad(int puntos) {

    if (puntos >= 0 && puntos <= 5) {
        _puntosFidelidad = puntos;
    } else {
        cout << "Puntos de fidelidad invalidos. No pueden ser negativos. Se asignara 0." << endl;
        _puntosFidelidad = 0;
    }
}

//Cargar()
void Cliente::Cargar(int id) {

Persona::Cargar(id);


cout <<endl;
int puntaje = ingresarEntero("Por favor ingrese el puntaje de fidelidad de 0 a 5: ");
setPuntosFidelidad(puntaje);
}


//Mostrar

void Cliente::Mostrar() {
    cout << "--- DATOS DEL CLIENTE ---" << endl;

    Persona::Mostrar();
    cout << "Puntos Fidelidad: " << _puntosFidelidad << endl;
    cout << "-------------------------" << endl;
}
