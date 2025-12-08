#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>

#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Persistence/ArchivoPagos.h"
// Includes visuales
#include "../../Headers/Utilidades/Tablas.h"
#include "../../Headers/Utilidades/Estilos.h"
#include "../../Headers/Utilidades/rlutil.h"

using namespace std;

// Constructor
ArchivoPagos::ArchivoPagos(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

// Grabar registro
bool ArchivoPagos::grabarRegistro(Pagos reg) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if (pArchivo == nullptr) {
        return false;
    }
    bool escribio = fwrite(&reg, sizeof(Pagos), 1, pArchivo);
    fclose(pArchivo);
    return escribio;
}

// Contar registros
int ArchivoPagos::contarRegistros() {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return 0;
    }
    fseek(pArchivo, 0L, SEEK_END);
    long tamanioEnbytes = ftell(pArchivo);
    fclose(pArchivo);
    return (int)(tamanioEnbytes / sizeof(Pagos));
}

// Leer registro
Pagos ArchivoPagos::leerRegistro(int posicion) {
    Pagos reg;
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return reg;
    }
    fseek(pArchivo, posicion * sizeof(Pagos), SEEK_SET);
    fread(&reg, sizeof(Pagos), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

// Buscar registro
int ArchivoPagos::buscarRegistro(int idPago) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return -1;
    }
    Pagos regLeido;
    int posicionActual = 0;
    while (fread(&regLeido, sizeof(Pagos), 1, pArchivo) == 1) {
        if (regLeido.getIdPago() == idPago) {
            fclose(pArchivo);
            return posicionActual;
        }
        posicionActual++;
    }
    fclose(pArchivo);
    return -1;
}

// Modificar Registro
bool ArchivoPagos::modificarRegistro(Pagos reg, int posicion) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if (pArchivo == nullptr) {
        return false;
    }
    fseek(pArchivo, posicion * sizeof(Pagos), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Pagos), 1, pArchivo);
    fclose(pArchivo);
    return escribio;
}

// Listar (AHORA CON ESTILO VISUAL)
void ArchivoPagos::listar() {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        imprimirMensajeError("No se pudo abrir el archivo de pagos.");
        return;
    }

    // Usamos el ancho de 78/80 que definimos en Tablas.cpp para pagos
    const int ANCHO_PAGOS = 80;

    imprimirTituloDecorado("LISTADO GENERAL DE PAGOS", ANCHO_PAGOS);

    // Encabezado de tabla
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_PAGOS);
    imprimirFilaPago("ID", "ID PED", "FECHA", "METODO", "MONTO");
    lineaSimple(ANCHO_PAGOS);
    restaurarColor();

    Pagos reg;
    while (fread(&reg, sizeof(Pagos), 1, pArchivo) == 1) {
        // Conversión de datos a string para la tabla visual
        char sId[10], sIdPed[10], sFecha[15], sMetodo[20], sMonto[20];

        sprintf(sId, "%d", reg.getIdPago());
        sprintf(sIdPed, "%d", reg.getIdPedido());

        Fecha f = reg.getFechaPago();
        sprintf(sFecha, "%02d/%02d/%d", f.getDia(), f.getMes(), f.getAnio());

        string metStr;
        switch(reg.getMetodoPago()){
            case 1: metStr = "Efectivo"; break;
            case 2: metStr = "Tarjeta"; break;
            case 3: metStr = "Transf."; break;
            default: metStr = "Otro"; break;
        }
        sprintf(sMetodo, "%s", metStr.c_str());
        sprintf(sMonto, "$ %.2f", reg.getMontoPagado());

        // Llamada a la funcion visual
        imprimirFilaPago(sId, sIdPed, sFecha, sMetodo, sMonto);
    }

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_PAGOS);
    restaurarColor();

    fclose(pArchivo);
}
