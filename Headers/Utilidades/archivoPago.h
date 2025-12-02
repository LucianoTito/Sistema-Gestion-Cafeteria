#pragma once

#include "../Entities/Pedido.h"
#include "../Entities/Pagos.h"
#include "../Persistence/ArchivoPagos.h"

// Funciones auxiliares para centralizar la gestión de pagos.
bool registrarPagoParaPedido(ArchivoPagos& arcPagos, const Pedido& pedido);
bool mostrarPagoDePedido(ArchivoPagos& arcPagos, int idPedido);
