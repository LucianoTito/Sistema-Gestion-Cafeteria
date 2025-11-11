#include <iostream>

#include "../../Headers/Entities/Fecha.h"

using namespace std;

//Constructor
Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
}

//Getters
int Fecha::getDia() {
    return _dia;
}
int Fecha::getMes() {
    return _mes;
}
int Fecha::getAnio() {
    return _anio;
}

//Setters
void Fecha::setDia(int dia) {
    if (dia > 0 && dia < 32) {
        _dia = dia;
    } else {
        cout << "Dato incorrecto. El numero de día debe ser entre 1 y 31. Se asignara 1 por defecto." << endl;
        _dia = 1;
    }
}
void Fecha::setMes(int mes) {
    if (mes > 0 && mes < 13) {
        _mes = mes;
    } else {
        cout << "Dato incorrecto. El numero de mes  debe ser entre 1 y 12. Se asignara 1 por defecto." << endl;
        _mes = 1; // Asignamos un valor seguro por defecto
    }
}
void Fecha::setAnio(int anio) {

    if (anio >= 2025 && anio <= 2050) {
        _anio = anio;
    } else {
        cout << "Año fuera del rango valido (2025 - 2050). Se asignara 2025 por defecto." << endl;
        _anio = 2025; // Asignamos un valor seguro por defecto
    }
}

// Cargar() se encarga de pedir los datos al usuario por consola
void Fecha::Cargar() {
    int d, m, a; // Variables temporales

    cout << "DIA: ";
    cin >> d;
    setDia(d);

    cout << "MES: ";
    cin >> m;
    setMes(m);

    cout << "ANIO: ";
    cin >> a;
    setAnio(a);
}

// Mostrar() se encarga de imprimir los datos en la consola
void Fecha::Mostrar() {
    cout << _dia << "/" << _mes << "/" << _anio << endl;
}

/*Sobrecarga de operadores: Estas funciones permiten comparar objetos Fecha de manera
natural usando los operadores relacionales (<, >, <=, >=, ==, !=).
Esto hace posible filtrar o ordenar fechas, como en el
reporte de productos vendidos por período.
  */

// Operador de igualdad
bool Fecha::operator==(const Fecha& f) const {
    return _dia == f._dia && _mes == f._mes && _anio == f._anio;
}

// Operador de desigualdad
bool Fecha::operator!=(const Fecha& f) const {
    return !(*this == f);
}

// Operador menor
bool Fecha::operator<(const Fecha& f) const {
    if (_anio != f._anio) return _anio < f._anio;
    if (_mes  != f._mes)  return _mes  < f._mes;
    return _dia < f._dia;
}

// Operador mayor
bool Fecha::operator>(const Fecha& f) const {
    return f < *this;
}

// Operador menor o igual
bool Fecha::operator<=(const Fecha& f) const {
    return !(*this > f);
}

// Operador mayor o igual
bool Fecha::operator>=(const Fecha& f) const {
    return !(*this < f);
}


