#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include "rlutil.h"

using namespace std;

namespace PaletaCafe {
    constexpr int BASE = rlutil::BROWN;
    constexpr int CREMA = rlutil::YELLOW;
    constexpr int ESPUMA = rlutil::WHITE;
    constexpr int HUMO = rlutil::GREY;
    constexpr int OK = rlutil::LIGHTGREEN;      // Verde: todo ok
    constexpr int ERROR = rlutil::LIGHTRED;     // Rojo: algo mal
    constexpr int ADVERTENCIA = rlutil::YELLOW; // Amarillo: cuidado
}

// Helpers de estilo
void restaurarColor();
void limpiarConsola();
void pausarConsola(const string& mensaje = "Presione ENTER para continuar...");
void imprimirTituloDecorado(const string& titulo, int ancho = 80);
void imprimirSubtituloDecorado(const string& subtitulo, int ancho = 80);
void imprimirMensajeOk(const string& mensaje);
void imprimirMensajeAdvertencia(const string& mensaje);
void imprimirMensajeError(const string& mensaje);
void imprimirPrompt(const string& prompt);
void imprimirBannerCafe();

// Funciones generales de linea
void lineaDoble(int n = 80); // Valor por defecto para facilitar uso
void lineaSimple(int n = 80);

// Filas genéricas (Las que me pasaste)
void imprimirFila5(const char* c1, const char* c2, const char* c3, const char* c4, const char* c5);
void imprimirFila4(const char* c1, const char* c2, const char* c3, const char* c4);
void imprimirFila2(const char* c1, const char* c2);

//Fila específica para listados de pedidos (ajustada para Fechas y Montos)
void imprimirFilaPedido(const char* id, const char* fecha, const char* idCli, const char* idEmp, const char* total);

//Fila específica para listados de pagos
void imprimirFilaPago(const char* idPago, const char* idPedido, const char* fecha, const char* metodo, const char* monto);

//Fila para empleados
void imprimirFilaEmpleado(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail, const char* puesto);


//Fila para productos
void imprimirFilaProducto(const char* id, const char* nombre, const char* precio, const char* stock);

//Fila para clientes
void imprimirFilaCliente(const char* id, const char* nombre, const char* apellido, const char* telefono, const char* mail);


// Filas para Reportes
void imprimirFilaRecaudacion(const char* mes, const char* total);
void imprimirFilaRankingProductos(const char* pos, const char* id, const char* nombre, const char* cantidad);
void imprimirFilaRankingEmpleados(const char* pos, const char* id, const char* apellido, const char* nombre, const char* cantidad);
