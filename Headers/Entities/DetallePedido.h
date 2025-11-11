#pragma once

class DetallePedido {

private:
    int _idDetalle;
    int _idPedido;
    int _idProducto;
    int _cantidad;
    float _precioUnitario;

public:
    // Constructor
    DetallePedido(int idDetalle = 0,
                  int idPedido = 0,
                  int idProducto = 0,
                  int cantidad = 0,
                  float precioUnitario = 0.0f);

    // Getters
    int getIdDetalle();
    int getIdPedido();
    int getIdProducto();
    int getCantidad();
    float getPrecioUnitario();

   //Setters
    void setCantidad(int cantidad);
    void setPrecioUnitario(float precioUnitario);

    // Métodos
    void Cargar(int idDetalle, int idPedido, int idProducto, int cantidad, float precioUnitario);
    void Mostrar();
};
