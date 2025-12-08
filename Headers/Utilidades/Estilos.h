#pragma once
#include <string>
#include "rlutil.h" // Asegurate de que rlutil.h esta en la misma carpeta


// Windows define una macro llamada ERROR que choca con nuestra constante.
// La desactivamos aquí para poder usar nuestro propio nombre.
#ifdef ERROR
#undef ERROR
#endif
// ----------------------------

namespace PaletaCafe {
    const int TEXTO = 15;        // Blanco brillante
    const int FONDO = 0;         // Negro
    const int BASE = 6;          // Marrón/Dorado
    const int CREMA = 14;        // Amarillo claro
    const int ESPUMA = 15;       // Blanco
    const int HUMO = 8;          // Gris oscuro
    const int EXITO = 10;        // Verde
    const int ERROR = 12;        // Rojo (Ahora sí funcionará)
    const int ADVERTENCIA = 14;  // Amarillo
    const int OK = 10;           // Alias
}

// Funciones visuales
void configurarConsola();
void restaurarColor();
void limpiarConsola();
void pausarConsola(const std::string& mensaje = "Presione ENTER para continuar...");

void imprimirTituloDecorado(const std::string& titulo, int ancho = 80);
void imprimirSubtituloDecorado(const std::string& subtitulo, int ancho = 80);

// Asegurate que estos nombres coincidan con los que usas en el .cpp
void imprimirMensajeExito(const std::string& mensaje);
void imprimirMensajeAdvertencia(const std::string& mensaje);
void imprimirMensajeError(const std::string& mensaje);

void imprimirPrompt(const std::string& prompt);
void imprimirBannerCafe();
