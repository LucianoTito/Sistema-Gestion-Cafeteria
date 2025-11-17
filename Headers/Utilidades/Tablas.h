#pragma once

#include <iostream>
#include <iomanip>

// Imprime una línea doble con '='
void lineaDoble(int n);

// Imprime una línea simple con '-'
void lineaSimple(int n);

// Tabla básica de 2 columnas (por ejemplo MES / RECAUDACION)
void imprimirFila2(const char* c1, const char* c2);

// Tabla de 4 columnas (POS / ID / PRODUCTO / CANT)
void imprimirFila4(const char* c1, const char* c2, const char* c3, const char* c4);




// Tabla de 5 columnas (POS / ID / APELLIDO / NOMBRE / OTRO)
void imprimirFila5(const char* c1,
                   const char* c2,
                   const char* c3,
                   const char* c4,
                   const char* c5);


