#include<iostream>
#include<string>

#include <cstdio>
#include "../../Headers/Entities/Pagos.h"
#include "../../Headers/Persistence/ArchivoPagos.h"

using namespace std;


//Constructor
ArchivoPagos::ArchivoPagos(std::string nombreArchivo){

_nombreArchivo = nombreArchivo;

}

//Grabar registro

bool ArchivoPagos::grabarRegistro(Pagos reg){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "ab");

if (pArchivo == nullptr){

cout<< "Error al abrir el archivo para grabar Pago"<<endl;

return false;

}

bool escribio = fwrite(&reg, sizeof(Pagos), 1, pArchivo);

fclose(pArchivo);

return escribio;

}

//Contar registros

int ArchivoPagos::contarRegistros(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return 0;
}

fseek(pArchivo, 0L, SEEK_END);

long tamanioEnbytes = ftell(pArchivo);

fclose(pArchivo);

int cantidadRegistros = tamanioEnbytes/sizeof(Pagos);

return cantidadRegistros;

}

//Leer registro

Pagos ArchivoPagos::leerRegistro(int posicion){

Pagos reg;

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return reg;

}

fseek(pArchivo, posicion *sizeof(Pagos), SEEK_SET);


fread(&reg, sizeof(Pagos), 1, pArchivo);

fclose(pArchivo);

return reg;

}

//Buscar registro

int ArchivoPagos::buscarRegistro(int idPago){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if(pArchivo == nullptr){

    return -1;
}

Pagos regLeido;
int posicionActual = 0;

while (fread(&regLeido, sizeof(Pagos), 1, pArchivo)==1){

    if(regLeido.getIdPago() == idPago){

        fclose(pArchivo);
        return posicionActual;

    }

    posicionActual++;
}

fclose(pArchivo);
return -1;

}

//Modificar Registro

bool ArchivoPagos::modificarRegistro(Pagos reg, int posicion){

FILE *pArchivo = fopen (_nombreArchivo.c_str(), "rb+");

if (pArchivo == nullptr){

    cout<< "Error al abrir el archivo para modificar Pagos"<<endl;
    return false;

}

fseek (pArchivo, posicion *sizeof(Pagos), SEEK_SET);

bool escribio = fwrite(&reg, sizeof(Pagos), 1, pArchivo);

fclose(pArchivo);

return escribio;
}

//Listar

void ArchivoPagos::listar(){

FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");

if (pArchivo == nullptr){

    cout << "Error al abrir el archivo para listar a Pagos."<<endl;

    return;
    }

    Pagos regLeido;

    cout << "---------- LISTADO DE PAGOS ----------"<<endl;

    while (fread(&regLeido, sizeof (Pagos), 1, pArchivo)==1){

        regLeido.Mostrar();

    }



cout << "---------- FIN DE LISTADO ----------"<<endl<<endl;

fclose(pArchivo);



}
