#include <stdio.h>
#include "menu.h"
#include "Funciones.h"
int main(void){
    int opcion,aux;
    char *nameaux;
    Articulo *miArticulo;
    Cola *cola;
    cola = crearCola();
    miArticulo = crearArticulo();
    char menu[]= "\n1)Imprimir \n2)Realizar pedido \n3)Ver mi carrito \n4)Editar Pedido\n5)Salir\n";

    do{
        printf("%s",menu);
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
                break;
            case 2:
                miArticulo = crearArticulo();
                capturarArticulo(miArticulo);
                insertar(cola,miArticulo);
                break;
            case 3:
                listar(*cola);
                break;
            case 4:
                listar(*cola);
                printf("Que Articulo desea eliminar?: ");
                scanf("%d",&aux);
                nameaux = borrarArticulo(cola,&aux);
                printf("El articulo:  %s fue eliminado",nameaux);
                break;
            default:
                break;
        }
    }while(opcion !=5);
    return 0;
}
