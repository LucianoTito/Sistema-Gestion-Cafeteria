#include<iostream>
#include <string>
#include <cstdio>
#include "../../Headers/Persistence/ArchivoPedido.h"
#include "../../Headers/Entities/Pedido.h"

using namespace std;


//Constructor

ArchivoPedido::ArchivoPedido(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}

//Grabar registro

bool ArchivoPedido::grabarRegistro(Pedido reg){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "ab");

if(pArchivo == nullptr){

    cout<< "Error al abrir el archivo para grabar  Pedido."<<endl;

    return false;

}

bool escribio = fwrite(&reg, sizeof(Pedido), 1, pArchivo);

fclose(pArchivo);

return escribio;



}

//Contar registros

int ArchivoPedido::contarRegistros(){


FILE *pArchivo = fopen(_nombreArchivo.c_str(),"rb");

if(pArchivo == nullptr){

    return 0;
}
fseek(pArchivo, 0L, SEEK_END);

long tamanioEnBytes = ftell(pArchivo);

    fclose(pArchivo);

    int cantidadRegistros = tamanioEnBytes /sizeof(Pedido);

    return cantidadRegistros;


}

//Leer Registro

Pedido ArchivoPedido::leerRegistro(int posicion){


Pedido reg;



FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");


if(pArchivo == nullptr) {

    return reg;
}

fseek(pArchivo, posicion *sizeof(Pedido), SEEK_SET);

fread(&reg, sizeof(Pedido), 1,pArchivo);

fclose(pArchivo);

return reg;


}

//Buscar registro

int ArchivoPedido::buscarRegistro(int idPedido){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return -1;
}

Pedido regLeido;

int posicionActual=0;

while(fread(&regLeido, sizeof(Pedido), 1, pArchivo)==1){

    if (regLeido.getIdPedido() == idPedido){

        fclose(pArchivo);

        return posicionActual;
    }
    posicionActual++;
}

fclose(pArchivo);

return -1;

}

//Modificar registro

bool ArchivoPedido::modificarRegistro(Pedido reg, int posicion){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para modificar Pedido."<<endl;

    return false;
}

fseek(pArchivo, posicion * sizeof(Pedido), SEEK_SET);

bool escribio = fwrite(&reg, sizeof(Pedido), 1, pArchivo);

fclose(pArchivo);

return escribio;

}

//Listar

void ArchivoPedido::listar(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    cout<< "Error al abrir el archivo para listar Pedido."<<endl;

    return;
}

Pedido regLeido;

cout<<endl<< "---------- LISTADO DE PEDIDOS ----------"<<endl;

while(fread(&regLeido, sizeof(Pedido), 1, pArchivo)==1){

    if(regLeido.getEliminado()==false){

        regLeido.Mostrar();
    }

}

cout<< "---------- FIN DEL LISTADO ----------"<<endl<<endl;

fclose(pArchivo);

}
