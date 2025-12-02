#include <iostream>

#include "../../Headers/Utilidades/archivoPago.h"

using namespace std;

// Genera y persiste un pago asociado al pedido recibido.
bool registrarPagoParaPedido(ArchivoPagos& arcPagos, const Pedido& pedido){
    Pagos regPago;

    // Calculo del ID autoincremental para el pago.
    int idPagoNuevo = arcPagos.contarRegistros() + 1;

    // El monto se calcula a partir del total del pedido.
    float montoAPagar = pedido.getTotal();

    cout << endl << "----------REGISTRAR PAGO ----------"<<endl;
    regPago.Cargar(idPagoNuevo, pedido.getIdPedido(), montoAPagar, pedido.getFecha());

    // Persisto el pago y devuelvo el resultado para que el llamador pueda deshacer si falla.
    bool exitoPago = arcPagos.grabarRegistro(regPago);
    if (!exitoPago){
        cout << "ERROR! El pedido se grabo, pero no se pudo registrar el Pago"<<endl;
        return false;
    }

    return true;
}

// Busca y muestra el pago asociado a un pedido. Informa si no existe.
bool mostrarPagoDePedido(ArchivoPagos& arcPagos, int idPedido){
    int cantidadPagos = arcPagos.contarRegistros();

    for (int i=0; i<cantidadPagos; i++){
        Pagos regPagoLeido = arcPagos.leerRegistro(i);

        //Busco el pago que coincida con el ID del pedido
        if (regPagoLeido.getIdPedido() == idPedido){
            regPagoLeido.Mostrar(); //Mostrar los datos del pago
            return true;
        }
    }

    cout << "Este pedido no tiene un pago asociado. "<<endl;
    return false;
}
