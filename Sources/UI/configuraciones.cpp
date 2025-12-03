#include <iostream>
#include <cstdlib>
#include <cstring>

#include "../../Headers/UI/configuraciones.h"
#include "../../Headers/Utilidades/GestorArchivos.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

// Prototipos locales para simplificar la logica de los menús
void realizarBackupArchivo(const char* nombreReal, const char* nombreBkp);
void restaurarBackupArchivo(const char* nombreBkp, const char* nombreReal);
void procesarExportacion(bool exito, const char* nombreArchivo);

// Menu principal de configuraciones
void menuConfiguraciones() {
    int opcion;
    while(true){
        limpiarConsola();
        imprimirTituloDecorado("CONFIGURACIONES DEL SISTEMA", 50);
        rlutil::setColor(PaletaCafe::CREMA);

        cout << "1. REALIZAR COPIA DE SEGURIDAD (.BKP)" << endl;
        cout << "2. RESTAURAR COPIA DE SEGURIDAD (.BKP)" << endl;
        cout << "3. EXPORTAR DATOS A EXCEL (CSV)" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(50);
        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(50);
        restaurarColor();

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        limpiarConsola();

        switch(opcion){
            case 1: backupMenu(); break;
            case 2: restaurarCopiaSeguridad(); break;
            case 3: exportarDatosCSV(); break;
            case 0: return;
            default: imprimirMensajeError("Opcion incorrecta."); break;
        }
        system("pause");
    }
}

// Submenu para crear backups
void backupMenu() {
    while (true) {
        limpiarConsola();
        imprimirTituloDecorado("CREAR COPIAS DE SEGURIDAD", 60);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. Clientes" << endl;
        cout << "2. Productos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Pedidos" << endl;
        cout << "5. Detalles" << endl;
        cout << "6. Pagos" << endl;
        cout << "7. RESPALDAR TODO" << endl;
        cout << "0. Volver" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(60);
        restaurarColor();

        int opc = ingresarEntero("Opcion: ");
        if (opc == 0) return;

        // Llamamos al helper con el nombre del archivo original y el nombre que tendra el backup
        switch (opc) {
            case 1: realizarBackupArchivo("Clientes.dat", "Clientes.bkp"); break;
            case 2: realizarBackupArchivo("Productos.dat", "Productos.bkp"); break;
            case 3: realizarBackupArchivo("Empleados.dat", "Empleados.bkp"); break;
            case 4: realizarBackupArchivo("Pedidos.dat", "Pedidos.bkp"); break;
            case 5: realizarBackupArchivo("DetallesPedidos.dat", "DetallesPedidos.bkp"); break;
            case 6: realizarBackupArchivo("Pagos.dat", "Pagos.bkp"); break;
            case 7:
                // Respaldo masivo: llamamos a la funcion para cada archivo
                realizarBackupArchivo("Clientes.dat", "Clientes.bkp");
                realizarBackupArchivo("Productos.dat", "Productos.bkp");
                realizarBackupArchivo("Empleados.dat", "Empleados.bkp");
                realizarBackupArchivo("Pedidos.dat", "Pedidos.bkp");
                realizarBackupArchivo("DetallesPedidos.dat", "DetallesPedidos.bkp");
                realizarBackupArchivo("Pagos.dat", "Pagos.bkp");
                imprimirMensajeOk(">>> BACKUP COMPLETO FINALIZADO.");
                break;
            default: imprimirMensajeError("Opcion invalida."); break;
        }
        pausarConsola();
    }
}

// Submenu para restaurar datos (Sobreescribe archivos .dat)
void restaurarCopiaSeguridad(){
    while(true) {
        limpiarConsola();
        imprimirTituloDecorado("RESTAURAR DESDE BACKUP", 60);
        rlutil::setColor(PaletaCafe::CREMA);

        cout << "1. Clientes" << endl;
        cout << "2. Productos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Pedidos" << endl;
        cout << "5. Detalles" << endl;
        cout << "6. Pagos" << endl;
        cout << "7. RESTAURAR TODO" << endl;
        cout << "0. Volver" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(60);
        restaurarColor();

        int opc = ingresarEntero("Opcion: ");
        if(opc == 0) return;

        char conf;
        imprimirMensajeAdvertencia("CUIDADO: Esto sobreescribira los datos actuales con la copia.");
        imprimirPrompt("Continuar? (S/N): ");
        cin >> conf;
        if(conf != 'S' && conf != 's') continue;

        switch (opc){
            // Notese que aqui el origen es .bkp y el destino es .dat (al reves que en el backup)
            case 1: restaurarBackupArchivo("Clientes.bkp", "Clientes.dat"); break;
            case 2: restaurarBackupArchivo("Productos.bkp", "Productos.dat"); break;
            case 3: restaurarBackupArchivo("Empleados.bkp", "Empleados.dat"); break;
            case 4: restaurarBackupArchivo("Pedidos.bkp", "Pedidos.dat"); break;
            case 5: restaurarBackupArchivo("DetallesPedidos.bkp", "DetallesPedidos.dat"); break;
            case 6: restaurarBackupArchivo("Pagos.bkp", "Pagos.dat"); break;
            case 7:
                restaurarBackupArchivo("Clientes.bkp", "Clientes.dat");
                restaurarBackupArchivo("Productos.bkp", "Productos.dat");
                restaurarBackupArchivo("Empleados.bkp", "Empleados.dat");
                restaurarBackupArchivo("Pedidos.bkp", "Pedidos.dat");
                restaurarBackupArchivo("DetallesPedidos.bkp", "DetallesPedidos.dat");
                restaurarBackupArchivo("Pagos.bkp", "Pagos.dat");
                imprimirMensajeOk(">>> RESTAURACION COMPLETA FINALIZADA.");
                break;
                default: imprimirMensajeError("Opcion invalida."); break;

        }
        pausarConsola();
    }
}

// Submenu para exportar a CSV
void exportarDatosCSV(){
    while(true) {
        limpiarConsola();
        imprimirTituloDecorado("EXPORTAR A CSV (EXCEL)", 55);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. Clientes" << endl;
        cout << "2. Productos" << endl;
        cout << "3. Empleados" << endl;
        cout << "4. Pedidos" << endl;
        cout << "5. Detalles" << endl;
        cout << "6. Pagos" << endl;
        cout << "7. EXPORTAR TODO" << endl;
        cout << "0. Volver" << endl;
        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(55);
        restaurarColor();

        int opc = ingresarEntero("Opcion: ");
        if(opc == 0) return;

        switch (opc){
            // procesarExportacion maneja el mensaje de exito/error
            case 1: procesarExportacion(exportarClientesCSV("Clientes.csv"), "Clientes.csv"); break;
            case 2: procesarExportacion(exportarProductosCSV("Productos.csv"), "Productos.csv"); break;
            case 3: procesarExportacion(exportarEmpleadosCSV("Empleados.csv"), "Empleados.csv"); break;
            case 4: procesarExportacion(exportarPedidosCSV("Pedidos.csv"), "Pedidos.csv"); break;
            case 5: procesarExportacion(exportarDetallesCSV("Detalles.csv"), "Detalles.csv"); break;
            case 6: procesarExportacion(exportarPagosCSV("Pagos.csv"), "Pagos.csv"); break;
            case 7:
                procesarExportacion(exportarClientesCSV("Clientes.csv"), "Clientes");
                procesarExportacion(exportarProductosCSV("Productos.csv"), "Productos");
                procesarExportacion(exportarEmpleadosCSV("Empleados.csv"), "Empleados");
                procesarExportacion(exportarPedidosCSV("Pedidos.csv"), "Pedidos");
                procesarExportacion(exportarDetallesCSV("Detalles.csv"), "Detalles");
                procesarExportacion(exportarPagosCSV("Pagos.csv"), "Pagos");
                imprimirMensajeOk(">>> EXPORTACION MASIVA COMPLETADA.");
                break;
            default: imprimirMensajeError("Incorrecto."); break;
        }
        pausarConsola();
    }
}

// --- HELPERS LOCALES DE UI ---
// Estas funciones se encargan de la interaccion con el usuario (mensajes)
// y delegan la accion real al GestorArchivos.

void realizarBackupArchivo(const char* nombreReal, const char* nombreBkp) {
    if (existeArchivo(nombreReal)) {
        if (copiarArchivoBinario(nombreReal, nombreBkp)) {
            imprimirMensajeOk(string("Backup creado: ") + nombreBkp);
        } else {
            imprimirMensajeError(string("Fallo al crear backup de ") + nombreReal);
        }
    } else {
        imprimirMensajeAdvertencia(string("Archivo no existe: ") + nombreReal + " (omitido)");
    }
}


void restaurarBackupArchivo(const char* nombreBkp, const char* nombreReal) {
    if (existeArchivo(nombreBkp)) {
        if (copiarArchivoBinario(nombreBkp, nombreReal)) {

            imprimirMensajeOk(string("Restaurado: ") + nombreReal);
        } else {

            imprimirMensajeError(string("Fallo al restaurar ") + nombreReal);
        }
    } else {

        imprimirMensajeError(string("No existe el backup: ") + nombreBkp);
    }
}

void procesarExportacion(bool exito, const char* nombreArchivo) {
    if (exito) imprimirMensajeOk(string("Exportado: ") + nombreArchivo);
    else imprimirMensajeError(string("Fallo exportacion de ") + nombreArchivo);
}
