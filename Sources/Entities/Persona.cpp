#include <iostream>
#include <cstring>
#include <cstdio>
//#include "Persona.h"

#include "../../Headers/Entities/Persona.h"


using namespace std;

// Constructor
Persona::Persona(int id,
                 const char* nombre,
                 const char* apellido,
                 bool eliminado) {
    setId(id);
    setNombre(nombre);
    setApellido(apellido);
    setEliminado(eliminado);
}

// Getters
int Persona::getId() { return _id; }
const char* Persona::getNombre() { return _nombre; }
const char* Persona::getApellido() { return _apellido; }
bool Persona::getEliminado() { return _eliminado; }

// Setters
void Persona::setId(int id) {
    if (id >= 0) {
        _id = id;
    } else {
        cout << "ID incorrecto. Debe ser igual o mayor a 0. Se asignar 0 por defecto." << endl;
        _id = 0;
    }
}
void Persona::setNombre(const char* nombre) {
    if (nombre != nullptr && nombre[0] != '\0') {
        if (strlen(nombre) < 30) {
            strcpy(_nombre, nombre);
        } else {
            cout << "Nombre demasiado largo. Se cortara en 29 caracteres." << endl;
            strncpy(_nombre, nombre, 29);
            _nombre[29] = '\0';
        }
    } else {
        cout << "Nombre invalido. Se asignara 'Sin Nombre'." << endl;
        strcpy(_nombre, "Sin Nombre");
    }
}


void Persona::setApellido(const char* apellido) {
    if (apellido != nullptr && apellido[0] != '\0') {
        if (strlen(apellido) < 30) {
            strcpy(_apellido, apellido);

        } else {
             cout << "Apellido demasiado largo. Se cortara en 29 caracteres." << endl;
             strncpy(_apellido, apellido, 29);
        }
    } else {
        cout << "Apellido inválido. Se asignara 'Sin Apellido'." << endl;
        strcpy(_apellido, "Sin Apellido");
    }
}


void Persona::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

// Método cargar
void Persona::Cargar(int id) {

    char nombreTemporal[30];
    char apellidoTemporal[30];


    setId(id);
    cout << "ID de Persona asignado: "<< id <<endl;

    cout << "Ingrese nombre: ";

    fflush(stdin);
    int i;
    for (i = 0; i < 29; i++) {
        nombreTemporal[i] = cin.get();

        if (nombreTemporal[i] == '\n') {
            break;
        }
    }
    nombreTemporal[i] = '\0';
    fflush(stdin);
    setNombre(nombreTemporal);

    cout << "Ingrese apellido: ";

    fflush(stdin);
    int j;
    for (j = 0; j < 29; j++) {
        apellidoTemporal[j] = cin.get();

        if (apellidoTemporal[j] == '\n') {
            break; // Termina si presiona Enter
        }
    }
    apellidoTemporal[j] = '\0';
    fflush(stdin);
    setApellido(apellidoTemporal);

    _eliminado = false;
    cout << "Persona cargada correctamente." << endl;
}

// Método Mostrar (Perfecto)
void Persona::Mostrar() {
    cout << "-----------------------------" << endl;
    cout << "ID Persona: " << _id << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "-----------------------------" << endl;
}
