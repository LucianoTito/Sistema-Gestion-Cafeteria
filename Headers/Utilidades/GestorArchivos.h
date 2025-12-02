#pragma once

// Funciones generales de archivos
bool existeArchivo(const char* nombreArchivo);
bool copiarArchivoBinario(const char* origen, const char* destino);

// Funciones especificas de exportacion a CSV
bool exportarClientesCSV(const char* csvDestino);
bool exportarProductosCSV(const char* csvDestino);
bool exportarEmpleadosCSV(const char* csvDestino);
bool exportarPedidosCSV(const char* csvDestino);
bool exportarDetallesCSV(const char* csvDestino);
bool exportarPagosCSV(const char* csvDestino);
