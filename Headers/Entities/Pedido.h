#pragma once
#include "Fecha.h"


class Pedido {
private:
    int _idPedido;
    int _idCliente;
    int _idEmpleado;
    int _nroMesa;
    Fecha _fecha;
    float _subtotal;
    int _porcentajeDescuento;
    bool _eliminado;

public:
    //Constructor
    Pedido(int idPedido = 0,
           int idCliente = 0,
           int idEmpleado = 0,
           int nroMesa = 0,
           Fecha fecha = Fecha(),
           float subtotal = 0.0f,
           int porcentajeDesc = 0,
           bool eliminado = false);

    //  Getters
    int getIdPedido() const;
    int getIdCliente() const;
    int getIdEmpleado() const;
    int getNroMesa() const;
    Fecha getFecha() const;
    float getSubtotal() const;
    int getPorcentajeDescuento() const;
    float getTotal() const;
    bool getEliminado() const;

    // Setters
    void setNroMesa(int nro, bool mostrarAdvertencia = true);
    void setFecha(Fecha fecha);
    void setSubtotal(float subtotal);
    void setPorcentajeDescuento(int porcentaje);
    void setEliminado(bool eliminado);

    //Métodos
    void Cargar(int idPedido, int idCliente, int idEmpleado);
    void Mostrar();
};
