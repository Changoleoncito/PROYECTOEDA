#include <stdlib.h>
#include <stdio.h>
#include "Funciones.h"
#include <time.h>
#include<string.h>
#define TAMANO 4 
#define TAMANO_CALLE 30
Articulo *crearArticulo(){
    Articulo *miArticulo;
    miArticulo = (Articulo *)calloc(1,sizeof(Articulo));
    miArticulo->marca = (char *)calloc(30,sizeof(char));
    miArticulo->nombre = (char *)calloc(30,sizeof(char));

    if (miArticulo->marca==NULL){
        printf("Error: Espacio insuficiente...");
        exit(0);
    }
    if (miArticulo->nombre==NULL){
        printf("Error: Espacio insuficiente...");
        exit(0);
    }
    if (miArticulo==NULL){
        printf("Error: Espacio insuficiente...");
        exit(0);
    }
    return miArticulo;
}
void listarArticulos(int tipo,Articulo *dispArticulos){
    char ruta[6][MAX_TEXTO]= {"./comida.csv","./belleza.csv","./herramientas.csv","./ropa.csv","./juguetes.csv","./instrumentos.csv"};
    tipo--;
    printf("%s",ruta[tipo]);// esta linea era para debuguear algo
    FILE *archivo = fopen(ruta[tipo], "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo");
        exit(0);
    }

    char linea[MAX_LONGITUD];
    //printf("\nNOMBRE \tPRECIO \tOTROS");
    int i=0;
    while(fgets(linea,sizeof(linea),archivo)){
        linea[strcspn(linea,"\n")] = '\0'; // esta parte sirve para eliminar los saltos de linea;
        if(i==0){
            i++;
            continue; // esto es para no tomar en cuenta el inicio del documento;
        }
        if(i == 1)printf("\n");
        char *fnombre = strtok(linea, ",");
        char *fmarca = strtok(NULL,",");
        char *precio = strtok(NULL,",");
        char *stock = strtok (NULL, ",");

        float fprecio = atof(precio);
        int fstock = atoi (stock);

        dispArticulos[(i-1)].nombre = strdup(fnombre);
        dispArticulos[(i-1)].marca = strdup(fmarca);
        dispArticulos[(i-1)].precio = fprecio;
        dispArticulos[(i-1)].cantidad = fstock;
        printf("%-3d. %-30s %-20s %-9.2f\n",i,fnombre,fmarca,fprecio);
        i++;
    }
    fclose(archivo);
}
void capturarArticulo(Articulo *miArticulo){
    int tipo;
    int cantidad;
    int aux;
    //Uso del arreglo para acceder a un producto
    Articulo *dispArticulos;

    int n=20;
    dispArticulos = (Articulo *)calloc(n,sizeof(Articulo));

    printf("Que tipo de articulo desea?\n 1.Comida 2.Belleza 3.Herraminetas 4.Ropa 5.Juguetes 6.Instrumentos\n");
    scanf("%d",&tipo);
    printf("Los siguientes Articulos se encuentran disponibles: ");
    listarArticulos(tipo,dispArticulos);

    printf("¿Que articulo va a seleccionar?(Presione 0 para cancelar)\n");
    scanf("%d",&aux);
    if(aux != 0){
        miArticulo->nombre = dispArticulos[aux-1].nombre;
        miArticulo->marca = dispArticulos[aux-1].marca;
        miArticulo->precio = dispArticulos[aux-1].precio;
        printf("¿cuantos quiere añadir a su carrito?: ");
        scanf("%d",&cantidad);
        while(cantidad > dispArticulos->cantidad){
            printf("No hay suficientes Articulos, selecciona una menor cantidad: ");
            scanf("%d",&cantidad);
        }
        miArticulo->cantidad = cantidad;
        miArticulo->visible = 1;
    }


}
int colaVacia(Cola cola){
    return cola.h== NULL ;
}
Cola *crearCola(){
    Cola *nuevaCola;
    //CREACIÓN DINÁMICA DE LA ESTRUCTURA COLA
    nuevaCola=(Cola *)malloc( 1*sizeof(Cola ));
    if (nuevaCola==NULL){
        printf("Error: Espacio insuficiente...");
        exit(0);
    }
    //INICIALIZANDO h y t
    nuevaCola->h= NULL;
    nuevaCola->t= NULL;
    return  nuevaCola ;
}
void insertar(Cola *cola,Articulo *miarticulo){
    Nodo *nuevoNodo;
    //CREA EL NODO
    nuevoNodo=(Nodo *)malloc(sizeof( Nodo));
    if (nuevoNodo == NULL){
       printf("Error: memoria insuficiente...");
       exit(0);
    }
    //1.ASIGNA VALORES AL NODO
     nuevoNodo->miArticulo = miarticulo;
     nuevoNodo->sig= NULL;
    //2.INSERTA EL NODO EN LA COLA
    if (colaVacia(*cola))
        cola->h= cola->t= nuevoNodo;
    else {
        cola ->t->sig =  nuevoNodo;
        cola->t = nuevoNodo;
    }
}
void listar(Cola cola){
    Nodo *q;
    if (colaVacia(cola))
        printf("\nNo hay datos en la fila...\n");
    else{
        printf("\t20Mi carrito: ");
        int i = 1;
        for(q= cola.h; q!= NULL ; q= q->sig){
            if(q->miArticulo->visible){
                printf("\nDatos del Articulo [%d]:\n Nombre: %s\nMarca: %s\n Precio:%.2f \n Cantidad: %i\n",i,q->miArticulo->nombre,q->miArticulo->marca,q->miArticulo->precio,q->miArticulo->cantidad);
                i++;
                }
            }
        }
    printf("\n");
}
char *borrarArticulo(Cola *cola,int *n){
    char *dato;
    Nodo *q =cola->h;
    //Nodo *aux;
    if (!colaVacia(*cola)){
        if(cola->h==cola->t)
            cola->h=cola->t= NULL;
        else{
            for(int i=0;i<(*n)-1;i++)q=q->sig;
            q->miArticulo->visible = 0;
        }
            //cola->h = cola->h->sig;

        dato =  q->miArticulo->nombre; //EXTRAE LA INFORMACIÓN
        //free(q); //LIBERA LA MEMORIA <- Esta linea no va, si liberas q, borras la informacion, y esta funcion solo oculta los articulos del carrito, pero no los borra, eso es en otra funcion
    }
    else
        printf("\nNo hay datos registrados...");
    return dato;
}
float pagar(Cola *cola){
    float total = 0;
    Nodo *q;
    q = cola->h;
    for(q;q!= NULL;q = q->sig){
        if(q->miArticulo->visible){
            total+=((q->miArticulo->precio)*(q->miArticulo->cantidad));
        }
        
    }
    return total;
}
PILA *crearPila(int max){
    PILA *nuevaPila;
    //1. crear la pila y el arreglo de la pila
    nuevaPila = (PILA *)malloc(1*sizeof(PILA)); //CREA LA ESTRUCTURA PILA CON TODOS SUS ELEMENTOS
    nuevaPila->arr= (char **)calloc(max , sizeof(char*));//CREANDO EL ARREGLO DE LA PILA
    //2. INICIALIZA VALORES
    nuevaPila->tope = -1;
    nuevaPila->max = max;
    return nuevaPila;
}
void listarPILA(PILA pila){
    int i;
    for (i= pila.tope; i >= 0; i--)
        printf(" %s\n ",pila.arr[i]);
}
void ViajeEmpleado(){
    srand(time(NULL));  //LLAMARLA EN EL MAIN PARA QUE SEA GLOBAL
    int opcion,i,contador,yaesta;
    contador=0;
    PILA *nuevapila;
    nuevapila=crearPila(4);
    int repetidos[4];
    char str[TAMANO][TAMANO_CALLE] = {"CALLE A", "CALLE B", "CALLE C", "CALLE D"};
    char *str1[TAMANO]={"Insurgentes", "Reforma","Pedregal","Tasquena"};
    printf("cual es su dirreccion\n1)Insurgentes\n2)Reforma\n3)Pedregal\n4)Tasquena\n");
    scanf("%d",&opcion);
        printf("preparando viaje...\n");
        printf("Viaje a:\n");
        while(contador<4){
            i=rand()%4;
            yaesta=0;
            for(int j=0;j<contador;j++){
                if(repetidos[j]==i){
                    yaesta=1;
                    break;
                }
            }
            if(yaesta==0){
                repetidos[contador]=i;
                nuevapila->tope++;
                nuevapila->arr[nuevapila->tope]=str[i];
                printf("%s\n", str[i]);
                contador++;
            }
        }
        printf("Llego el pedido a %s\n",str1[opcion-1]);
        printf("Repartidor de regreso...\n");
        listarPILA(*nuevapila);
        printf("\n");
        printf("Regreso");
        
 }
//funciones para liberar la memoria.
// estas se utilizaran al momento de salir el programa o se vera su uso cuando veamos como queda el main.


void liberarArticulo(Articulo *articulo) {
    if (articulo == NULL) return;

    free(articulo->nombre);
    free(articulo->marca);
    free(articulo);
}

void liberarNodo(Nodo *nodo) {
    if (nodo == NULL) return;

    liberarArticulo(nodo->miArticulo);
    free(nodo);
}

void liberarCola(Cola *cola) {
    if (cola == NULL) return;

    Nodo *q = cola->h;  
    Nodo *sig;

    while (q != NULL) {
        sig = q->sig;  
        q->sig = NULL;  
        liberarNodo(q);  
        q = sig; 
    }
    free(cola);
}

Usuario* crearUsuario(){
    Usuario *usuario;
    srand(time(0));
    usuario = (Usuario *)calloc(1,sizeof(Usuario));
    for(int i=0;i<10;i++){
        usuario->nombre[i] = rand() % (26) + 'a';   // para generar las letras 
    }
    
   usuario->saldo = rand() % 2000;
    usuario->correo = (char *)calloc(10,sizeof(char));
    for(int i=0;i<10;i++)usuario->correo[i] = rand() % (26) + 'a'; 
    usuario->ID = rand() %  10000;
    return usuario;
}

void imprimirDatos(Usuario usuario){
    printf("\nNombre: %s\n",usuario.nombre);
    printf("\nCorreo: %s",usuario.correo);
    if(usuario.ID % 2 == 0)printf("@gmail.com\n");
    else printf("@outlook.com\n");
    printf("\nID: %d\n",usuario.ID);
    printf("\nSaldo: %.2f\n",usuario.saldo);
    printf("\nPedidos: %d\n",usuario.pedidos);
    
}
