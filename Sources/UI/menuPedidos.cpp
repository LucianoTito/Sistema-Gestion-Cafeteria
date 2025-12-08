#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <windows.h> // Necesario para la funcion Sleep()

#include "../../Headers/UI/menuPedidos.h"
#include "../../Headers/Entities/Cliente.h"
#include "../../Headers/Persistence/ArchivoCliente.h"
#include "../../Headers/Entities/Empleado.h"
#include "../../Headers/Persistence/ArchivoEmpleado.h"
#include "../../Headers/Entities/Producto.h"
#include "../../Headers/Persistence/ArchivoProducto.h"
#include "../../Headers/Entities/Pedido.h"
#include "../../Headers/Entities/Fecha.h"
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Entities/DetallePedido.h"
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Persistence/ArchivoPagos.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/archivoPago.h"
#include "../../Headers/Utilidades/Tablas.h"
#include "../../Headers/Utilidades/Estilos.h"
#include "../../Headers/Utilidades/rlutil.h"

using namespace std;

// Anchos estandarizados para las tablas
const int ANCHO_MENU = 80;
const int ANCHO_TABLA_CLIENTES = 94;

const int ANCHO_TABLA_EMPLEADOS = 120;
const int ANCHO_TABLA_PRODUCTOS = 81;

// ==========================================
// PROTOTIPOS LOCALES
// ==========================================
void ordenarPedidosPorFecha(Pedido vectorPedidos[], int cantidad);
void mostrarEncabezadoTablaPedidos();
void mostrarFilaPedido(Pedido p);

// Funciones visuales de selección
void listarProductosParaSeleccion();
void listarClientesParaSeleccion();
void listarEmpleadosParaSeleccion();
void mostrarTablaDetallesActuales(int idPedido);

// Submenús y Consultas
void menuConsultasPedidos();
void consultaPedidosPorRangoFechas();
void consultaPedidosPorCliente();
void consultaPedidosPorEmpleado();

// Helpers Lógicos
int seleccionarClienteValido();
int seleccionarEmpleadoValido();
bool cargarProductosEnPedido(Pedido &regPedido, int &cantidadDetallesIniciales);
void actualizarStockProducto(int idProducto, int cantidad, bool devolverStock);
void revertirCambiosStock(int idPedido);

// ==========================================
// MENU PRINCIPAL DE PEDIDOS
// ==========================================
void menuPedidos(){
    int opcion;
    while (true){
        limpiarConsola();
        imprimirTituloDecorado("GESTION DE PEDIDOS", ANCHO_MENU);

        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. REALIZAR UN PEDIDO" << endl;
        cout << "2. VER DETALLE DE UN PEDIDO" << endl;
        cout << "3. LISTAR PEDIDOS (ORDENADOS POR FECHA)" << endl;
        cout << "4. CONSULTAS DE PEDIDOS" << endl;
        cout << "5. ANULAR UN PEDIDO (BAJA LOGICA)" << endl;

        rlutil::setColor(PaletaCafe::BASE);
        lineaSimple(ANCHO_MENU);

        rlutil::setColor(PaletaCafe::ESPUMA);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;

        rlutil::setColor(PaletaCafe::BASE);
        lineaDoble(ANCHO_MENU);
        restaurarColor();

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        limpiarConsola();

        bool pausar = true;

        switch (opcion){
            case 1: realizarPedido(); break;
            case 2: verDetallePedido(); break;
            case 3: listarPedidos(); break;
            case 4:
                menuConsultasPedidos();
                pausar = false;
                break;
            case 5: anularPedido(); break;
            case 0: return;
            default: imprimirMensajeError("Opcion incorrecta."); break;
        }

        if(pausar) {
            // CORRECCIÓN: cin.sync() limpia el buffer sin bloquear si está vacío.
            // Esto evita el problema de tener que dar dos Enter o que se salte la pausa.
            cin.sync();
            pausarConsola();
        }
    }
}

// ==========================================
// FUNCION PRINCIPAL: REALIZAR PEDIDO
// ==========================================
void realizarPedido() {
    ArchivoPedido arcPedido ("Pedidos.dat");
    ArchivoDetallePedido arcDetalle ("DetallesPedidos.dat");
    ArchivoPagos arcPagos ("Pagos.dat");

    int cantidadPedidosPrevios = arcPedido.contarRegistros();
    int cantidadDetallesInicial = arcDetalle.contarRegistros();

    // PASO 1: CLIENTE
    limpiarConsola();
    imprimirTituloDecorado("NUEVO PEDIDO - PASO 1: SELECCIONAR CLIENTE", ANCHO_TABLA_CLIENTES);

    int idCliente = seleccionarClienteValido();
    if (idCliente == -1) return;

    // PASO 2: EMPLEADO
    limpiarConsola();
    imprimirTituloDecorado("NUEVO PEDIDO - PASO 2: SELECCIONAR EMPLEADO", ANCHO_TABLA_EMPLEADOS);

    int idEmpleado = seleccionarEmpleadoValido();
    if (idEmpleado == -1) return;

    limpiarConsola();

    // 3. INICIALIZAR PEDIDO
    Pedido regPedido;
    int idNuevoPedido = cantidadPedidosPrevios + 1;
    regPedido.Cargar(idNuevoPedido, idCliente, idEmpleado);

    // 4. CARGA DE PRODUCTOS (Carrito Visual)
    if (!cargarProductosEnPedido(regPedido, cantidadDetallesInicial)) {
        imprimirMensajeAdvertencia("Pedido cancelado (sin productos).");
        return;
    }

    // 5. GRABAR PEDIDO
    if (!arcPedido.grabarRegistro(regPedido)){
        imprimirMensajeError("ERROR CRITICO: No se pudo grabar el pedido.");
        revertirCambiosStock(idNuevoPedido);
        arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
        return;
    }

    // 6. GESTIONAR PAGO
    limpiarConsola();
    imprimirTituloDecorado("NUEVO PEDIDO - PASO 4: PAGO", ANCHO_MENU);

    if (!registrarPagoParaPedido(arcPagos, regPedido)){
        imprimirMensajeError("Pago no concretado. Revertiendo pedido...");
        revertirCambiosStock(idNuevoPedido);
        arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
        arcPedido.restaurarCantidadRegistros(cantidadPedidosPrevios);
        return;
    }

    imprimirMensajeExito("PEDIDO COMPLETADO EXITOSAMENTE");
}

// ==========================================
// LOGICA DE CARGA DE PRODUCTOS
// ==========================================
bool cargarProductosEnPedido(Pedido &regPedido, int &cantidadDetallesInicial) {
    ArchivoProducto arcProducto("Productos.dat");
    ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");

    if(!arcProducto.hayProductosConEstadoEliminado(false)){
        imprimirMensajeError("No hay productos activos disponibles.");
        return false;
    }

    bool seAgregoProducto = false;

    while(true){
        limpiarConsola();
        imprimirTituloDecorado("NUEVO PEDIDO - PASO 3: PRODUCTOS", ANCHO_TABLA_PRODUCTOS);

        // MOSTRAR CARRITO
        if(seAgregoProducto){
            rlutil::setColor(PaletaCafe::CREMA);
            cout << ">>> DETALLE ACTUAL DEL PEDIDO (CARRITO)" << endl;
            mostrarTablaDetallesActuales(regPedido.getIdPedido());

            rlutil::setColor(PaletaCafe::EXITO); // Verde
            cout << "   SUBTOTAL ACUMULADO: $ " << fixed << setprecision(2) << regPedido.getSubtotal() << endl;
            restaurarColor();
            cout << endl;
        }

        // MOSTRAR CATALOGO
        rlutil::setColor(PaletaCafe::CREMA);
        cout << ">>> CATALOGO DE PRODUCTOS:" << endl;
        listarProductosParaSeleccion();

        cout << endl;
        int idProducto = ingresarEntero("Seleccione ID Producto (0 para TERMINAR): ");

        if (idProducto == 0){
            if(!seAgregoProducto){
                char cancelar;
                rlutil::setColor(PaletaCafe::ADVERTENCIA);
                cout << "El pedido esta vacio. Desea cancelarlo? (S/N): ";
                cin >> cancelar;
                restaurarColor();
                if(cancelar == 'S' || cancelar == 's'){
                    arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
                    return false;
                }
                continue;
            }
            break;
        }

        int posProd = arcProducto.buscarRegistro(idProducto);
        if(posProd == -1){
            imprimirMensajeError("ID inexistente.");
            Sleep(1500); // Pausa automatica
            continue;
        }

        Producto regProd = arcProducto.leerRegistro(posProd);
        if (regProd.getEliminado() || regProd.getStock() <= 0) {
            imprimirMensajeError("Producto no disponible (Eliminado o Sin Stock).");
            Sleep(1100); // Pausa automatica
            continue;
        }

        cout << endl;
        rlutil::setColor(PaletaCafe::BASE); lineaSimple(60);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << " Seleccionado: " << regProd.getNombre() << endl;
        cout << " Precio: $" << regProd.getPrecio() << " | Stock Disp: " << regProd.getStock() << endl;
        rlutil::setColor(PaletaCafe::BASE); lineaSimple(60); restaurarColor();

        int cantidad = ingresarEntero("Ingrese cantidad a llevar: ");

        if (cantidad <= 0 || cantidad > regProd.getStock()){
            imprimirMensajeError("Cantidad invalida o stock insuficiente.");
            Sleep(1500); // Pausa automatica
            continue;
        }

        // AGREGAR / ACTUALIZAR DETALLE
        int posDetalleExistente = arcDetalle.buscarDetallePorPedidoYProducto(regPedido.getIdPedido(), idProducto);
        float subtotalItem = 0;

        if (posDetalleExistente != -1) {
            DetallePedido detalle = arcDetalle.leerRegistro(posDetalleExistente);
            int nuevaCant = detalle.getCantidad() + cantidad;

            if (nuevaCant > regProd.getStock()) {
                 imprimirMensajeError("La suma total supera el stock disponible.");
                 Sleep(1500);
                 continue;
            }

            detalle.setCantidad(nuevaCant);
            if(arcDetalle.modificarRegistro(detalle, posDetalleExistente)){
                subtotalItem = regProd.getPrecio() * cantidad;
                regPedido.setSubtotal(regPedido.getSubtotal() + subtotalItem);
                actualizarStockProducto(idProducto, cantidad, false);
                imprimirMensajeExito("Cantidad actualizada en el carrito.");
                seAgregoProducto = true;
            }
        } else {
            int idDetalle = arcDetalle.contarRegistros() + 1;
            DetallePedido nuevoDetalle(idDetalle, regPedido.getIdPedido(), idProducto, cantidad, regProd.getPrecio());

            if (arcDetalle.grabarRegistro(nuevoDetalle)) {
                subtotalItem = regProd.getPrecio() * cantidad;
                regPedido.setSubtotal(regPedido.getSubtotal() + subtotalItem);
                actualizarStockProducto(idProducto, cantidad, false);
                imprimirMensajeExito("Producto agregado al carrito.");
                seAgregoProducto = true;
            }
        }

        // MEJORA: Pausa automatica de 1.5 seg en lugar de pedir Enter
        // Esto permite leer "Producto agregado" y que la pantalla se limpie sola
        Sleep(1500);
    }
    return seAgregoProducto;
}

// ==========================================
// SELECCIONADORES VISUALES (CLIENTE/EMPLEADO)
// ==========================================

void listarClientesParaSeleccion() {
    ArchivoCliente arc("Clientes.dat");

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_TABLA_CLIENTES);
    imprimirFilaCliente("ID", "NOMBRE", "APELLIDO", "TELEFONO", "MAIL");
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(ANCHO_TABLA_CLIENTES);

    int n = arc.contarRegistros();
    for(int i=0; i<n; i++){
        Cliente c = arc.leerRegistro(i);
        if(!c.getEliminado()){
            char sId[10];
            sprintf(sId, "%d", c.getId());
            imprimirFilaCliente(sId, c.getNombre(), c.getApellido(), c.getTelefono(), c.getMail());
        }
    }
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_TABLA_CLIENTES);
    restaurarColor();
}

int seleccionarClienteValido() {
    ArchivoCliente arc("Clientes.dat");
    if (!arc.hayClientesConEstadoEliminado(false)){
        imprimirMensajeError("No hay clientes activos para seleccionar.");
        return -1;
    }

    rlutil::setColor(PaletaCafe::CREMA);
    cout << ">>> LISTADO DE CLIENTES DISPONIBLES:" << endl;
    listarClientesParaSeleccion();
    cout << endl;

    int id = ingresarEntero("Seleccione ID Cliente: ");
    int pos = arc.buscarRegistro(id);

    if (pos != -1 && !arc.leerRegistro(pos).getEliminado()) return id;

    imprimirMensajeError("Cliente invalido o inexistente.");
    pausarConsola("");
    return -1;
}

void listarEmpleadosParaSeleccion() {
    ArchivoEmpleado arc("Empleados.dat");

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_TABLA_EMPLEADOS);
    imprimirFilaEmpleado("ID", "NOMBRE", "APELLIDO", "TELEFONO", "MAIL", "PUESTO");
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(ANCHO_TABLA_EMPLEADOS);

    int n = arc.contarRegistros();
    for(int i=0; i<n; i++){
        Empleado e = arc.leerRegistro(i);
        if(!e.getEliminado()){
            char sId[10];
            sprintf(sId, "%d", e.getId());
            imprimirFilaEmpleado(sId, e.getNombre(), e.getApellido(), e.getTelefono(), e.getMail(), e.getPuesto());
        }
    }
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_TABLA_EMPLEADOS);
    restaurarColor();
}

int seleccionarEmpleadoValido() {
    ArchivoEmpleado arc("Empleados.dat");
    if (!arc.hayEmpleadosConEstadoEliminado(false)){
        imprimirMensajeError("No hay empleados activos.");
        return -1;
    }

    rlutil::setColor(PaletaCafe::CREMA);
    cout << ">>> LISTADO DE EMPLEADOS DISPONIBLES:" << endl;
    listarEmpleadosParaSeleccion();
    cout << endl;

    int id = ingresarEntero("Seleccione ID Empleado: ");
    int pos = arc.buscarRegistro(id);

    if (pos != -1 && !arc.leerRegistro(pos).getEliminado()) return id;

    imprimirMensajeError("Empleado invalido.");
    pausarConsola("");
    return -1;
}

// ==========================================
// FUNCIONES VISUALES (TABLAS)
// ==========================================

void listarProductosParaSeleccion() {
    ArchivoProducto arc("Productos.dat");

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_TABLA_PRODUCTOS);
    imprimirFilaProducto("ID", "NOMBRE", "PRECIO ($)", "STOCK");
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(ANCHO_TABLA_PRODUCTOS);

    int n = arc.contarRegistros();
    for(int i=0; i<n; i++){
        Producto p = arc.leerRegistro(i);
        if(!p.getEliminado()){
            char sId[10], sPrecio[20], sStock[10];
            sprintf(sId, "%d", p.getIdProducto());
            sprintf(sPrecio, "%.2f", p.getPrecio());
            sprintf(sStock, "%d", p.getStock());

            imprimirFilaProducto(sId, p.getNombre(), sPrecio, sStock);
        }
    }
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_TABLA_PRODUCTOS);
    restaurarColor();
}

void mostrarTablaDetallesActuales(int idPedido) {
    ArchivoDetallePedido arcDet("DetallesPedidos.dat");
    ArchivoProducto arcProd("Productos.dat");

    const int ANCHO_CARRITO = 68;

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_CARRITO);

    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "|| " << left << setw(25) << "PRODUCTO"
         << " | " << right << setw(5) << "CANT"
         << " | " << right << setw(10) << "P.UNIT"
         << " | " << right << setw(12) << "SUBTOTAL" << " ||" << endl;

    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(ANCHO_CARRITO);

    int n = arcDet.contarRegistros();
    for(int i=0; i<n; i++){
        DetallePedido d = arcDet.leerRegistro(i);
        if(d.getIdPedido() == idPedido){
            int posP = arcProd.buscarRegistro(d.getIdProducto());
            Producto p = arcProd.leerRegistro(posP);

            float sub = d.getCantidad() * d.getPrecioUnitario();

            rlutil::setColor(PaletaCafe::BASE); cout << "|| ";
            rlutil::setColor(PaletaCafe::ESPUMA);
            cout << left << setw(25) << p.getNombre()
                 << " | " << right << setw(5) << d.getCantidad()
                 << " | " << right << setw(10) << fixed << setprecision(2) << d.getPrecioUnitario()
                 << " | " << right << setw(12) << sub;
            rlutil::setColor(PaletaCafe::BASE); cout << " ||" << endl;
        }
    }
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_CARRITO);
    restaurarColor();
}

// ==========================================
// FUNCIONES RESTANTES (ANULAR, LISTAR, ETC)
// ==========================================

void anularPedido () {
    ArchivoPedido arcPedido("Pedidos.dat");
    cout << "---------- ANULAR PEDIDO ----------" << endl;

    if(!arcPedido.hayPedidosConEstado(false)){
        imprimirMensajeError("No hay pedidos activos."); return;
    }

    listarPedidos();
    cout << endl;

    int idAnular = ingresarEntero("ID del Pedido a anular: ");
    int pos = arcPedido.buscarRegistro(idAnular);

    if (pos == -1){
        imprimirMensajeError("Pedido no encontrado."); return;
    }

    Pedido regPedido = arcPedido.leerRegistro(pos);
    if (regPedido.getEliminado()){
        imprimirMensajeError("El pedido ya esta anulado."); return;
    }

    cout << endl << "Detalle del pedido a anular:" << endl;
    mostrarEncabezadoTablaPedidos();
    mostrarFilaPedido(regPedido);
    lineaSimple(ANCHO_MENU);

    char conf;
    cout << "Seguro desea anular? (S/N): "; cin >> conf;

    if (conf == 'S' || conf == 's'){
        cout << "Restaurando stock..." << endl;
        revertirCambiosStock(idAnular);

        regPedido.setEliminado(true);
        if (arcPedido.modificarRegistro(regPedido, pos)){
            imprimirMensajeExito("Pedido anulado exitosamente.");
        } else {
            imprimirMensajeError("Error al actualizar estado.");
        }
    }
}

// Helpers de stock y validacion
void actualizarStockProducto(int idProducto, int cantidad, bool devolverStock) {
    ArchivoProducto arc("Productos.dat");
    int pos = arc.buscarRegistro(idProducto);
    if (pos != -1) {
        Producto p = arc.leerRegistro(pos);
        int stockActual = p.getStock();
        if (devolverStock) p.setStock(stockActual + cantidad);
        else p.setStock(stockActual - cantidad);
        arc.modificarRegistro(p, pos);
    }
}

void revertirCambiosStock(int idPedido) {
    ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");
    int total = arcDetalle.contarRegistros();
    for(int i=0; i<total; i++){
        DetallePedido det = arcDetalle.leerRegistro(i);
        if(det.getIdPedido() == idPedido){
            actualizarStockProducto(det.getIdProducto(), det.getCantidad(), true);
        }
    }
}

// ==========================================
// VISUALIZACION
// ==========================================

void listarPedidos() {
    ArchivoPedido arcPedido ("Pedidos.dat");
    cout << "---------- LISTADO DE PEDIDOS POR FECHA ----------" << endl;

    int cant = arcPedido.contarRegistros();
    if(cant == 0){ cout << "Sin registros." << endl; return; }

    Pedido *vector = new Pedido[cant];
    int validos = 0;
    for(int i=0; i<cant; i++){
        Pedido p = arcPedido.leerRegistro(i);
        if(p.getIdPedido() != -1) vector[validos++] = p;
    }

    if(validos > 0) ordenarPedidosPorFecha(vector, validos);

    cout << endl << ">>> PEDIDOS ACTIVOS" << endl;
    mostrarEncabezadoTablaPedidos();
    bool hayActivos = false;
    for(int i=0; i<validos; i++) {
        if(!vector[i].getEliminado()){
            mostrarFilaPedido(vector[i]);
            hayActivos = true;
        }
    }
    if (!hayActivos) cout << "|| (No hay pedidos activos)" << endl;
    lineaDoble(ANCHO_MENU);

    cout << endl << ">>> PEDIDOS ANULADOS" << endl;
    mostrarEncabezadoTablaPedidos();
    bool hayAnulados = false;
    for(int i=0; i<validos; i++) {
        if(vector[i].getEliminado()){
            mostrarFilaPedido(vector[i]);
            hayAnulados = true;
        }
    }
    if (!hayAnulados) cout << "|| (No hay pedidos anulados)" << endl;
    lineaDoble(ANCHO_MENU);

    delete[] vector;
}

void mostrarEncabezadoTablaPedidos() {
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ANCHO_MENU);
    imprimirFilaPedido("ID", "FECHA", "ID CLI", "ID EMP", "TOTAL ($)");
    rlutil::setColor(PaletaCafe::BASE);
    lineaSimple(ANCHO_MENU);
    restaurarColor();
}

void mostrarFilaPedido(Pedido p) {
    char sId[15], sFecha[15], sCli[15], sEmp[15], sTotal[20];
    Fecha f = p.getFecha();

    sprintf(sId, "%d", p.getIdPedido());
    sprintf(sFecha, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());
    sprintf(sCli, "%d", p.getIdCliente());
    sprintf(sEmp, "%d", p.getIdEmpleado());
    sprintf(sTotal, "%.2f", p.getTotal());

    imprimirFilaPedido(sId, sFecha, sCli, sEmp, sTotal);
}

void ordenarPedidosPorFecha(Pedido vector[], int cantidad){
    for(int i=0; i<cantidad-1; i++){
        for(int j=i+1; j<cantidad; j++){
            if(vector[j].getFecha() < vector[i].getFecha()){
                Pedido aux = vector[i]; vector[i] = vector[j]; vector[j] = aux;
            }
        }
    }
}

void menuConsultasPedidos(){
    int opcion;
    while(true){
        limpiarConsola();
        imprimirTituloDecorado("CONSULTAS DE PEDIDOS", ANCHO_MENU);
        rlutil::setColor(PaletaCafe::CREMA);
        cout << "1. POR RANGO DE FECHAS" << endl;
        cout << "2. POR CLIENTE" << endl;
        cout << "3. POR EMPLEADO" << endl;
        rlutil::setColor(PaletaCafe::BASE); lineaSimple(ANCHO_MENU);
        rlutil::setColor(PaletaCafe::ESPUMA); cout << "0. VOLVER" << endl;
        rlutil::setColor(PaletaCafe::BASE); lineaDoble(ANCHO_MENU);
        restaurarColor();

        opcion = ingresarEntero("OPCION: ");
        limpiarConsola();

        switch(opcion){
            case 1: consultaPedidosPorRangoFechas(); break;
            case 2: consultaPedidosPorCliente(); break;
            case 3: consultaPedidosPorEmpleado(); break;
            case 0: return;
            default: imprimirMensajeError("Incorrecto."); break;
        }
        pausarConsola();
    }
}

void consultaPedidosPorRangoFechas(){
    ArchivoPedido arc("Pedidos.dat");
    if(!arc.hayPedidosConEstado(false)){ cout << "Sin pedidos activos." << endl; return;}

    cout << "Ingrese RANGO DE FECHAS:" << endl;
    cout << "Desde: " << endl; Fecha f1; f1.Cargar();
    cout << endl << "Hasta: " << endl; Fecha f2; f2.Cargar();

    if(f2 < f1) { imprimirMensajeError("Rango invalido."); return; }

    cout << endl;
    mostrarEncabezadoTablaPedidos();
    int cant = arc.contarRegistros();
    int cont = 0;
    for(int i=0; i<cant; i++){
        Pedido p = arc.leerRegistro(i);
        if(!p.getEliminado() && p.getFecha() >= f1 && p.getFecha() <= f2) {
            mostrarFilaPedido(p);
            cont++;
        }
    }
    lineaSimple(ANCHO_MENU);
    cout << "Total encontrados: " << cont << endl;
}

void consultaPedidosPorCliente(){
    int id = seleccionarClienteValido();
    if(id == -1) return;

    ArchivoPedido arc("Pedidos.dat");
    int cant = arc.contarRegistros();

    cout << endl << "Pedidos del cliente ID " << id << ":" << endl;
    mostrarEncabezadoTablaPedidos();
    for(int i=0; i<cant; i++){
        Pedido p = arc.leerRegistro(i);
        if(!p.getEliminado() && p.getIdCliente() == id) mostrarFilaPedido(p);
    }
    lineaSimple(ANCHO_MENU);
}

void consultaPedidosPorEmpleado(){
    int id = seleccionarEmpleadoValido();
    if(id == -1) return;

    ArchivoPedido arc("Pedidos.dat");
    int cant = arc.contarRegistros();

    cout << endl << "Pedidos del empleado ID " << id << ":" << endl;
    mostrarEncabezadoTablaPedidos();
    for(int i=0; i<cant; i++){
        Pedido p = arc.leerRegistro(i);
        if(!p.getEliminado() && p.getIdEmpleado() == id) mostrarFilaPedido(p);
    }
    lineaSimple(ANCHO_MENU);
}

void verDetallePedido(){
    ArchivoPedido arcP("Pedidos.dat");
    ArchivoDetallePedido arcD("DetallesPedidos.dat");
    ArchivoProducto arcProd("Productos.dat");
    ArchivoPagos arcPagos("Pagos.dat");

    int id = ingresarEntero("Ingrese ID Pedido: ");
    int pos = arcP.buscarRegistro(id);
    if(pos == -1){ imprimirMensajeError("No existe."); return; }

    Pedido p = arcP.leerRegistro(pos);
    cout << endl;
    lineaDoble(ANCHO_MENU);
    cout << " PEDIDO: " << p.getIdPedido() << (p.getEliminado() ? " [ANULADO]" : " [ACTIVO]") << endl;
    lineaDoble(ANCHO_MENU);

    int cant = arcD.contarRegistros();
    cout << " PRODUCTOS: " << endl;
    lineaSimple(ANCHO_MENU);
    for(int i=0; i<cant; i++){
        DetallePedido d = arcD.leerRegistro(i);
        if(d.getIdPedido() == id){
            int posProd = arcProd.buscarRegistro(d.getIdProducto());
            Producto prod = arcProd.leerRegistro(posProd);
            cout << " * " << prod.getNombre() << " (x" << d.getCantidad() << ")"
                 << " - Unit: $" << d.getPrecioUnitario() << endl;
        }
    }
    lineaSimple(ANCHO_MENU);
    cout << " INFORMACION DE PAGO: " << endl;
    mostrarPagoDePedido(arcPagos, id);
    cout << endl;
}
