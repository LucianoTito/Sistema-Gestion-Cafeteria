#include<iostream>
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;


// Imprimo una línea doble usando '='.
//La uso para separar secciones importantes, como títulos de reportes.
void lineaDoble(int n) {
    for (int i = 0; i < n; i++) cout << "=";
    cout << endl;
}


// Imprimo una línea simple usando '-'.
void lineaSimple(int n) {
    for (int i = 0; i < n; i++) cout << "-";
    cout << endl;
}


// Esta funcion imprime una fila completa con 5 columnas.
// Mantengo los anchos definidos previamente para asegurar que
// todas las tablas del sistema tengan un formato uniforme.
//
// COLUMNAS (Estilo B)
//  - Col1: ancho 4
//  - Col2: ancho 4
//  - Col3: ancho 16
//  - Col4: ancho 16
//  - Col5: ancho 5
//
// Los valores llegan como cadenas const char*, porque así puedo usar sprintf()
// antes de llamar a esta función cuando necesito imprimir números.
void imprimirFila5(const char* c1,
                   const char* c2,
                   const char* c3,
                   const char* c4,
                   const char* c5) {

    cout << "|| "
         << left << setw(4)  << c1 << " || "
         << left << setw(4)  << c2 << " || "
         << left << setw(20) << c3 << " || "
         << left << setw(18) << c4 << " || "
         << left << setw(4)  << c5 << " ||"
         << endl;
}

void imprimirFila4(const char* c1, const char* c2, const char* c3, const char* c4) {

    const int a1 = 10;   // POS
    const int a2 = 10;   // ID
    const int a3 = 25;  // PRODUCTO
    const int a4 = 10;   // CANT.

    cout << "|| "
         << left << setw(a1) << c1 << " || "
         << left << setw(a2) << c2 << " || "
         << left << setw(a3) << c3 << " || "
         << left << setw(a4) << c4 << " ||"
         << endl;
}
