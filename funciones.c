#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "funciones.h"

const char *alcaldias[MAX_ALCALDIAS] = {"Benito Juárez", "Coyoacan", "Cuauhtémoc", "Miguel Hidalgo"};
const char *calles[MAX_CALLES] = {"Calle A", "Calle B", "Calle C", "Calle D", "Calle E", "Calle F"};
const char *archivos[6] = {"./farmacia.csv", "./belleza.csv", "./herramientas.csv", "./ropa.csv", "./juguetes.csv", "./instrumentos.csv"};
const char *categorias[6] = {"Farmacia", "Belleza", "Herramientas", "Ropa", "Juguetes", "Instrumentos"};

// FUNCIONDES DE ARREGLO
Arreglo *crearArreglo(int capacidad){
    Arreglo *arreglo = (Arreglo *)malloc(sizeof(Arreglo));
    if(arreglo == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }

    arreglo->articulo = (Articulo *)calloc(capacidad, sizeof(Articulo));
    if(arreglo->articulo == NULL){
        free(arreglo);
        printf("Error: Espacio insuficiente...");
        exit(1);
    }

    arreglo->capacidad = capacidad;
    arreglo->tam = 0;
    return arreglo;
}

int pushArreglo(Arreglo *arreglo, Articulo art){
    arreglo->articulo[arreglo->tam++] = art;
    return arreglo->tam - 1; // Retorna índice donde se insertó
}

void listarArreglo(Arreglo *arreglo){
    if(arreglo->tam == 0){
        printf("\nNo hay artículos en el arreglo.\n");
        return;
    }

    Articulo *art = arreglo->articulo;
    for(int i = 0; i < arreglo->tam; i++){
        printf("%3d) %-30s %-20s $%-5.2f\n", i + 1, (art + i)->nombre, (art + i)->marca, (art + i)->precio); // Aritmetica de apuntadores
    }
}

// FUNCIONES DE COLA
Cola *crearCola(){
    Cola *cola = (Cola *)malloc(sizeof(Cola));
    if(cola == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }

    cola->h = NULL;
    cola->t = NULL;
    return cola;
}

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

    articulo->stock = 0;
    articulo->precio = 0.0;
    articulo->ventas = 0;
    articulo->visible = 0;
    return articulo;
}

int miCarrito(Cola *cola, Usuario *usuario){
    int opcion;
    int aux;
    do{
        listarCola(*cola);
        printf("\n¿Qué desea hacer?\n1) Eliminar producto\n2) Proceder al pago\n3) Regresar\nIngrese opción: ");
        scanf("%d", &opcion);
        switch(opcion){
        case 1: // Eliminar producto
            if(!colaVacia(*cola)){
                listarCola(*cola);
                printf("Ingrese el producto a eliminar: ");
                scanf("%d", &aux);
                
                char *nameaux = popCola(cola, &aux);
                if(nameaux != NULL){
                    printf("\n%s eliminado del carrito.\n", nameaux);
                    free(nameaux);
                }else{
                    printf("\nNo se encontró el producto.\n");
                }
            }else{
                printf("\nNo hay producto en el carrito.\n");
                return 0;
            }
            break;
        case 2: // Proceder al pago
            if(!colaVacia(*cola)){
                float pagoTotal = comprar(cola); // Calcular total
                printf("\nEl total es de $%.2f", pagoTotal);
                if (usuario->tarjeta->saldo < pagoTotal){
                    printf("\nSaldo Insuficiente.\n");
                }else{
                    printf("\nConfirme su pago (Presione 0 para cancelar y 1 para confirmar): ");
                    scanf("%d", &aux);
                    if(aux == 1){
                        usuario->tarjeta->saldo -= pagoTotal; // Actualizar saldo
                        actualizarSaldo(usuario);
                        printf("\nPago realizado. Saldo actual: $%.2f\n", usuario->tarjeta->saldo);
                        printf("\n¡Gracias por su compra!\n");
                        viajeEmpleado(); // Simulación de envío
                        while(!colaVacia(*cola)){ // Borrar los productos del carrito
                            int n = 1;
                            char *nombre = popCola(cola, &n);
                        }
                    }
                }
            }
            break;
        }
    }while(opcion != 3);
    return 0;
}

void agregarCarrito(Cola *cola, Articulo articulo, int cantidad){
    Articulo *articuloCarrito = crearArticulo();
    if(articuloCarrito == NULL){
        printf("Error al crear el artículo del carrito.\n");
        return;
    }

    articuloCarrito->nombre = strdup(articulo.nombre);
    articuloCarrito->marca = strdup(articulo.marca);
    if(articuloCarrito->nombre == NULL || articuloCarrito->marca == NULL){
        printf("Error al asignar memoria para el nombre o marca del artículo.\n");
        liberarArticulo(articuloCarrito);
        return;
    }

    articuloCarrito->precio = articulo.precio;
    articuloCarrito->stock = cantidad;
    articuloCarrito->visible = 1;

    pushCola(cola, articuloCarrito); // Se agrega el producto al carrito
    printf("\n%s agregado al carrito.\n", articuloCarrito->nombre);
}

void *buscarArticulo(Cola *cola){ 
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
            printf("\nProducto: %s\nCategoría: %s\nMarca: %s\nPrecio: %.2f\nCantidad: %d\n", articulo->nombre, categorias[i], articulo->marca, articulo->precio, articulo->stock);

            printf("\n¿Desea agregarlo al carrito? \n1) Si \n2) No \nIngrese opción: ");
            scanf("%d", &opcion);

            if(opcion == 1){
                printf("Ingrese la cantidad de producto que desea agregar al carrito: ");
                scanf("%d", &cantidad);

                while(cantidad > articulo->stock){
                    printf("No hay suficiente stock. Seleccione otra cantidad: ");
                    scanf("%d", &cantidad);
                }

                agregarCarrito(cola, *articulo, cantidad);
                liberarArticulo(articulo);
                return NULL;
            }else{
                liberarArticulo(articulo);
                return NULL;
            }
        }
    }
    printf("\nEl producto %s no se encuentra en nuestro inventario. Lo sentimos.\n", articulo_nombre);
    return NULL;
}

Articulo *buscarArchivo(FILE *archivo, const char *articulo){
    char linea[MAX_LONGITUD];
    Articulo *Art = NULL;

    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    fgets(linea, sizeof(linea), archivo); // Saltar encabezado

    while(fgets(linea, sizeof(linea), archivo)){
        linea[strcspn(linea, "\n")] = '\0';

        char *nombre = strtok(linea, ",");
        if(nombre && strcmp(nombre, articulo) == 0){
            Art = crearArticulo();
            if(Art != NULL){
                strcpy(Art->nombre, nombre);
                Art->nombre[MAX_TEXTO] = '\0';

                char *marca = strtok(NULL, ",");
                if(marca != NULL){
                    strcpy(Art->marca, marca);
                    Art->marca[MAX_TEXTO] = '\0';
                }

                char *precio = strtok(NULL, ",");
                if(precio != NULL){
                    Art->precio = atof(precio);
                }

                char *stock = strtok(NULL, ",");
                if(stock != NULL){
                    Art->stock = atoi(stock);
                }

                char *ventas = strtok(NULL, ",");
                if(ventas != NULL){
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

void pushCola(Cola *cola, Articulo *articulo){
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

char *popCola(Cola *cola, int *n){
    if (colaVacia(*cola)){
        printf("\nNo hay productos en el carrito.\n");
        return NULL;
    }
    
    Nodo *q = cola->h;
    Nodo *anterior = NULL;
    int i = 1;
    char *nombre = NULL;

    // Buscar el nodo a eliminar
    for(q = cola->h; q != NULL && i < *n; q = q->sig){
        anterior = q;
        i++;
    }

    if(q == NULL){
        return NULL; // No se encontró el nodo
    }

    nombre = strdup(q->art->nombre); // Extrae el nombre

    // Eliminar el nodo
    if(anterior == NULL){
        cola->h = q->sig; // Es el primer nodo
        if (cola->h == NULL){
            cola->t = NULL;
        }
    }else{
        anterior->sig = q->sig;
        if(q->sig == NULL){
            cola->t = anterior;
        }
    }
    liberarNodo(q);
    return nombre;
}

void listarCola(Cola cola){
    if(colaVacia(cola)){
        printf("\nNo hay productos en el carrito\n");
        return;
    }else{
        printf("\n----- MI CARRITO -----\n");
        int i = 1;
        Nodo *q = NULL;
        for(q = cola.h; q != NULL; q = q->sig){
            if(q->art->visible){
                printf("\n%3d) %s\tMarca: %s\tPrecio: $%.2f \tCantidad: %i\n", i, q->art->nombre, q->art->marca, q->art->precio, q->art->stock);
                i++;
            }
        }
    }
    printf("\n");
}

int cargarInventario(int a, Arreglo *arreglo){
    FILE *archivo = fopen(archivos[a], "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    char linea[MAX_LONGITUD];
    fgets(linea, sizeof(linea), archivo); // Saltar encabezado

    while(fgets(linea, sizeof(linea), archivo)){
        linea[strcspn(linea, "\n")] = '\0'; // eliminar los saltos de linea;

        char *fnombre = strtok(linea, ",");
        char *fmarca = strtok(NULL, ",");
        char *fprecio = strtok(NULL, ",");
        char *fstock = strtok(NULL, ",");
        char *fventas = strtok(NULL, ",");
        if(fnombre == NULL || fmarca == NULL || fprecio == NULL || fstock == NULL || fventas == NULL){
            printf("Error al leer el archivo.\n");
            return 0;
        }

        float precio = atof(fprecio);
        int stock = atoi(fstock);
        int ventas = atoi(fventas);

        Articulo *art = crearArticulo();

        art->nombre = strdup(fnombre);
        art->marca = strdup(fmarca);
        if(art->nombre == NULL || art->marca == NULL){
            printf("Error al asignar memoria para el nombre o marca del artículo.\n");
            liberarArticulo(art);
            continue;
        }
        art->precio = precio;
        art->stock = stock;
        art->ventas = ventas;
        art->visible = 1;
        
        pushArreglo(arreglo, *art);
    }
    fclose(archivo);
    return 1;
}

void explorar(Cola *cola, Usuario *usuario){
    int opcion, archivo, cantidad, aux;
    int n = 20;
    do{
        printf("\n---- EXPLORAR ----\n1) Categorías\n2) Estadísticas\n3) Regresar\nIngrese opción: ");
        scanf("%d", &opcion);
        while(opcion < 1 || opcion > 3){
            printf("Opción no válida. Ingrese nuevamente: ");
            scanf("%d", &opcion);
        }

        switch(opcion){
        case 1: // Categorías
            printf("\n---- CATEGORÍAS ----\n1) Farmacia\n2) Belleza\n3) Herraminetas\n4) Ropa\n5) Juguetes\n6) Instrumentos\nIngrese opción: ");
            scanf("%d", &archivo);
            while(archivo < 1 || archivo > 6){
                printf("Opción no válida. Ingrese nuevamente: ");
                scanf("%d", &archivo);
            }
            Arreglo *inventario = crearArreglo(n);
            cargarInventario(archivo - 1, inventario);

            printf("\nSe encuentran disponibles los siguientes productos:\n");
            listarArreglo(inventario);

            printf("Ingrese el producto a seleccionar (Presione 0 para cancelar): ");
            scanf("%d", &aux);
            while(aux < 0 || aux > inventario->tam){
                printf("Opción no válida. Ingrese nuevamente: ");
                scanf("%d", &aux);
            }

            if(aux != 0){
                printf("Ingrese la cantidad de productos que desea agregar al carrito: ");
                scanf("%d", &cantidad);

                while(cantidad > inventario->articulo[aux - 1].stock || cantidad < 1){
                    printf("No hay suficiente stock. Seleccione otra cantidad: ");
                    scanf("%d", &cantidad);
                }
                agregarCarrito(cola, inventario->articulo[aux - 1], cantidad);
            }
            liberarArreglo(inventario);
            break;
        case 2: // Estadísticas
            estadisticas(usuario);
            break;
        }
    }while(opcion != 3);
}

float comprar(Cola *cola){
    float total = 0;
    Nodo *q = cola->h;
    for(q = cola->h; q != NULL; q = q->sig){
        if (q->art->visible){
            total += (q->art->precio * q->art->stock); // Aritmetica de apuntadores
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

        char *correo = strtok(lineaCopia, ",");
        if(correo && strcmp(correo, usuario->correo) == 0){
            buscar = 1;
            fprintf(temp, "%s,%s,%s,%ld,%s,%s,%.2f,%d\n", usuario->correo, usuario->password, usuario->nombre, usuario->telefono, usuario->tarjeta->tarjeta, usuario->tarjeta->tipoTarjeta, usuario->tarjeta->saldo, usuario->ID);
        }else{
            fputs(linea, temp);
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

// FUNCIONES ESTADISTICAS
void estadisticas(Usuario *usuario){
    int opcion;
    do{
        printf("\n---- ESTADÍSTICAS ----\n1) Producto más vendido por categoría\n2) Producto menos vendido por categoría\n3) Ventas promedio por categoría\n4) ¿Qué productos puedo comprar por categoría?\n5) Precio mayor por categoría\n6) Precio menor por categoría\n7) Precio promedio por categoría\n8) Producto con mayor stock por categoría\n9) Producto con menor stock por categoría\n10) Stock promedio por categoría\n11) Regresar\nIngrese opción: ");
        scanf("%d", &opcion);
        printf("\n");
        
        switch(opcion){
            case 1: // Producto más vendido
                mostrarMasVendido();
                break;
            case 2: // Producto menos vendido
                mostrarMenosVendido();
                break;
            case 3: // Ventas promedio
                mostrarVentasPromedio();
                break;
            case 4: // Productos comprables
                mostrarProductosComprables(usuario);
                break;
            case 5: // Precio mayor
                mostrarPrecioMayor();
                break;
            case 6: // Precio menor
                mostrarPrecioMenor();
                break;
            case 7: // Precio promedio
                mostrarPrecioPromedio();
                break;
            case 8: // Producto con mayor stock
                mostrarMayorStock();
                break;
            case 9: // Producto con menor stock
                mostrarMenorStock();
                break;
            case 10: // Stock promedio
                mostrarStockPromedio();
                break;
        }
    }while(opcion != 11);
}

void mostrarMasVendido(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        int max_ventas = -1;
        char nombre_max_ventas[MAX_TEXTO] = "";

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            strtok(NULL, ","); // Saltar marca
            strtok(NULL, ","); // Saltar precio
            strtok(NULL, ","); // Saltar stock
            char *fventas = strtok(NULL, ",");
            int ventas = atoi(fventas);

            if(max_ventas == -1 || ventas > max_ventas){ // Comparar ventas
                max_ventas = ventas;
                strcpy(nombre_max_ventas, fnombre);
            }
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("%s: %d ventas\n", nombre_max_ventas, max_ventas);
    }
}

void mostrarMenosVendido(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        int min_ventas = -1;
        char nombre_min_ventas[MAX_TEXTO] = "";

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            strtok(NULL, ","); // Saltar marca
            strtok(NULL, ","); // Saltar precio
            strtok(NULL, ","); // Saltar stock
            char *fventas = strtok(NULL, ",");
            int ventas = atoi(fventas);

            if(min_ventas == -1 || ventas < min_ventas){ // Comparar ventas
                min_ventas = ventas;
                strcpy(nombre_min_ventas, fnombre);
            }
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("%s: %d ventas\n", nombre_min_ventas, min_ventas);
    }
}

void mostrarVentasPromedio(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        int arreglo_venta[20];
        int cont = 0;
        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        while (fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            strtok(linea, ","); // Ignorar nombre
            strtok(NULL, ",");  // Ignorar marca
            strtok(NULL, ",");  // Ignorar precio
            strtok(NULL, ",");  // Ignorar stock
            char *fventas = strtok(NULL, ",");
            int ventas = atoi(fventas);

            arreglo_venta[cont] = ventas;
            cont++;
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("Promedio de ventas: %.1f ventas\n", promedio(arreglo_venta, cont));
    }
}

void mostrarProductosComprables(Usuario *usuario){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        printf("-- %s --\n", categorias[i]);
        printf("Productos que puedes comprar con tu saldo actual ($%.2f):\n", usuario->tarjeta->saldo);

        int disponible = 0;

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            char *fmarca = strtok(NULL, ",");
            char *fprecio = strtok(NULL, ",");
            //char *fstock = strtok(NULL, ",");
            //strtok(NULL, ","); // Saltar ventas

            float precio = atof(fprecio);
            //int stock = atoi(fstock);

            if(precio <= usuario->tarjeta->saldo){
                printf("%-30s %-20s $%-5.2f\n", fnombre, fmarca, precio);
                disponible = 1;
            }
        }

        if(disponible == 0){
            printf("No hay productos disponibles en esta categoría.\n");
        }

        printf("\n");
        fclose(archivo);
    }
}

void mostrarPrecioMayor(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        float max_precio = -1;
        char nombre_max_precio[MAX_TEXTO] = "";

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            strtok(NULL, ","); // Saltar marca
            char *fprecio = strtok(NULL, ",");

            float precio = atof(fprecio);

            if(max_precio == -1 || precio > max_precio){ // Comparar precio
                max_precio = precio;
                strcpy(nombre_max_precio, fnombre);
            }
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("%s: $%.2f\n", nombre_max_precio, max_precio);
    }
}

void mostrarPrecioMenor(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        float min_precio = -1;
        char nombre_min_precio[MAX_TEXTO] = "";

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            strtok(NULL, ","); // Saltar marca
            char *fprecio = strtok(NULL, ",");

            float precio = atof(fprecio);

            if(min_precio == -1 || precio < min_precio){ // Comparar precio
                min_precio = precio;
                strcpy(nombre_min_precio, fnombre);
            }
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("%s: $%.2f\n", nombre_min_precio, min_precio);
    }
}

void mostrarPrecioPromedio(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        float arreglo_precio[20];
        int cont = 0;
        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        while (fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            strtok(linea, ","); // Ignorar nombre
            strtok(NULL, ",");  // Ignorar marca
            char *fprecio = strtok(NULL, ",");
            float precio = atof(fprecio);

            arreglo_precio[cont] = precio;
            cont++;
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("Promedio de precios: $%.2f\n", promedioFloat(arreglo_precio, cont));
    }
}

void mostrarMayorStock(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        int max_stock = -1;
        char nombre_max_stock[MAX_TEXTO] = "";

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            strtok(NULL, ","); // Saltar marca
            strtok(NULL, ","); // Saltar precio
            char *fstock = strtok(NULL, ",");
            strtok(NULL, ",");
            int stock = atoi(fstock);

            if(max_stock == -1 || stock > max_stock){ // Comparar stock
                max_stock = stock;
                strcpy(nombre_max_stock, fnombre);
            }
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("%s: %d unidades\n", nombre_max_stock, max_stock);
    }
}

void mostrarMenorStock(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        int min_stock = -1;
        char nombre_min_stock[MAX_TEXTO] = "";

        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *fnombre = strtok(linea, ",");
            strtok(NULL, ","); // Saltar marca
            strtok(NULL, ","); // Saltar precio
            char *fstock = strtok(NULL, ",");
            strtok(NULL, ",");
            int stock = atoi(fstock);

            if(min_stock == -1 || stock < min_stock){ // Comparar stock
                min_stock = stock;
                strcpy(nombre_min_stock, fnombre);
            }
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("%s: %d unidades\n", nombre_min_stock, min_stock);
    }
}

void mostrarStockPromedio(){
    for(int i = 0; i < 6; i++){
        FILE *archivo = fopen(archivos[i], "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo.\n");
            return;
        }

        int arreglo_stock[20];
        int cont = 0;
        char linea[MAX_LONGITUD];
        fgets(linea, sizeof(linea), archivo); // Saltar encabezado

        while (fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            strtok(linea, ","); // Ignorar nombre
            strtok(NULL, ",");  // Ignorar marca
            strtok(NULL, ",");  // Ignorar precio
            char *fstock = strtok(NULL, ",");
            int stock = atoi(fstock);

            arreglo_stock[cont] = stock;
            cont++;
        }

        fclose(archivo);
        printf("-- %s --\n", categorias[i]);
        printf("Stock promedio: %.1f unidades\n", promedio(arreglo_stock, cont));
    }
}

float promedio(int datos[], int n){
    int suma = 0;
    int *p = datos;
    for(int i = 0; i < n; i++){
        suma += *(p + i); // Aritmetica de apuntadores
    }
    return (float) suma / n;
}

float promedioFloat(float datos[], int n){
    float suma = 0.0;
    float *p = datos;
    for(int i = 0; i < n; i++){
        suma += *(p + i); // Aritmetica de apuntadores
    }
    return suma / n;
}


// FUNCIONES DE PILA
Pila *crearPila(){
    Pila *pila = (Pila *)calloc(1, sizeof(Pila));
    if(pila == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }

    for(int i = 0; i < 4; i++){ // Inicializar la pila
        pila->elementos[i][0] = '\0';
    }

    pila->t = -1;
    pila->max = 4;
    return pila;
}

void listarPila(Pila pila){
    if(pilaVacia(pila)){
        printf("No hay recorrido.\n");
        return;
    }

    for(int i = pila.t; i >= 0; i--){
        printf("%s\n ", pila.elementos[i]);
    }
}

int pilaVacia(Pila pila){
    return pila.t == -1;
}

void pushPila(Pila *pila, const char *calle){
    if(pila->t == pila->max - 1){
        printf("Recorrido lleno.\n");
        return;
    }
    pila->t++;
    strcpy(pila->elementos[pila->t], calle);
    pila->elementos[pila->t][MAX_TEXTO - 1] = '\0';
}

void popPila(Pila *pila){
    if(pilaVacia(*pila)){
        printf("Recorrido vacio.\n");
        return;
    }
    pila->elementos[pila->t][0] = '\0'; // Limpiar datos
    pila->t--;
}

void viajeEmpleado(){
    int opcion;

    printf("\n¿A qué alcaldía se enviará el pedido?\n1) %s\n2) %s\n3) %s\n4) %s\nIngrese opción: ", alcaldias[0], alcaldias[1], alcaldias[2], alcaldias[3]);
    scanf("%d", &opcion);

    while(opcion < 1 || opcion > MAX_ALCALDIAS){
        printf("Opción no válida. Ingrese nuevamente: ");
        scanf("%d", &opcion);
    }

    printf("\nPreparando envío a %s...\n", alcaldias[opcion - 1]);

    Pila *recorrido = crearPila();
    int callesUsadas[MAX_CALLES] = {0};
    int callesAsignadas = 0;

    srand(time(NULL));
    while(callesAsignadas < 4){
        int i = rand() % MAX_CALLES;
        if(!callesUsadas[i]){
            pushPila(recorrido, calles[i]);
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
    printf("El repartidor está regresando...\n");

    while(!pilaVacia(*recorrido)){
        popPila(recorrido);
    }
    liberarPila(recorrido);
}

// FUNCIONES DE USUARIO
Usuario *crearUsuario(){
    Usuario *usuario = (Usuario *)calloc(1, sizeof(Usuario));
    if(usuario == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }

    usuario->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->correo = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->password = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(usuario->nombre == NULL || usuario->correo == NULL || usuario->password == NULL){
        liberarUsuario(usuario);
        return NULL;
    }
    
    usuario->tarjeta = crearTarjeta();
    if(usuario->tarjeta == NULL){
        liberarUsuario(usuario);
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    return usuario;
}

Tarjeta *crearTarjeta(){
    Tarjeta *tarjeta = (Tarjeta *)calloc(1, sizeof(Tarjeta));
    if(tarjeta == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }

    tarjeta->tarjeta = (char *)calloc(17, sizeof(char));
    tarjeta->tipoTarjeta = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(tarjeta->tarjeta == NULL || tarjeta->tipoTarjeta == NULL){
        liberarTarjeta(tarjeta);
        printf("Error: Espacio insuficiente...");
        exit(1);
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
        case 1: // Iniciar sesión
            usuario = iniciarSesion();
            if(usuario == NULL){
                break;
            }
            return usuario;
            break;
        case 2: // Registrarse
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

    if (buscar == 1){
        return usuario;
    }else{
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

void liberarArreglo(Arreglo *arreglo){
    for(int i = 0; i < arreglo->tam; i++){
        free(arreglo->articulo[i].nombre);
        free(arreglo->articulo[i].marca);
    }
    free(arreglo->articulo);
    free(arreglo);
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