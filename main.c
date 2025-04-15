#include <stdio.h>
#include "menu.h"
#include "Funciones.h"

int main(void){
   
    int opcion,aux;
    char *nameaux;
    float pagoTotal;
    Articulo *miArticulo;
    Cola *cola;
    cola = crearCola();
    miArticulo = crearArticulo();
    Usuario *usuario;
    usuario = crearUsuario();
    char menu[]= "\n1)Imprimir \n2)Añadir al carrito \n3)Ver mi carrito \n4)Editar Pedido\n5)Pagar\n6)Mi cuenta\n";
    
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
                if(!colaVacia(*cola)){
                    listar(*cola);
                    printf("Que Articulo desea eliminar?: ");
                    scanf("%d",&aux);
                    nameaux = borrarArticulo(cola,&aux);
                    printf("El articulo:  %s fue eliminado",nameaux);
                }else{
                    printf("\nNo hay articulos en el carrito\n");
                }
                    

                
                break;
            case 5: 
                if(!colaVacia(*cola)){
                    pagoTotal = pagar(cola);
                    printf("El total es de $%.2f",pagoTotal);
                    if(usuario->saldo < pagoTotal) printf("\nSaldo Insuficiente\n");
                    else{
                        printf("\nConfirme su pago: Presione 0 para cancelar y 1 para confirmar\n");
                        scanf("%d",&aux);
                        if(aux){
                            ViajeEmpleado();
                            usuario->saldo-=pagoTotal;
                            printf("\nSaldo actual: $%.2f\n",pagoTotal);

                        }
                    }
                }else{
                    printf("\nNo hay articulos en el carrito\n");
                }
                break;
            case 6:
                imprimirDatos(*usuario);
                break;
            case 7:
                //por ahora aqui pondre las funciones para liberar la momoria.
                //liberarClase(miClase);
                //liberarCiudadDatos(miCiudad);
                liberarCola(cola);
                printf("Memoria liberada. Saliendo del programa.\n");
                break;

            default:
                printf("Opcion no valida, intente de nuevo\n");
                break;
        }
    }while(opcion !=7);
    return 0;
}
