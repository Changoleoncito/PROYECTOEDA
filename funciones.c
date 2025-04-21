#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "funciones.h"

const char *alcaldias[4] = {"Benito Juárez", "Coyoacan", "Cuauhtémoc", "Miguel Hidalgo"};
const char *calles[6] = {"Calle A", "Calle B", "Calle C", "Calle D", "Calle E", "Calle F"};

// FUNCIONES DE CREACION
Articulo *crearArticulo(){
    Articulo *articulo = (Articulo *)calloc(1, sizeof(Articulo));
    if(articulo == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    articulo->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    articulo->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(articulo->marca == NULL || articulo->nombre == NULL){
        printf("Error: Espacio insuficiente...");
        free(articulo->marca);
        free(articulo->nombre);
        free(articulo);
        exit(1);
    }
    return articulo;
}

// FUNCIONES DE COLA
Cola *crearCola(){
    Cola *nuevaCola;
    nuevaCola = (Cola *)malloc(sizeof(Cola));
    if(nuevaCola == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    nuevaCola->h = NULL;
    nuevaCola->t = NULL;
    return nuevaCola;
}

int miCarrito(Cola *cola, Usuario *usuario){
    int opcion;
    do{
        listar(*cola);
        printf("\n¿Qué desea hacer?\n1) Eliminar producto\n2) Proceder al pago\n3) Regresar\nIngrese opción: ");
        scanf("%d", &opcion);
        switch(opcion){
        case 1:
            if(!colaVacia(*cola)){
                listar(*cola);
                printf("Que articulo desea eliminar?: ");
                scanf("%d", &opcion);
                char *nameaux = borrarArticulo(cola, &opcion);
                printf("%s elimidado del carrito.", nameaux);
            }else{
                printf("\nNo hay articulos en el carrito.\n");
            }
            break;
        case 2:
            if(!colaVacia(*cola)){
                float pagoTotal = comprar(cola);
                printf("\nEl total es de $%.2f", pagoTotal);
                if (usuario->tarjeta->saldo < pagoTotal){
                    printf("\nSaldo Insuficiente.\n");
                }else{
                    printf("\nConfirme su pago (Presione 0 para cancelar y 1 para confirmar): ");
                    scanf("%d", &opcion);
                    if(opcion){
                        usuario->tarjeta->saldo -= pagoTotal;
                        actualizarSaldo(usuario);
                        sleep(2);
                        printf("\nPago realizado. Saldo actual: $%.2f\n", usuario->tarjeta->saldo);
                        while(!colaVacia(*cola)){
                            int n = 1;
                            char *nombre = borrarArticulo(cola, &n);
                            n++;
                        }
                        viajeEmpleado();
                    }
                }
            }
            break;
        }
    }while(opcion != 3);
    return 0;
}

Articulo *buscarArticulo(Cola *cola){ 
    const char *categorias[6] = {"Farmacia", "Belleza", "Herramientas", "Ropa", "Juguetes", "Instrumentos"};
    const char *archivos[6] = {"./farmacia.csv", "./belleza.csv", "./herramientas.csv", "./ropa.csv", "./juguetes.csv", "./instrumentos.csv"};
    char articulo_nombre[MAX_TEXTO];
    int opcion, cantidad;

    printf("\n---- BUSCAR PRODUCTO ----\n");
    printf("\nIngrese el nombre del producto a buscar: ");
    getchar();
    fgets(articulo_nombre, MAX_TEXTO, stdin);
    articulo_nombre[strcspn(articulo_nombre, "\n")] = '\0';

    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if (archivo == NULL){
            printf("Error al abrir el archivo.\n");
            continue;
        }
        Articulo *articulo = buscarArchivo(archivo, articulo_nombre);
        fclose(archivo);

        if(articulo != NULL){
            printf("\nArtículo: %s\nCategoría: %s\nMarca: %s\nPrecio: %.2f\nCantidad: %d\n", articulo->nombre, categorias[i], articulo->marca, articulo->precio, articulo->stock);

            printf("\n¿Desea agregarlo al carrito? \n1) Si \n2) No \nIngrese opción: ");
            scanf("%d", &opcion);

            if(opcion == 1){
                printf("Ingrese la cantidad de articulos que desea agregar al carrito: ");
                scanf("%d", &cantidad);

                while(cantidad > articulo->stock){
                    printf("No hay suficiente stock. Seleccione otra cantidad: ");
                    scanf("%d", &cantidad);
                }

                Articulo *articuloCarrito = crearArticulo();
                strcpy(articuloCarrito->nombre, articulo->nombre);
                strcpy(articuloCarrito->marca, articulo->marca);
                articuloCarrito->precio = articulo->precio;
                articuloCarrito->stock = cantidad;
                articuloCarrito->visible = 1;

                insertar(cola, articuloCarrito);
                printf("\n%s agregado al carrito.\n", articuloCarrito->nombre);

                liberarArticulo(articulo);
                return articuloCarrito;
            }else{
                liberarArticulo(articulo);
                return NULL;
            }
        }
    }
    printf("\nEl artículo %s no se encuentra en nuestro inventario. Lo sentimos.\n", articulo_nombre);
    return NULL;
}

Articulo *buscarArchivo(FILE *archivo, const char *articulo){
    char linea[MAX_LONGITUD];
    Articulo *Art = NULL;

    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    fgets(linea, sizeof(linea), archivo);

    while(fgets(linea, sizeof(linea), archivo)){
        linea[strcspn(linea, "\n")] = '\0';

        char *nombre = strtok(linea, ",");
        if(nombre && strcmp(nombre, articulo) == 0){
            Art = crearArticulo();
            if(Art){
                strncpy(Art->nombre, nombre, MAX_TEXTO - 1);
                Art->nombre[MAX_TEXTO - 1] = '\0';

                char *marca = strtok(NULL, ",");
                if(marca){
                    strncpy(Art->marca, marca, MAX_TEXTO);
                    Art->marca[MAX_TEXTO - 1] = '\0';
                }

                char *precio = strtok(NULL, ",");
                if(precio){
                    Art->precio = atof(precio);
                }
                char *stock = strtok(NULL, ",");
                if(stock){
                    Art->stock = atoi(stock);
                }
                char *ventas = strtok(NULL, ",");
                if(ventas){
                    Art->ventas = atoi(ventas);
                }
                break;
            }
        }
    }
    return Art;
}

int colaVacia(Cola cola){
    return cola.h == NULL;
}

void insertar(Cola *cola, Articulo *articulo){
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if(nuevoNodo == NULL){
        printf("Error: memoria insuficiente...");
        exit(1);
    }
    nuevoNodo->art = articulo;
    nuevoNodo->sig = NULL;
    if(colaVacia(*cola)){
        cola->h = cola->t = nuevoNodo;
    }else{
        cola->t->sig = nuevoNodo;
        cola->t = nuevoNodo;
    }
}

void listar(Cola cola){
    Nodo *q;
    if(colaVacia(cola)){
        printf("\nNo hay productos en el carrito\n");
    }else{
        printf("\n----- MI CARRITO -----\n");
        int i = 1;
        for(q = cola.h; q != NULL; q = q->sig){
            if(q->art->visible){
                printf("\n%3d) %s\tMarca: %s\tPrecio: %.2f \tCantidad: %i\n", i, q->art->nombre, q->art->marca, q->art->precio, q->art->stock);
                i++;
            }
        }
    }
    printf("\n");
}

void listarArticulos(int archiv, Articulo *dispArticulos){
    const char *archivos[6] = {"./farmacia.csv", "./belleza.csv", "./herramientas.csv", "./ropa.csv", "./juguetes.csv", "./instrumentos.csv"};
    archiv--;
    FILE *archivo = fopen(archivos[archiv], "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    char linea[MAX_LONGITUD];
    int i = 0;
    while(fgets(linea, sizeof(linea), archivo)){
        linea[strcspn(linea, "\n")] = '\0'; // eliminar los saltos de linea;
        if(i == 0){
            i++;
            continue; // No tomar en cuenta el primer renglón;
        }
        if(i == 1){
            printf("\n");
        }
        char *fnombre = strtok(linea, ",");
        char *fmarca = strtok(NULL, ",");
        char *precio = strtok(NULL, ",");
        char *stock = strtok(NULL, ",");
        char *ventas = strtok(NULL, ",");
        float fprecio = atof(precio);
        int fstock = atoi(stock);
        int fventas = atoi(ventas);
        dispArticulos[(i - 1)].nombre = strdup(fnombre);
        dispArticulos[(i - 1)].marca = strdup(fmarca);
        dispArticulos[(i - 1)].precio = fprecio;
        dispArticulos[(i - 1)].stock = fstock;
        dispArticulos[(i - 1)].ventas = fventas;
        printf("%3d) %-30s %-20s %-5.2f\n", i, fnombre, fmarca, fprecio);
        i++;
    }
    fclose(archivo);
}

void capturarArticulo(Articulo *articulo){
    int opcion, archiv, cantidad, aux;
    // Uso del arreglo para acceder a un producto
    Articulo *dispArticulos;
    int n = 20;
    dispArticulos = (Articulo *)calloc(n, sizeof(Articulo));
    do{
        printf("\n---- EXPLORAR ----\n1) Categorías\n2) Estadísticas\n3) Regresar\nIngrese opción: ");
        scanf("%d", &opcion);
        switch(opcion){
        case 1:
            printf("\n---- CATEGORÍAS ----\n1) Farmacia\n2) Belleza\n3) Herraminetas\n4) Ropa\n5) Juguetes\n6) Instrumentos\nIngrese opción: ");
            scanf("%d", &archiv);
            printf("\nSe encientran disponibles los siguientes productos:");
            listarArticulos(archiv, dispArticulos);
            printf("Ingrese el artículo a seleccionar (Presione 0 para cancelar): ");
            scanf("%d", &aux);
            if(aux != 0){
                articulo->nombre = dispArticulos[aux - 1].nombre;
                articulo->marca = dispArticulos[aux - 1].marca;
                articulo->precio = dispArticulos[aux - 1].precio;
                printf("Ingrese la cantidad de articulos que desea agregar al carrito: ");
                scanf("%d", &cantidad);
                while(cantidad > dispArticulos->stock){
                    printf("No hay suficiente stock. Seleccione otra cantidad: ");
                    scanf("%d", &cantidad);
                }
                articulo->stock = cantidad;
                articulo->visible = 1;
                printf("%s agregado al carrito.\n", articulo->nombre);
            }
            break;
        case 2:
            estadisticas();
            break;
        }
    }while(opcion != 3);
}

void estadisticas(){
    int opcion;
    int arrventas[20], arrstock[20];
    float arrprecios[20];
    const char *categorias[6] = {"Farmacia", "Belleza", "Herramientas", "Ropa", "Juguetes", "Instrumentos"};
    const char *archivos[6] = {"./farmacia.csv", "./belleza.csv", "./herramientas.csv", "./ropa.csv", "./juguetes.csv", "./instrumentos.csv"};
    
    do{
        printf("\n---- ESTADÍSTICAS ----\n1) Producto más vendido por categoría\n2) Producto menos vendido por categoría\n3) Ventas promedio por categoría\n4) Número de productos por categoría\n5) Precio mayor por categoría\n6) Precio menor por categoría\n7) Precio promedio por categoría\n8) Producto con mayor stock por categoría\n9) Producto con menor stock por categoría\n10) Stock promedio por categoría\n11) Regresar\nIngrese opción: ");
        scanf("%d", &opcion);

        if(opcion == 11){
            break;
        }

        printf("\n");
        for(int i = 0; i < 6; i++){
            FILE *archivo = fopen(archivos[i], "r");
            if(archivo == NULL){
                printf("Error al abrir el archivo %s\n", archivos[i]);
                continue;
            }

            char linea[MAX_LONGITUD];
            fgets(linea, sizeof(linea), archivo); // Saltar encabezado

            int cont = 0;
            float max_ventas = -1, min_ventas = -1;
            float max_precio = -1, min_precio = -1;
            int max_stock = -1, min_stock = -1;

            char nombre_max_ventas[MAX_TEXTO] = "", nombre_min_ventas[MAX_TEXTO] = "";
            char nombre_max_precio[MAX_TEXTO] = "", nombre_min_precio[MAX_TEXTO] = "";
            char nombre_max_stock[MAX_TEXTO] = "", nombre_min_stock[MAX_TEXTO] = "";

            while(fgets(linea, sizeof(linea), archivo)){
                linea[strcspn(linea, "\n")] = '\0';
                
                char *fnombre = strtok(linea, ",");
                char *fmarca = strtok(NULL, ",");
                char *fprecio = strtok(NULL, ",");
                char *fstock = strtok(NULL, ",");
                char *fventas = strtok(NULL, ",");
                float precio = atof(fprecio);
                int stock = atoi(fstock);
                int ventas = atoi(fventas);
                
                arrprecios[cont] = precio;
                arrstock[cont] = stock;
                arrventas[cont] = ventas;
                cont++;

                // Producto más/menos vendido
                if(max_ventas == -1 || ventas > max_ventas){
                    max_ventas = ventas;
                    strncpy(nombre_max_ventas, fnombre, MAX_TEXTO);
                }
                if(min_ventas == -1 || ventas < min_ventas){
                    min_ventas = ventas;
                    strncpy(nombre_min_ventas, fnombre, MAX_TEXTO);
                }

                // Producto con mayor/menor precio
                if (max_precio == -1 || precio > max_precio) {
                    max_precio = precio;
                    strncpy(nombre_max_precio, fnombre, MAX_TEXTO);
                }
                if (min_precio == -1 || precio < min_precio) {
                    min_precio = precio;
                    strncpy(nombre_min_precio, fnombre, MAX_TEXTO);
                }

                // Producto con mayor/menor stock
                if (max_stock == -1 || stock > max_stock) {
                    max_stock = stock;
                    strncpy(nombre_max_stock, fnombre, MAX_TEXTO);
                }
                if (min_stock == -1 || stock < min_stock) {
                    min_stock = stock;
                    strncpy(nombre_min_stock, fnombre, MAX_TEXTO);
                }
            }
            fclose(archivo);

            // Mostrar resultados según la opción seleccionada
            printf("-- %s --\n", categorias[i]);
            switch(opcion){
                case 1:
                    printf("%s: %d ventas\n", nombre_max_ventas, (int)max_ventas);
                    break;
                case 2:
                    printf("%s: %d ventas\n", nombre_min_ventas, (int)min_ventas);
                    break;
                case 3:
                    printf("Promedio de ventas: %.1f ventas\n", promedio(arrventas, cont));
                    break;
                case 4:
                    printf("Número de productos: %d\n", cont);
                    break;
                case 5:
                    printf("%s: $%.2f\n", nombre_max_precio, max_precio);
                    break;
                case 6:
                    printf("%s: $%.2f\n", nombre_min_precio, min_precio);
                    break;
                case 7:
                    printf("Promedio de precios: $%.2f\n", promedioFloat(arrprecios, cont));
                    break;
                case 8:
                    printf("%s: %d unidades\n", nombre_max_stock, max_stock);
                    break;
                case 9:
                    printf("%s: %d unidades\n", nombre_min_stock, min_stock);
                    break;
                case 10:
                    printf("Stock promedio: %.1f unidades\n", promedio(arrstock, cont));
                    break;
            }
            printf("\n");
        }
    }while(opcion != 11);
}

float promedio(int datos[], int n){
    int suma = 0;
    for(int i = 0; i < n; i++){
        suma += datos[i];
    }
    return (float) suma / n;
}

float promedioFloat(float datos[], int n){
    float suma = 0.0;
    for(int i = 0; i < n; i++){
        suma += datos[i];
    }
    return suma / n;
}

char *borrarArticulo(Cola *cola, int *n){
    char *dato;
    Nodo *q = cola->h;
    if(!colaVacia(*cola)){
        if (cola->h == cola->t){
            cola->h = cola->t = NULL;
        }else{
            for(int i = 0; i < (*n) - 1; i++){
                q = q->sig;
            }
            q->art->visible = 0;
        }
        dato = q->art->nombre; // Extraer el nombre del articulo
    }else{
        printf("\nNo hay productos en el carrito.\n");
    }
    return dato;
}

float comprar(Cola *cola){
    float total = 0;
    Nodo *q;
    q = cola->h;
    for(q = cola->h; q != NULL; q = q->sig){
        if (q->art->visible){
            total += ((q->art->precio) * (q->art->stock));
        }
    }
    return total;
}

void actualizarSaldo(Usuario *usuario){
    char linea[MAX_LONGITUD];
    int buscar = 0;
    FILE *archivo = fopen("usuarios.csv", "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if(temp == NULL){
        printf("Error al crear archivo temporal.\n");
        fclose(archivo);
        return;
    }

    while(fgets(linea, sizeof(linea), archivo)){
        char lineaCopia[MAX_LONGITUD];
        strcpy(lineaCopia, linea);
        lineaCopia[strcspn(lineaCopia, "\n")] = '\0';

        char *aux = strtok(lineaCopia, ",");
        if(aux && strcmp(aux, usuario->correo) == 0){
            buscar = 1;
            char *correo = aux;
            char *password = strtok(NULL, ",");
            char *nombre = strtok(NULL, ",");
            char *telefono = strtok(NULL, ",");
            char *tarjeta = strtok(NULL, ",");
            char *tipoTarjeta = strtok(NULL, ",");
            char *saldo = strtok(NULL, ",");
            char *id = strtok(NULL, ",");

            fprintf(temp, "%s,%s,%s,%s,%s,%s,%.2s,%s\n", correo, password, nombre, telefono, tarjeta, tipoTarjeta, saldo, id);
        }else{
            fprintf(temp, "%s", linea);
        }
    }
    fclose(archivo);
    fclose(temp);

    if(buscar){
        remove("usuarios.csv");
        rename("temp.csv", "usuarios.csv");
    }else{
        printf("Usuario no encontrado en el archivo.\n");
        remove("temp.csv");
    }
}

// FUNCIONES DE PILA
Pila *crearPila(){
    Pila *nuevaPila = (Pila *)calloc(1, sizeof(Pila));
    nuevaPila->t = -1;
    nuevaPila->max = 4;
    return nuevaPila;
}

void listarPila(Pila pila){
    if(pilaVacia(pila)){
        printf("No hay recorrido.\n");
        return;
    }

    int i;
    for(i = pila.t; i >= 0; i--){
        printf("- %s\n ", pila.elementos[i]);
    }
}

int pilaVacia(Pila pila){
    return pila.t == -1;
}

void push(Pila *pila, const char *calle){
    if(pila->t == pila->max - 1){
        printf("Recorrido lleno.\n");
        return;
    }
    pila->t++;
    strncpy(pila->elementos[pila->t], calle, MAX_TEXTO - 1);
    pila->elementos[pila->t][MAX_TEXTO - 1] = '\0';
}

void pop(Pila *pila){
    if(pilaVacia(*pila)){
        printf("Recorrido vacio.\n");
        return;
    }
    pila->t--;
}

void viajeEmpleado(){
    int opcion;

    printf("\n¿A qué alcaldía se enviará el pedido?\n1) %s\n2) %s\n3) %s\n4) %s\nIngrese opción: ", alcaldias[0], alcaldias[1], alcaldias[2], alcaldias[3]);
    scanf("%d", &opcion);

    while (opcion < 1 || opcion > MAX_ALCALDIAS){
        printf("Opción no válida. Ingrese nuevamente: ");
        scanf("%d", &opcion);
    }

    printf("\nPreparando envío a %s...\n", alcaldias[opcion - 1]);

    Pila *recorrido = crearPila();
    int callesUsadas[MAX_CALLES] = {0};
    int callesAsignadas = 0;

    srand(time(NULL));
    while (callesAsignadas < 4)
    {
        int i = rand() % MAX_CALLES;
        if (!callesUsadas[i])
        {
            push(recorrido, calles[i]);
            callesUsadas[i] = 1;
            callesAsignadas++;

            sleep(2);
            printf("El pedido se encuentra en: %s\n", calles[i]);
        }
    }
    sleep(2);
    printf("\nEl pedido ha llegado a su destino en %s\n", alcaldias[opcion - 1]);

    sleep(2);
    printf("\nRecorrido completo del envío:\n");
    listarPila(*recorrido);

    sleep(2);
    printf("El repartidor está regresando...\n");
    while (!pilaVacia(*recorrido))
    {
        pop(recorrido);
    }
    liberarPila(recorrido);
}

// FUNCIONES DE USUARIO
Usuario *crearUsuario(){
    Usuario *usuario = (Usuario *)calloc(1, sizeof(Usuario));
    if(!usuario){
        return NULL;
    }
    usuario->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->correo = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->password = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(!usuario->nombre || !usuario->correo || !usuario->password){
        liberarUsuario(usuario);
        return NULL;
    }
    
    usuario->tarjeta = crearTarjeta();
    if(!usuario->tarjeta){
        liberarUsuario(usuario);
        return NULL;
    }
    return usuario;
}

Tarjeta *crearTarjeta(){
    Tarjeta *tarjeta = (Tarjeta *)calloc(1, sizeof(Tarjeta));
    if(!tarjeta){
        return NULL;
    }
    tarjeta->tarjeta = (char *)calloc(17, sizeof(char));
    tarjeta->tipoTarjeta = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(!tarjeta->tarjeta || !tarjeta->tipoTarjeta){
        liberarTarjeta(tarjeta);
        return NULL;
    }
    tarjeta->saldo = 0;
    return tarjeta;
}

Usuario *miCuenta(Usuario *usuario){
    int opcion;
    do{
        printf("\n---- BIENVENIDO A SELLTRACK ----\n1) Iniciar sesión\n2) Registrarse\n3) Salir\nIngrese opción: ");
        scanf("%d", &opcion);
        switch(opcion){
        case 1:
            usuario = iniciarSesion();
            if(usuario == NULL){
                break;
            }
            return usuario;
            break;
        case 2:
            registrarse();
            break;
        }
    }while(opcion != 3);
    exit(0);
}

int registrarse(){
    Usuario *usuario = crearUsuario();
    srand(time(0));

    FILE *archivo = fopen("usuarios.csv", "a");
    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    printf("\n---- REGISTRARSE ----\n");

    printf("Ingrese su correo: ");
    getchar();
    fgets(usuario->correo, MAX_TEXTO, stdin);
    usuario->correo[strcspn(usuario->correo, "\n")] = '\0';

    printf("Ingrese su contraseña (letras y números): ");
    fgets(usuario->password, MAX_TEXTO, stdin);
    usuario->password[strcspn(usuario->password, "\n")] = '\0';

    encriptarBasico(usuario->password);

    printf("Ingrese su nombre: ");
    fgets(usuario->nombre, MAX_TEXTO, stdin);
    usuario->nombre[strcspn(usuario->nombre, "\n")] = '\0';

    printf("Ingrese su teléfono: ");
    scanf("%ld", &usuario->telefono);
    while(usuario->telefono < 1000000000 || usuario->telefono > 9999999999){
        printf("Ingrese un télefono valido: ");
        scanf("%ld", &usuario->telefono);
    }

    agregarTarjeta(usuario);

    do{
        usuario->ID = rand() % 10000;
    }while(usuario->tarjeta->saldo < 1000);

    fprintf(archivo, "%s,%s,%s,%ld,%s,%s,%.2f,%d\n", usuario->correo, usuario->password, usuario->nombre, usuario->telefono, usuario->tarjeta->tarjeta, usuario->tarjeta->tipoTarjeta, usuario->tarjeta->saldo, usuario->ID);
    fclose(archivo);
    printf("Sus datos han sido registrados correctamente\n");
    return 0;
}

int agregarTarjeta(Usuario *usuario){
    int opcion;
    printf("¿Desea agregar una tarjeta? \n1) Si \n2) No \nIngrese ocpión: ");
    scanf("%d", &opcion);
    if(opcion == 1){
        if(usuario->tarjeta){
            liberarTarjeta(usuario->tarjeta);
        }
        
        usuario->tarjeta = crearTarjeta();
        if(!usuario->tarjeta){
            printf("Error al crear la tarjeta.\n");
            return -1;
        }

        printf("Ingrese el número de tarjeta: ");
        scanf("%16s", usuario->tarjeta->tarjeta);
        while(!check(usuario->tarjeta->tarjeta)){
            printf("Ingrese un número de tarjeta válido: ");
            scanf("%16s", usuario->tarjeta->tarjeta);
        }
        usuario->tarjeta->tipoTarjeta = card_type(usuario->tarjeta->tarjeta);
        do{
            usuario->tarjeta->saldo = rand() % 10000;
        }while(usuario->tarjeta->saldo < 100);

    }else{
        strcpy(usuario->tarjeta->tarjeta, " ");
        usuario->tarjeta->tipoTarjeta = strdup(" ");
        do{
            usuario->tarjeta->saldo = rand() % 10000;
        }while(usuario->tarjeta->saldo < 100);
    }
    return 0;
}

Usuario *iniciarSesion(){
    Usuario *usuario = NULL;
    ;
    char auxcorreo[MAX_TEXTO];
    char auxpassword[MAX_TEXTO];
    char linea[MAX_LONGITUD];
    int buscar = 0;

    printf("\n---- INICIAR SESIÓN ----\n");

    printf("Ingrese su correo: ");
    getchar();
    fgets(auxcorreo, MAX_TEXTO, stdin);
    auxcorreo[strcspn(auxcorreo, "\n")] = '\0';

    printf("Ingrese su contraseña: ");
    fgets(auxpassword, MAX_TEXTO, stdin);
    auxpassword[strcspn(auxpassword, "\n")] = '\0';

    encriptarBasico(auxpassword); // Encriptar contraseña ingresada para validarla

    FILE *archivo = fopen("usuarios.csv", "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo de usuarios.\n");
        return NULL;
    }

    while(fgets(linea, sizeof(linea), archivo)){
        linea[strcspn(linea, "\n")] = '\0';

        char *aux = strtok(linea, ",");
        if(aux && strcmp(aux, auxcorreo) == 0){
            usuario = crearUsuario();
            if(usuario){
                strcpy(usuario->correo, aux); // Asignar campos con verificación

                aux = strtok(NULL, ",");
                if(aux){
                    strcpy(usuario->password, aux);
                }

                aux = strtok(NULL, ",");
                if(aux){
                    strcpy(usuario->nombre, aux);
                }

                aux = strtok(NULL, ",");
                if(aux){
                    usuario->telefono = atol(aux);
                }

                aux = strtok(NULL, ",");
                if(aux){
                    strcpy(usuario->tarjeta->tarjeta, aux);
                }

                aux = strtok(NULL, ",");
                if(aux){
                    usuario->tarjeta->tipoTarjeta = strdup(aux);
                }

                aux = strtok(NULL, ",");
                if(aux){
                    usuario->tarjeta->saldo = atof(aux);
                }

                aux = strtok(NULL, ",");
                if(aux){
                    usuario->ID = atoi(aux);
                }
                if(strcmp(usuario->password, auxpassword) == 0){ // Verificar contraseña
                    buscar = 1;
                    break;
                }else{
                    liberarUsuario(usuario);
                    usuario = NULL;
                }
            }
        }
    }
    fclose(archivo);

    if (buscar == 1)
    {
        return usuario;
    }
    else
    {
        printf("\nSus datos son incorrectos. Vuelva a intentarlo.\n");
        liberarUsuario(usuario);
        return NULL;
    }
}

void imprimirUsuario(Usuario *usuario){
    int longitud;
    printf("\n¡Hola %s!\n", usuario->nombre);
    printf("Correo: %s\n", usuario->correo);
    printf("Teléfono: %ld\n", usuario->telefono);
    longitud = strlen(usuario->tarjeta->tarjeta);
    if(longitud == 16){
        printf("Método de pago: ************%.4s %s\n", usuario->tarjeta->tarjeta + longitud - 4, usuario->tarjeta->tipoTarjeta);
    }else{
        printf("No tiene tarjeta registrada\n");
    }
    printf("Saldo disponible: $%.2f\n", usuario->tarjeta->saldo);
    printf("ID de usuario: %d\n", usuario->ID);
}

void encriptarBasico(char *password){
    for(int i = 0; password[i] != '\0'; i++){
        if(isalnum(password[i])){
            password[i] = password[i] + 3;
        }
    }
}

void desencriptarBasico(char *password){
    for(int i = 0; password[i] != '\0'; i++){
        if(isalnum(password[i])){
            password[i] = password[i] - 3;
        }
    }
}

int check(const char *card_number){ // Luhn algorithm
    int add = 0;
    int length = strlen(card_number);
    int double_digit = 0;
    for(int i = length - 1; i >= 0; i--){
        int digit = card_number[i] - '0';
        if(double_digit){
            digit = digit * 2;
            if(digit > 9){
                digit = digit - 9;
            }
        }
        add = add + digit;
        double_digit = !double_digit;
    }
    return(add % 10 == 0);
}

const char *card_type(const char *card_number){
    int length = strlen(card_number);
    if((length == 15) && (card_number[0] == '3') && (card_number[1] == '4' || card_number[1] == '7')){
        return "AMEX";
    }else if((length == 16) && (card_number[0] == '5') && (card_number[1] >= '1' && card_number[1] <= '5')){
        return "MASTERCARD";
    }else if((length == 13 || length == 16) && (card_number[0] == '4')){
        return "VISA";
    }else{
        return "INVALID";
    }
}

// FUNCIONES DE LIBERACION
void liberarArticulo(Articulo *articulo){
    if(articulo == NULL){
        return;
    }
    free(articulo->nombre);
    free(articulo->marca);
    free(articulo);
}

void liberarNodo(Nodo *nodo){
    if(nodo == NULL){
        return;
    }
    liberarArticulo(nodo->art);
    free(nodo);
}

void liberarCola(Cola *cola){
    if(cola == NULL){
        return;
    }
    Nodo *q = cola->h;
    Nodo *sig;
    while(q != NULL){
        sig = q->sig;
        q->sig = NULL;
        liberarNodo(q);
        q = sig;
    }
    free(cola);
}

void liberarUsuario(Usuario *usuario){
    if(usuario == NULL){
        return;
    }
    free(usuario->nombre);
    free(usuario->correo);
    free(usuario->password);
    free(usuario->tarjeta);
    free(usuario);
}

void liberarTarjeta(Tarjeta *tarjeta){
    if(tarjeta == NULL){
        return;
    }
    free(tarjeta->tarjeta);
    free(tarjeta);
}

void liberarPila(Pila *pila){
    if(pila != NULL){
        free(pila);
    }
}