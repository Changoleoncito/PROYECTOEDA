#include <stdio.h>
#include "funciones.h"

int main(void){
    
    int opcion,aux;
    char *nameaux;
    float pagoTotal;
    Articulo *miArticulo;
    Cola *cola;
    cola = crearCola();
    miArticulo = crearArticulo();
    Usuario *usuario;
    usuario = miCuenta(usuario);
    char menu[] = "\n---- MENÚ PRINCIPAL ----\n1) Información personal\n2) Explorar\n3) Buscar productos\n4) Mi carrito\n5) Rastrear pedido\n6) Salir\nIngrese opción: ";
    do{
        printf("%s", menu);
        scanf("%d", &opcion);
        switch(opcion){
            case 1: //Información personal
                imprimirUsuario(usuario);
                break;
            case 2: //Explorar
                miArticulo = crearArticulo();
                capturarArticulo(miArticulo);
                insertar(cola, miArticulo);
                break;
            case 3: //Buscar productos
                listar(*cola);
                break;
            case 4: //Mi carrito
                if(!colaVacia(*cola)){
                    listar(*cola);
                    printf("Que Articulo desea eliminar?: ");
                    scanf("%d", &aux);
                    nameaux = borrarArticulo(cola, &aux);
                    printf("El articulo:  %s fue eliminado", nameaux);
                }else{
                    printf("\nNo hay articulos en el carrito\n");
                }
                break;
            case 5: //Rastrear pedido
                if(!colaVacia(*cola)){
                    pagoTotal = pagar(cola);
                    printf("El total es de $%.2f", pagoTotal);
                    if(usuario->saldo < pagoTotal) printf("\nSaldo Insuficiente\n");
                    else{
                        printf("\nConfirme su pago: Presione 0 para cancelar y 1 para confirmar\n");
                        scanf("%d", &aux);
                        if(aux){
                            usuario->saldo -= pagoTotal;
                            printf("\nSaldo actual: $%.2f\n", pagoTotal);
                        }
                    }
                }else{
                    printf("\nNo hay articulos en el carrito\n");
                }
                break;
        }
    }while(opcion != 6);
    //liberarClase(miClase);
    //liberarCiudadDatos(miCiudad);
    liberarCola(cola);
    printf("Gracias por usar SellTrack\n");
    return 0;
}