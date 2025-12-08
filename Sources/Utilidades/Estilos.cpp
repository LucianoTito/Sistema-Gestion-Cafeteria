#include <iostream>
#include <iomanip>
#include <limits> // Para numeric_limits
#include "../../Headers/Utilidades/Estilos.h"
#include "../../Headers/Utilidades/Tablas.h"

using namespace std;

void configurarConsola() {
    //rlutil::saveDefaultColor();
    // rlutil::setWindowTitle("SISTEMA DE GESTION"); // Comentado por si falla en tu version
    rlutil::setColor(PaletaCafe::TEXTO);
    rlutil::hidecursor();
}

void restaurarColor() {
    rlutil::resetColor();
}

void limpiarConsola() {
    rlutil::cls();
}

void pausarConsola(const string& mensaje) {
    rlutil::setColor(PaletaCafe::CREMA);
    cout << endl << mensaje;
    restaurarColor();

    // Limpieza de buffer segura para evitar saltos
    // Si numeric_limits falla, usa: cin.ignore(1000, '\n');
    if (cin.rdbuf()->in_avail() > 0) {
        cin.ignore(10000, '\n');
    }
    rlutil::anykey("");
}

void imprimirTituloDecorado(const string& titulo, int ancho) {
    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ancho);

    rlutil::setColor(PaletaCafe::ESPUMA);
    int padding = (ancho - static_cast<int>(titulo.size())) / 2;
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << titulo << endl;

    rlutil::setColor(PaletaCafe::BASE);
    lineaDoble(ancho);
    restaurarColor();
}

void imprimirSubtituloDecorado(const string& subtitulo, int ancho) {
    rlutil::setColor(PaletaCafe::CREMA);
    cout << string((ancho - static_cast<int>(subtitulo.size())) / 2, ' ') << subtitulo << endl;
    restaurarColor();
}

void imprimirMensajeExito(const string& mensaje) {
    rlutil::setColor(PaletaCafe::OK);
    cout << ">>> [OK] " << mensaje << endl;
    restaurarColor();
}

void imprimirMensajeAdvertencia(const string& mensaje) {
    rlutil::setColor(PaletaCafe::ADVERTENCIA);
    cout << ">>> [!] " << mensaje << endl;
    restaurarColor();
}

void imprimirMensajeError(const string& mensaje) {
    rlutil::setColor(PaletaCafe::ERROR);
    cout << ">>> [ERROR] " << mensaje << endl;
    restaurarColor();
}

void imprimirPrompt(const string& prompt) {
    rlutil::setColor(PaletaCafe::CREMA);
    cout << prompt;
    restaurarColor();
}

void imprimirBannerCafe() {
    string m = "        ";
    rlutil::setColor(PaletaCafe::HUMO);
    cout << m << "      (  )   (   )  ) " << endl;
    cout << m << "       ) (   )  (  (  " << endl;
    cout << m << "       ( )  (    ) )  " << endl;

    rlutil::setColor(PaletaCafe::BASE);
    cout << m << "      ___________     " << endl;
    cout << m << "     (           )    " << endl;
    cout << m << "     |           |-.  " << endl;
    cout << m << "     |           |  | " << endl;
    cout << m << "     |___________|-'  " << endl;

    restaurarColor();
    cout << endl;
}
