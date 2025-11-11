#include<iostream>
#include <string>
#include <cstdio>
#include "../../Headers/Persistence/ArchivoDetallePedido.h"
#include "../../Headers/Entities/DetallePedido.h"



using namespace std;

//Constructor

ArchivoDetallePedido::ArchivoDetallePedido(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}

//Grabar registro

bool ArchivoDetallePedido::grabarRegistro(DetallePedido reg){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "ab");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para grabar DetallePedido."<<endl;

    return false;
}

bool escribio = fwrite (&reg, sizeof(DetallePedido), 1, pArchivo);

fclose(pArchivo);

return escribio;


}

//Contar Registros

int ArchivoDetallePedido::contarRegistros(){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb");


if(pArchivo == nullptr){

    return 0;
}

fseek(pArchivo, 0L, SEEK_END);

long tamanioEnBytes = ftell(pArchivo);

fclose(pArchivo);

int cantidadRegistros = tamanioEnBytes/sizeof(DetallePedido);

return cantidadRegistros;

}

//Leer registro

DetallePedido ArchivoDetallePedido::leerRegistro(int posicion){

DetallePedido reg;

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    return reg;
}

fseek(pArchivo, posicion * sizeof(DetallePedido), SEEK_SET);

fread(&reg, sizeof(DetallePedido), 1, pArchivo);

fclose(pArchivo);

return reg;



}


//Buscar registro

int ArchivoDetallePedido::buscarRegistro(int idDetallePedido){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo==nullptr){

    return -1;
}

DetallePedido regLeido;
int posicionActual = 0;


while (fread(&regLeido, sizeof (DetallePedido), 1,pArchivo)== 1){

    if (regLeido.getIdDetalle() == idDetallePedido){

        fclose(pArchivo);

        return posicionActual;
    }
    posicionActual++;
}

fclose(pArchivo);

return -1;

}

//Modificar Registro

bool ArchivoDetallePedido::modificarRegistro(DetallePedido reg, int posicion){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");

if(pArchivo == nullptr){

    cout << "Error al abrir el archivo para modificar DetallePedido."<<endl;

    return false;
}

fseek(pArchivo, posicion * sizeof(DetallePedido),SEEK_SET);

bool escribio = fwrite(&reg, sizeof(DetallePedido),1 ,pArchivo);

fclose(pArchivo);

return escribio;


}

//Listar

void ArchivoDetallePedido::listar(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    cout << "Error al abrir archivo para listar a DetallePedido."<<endl;
    return;
}

DetallePedido regLeido;

cout<<endl<< "---------- LISTADO DE DETALLES PEDIDOS ----------"<<endl;

while(fread(&regLeido, sizeof(DetallePedido), 1, pArchivo)==1){



        regLeido.Mostrar();

}

cout << "---------- FIN DEL LISTADO ----------"<<endl;

fclose(pArchivo);


}
