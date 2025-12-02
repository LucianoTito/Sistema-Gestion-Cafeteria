#include <iostream>
#include <cstdlib>
#include <cstdio> // Necesario para sprintf

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

using namespace std;

// ==========================================
// PROTOTIPOS DE FUNCIONES AUXILIARES
// ==========================================
void ordenarPedidosPorFecha(Pedido vectorPedidos[], int cantidad);

// Nuevas funciones de visualización (Tablas)
void mostrarEncabezadoTablaPedidos();
void mostrarFilaPedido(Pedido p);

// Consultas
void menuConsultasPedidos();
void consultaPedidosPorRangoFechas();
void consultaPedidosPorCliente();
void consultaPedidosPorEmpleado();

// Funciones helpers de lógica de negocio
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
        system ("cls");
        lineaDoble(40);
        cout << "          GESTION DE PEDIDOS          " << endl;
        lineaDoble(40);
        cout << "1. REALIZAR UN PEDIDO " << endl;
        cout << "2. VER DETALLE DE UN PEDIDO" << endl;
        cout << "3. LISTAR PEDIDOS (ORDENADOS POR FECHA)" << endl;
        cout << "4. CONSULTAS DE PEDIDOS" << endl;
        cout << "5. ANULAR UN PEDIDO (BAJA LOGICA)" << endl;
        lineaSimple(40);
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        lineaDoble(40);

        opcion = ingresarEntero("SELECCIONE UNA OPCION: ");
        system ("cls");
        bool mostrarPausa = true;

        switch (opcion){
            case 1: realizarPedido(); break;
            case 2: verDetallePedido(); break;
            case 3: listarPedidos(); break;
            case 4:
                menuConsultasPedidos();
                mostrarPausa = false;
                break;
            case 5: anularPedido(); break;
            case 0: return;
            default: cout << "Opcion incorrecta." << endl; break;
        }
        if(mostrarPausa) system ("pause");
    }
}

// ==========================================
// FUNCION PRINCIPAL: REALIZAR PEDIDO
// ==========================================
void realizarPedido() {
    ArchivoPedido arcPedido ("Pedidos.dat");
    ArchivoDetallePedido arcDetalle ("DetallesPedidos.dat");
    ArchivoPagos arcPagos ("Pagos.dat");

    // Guardamos estados iniciales por si hay que revertir (Rollback simple)
    int cantidadPedidosPrevios = arcPedido.contarRegistros();
    int cantidadDetallesInicial = arcDetalle.contarRegistros();

    cout << "-------- REALIZAR NUEVO PEDIDO --------" << endl;

    // 1. SELECCION DE CLIENTE
    int idCliente = seleccionarClienteValido();
    if (idCliente == -1) return; // Cancelado o error

    system("cls");

    // 2. SELECCION DE EMPLEADO
    int idEmpleado = seleccionarEmpleadoValido();
    if (idEmpleado == -1) return;

    system("cls");

    // 3. INICIALIZAR PEDIDO EN MEMORIA
    Pedido regPedido;
    int idNuevoPedido = cantidadPedidosPrevios + 1;
    regPedido.Cargar(idNuevoPedido, idCliente, idEmpleado);

    // 4. CARGA DE PRODUCTOS (Detalles)
    if (!cargarProductosEnPedido(regPedido, cantidadDetallesInicial)) {
        cout << "Pedido cancelado (sin productos cargados)." << endl;
        return;
    }

    // 5. GRABAR PEDIDO PRINCIPAL
    if (!arcPedido.grabarRegistro(regPedido)){
        cout << "ERROR CRITICO: No se pudo grabar el pedido." << endl;
        revertirCambiosStock(idNuevoPedido);
        arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
        return;
    }

    // 6. GESTIONAR PAGO
    if (!registrarPagoParaPedido(arcPagos, regPedido)){
        cout << "El pago no se concreto. Se revertira el pedido." << endl;
        revertirCambiosStock(idNuevoPedido);
        arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
        arcPedido.restaurarCantidadRegistros(cantidadPedidosPrevios);
        return;
    }

    cout << endl << "------ PEDIDO COMPLETADO EXITOSAMENTE ------" << endl;
}

// ==========================================
// LOGICA DE CARGA DE PRODUCTOS
// ==========================================
bool cargarProductosEnPedido(Pedido &regPedido, int &cantidadDetallesInicial) {
    ArchivoProducto arcProducto("Productos.dat");
    ArchivoDetallePedido arcDetalle("DetallesPedidos.dat");

    if(!arcProducto.hayProductosConEstadoEliminado(false)){
        cout << "No hay productos activos disponibles." << endl;
        return false;
    }

    bool seAgregoProducto = false;
    cout << endl << "-------- AGREGAR PRODUCTOS AL PEDIDO --------" << endl;

    while(true){
        cout << endl << "PRODUCTOS DISPONIBLES: " << endl;
        arcProducto.listar();

        cout << endl;
        int idProducto = ingresarEntero("Seleccione ID Producto (0 para terminar): ");

        if (idProducto == 0){
            if(!seAgregoProducto){
                char cancelar;
                cout << "No cargo productos. Desea cancelar el pedido? (S/N): ";
                cin >> cancelar;
                if(cancelar == 'S' || cancelar == 's'){
                    arcDetalle.restaurarCantidadRegistros(cantidadDetallesInicial);
                    return false;
                }
                continue;
            }
            break;
        }

        // --- Validaciones de Producto ---
        int posProd = arcProducto.buscarRegistro(idProducto);
        if(posProd == -1){
            cout << "ERROR: ID inexistente." << endl; system("pause"); system("cls"); continue;
        }

        Producto regProd = arcProducto.leerRegistro(posProd);
        if (regProd.getEliminado() || regProd.getStock() <= 0) {
            cout << "ERROR: Producto eliminado o sin stock." << endl; system("pause"); system("cls"); continue;
        }

        cout << "Seleccionado: " << regProd.getNombre() << " | Stock: " << regProd.getStock() << endl;
        int cantidad = ingresarEntero("Ingrese cantidad: ");

        if (cantidad <= 0 || cantidad > regProd.getStock()){
            cout << "ERROR: Cantidad invalida o stock insuficiente." << endl; system("pause"); system("cls"); continue;
        }

        // --- Logica de Insertar/Actualizar Detalle ---
        int posDetalleExistente = arcDetalle.buscarDetallePorPedidoYProducto(regPedido.getIdPedido(), idProducto);
        float subtotalItem = 0;

        if (posDetalleExistente != -1) {
            // -- ACTUALIZAR EXISTENTE --
            DetallePedido detalle = arcDetalle.leerRegistro(posDetalleExistente);
            int nuevaCant = detalle.getCantidad() + cantidad;

            if (nuevaCant > regProd.getStock()) {
                 cout << "ERROR: La suma total supera el stock disponible." << endl; system("pause"); continue;
            }

            detalle.setCantidad(nuevaCant);
            if(arcDetalle.modificarRegistro(detalle, posDetalleExistente)){
                subtotalItem = regProd.getPrecio() * cantidad;
                regPedido.setSubtotal(regPedido.getSubtotal() + subtotalItem);

                actualizarStockProducto(idProducto, cantidad, false); // false = restar
                cout << "Cantidad actualizada." << endl;
                seAgregoProducto = true;
            }
        } else {
            // -- CREAR NUEVO DETALLE --
            int idDetalle = arcDetalle.contarRegistros() + 1;
            DetallePedido nuevoDetalle(idDetalle, regPedido.getIdPedido(), idProducto, cantidad, regProd.getPrecio());

            if (arcDetalle.grabarRegistro(nuevoDetalle)) {
                subtotalItem = regProd.getPrecio() * cantidad;
                regPedido.setSubtotal(regPedido.getSubtotal() + subtotalItem);

                actualizarStockProducto(idProducto, cantidad, false); // false = restar
                cout << "Producto agregado." << endl;
                seAgregoProducto = true;
            }
        }
        system("pause");
        system("cls");
    }
    return seAgregoProducto;
}

// ==========================================
// ANULAR PEDIDO
// ==========================================
void anularPedido () {
    ArchivoPedido arcPedido("Pedidos.dat");

    cout << "---------- ANULAR PEDIDO ----------" << endl;

    if(!arcPedido.hayPedidosConEstado(false)){
        cout << "No hay pedidos activos." << endl; return;
    }

    // Aquí podrías llamar a listarPedidos() para verlos en tabla antes de anular
    arcPedido.listarPorEstado(false);
    cout << endl;

    int idAnular = ingresarEntero("ID del Pedido a anular: ");
    int pos = arcPedido.buscarRegistro(idAnular);

    if (pos == -1){
        cout << "Pedido no encontrado." << endl; return;
    }

    Pedido regPedido = arcPedido.leerRegistro(pos);
    if (regPedido.getEliminado()){
        cout << "El pedido ya esta anulado." << endl; return;
    }

    cout << endl << "Detalle del pedido a anular:" << endl;
    mostrarEncabezadoTablaPedidos();
    mostrarFilaPedido(regPedido);
    lineaSimple(70);

    char conf;
    cout << "Seguro desea anular? (S/N): ";
    cin >> conf;

    if (conf == 'S' || conf == 's'){
        cout << "Restaurando stock..." << endl;
        revertirCambiosStock(idAnular);

        regPedido.setEliminado(true);
        if (arcPedido.modificarRegistro(regPedido, pos)){
            cout << "Pedido anulado exitosamente." << endl;
        } else {
            cout << "Error al actualizar estado del pedido." << endl;
        }
    }
}

// ==========================================
// FUNCIONES AUXILIARES (STOCK & SELECCION)
// ==========================================
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

int seleccionarClienteValido() {
    ArchivoCliente arc("Clientes.dat");
    if (!arc.hayClientesConEstadoEliminado(false)){
        cout << "No hay clientes activos." << endl; return -1;
    }
    cout << "CLIENTES DISPONIBLES:" << endl;
    arc.listar();
    int id = ingresarEntero("Seleccione ID Cliente: ");
    int pos = arc.buscarRegistro(id);
    if (pos != -1 && !arc.leerRegistro(pos).getEliminado()) return id;

    cout << "Cliente invalido." << endl; system("pause");
    return -1;
}

int seleccionarEmpleadoValido() {
    ArchivoEmpleado arc("Empleados.dat");
    if (!arc.hayEmpleadosConEstadoEliminado(false)){
        cout << "No hay empleados activos." << endl; return -1;
    }
    cout << "EMPLEADOS DISPONIBLES:" << endl;
    arc.listar();
    int id = ingresarEntero("Seleccione ID Empleado: ");
    int pos = arc.buscarRegistro(id);
    if (pos != -1 && !arc.leerRegistro(pos).getEliminado()) return id;

    cout << "Empleado invalido." << endl; system("pause");
    return -1;
}

// ==========================================
// FUNCIONES DE CONSULTA Y LISTADO (TABLAS)
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

    // --- ACTIVOS ---
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
    lineaDoble(70);

    // --- ANULADOS ---
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
    lineaDoble(70);

    delete[] vector;
}

void menuConsultasPedidos(){
    int opcion;
    while(true){
        system("cls");
        lineaDoble(40);
        cout << "      CONSULTAS DE PEDIDOS" << endl;
        lineaDoble(40);
        cout << "1. POR RANGO DE FECHAS" << endl;
        cout << "2. POR CLIENTE" << endl;
        cout << "3. POR EMPLEADO" << endl;
        lineaSimple(40);
        cout << "0. VOLVER" << endl;
        lineaDoble(40);

        opcion = ingresarEntero("OPCION: ");
        system("cls");
        switch(opcion){
            case 1: consultaPedidosPorRangoFechas(); break;
            case 2: consultaPedidosPorCliente(); break;
            case 3: consultaPedidosPorEmpleado(); break;
            case 0: return;
            default: cout << "Incorrecto." << endl; break;
        }
        system("pause");
    }
}

void consultaPedidosPorRangoFechas(){
    ArchivoPedido arc("Pedidos.dat");
    if(!arc.hayPedidosConEstado(false)){ cout << "Sin pedidos activos." << endl; return;}

    cout << "Ingrese RANGO DE FECHAS:" << endl;
    cout << "Desde: " << endl; Fecha f1; f1.Cargar();
    cout << endl << "Hasta: " << endl; Fecha f2; f2.Cargar();

    if(f2 < f1) { cout << "Rango invalido." << endl; return; }

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
    lineaSimple(70);
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
    lineaSimple(70);
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
    lineaSimple(70);
}

// ==========================================
// UTILERIAS DE VISUALIZACION
// ==========================================

void mostrarEncabezadoTablaPedidos() {
    lineaDoble(70);
    // Llama a la funcion de Tablas.h con los titulos
    imprimirFilaPedido("ID", "FECHA", "ID CLIENTE", "ID EMPL.", "TOTAL ($)");
    lineaSimple(70);
}

void mostrarFilaPedido(Pedido p) {
    char sId[15], sFecha[15], sCli[15], sEmp[15], sTotal[20];
    Fecha f = p.getFecha();

    // Formateamos los datos para que entren en la tabla como texto
    sprintf(sId, "%d", p.getIdPedido());
    sprintf(sFecha, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());
    sprintf(sCli, "%d", p.getIdCliente());
    sprintf(sEmp, "%d", p.getIdEmpleado());
    sprintf(sTotal, "$ %.2f", p.getTotal());

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

void verDetallePedido(){
    ArchivoPedido arcP("Pedidos.dat");
    ArchivoDetallePedido arcD("DetallesPedidos.dat");
    ArchivoProducto arcProd("Productos.dat");
    ArchivoPagos arcPagos("Pagos.dat");

    int id = ingresarEntero("Ingrese ID Pedido: ");
    int pos = arcP.buscarRegistro(id);
    if(pos == -1){ cout << "No existe." << endl; return; }

    Pedido p = arcP.leerRegistro(pos);
    cout << endl;
    lineaDoble(50);
    cout << " PEDIDO: " << p.getIdPedido() << (p.getEliminado() ? " [ANULADO]" : " [ACTIVO]") << endl;
    lineaDoble(50);

    // Listado de productos en formato simple (o podrias crear tabla si quieres)
    int cant = arcD.contarRegistros();
    cout << " PRODUCTOS: " << endl;
    lineaSimple(50);
    for(int i=0; i<cant; i++){
        DetallePedido d = arcD.leerRegistro(i);
        if(d.getIdPedido() == id){
            int posProd = arcProd.buscarRegistro(d.getIdProducto());
            Producto prod = arcProd.leerRegistro(posProd);
            cout << " * " << prod.getNombre() << " (x" << d.getCantidad() << ")"
                 << " - Unit: $" << d.getPrecioUnitario() << endl;
        }
    }
    lineaSimple(50);
    cout << " INFORMACION DE PAGO: " << endl;
    mostrarPagoDePedido(arcPagos, id);
    cout << endl;
}
