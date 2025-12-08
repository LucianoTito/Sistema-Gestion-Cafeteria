#include <iostream>
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"
#include "../../Headers/Utilidades/Estilos.h"

using namespace std;

//validacion para numeros enteros
int ingresarEntero(string mensaje) {

    int dato;

    while (true) {

        imprimirPrompt(mensaje);
        cin >> dato;

        if (cin.fail()) {

            cin.clear();              // Apaga el estado de error
            cin.ignore(1000, '\n');   // Limpio lo que quedó en el buffer
            imprimirMensajeError("Debe ingresar un numero entero.");
            continue;

        } else {

            cin.ignore(100, '\n');   // Limpio caracteres sobrantes

            if (dato < 0) {
                imprimirMensajeAdvertencia("El numero no puede ser negativo.");
                continue;
            } else {
                return dato;
            }
        }
    }
}


//validaciones para floats no negativos
float ingresarFloat(string mensaje) {

    float dato;

    while (true) {

        imprimirPrompt(mensaje);
        cin >> dato;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(100, '\n');
            imprimirMensajeError("Debe ingresar un numero decimal valido.");

        } else {

            cin.ignore(100, '\n');

            if (dato < 0) {
                imprimirMensajeAdvertencia("El valor no puede ser negativo.");
            } else {
                return dato;
            }
        }
    }
}


//Funcion cargar cadena
void cargarCadena (char *palabra, int tamano){

fflush(stdin); // Limpia buffer antes de leer carácter por carácter
    int i;
    for (i = 0; i < tamano; i++) { // Leemos hasta 49 para dejar espacio al '\0'
        palabra[i] = cin.get(); // Lee un carácter
        if (palabra[i] == '\n') { // Si es Enter, termina
            break;
        }
    }
    palabra[i] = '\0'; // Agrega el terminador nulo
    fflush(stdin); // Limpia buffer después

}


//Solicita una cadena obligatoria y muestra un mensaje de error si el usuario intenta dejarla vacía
void cargarCadenaObligatoria(const string& mensaje,
                             const string& mensajeError,
                             char* destino,
                             int tamano){

                             do {
                                imprimirPrompt(mensaje);
                                cargarCadena(destino, tamano);
                                if(destino[0] == '\0'){
                                    imprimirMensajeError(mensajeError);
                                }
                             } while(destino[0] == '\0');

                             }
