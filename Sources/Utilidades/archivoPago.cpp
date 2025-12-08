#include <iostream>
#include <iomanip>
#include <cstdio>
#include "../../Headers/Utilidades/archivoPago.h"
#include "../../Headers/Utilidades/Validaciones.h"
#include "../../Headers/Utilidades/Estilos.h"
#include "../../Headers/Utilidades/Tablas.h"
#include "../../Headers/Utilidades/rlutil.h"

using namespace std;

// ==========================================
// REGISTRAR PAGO (Flujo de Caja)
// ==========================================
bool registrarPagoParaPedido(ArchivoPagos& archivoPagos, Pedido& pedido) {

    // Encabezado visual del paso actual
    rlutil::setColor(PaletaCafe::CREMA);
    cout << "   >>> DETALLE DEL PAGO" << endl;
    rlutil::setColor(PaletaCafe::BASE);
    cout << "   ----------------------------------------" << endl;

    // Mostrar monto grande y claro
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "   TOTAL A COBRAR: ";
    rlutil::setColor(PaletaCafe::EXITO); // Verde para el dinero
    cout << "$ " << fixed << setprecision(2) << pedido.getTotal() << endl;
    restaurarColor();

    cout << endl;
    rlutil::setColor(PaletaCafe::BASE);
    cout << "   MEDIOS DE PAGO DISPONIBLES:" << endl;
    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "   1. Efectivo" << endl;
    cout << "   2. Tarjeta de Debito/Credito" << endl;
    cout << "   3. Cuenta DNI / Transferencia" << endl;
    cout << endl;

    int medioPago = ingresarEntero("   >>> Seleccione medio de pago (1-3): ");

    while (medioPago < 1 || medioPago > 3) {
        imprimirMensajeError("Opcion invalida. Intente nuevamente.");
        medioPago = ingresarEntero("   >>> Seleccione medio de pago (1-3): ");
    }

    // Creación del objeto Pago
    Pagos pago;
    int nuevoId = archivoPagos.contarRegistros() + 1;

    pago.setIdPago(nuevoId);
    pago.setIdPedido(pedido.getIdPedido());
    pago.setMontoPagado(pedido.getTotal());
    pago.setMetodoPago(medioPago);

    // Asignamos fecha actual por defecto
    Fecha hoy;
    pago.setFechaPago(hoy);

    // Guardado
    if (archivoPagos.grabarRegistro(pago)) {
        return true;
    } else {
        return false;
    }
}

// ==========================================
// VISUALIZAR PAGO (Estilo Ticket)
// ==========================================
void mostrarPagoDePedido(ArchivoPagos& archivoPagos, int idPedido) {
    int cantidad = archivoPagos.contarRegistros();
    int pos = -1;

    // Busqueda secuencial del pago asociado al pedido
    for(int i=0; i<cantidad; i++) {
        Pagos p = archivoPagos.leerRegistro(i);
        if (p.getIdPedido() == idPedido) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << endl;
        rlutil::setColor(PaletaCafe::ADVERTENCIA);
        cout << "   [!] ESTE PEDIDO FIGURA COMO IMPAGO O PENDIENTE." << endl;
        restaurarColor();
        return;
    }

    Pagos p = archivoPagos.leerRegistro(pos);

    // Diseño tipo "Ticket" elegante
    cout << endl;
    rlutil::setColor(PaletaCafe::BASE);
    cout << "   .--------------------------------------." << endl;
    cout << "   |          COMPROBANTE DE PAGO         |" << endl;
    cout << "   +--------------------------------------+" << endl;

    rlutil::setColor(PaletaCafe::ESPUMA);
    cout << "   | ID Pago:     " << left << setw(23) << p.getIdPago() << " |" << endl;

    string metodoStr;
    switch(p.getMetodoPago()){
        case 1: metodoStr = "Efectivo"; break;
        case 2: metodoStr = "Tarjeta"; break;
        case 3: metodoStr = "Transferencia"; break;
        default: metodoStr = "Otro"; break;
    }
    cout << "   | Metodo:      " << left << setw(23) << metodoStr << " |" << endl;

    // Formateo de fecha
    char bufferFecha[20];
    sprintf(bufferFecha, "%02d/%02d/%d", p.getFechaPago().getDia(), p.getFechaPago().getMes(), p.getFechaPago().getAnio());
    cout << "   | Fecha:       " << left << setw(23) << bufferFecha << " |" << endl;

    cout << "   |                                      |" << endl;
    rlutil::setColor(PaletaCafe::EXITO);
    cout << "   | TOTAL PAGADO: $ " << left << setw(21) << fixed << setprecision(2) << p.getMontoPagado() << "|" << endl;

    rlutil::setColor(PaletaCafe::BASE);
    cout << "   '--------------------------------------'" << endl;
    restaurarColor();
}
