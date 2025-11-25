#pragma once
#include <string>


//Validacion para que sea un número no negativo
int ingresarEntero(std::string mensaje);


//Pide un float y valida que no sea negativo
float ingresarFloat(std::string mensaje);


void cargarCadena(char *palabra, int tamano);


//Carga una cadena obligatoria mostrando un mensaje y un aviso de error si se deja vacío
void cargarCadenaObligatoria(const std::string& mensaje,
                             const std::string& mensajeError,
                             char* destino,
                             int tamano);
