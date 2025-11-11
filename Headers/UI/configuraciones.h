#pragma once

//Menu principa
void menuConfiguraciones();

//Submenús
void backupMenu();
void restaurarCopiaSeguridad();
void exportarDatosCSV();

//Constantes de nombres de archivos
#define NOMBRE_ARCH_CLIENTES          "Clientes.dat"
#define NOMBRE_ARCH_PRODUCTOS         "Productos.dat"
#define NOMBRE_ARCH_EMPLEADOS         "Empleados.dat"
#define NOMBRE_ARCH_PEDIDOS           "Pedidos.dat"
#define NOMBRE_ARCH_DETALLES          "DetallesPedidos.dat"
#define NOMBRE_ARCH_PAGOS             "Pagos.dat"


//Extensión para backup
#define EXTENSION_BACKUP               ".bkp"


//Helpers

//da true si se pudo copiar completamente
bool copiarArchivoBinario (const char* origen, const char* destino);



//si el archivo existe y se puede abrir en modo lectura binaria devuelve true
bool existeArchivo(const char* nombreArchivo);

//Exportadores CSV por entidad
bool exportarClientesCSV(const char* csvDestino);
bool exportarProductosCSV( const char* csvDestino);
bool exportarEmpleadosCSV( const char* csvDestino);
bool exportarPedidosCSV( const char* csvDestino);
bool exportarDetallesCSV(const char* csvDestino);
bool exportarPagosCSV(const char* csvDestino);
