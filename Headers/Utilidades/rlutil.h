#pragma once
#include <iostream>
#include <string>

// Versión simplificada de rlutil basada en secuencias ANSI para colorear y
// limpiar la consola sin dependencias externas. Se mantiene la interfaz
// clave usada en el proyecto.
namespace rlutil {

enum COLOR {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARKGREY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

inline const char* colorCode(int color) {
    switch (color) {
        case BLACK: return "0";
        case BLUE: return "34";
        case GREEN: return "32";
        case CYAN: return "36";
        case RED: return "31";
        case MAGENTA: return "35";
        case BROWN: return "33";
        case GREY: return "37";
        case DARKGREY: return "90";
        case LIGHTBLUE: return "94";
        case LIGHTGREEN: return "92";
        case LIGHTCYAN: return "96";
        case LIGHTRED: return "91";
        case LIGHTMAGENTA: return "95";
        case YELLOW: return "93";
        case WHITE: return "97";
        default: return "0";
    }
}

inline void setColor(int color) {
    std::cout << "\033[" << colorCode(color) << "m";
}

inline void resetColor() {
    std::cout << "\033[0m";
}

inline void cls() {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

inline void anykey(const std::string& mensaje = "") {
    if (!mensaje.empty()) {
        std::cout << mensaje;
    }
    std::cin.get();
}

inline void hidecursor() {
    std::cout << "\033[?25l";
}

inline void showcursor() {
    std::cout << "\033[?25h";
}

inline void locate(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

} // namespace rlutil
