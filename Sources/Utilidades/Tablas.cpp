#include <iostream>
#include <iomanip>
#include "../../Headers/Utilidades/Tablas.h"
#include "../../Headers/Utilidades/Estilos.h" // Aqui traemos los colores
#include "../../Headers/Utilidades/rlutil.h"

using namespace std;

// ==========================================
// FUNCIONES DE LINEAS
// ==========================================

void lineaDoble(int n) {
    rlutil::setColor(PaletaCafe::BASE);
    for (int i = 0; i < n; i++) cout << "=";
    restaurarColor();
    cout << endl;
}

void lineaSimple(int n) {
    rlutil::setColor(PaletaCafe::BASE);
    for (int i = 0; i < n; i++) cout << "-";
    restaurarColor();
    cout << endl;
}

// ==========================================
// FILAS ESPECIFICAS
// ==========================================

void imprimirFilaPedido(const char* id, const char* fecha, const char* idCli, const char* idEmp, const char* total) {
    const int wId = 8; const int wFecha = 12; const int wCli = 12; const int wEmp = 12; const int wTotal = 12;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wFecha) << fecha;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wCli) << idCli;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wEmp) << idEmp;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wTotal) << total;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaPago(const char* idPago, const char* idPedido, const char* fecha, const char* metodo, const char* monto) {
    const int wIdPago = 8; const int wIdPedido = 10; const int wFecha = 12; const int wMetodo = 16; const int wMonto = 12;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wIdPago) << idPago;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wIdPedido) << idPedido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wFecha) << fecha;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMetodo) << metodo;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wMonto) << monto;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaEmpleado(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail, const char* puesto) {
    const int wId = 6; const int wNombre = 15; const int wApellido = 15; const int wTel = 15; const int wMail = 35; const int wPuesto = 15;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNombre) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wApellido) << apellido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wTel) << telefono;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMail) << mail;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wPuesto) << puesto;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaProducto(const char* id, const char* nombre, const char* precio, const char* stock) {
    const int wId = 6; const int wNombre = 35; const int wPrecio = 15; const int wStock = 10;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNombre) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wPrecio) << precio;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wStock) << stock;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaCliente(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail) {
    const int wId = 6; const int wNom = 15; const int wApe = 15; const int wTel = 15; const int wMail = 25;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNom) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wApe) << apellido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wTel) << telefono;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMail) << mail;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaRecaudacion(const char* mes, const char* total) {
    const int wMes = 20; const int wTotal = 21;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wMes) << mes;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wTotal) << total;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaRankingProductos(const char* pos, const char* id, const char* nombre, const char* cantidad) {
    const int wPos = 5; const int wId = 8; const int wNom = 37; const int wCant = 10;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wPos) << pos;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNom) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wCant) << cantidad;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}

void imprimirFilaRankingEmpleados(const char* pos, const char* id, const char* apellido, const char* nombre, const char* cantidad) {
    const int wPos = 5; const int wId = 8; const int wApe = 20; const int wNom = 19; const int wCant = 10;
    rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wPos) << pos;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wId) << id;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wApe) << apellido;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << left << setw(wNom) << nombre;
    rlutil::setColor(PaletaCafe::BASE); cout << " | ";
    rlutil::setColor(PaletaCafe::ESPUMA); cout << right << setw(wCant) << cantidad;
    rlutil::setColor(PaletaCafe::BASE); cout << " ||";
    restaurarColor(); cout << endl;
}
