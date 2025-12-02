#include <iostream>
#include <cstdlib>

#include "../../Headers/UI/menuPrincipal.h"
#include "../../Headers/UI/menuGestionProductos.h"
#include "../../Headers/UI/menuGestionClientes.h"
#include "../../Headers/UI/menuEmpleados.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/UI/menuPedidos.h"
#include "../../Headers/UI/reportes.h"
#include "../../Headers/UI/configuraciones.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// Definimos un ancho estándar para que el menú se vea centrado y robusto
const int ANCHO_MENU_PPAL = 60;

void menuPrincipal() {

    int opcion;

    while (true) {
        system("cls");

        // --- ENCABEZADO ---
        lineaDoble(ANCHO_MENU_PPAL);
        // Centrado manual aproximado para ancho 60
        cout << "          SISTEMA DE GESTION - BASTI CAFE" << endl;
        lineaDoble(ANCHO_MENU_PPAL);
        cout << endl;

        // --- MODULOS OPERATIVOS ---
        cout << "   1.   GESTION DE PRODUCTOS" << endl;
        cout << endl;
        cout << "   2.   GESTION DE CLIENTES" << endl;
        cout << endl;
        cout << "   3.   GESTION DE EMPLEADOS" << endl;
        cout << endl;
        cout << "   4.   GESTION DE PEDIDOS" << endl;
        cout << endl;

        // --- MODULOS ADMINISTRATIVOS ---
        lineaSimple(ANCHO_MENU_PPAL);
        cout << endl;
        cout << "   5.   REPORTES Y ESTADISTICAS" << endl;
        cout << endl;
        cout << "   6.   CONFIGURACIONES Y RESPALDO" << endl;
        cout << endl;
        lineaSimple(ANCHO_MENU_PPAL);

        // --- SALIDA ---
        cout << "   0.   SALIR DEL SISTEMA" << endl;
        lineaDoble(ANCHO_MENU_PPAL);



        // 2. El contenido (Texto centrado)
        cout << "             SELECCIONE UNA OPCION" << endl;
        // 3. Pan de abajo
        lineaDoble(ANCHO_MENU_PPAL);

        // El input se pide justo debajo del sándwich
        // CORRECCION AQUI: Primero imprimimos el prompt ">>>" dentro de ingresarEntero
        opcion = ingresarEntero("  Opcion  >>> ");


        system("cls");

        bool mostrarPausa = false;

        switch (opcion) {
            case 1:
                menuProductos();
                break;
            case 2:
                menuClientes();
                break;
            case 3:
                menuEmpleados();
                break;
            case 4:
                menuPedidos();
                break;
            case 5:
                menuReportes();
                break;
            case 6:
                menuConfiguraciones();
                break;
            case 0:
                lineaDoble(ANCHO_MENU_PPAL);
                cout << "   Cerrando el sistema... Hasta luego!" << endl;
                lineaDoble(ANCHO_MENU_PPAL);
                return;
            default:
                cout << ">>> Opcion incorrecta. Intente nuevamente." << endl;
                mostrarPausa = true;
                break;
        }

        if (mostrarPausa) {
            system("pause");
        }
    }
}
