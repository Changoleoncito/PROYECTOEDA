#include <stdlib.h>
#include <stdio.h>
#include "Funciones.h"
#include <time.h>
#include<string.h>

Clase *crearclase(){
    Clase *clasenueva;
    clasenueva=(Clase*)malloc(sizeof(Clase));
    if(clasenueva==NULL){
        printf("No se pudo asigar memoria para clase");
        exit(1);
    }
    clasenueva->belleza=( belleza*)calloc(1,sizeof(belleza));
    if(clasenueva->belleza==NULL){
        printf("No se pudo asigar memoria para belleza");
        exit(1);
    }
    clasenueva->belleza->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->belleza->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->belleza->precio=(float*)calloc(1,sizeof(float));
    clasenueva->belleza->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->belleza->nombre==NULL|| clasenueva->belleza->marca==NULL||clasenueva->belleza->precio==NULL||clasenueva->belleza->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de belleza");
        exit(1);
    }

    clasenueva->comida=(comida*)calloc(1,sizeof(comida));
    if(clasenueva->comida==NULL){
        printf("No se pudo asigar memoria para comida");
        exit(1);
    }
    clasenueva->comida->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->comida->bebida=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->comida->cantidad=(float*)calloc(1,sizeof(float));
    clasenueva->comida->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->comida->bebida==NULL|| clasenueva->comida->cantidad==NULL||clasenueva->comida->nombre==NULL||clasenueva->comida->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de comida");
        exit(1);
    }
    clasenueva->herramientas=(herramientas*)calloc(1,sizeof(herramientas));
    if(clasenueva->herramientas==NULL){
        printf("No se pudo asignar memoria para herramientas");
    }
    clasenueva->herramientas->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->herramientas->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->herramientas->precio=(float*)calloc(1,sizeof(float));
    clasenueva->herramientas->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->herramientas->nombre==NULL|| clasenueva->herramientas->marca==NULL||clasenueva->herramientas->precio==NULL||clasenueva->herramientas->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de herramienta");
        exit(1);
    }
    clasenueva->instrumentos=(instrumentos*)calloc(1,sizeof(instrumentos));
    if(clasenueva->instrumentos==NULL){
        printf("No se pudo asigar memoria para instrumentos");
        exit(1);
    }
    clasenueva->instrumentos->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->instrumentos->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->instrumentos->precio=(float*)calloc(1,sizeof(float));
    clasenueva->instrumentos->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->instrumentos->nombre==NULL|| clasenueva->instrumentos->marca==NULL||clasenueva->instrumentos->precio==NULL||clasenueva->instrumentos->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de herramienta");
        exit(1);
    }
    clasenueva->juguetes=(juguetes*)calloc(1,sizeof(juguetes));
    if(clasenueva->juguetes==NULL){
        printf("No se pudo asigar memoria para juguetes");
        exit(1);
    }
    clasenueva->juguetes->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->juguetes->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->juguetes->precio=(float*)calloc(1,sizeof(float));
    clasenueva->juguetes->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->juguetes->nombre==NULL|| clasenueva->juguetes->marca==NULL||clasenueva->juguetes->precio==NULL||clasenueva->juguetes->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de juguetes");
        exit(1);
    }
    clasenueva->ropa=(ropa*)calloc(1,sizeof(ropa));
    if(clasenueva->ropa==NULL){
        printf("No se pudo asigar memoria para ropa");
        exit(1);
    }
    clasenueva->ropa->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->ropa->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->ropa->precio=(float*)calloc(1,sizeof(float));
    clasenueva->ropa->sobrante=(int*)calloc(1,sizeof(int));
    if(clasenueva->ropa->nombre==NULL|| clasenueva->ropa->marca==NULL||clasenueva->ropa->precio==NULL||clasenueva->ropa->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de juguetes");
        exit(1);
    }
    return clasenueva;
}
CiudadDatos *crearCiudadDatos(){
    CiudadDatos *nuevaCiudadDatos;
    nuevaCiudadDatos=(CiudadDatos*)malloc(sizeof(CiudadDatos));
    if(nuevaCiudadDatos==NULL){
        printf("No se pudo asignar memoria a nuevaciudaddatos");
        exit(1);
    }
    nuevaCiudadDatos->calle=(char*)calloc(MAX_TEXTO,sizeof(char));
    if(nuevaCiudadDatos->calle==NULL){
        printf("No se pudo asignar memoria a calle");
        exit(1);
    }
    nuevaCiudadDatos->ciudad=(char*)calloc(MAX_TEXTO,sizeof(char));
    if(nuevaCiudadDatos->ciudad==NULL){
        printf("No se pudo asignar memoria a ciudad");
        exit(1);
    }
    nuevaCiudadDatos->dinero=(float*)calloc(1,sizeof(float));
    if(nuevaCiudadDatos->dinero==NULL){
        printf("No se pudo asignar memoria a dinero");
        exit(1);
    }
    nuevaCiudadDatos->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    if(nuevaCiudadDatos->nombre==NULL){
        printf("No se pudo asignar memoria a nombre");
        exit(1);
    }
    nuevaCiudadDatos->producto=(Clase*)calloc(1,sizeof(Clase));
    if(nuevaCiudadDatos->producto==NULL){
        printf("No se pudo asignar memoria a producto");
        exit(1);
    }
    return nuevaCiudadDatos;

}
    
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
//funciones para liberar la memoria.
// estas se utilizaran al momento de salir el programa o se vera su uso cuando veamos como queda el main.
void liberarClase(Clase *clase) {
    if (clase == NULL) return;

    // Libera la memoria de belleza
    if (clase->belleza != NULL) {
        free(clase->belleza->nombre);
        free(clase->belleza->marca);
        free(clase->belleza->precio);
        free(clase->belleza->sobrante);
        free(clase->belleza);
    }

    // Libera la memoria de comida
    if (clase->comida != NULL) {
        free(clase->comida->nombre);
        free(clase->comida->bebida);
        free(clase->comida->cantidad);
        free(clase->comida->sobrante);
        free(clase->comida);
    }

    // Libera la memoria de herramientas
    if (clase->herramientas != NULL) {
        free(clase->herramientas->nombre);
        free(clase->herramientas->marca);
        free(clase->herramientas->precio);
        free(clase->herramientas->sobrante);
        free(clase->herramientas);
    }

    // Libera la memoria de instrumentos
    if (clase->instrumentos != NULL) {
        free(clase->instrumentos->nombre);
        free(clase->instrumentos->marca);
        free(clase->instrumentos->precio);
        free(clase->instrumentos->sobrante);
        free(clase->instrumentos);
    }

    // Libera la memoria de juguetes
    if (clase->juguetes != NULL) {
        free(clase->juguetes->nombre);
        free(clase->juguetes->marca);
        free(clase->juguetes->precio);
        free(clase->juguetes->sobrante);
        free(clase->juguetes);
    }

    // Libera la memoria de ropa
    if (clase->ropa != NULL) {
        free(clase->ropa->nombre);
        free(clase->ropa->marca);
        free(clase->ropa->precio);
        free(clase->ropa->sobrante);
        free(clase->ropa);
    }

    // Libera la estructura Clase
    free(clase);
}

void liberarCiudadDatos(CiudadDatos *ciudad) {
    if (ciudad == NULL) return;

    free(ciudad->nombre);
    free(ciudad->ciudad);
    free(ciudad->calle);
    free(ciudad->dinero);

    // Libera la estructura Clase dentro de CiudadDatos
    liberarClase(ciudad->producto);

    // Libera la estructura CiudadDatos
    free(ciudad);
}

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
