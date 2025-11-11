#include <iostream>
#include "../Headers/Entities/Fecha.h"


using namespace std;

int main() {
    system("cls");
    cout << "========== TEST DE SOBRECARGA DE OPERADORES (CLASE FECHA) ==========" << endl;

    /// Creo tres fechas de prueba
    Fecha f1(5, 3, 2025);
    Fecha f2(10, 3, 2025);
    Fecha f3(5, 3, 2025);

    cout << "Fechas de prueba:" << endl;
    cout << "f1: ";
    f1.Mostrar();
    cout << "f2: ";
    f2.Mostrar();
    cout << "f3: ";
    f3.Mostrar();
    cout << "--------------------------------------------------------------------" << endl;

    /// Pruebo igualdad (==)
    cout << "f1 == f3 ? ";
    if (f1 == f3) cout << "Verdadero" << endl;
    else cout << "Falso" << endl;

    /// Pruebo desigualdad (!=)
    cout << "f1 != f2 ? ";
    if (f1 != f2) cout << "Verdadero" << endl;
    else cout << "Falso" << endl;

    /// Pruebo menor (<)
    cout << "f1 < f2 ? ";
    if (f1 < f2) cout << "Verdadero" << endl;
    else cout << "Falso" << endl;

    /// Pruebo mayor (>)
    cout << "f2 > f1 ? ";
    if (f2 > f1) cout << "Verdadero" << endl;
    else cout << "Falso" << endl;

    /// Pruebo menor o igual (<=)
    cout << "f1 <= f3 ? ";
    if (f1 <= f3) cout << "Verdadero" << endl;
    else cout << "Falso" << endl;

    /// Pruebo mayor o igual (>=)
    cout << "f2 >= f1 ? ";
    if (f2 >= f1) cout << "Verdadero" << endl;
    else cout << "Falso" << endl;

    cout << "--------------------------------------------------------------------" << endl;
    cout << "Fin del test. Si todos los resultados son correctos, las sobrecargas" << endl;
    cout << "funcionan perfectamente y pueden usarse en los reportes." << endl;

    cout << endl;
    system("pause");
    return 0;
}
