#include <stdio.h>
#include "funciones.h"

int main(void){
    
    int opcion,aux;
    char *nameaux;
    float pagoTotal;
    Articulo *miArticulo = crearArticulo();
    Cola *cola = crearCola();
    Usuario *usuario;
    usuario = miCuenta(usuario);
    char menu[] = "\n---- MENÚ PRINCIPAL ----\n1) Información personal\n2) Explorar\n3) Buscar productos\n4) Mi carrito\n5) Salir\nIngrese opción: ";
    do{
        printf("%s", menu);
        scanf("%d", &opcion);
        switch(opcion){
            case 1: //Información personal
                imprimirUsuario(usuario);
                break;
            case 2: //Explorar
                miArticulo = crearArticulo();
                explorar(cola);
                break;
            case 3: //Buscar productos
                buscarArticulo(cola);
                break;
            case 4: //Mi carrito
                miCarrito(cola, usuario);
                break;
        }
    }while(opcion != 5);
    liberarCola(cola);
    printf("\n!Gracias por usar SellTrack!\n");
    return 0;
}