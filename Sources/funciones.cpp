#include<iostream>
using namespace std;


int mostrarMenu(int opcion, char* texto){

 system("cls");

    cout << "------- GESTION DE " << texto <<"--------"<<endl;
    cout << "====================================" <<endl;
    cout << "1. AGREGAR " << texto  <<endl;
    cout << "2. LISTAR PRODUCTOS" <<endl;
    cout << "3. MODIFICAR PRODUCTO "<<endl;
    cout << "4. ELIMINAR PRODUCTO "<<endl;
    cout << "------------------------------------" <<endl;
    cout << "0. VOLVER AL MENU PRINCIPAL" <<endl;
    cout << "====================================" <<endl;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;



    system ("cls");

    return opcion;
}
