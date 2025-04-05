#include <stdio.h>
#include "menu.h"

int main(void){
    int opcion;
    Articulo *miArticulo;
    Cola *cola;
    cola = crearCola();
    miArticulo = crearArticulo;
    char menu[] = {"1)Imprimir", "2)Realizar pedido", "3)Imprimir", "4)Imprimir"};
 
    do{
        opcion = mostrar_menu(menu,4);
        switch(opcion){
            case 1:
                break;
            case 2:
                
                break;
            case 3:
                break;        
        }
    }while(opcion !=4);
    return 0;
}
