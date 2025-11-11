#include<iostream>
#include <cstring>
#include <locale.h>

#include "../Headers/UI/menus.h"

using namespace std;

int main(){

//Para que la consola pueda incorporar ñ o tildes
setlocale(LC_ALL, "spanish");

//Intenta forzar la consola a la página de códigos UTF-8
    system("chcp 65001");
    system("cls");

menuPrincipal();

return 0;


}
