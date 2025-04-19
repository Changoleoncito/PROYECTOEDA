#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

Clase *crearclase(){
    Clase *clasenueva;
    clasenueva = (Clase *)malloc(sizeof(Clase));
    if(clasenueva == NULL){
        printf("Error al asignar memoria a clase");
        exit(1);
    }
    clasenueva->belleza = (Belleza *)calloc(1, sizeof(Belleza));
    if(clasenueva->belleza == NULL){
        printf("Error al asignar memoria a belleza");
        exit(1);
    }
    clasenueva->belleza->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->belleza->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->belleza->precio = (float *)calloc(1, sizeof(float));
    clasenueva->belleza->sobrante = (float *)calloc(1, sizeof(float));
    if(clasenueva->belleza->nombre == NULL || clasenueva->belleza->marca == NULL || clasenueva->belleza->precio == NULL || clasenueva->belleza->sobrante == NULL){
        printf("Error al asignar memoria a los datos de belleza");
        exit(1);
    }
    clasenueva->farmacia=(Farmacia *)calloc(1, sizeof(Farmacia));
    if(clasenueva->farmacia == NULL){
        printf("Error al asignar memoria a comida");
        exit(1);
    }
    clasenueva->farmacia->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->farmacia->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->farmacia->precio = (float *)calloc(1, sizeof(float));
    clasenueva->farmacia->sobrante = (float *)calloc(1, sizeof(float));
    if(clasenueva->farmacia->nombre == NULL || clasenueva->farmacia->marca == NULL || clasenueva->farmacia->precio == NULL || clasenueva->farmacia->sobrante == NULL){
        printf("Error al asignar memoria a los datos de comida");
        exit(1);
    }
    clasenueva->herramientas=(Herramientas *)calloc(1, sizeof(Herramientas));
    if(clasenueva->herramientas == NULL){
        printf("Error al asignar memoria a herramientas");
    }
    clasenueva->herramientas->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->herramientas->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->herramientas->precio = (float *)calloc(1, sizeof(float));
    clasenueva->herramientas->sobrante = (float *)calloc(1, sizeof(float));
    if(clasenueva->herramientas->nombre == NULL || clasenueva->herramientas->marca == NULL || clasenueva->herramientas->precio == NULL || clasenueva->herramientas->sobrante == NULL){
        printf("Error al asignar memoria a los datos de herramienta");
        exit(1);
    }
    clasenueva->instrumentos = (Instrumentos *)calloc(1, sizeof(Instrumentos));
    if(clasenueva->instrumentos == NULL){
        printf("Error al asignar memoria a instrumentos");
        exit(1);
    }
    clasenueva->instrumentos->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->instrumentos->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->instrumentos->precio = (float *)calloc(1, sizeof(float));
    clasenueva->instrumentos->sobrante = (float *)calloc(1, sizeof(float));
    if(clasenueva->instrumentos->nombre == NULL || clasenueva->instrumentos->marca == NULL || clasenueva->instrumentos->precio == NULL || clasenueva->instrumentos->sobrante == NULL){
        printf("Error al asignar memoria a los datos de herramienta");
        exit(1);
    }
    clasenueva->juguetes = (Juguetes *)calloc(1, sizeof(Juguetes));
    if(clasenueva->juguetes == NULL){
        printf("Error al asignar memoria a juguetes");
        exit(1);
    }
    clasenueva->juguetes->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->juguetes->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->juguetes->precio = (float *)calloc(1, sizeof(float));
    clasenueva->juguetes->sobrante = (float *)calloc(1, sizeof(float));
    if(clasenueva->juguetes->nombre == NULL || clasenueva->juguetes->marca == NULL || clasenueva->juguetes->precio == NULL || clasenueva->juguetes->sobrante == NULL){
        printf("Error al asignar memoria a los datos de juguetes");
        exit(1);
    }
    clasenueva->ropa = (Ropa *)calloc(1, sizeof(Ropa));
    if(clasenueva->ropa == NULL){
        printf("Error al asignar memoria a ropa");
        exit(1);
    }
    clasenueva->ropa->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->ropa->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    clasenueva->ropa->precio = (float *)calloc(1, sizeof(float));
    clasenueva->ropa->sobrante = (int *)calloc(1, sizeof(int));
    if(clasenueva->ropa->nombre == NULL || clasenueva->ropa->marca == NULL || clasenueva->ropa->precio == NULL || clasenueva->ropa->sobrante == NULL){
        printf("Error al asignar memoria a los datos de juguetes");
        exit(1);
    }
    return clasenueva;
}

CiudadDatos *crearCiudadDatos(){
    CiudadDatos *nuevaCiudadDatos;
    nuevaCiudadDatos = (CiudadDatos *)malloc(sizeof(CiudadDatos));
    if(nuevaCiudadDatos == NULL){
        printf("No se pudo asignar memoria a nuevaciudaddatos");
        exit(1);
    }
    nuevaCiudadDatos->calle = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(nuevaCiudadDatos->calle == NULL){
        printf("No se pudo asignar memoria a calle");
        exit(1);
    }
    nuevaCiudadDatos->ciudad = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(nuevaCiudadDatos->ciudad == NULL){
        printf("No se pudo asignar memoria a ciudad");
        exit(1);
    }
    nuevaCiudadDatos->dinero = (float *)calloc(1, sizeof(float));
    if(nuevaCiudadDatos->dinero == NULL){
        printf("No se pudo asignar memoria a dinero");
        exit(1);
    }
    nuevaCiudadDatos->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    if(nuevaCiudadDatos->nombre == NULL){
        printf("No se pudo asignar memoria a nombre");
        exit(1);
    }
    nuevaCiudadDatos->producto = (Clase *)calloc(1, sizeof(Clase));
    if(nuevaCiudadDatos->producto == NULL){
        printf("No se pudo asignar memoria a producto");
        exit(1);
    }
    return nuevaCiudadDatos;
}
    
Articulo *crearArticulo(){
    Articulo *miArticulo;
    miArticulo = (Articulo *)calloc(1, sizeof(Articulo));
    miArticulo->marca = (char *)calloc(MAX_TEXTO, sizeof(char));
    miArticulo->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    if (miArticulo->marca == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    if (miArticulo->nombre == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    if (miArticulo == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    return miArticulo;
}

void listarArticulos(int arc, Articulo *dispArticulos){
    const char *ruta[6] = {"./farmacia.csv","./belleza.csv","./herramientas.csv","./ropa.csv","./juguetes.csv","./instrumentos.csv"};
    arc--;
    FILE *archivo = fopen(ruta[arc], "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    char linea[MAX_LONGITUD];
    int i = 0;
    while(fgets(linea, sizeof(linea), archivo)){
        linea[strcspn(linea, "\n")] = '\0'; //eliminar los saltos de linea;
        if(i == 0){
            i++;
            continue; //No tomar en cuenta el primer renglón;
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
        printf("%3d) %-30s %-20s %-5.2f\n", i, fnombre, fmarca, fprecio);
        i++;
    }
    fclose(archivo);
}

void capturarArticulo(Articulo *miArticulo){
    int opcion, arc, cantidad, aux;
    //Uso del arreglo para acceder a un producto
    Articulo *dispArticulos;
    int n = 20;
    dispArticulos = (Articulo *)calloc(n, sizeof(Articulo));
    printf("\n---- EXPLORAR ----\n1) Categorías\n2) Más vendidos\n3) Mejor valorados\n4) Salir\nIngrese opción: ");
    scanf("%d", &opcion);
    switch(opcion){
    case 1:
        printf("\n---- CATEGORÍAS ----\n1) Farmacia\n2) Belleza\n3) Herraminetas\n4) Ropa\n5) Juguetes\n6) Instrumentos\nIngrese opción: ");
        scanf("%d", &arc);
        printf("\nSe encientran disponibles los siguientes productos:");
        listarArticulos(arc, dispArticulos);
        printf("Ingrese el artículo a seleccionar (Presione 0 para cancelar)\n");
        scanf("%d", &aux);
        if(aux != 0){
            miArticulo->nombre = dispArticulos[aux-1].nombre;
            miArticulo->marca = dispArticulos[aux-1].marca;
            miArticulo->precio = dispArticulos[aux-1].precio;
            printf("Ingrese la cantidad de articulos que desea agregar al carrito: ");
            scanf("%d", &cantidad);
            while(cantidad > dispArticulos->cantidad){
                printf("No hay suficiente stock. Seleccione otra cantidad: ");
                scanf("%d", &cantidad);
            }
            miArticulo->cantidad = cantidad;
            miArticulo->visible = 1;
        }
        break;
    }
}

int colaVacia(Cola cola){
    return cola.h == NULL;
}

Cola *crearCola(){
    Cola *nuevaCola;
    //CREACIÓN DINÁMICA DE LA ESTRUCTURA COLA
    nuevaCola = (Cola *)malloc(sizeof(Cola ));
    if (nuevaCola == NULL){
        printf("Error: Espacio insuficiente...");
        exit(1);
    }
    //INICIALIZANDO h y t
    nuevaCola->h = NULL;
    nuevaCola->t = NULL;
    return nuevaCola;
}

void insertar(Cola *cola, Articulo *miarticulo){
    Nodo *nuevoNodo;
    //CREA EL NODO
    nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL){
       printf("Error: memoria insuficiente...");
       exit(1);
    }
     nuevoNodo->miArticulo = miarticulo;
     nuevoNodo->sig = NULL;
    if (colaVacia(*cola))
        cola->h = cola->t = nuevoNodo;
    else{
        cola->t->sig = nuevoNodo;
        cola->t = nuevoNodo;
    }
}

void listar(Cola cola){
    Nodo *q;
    if(colaVacia(cola))
        printf("\nNo hay datos en la fila...\n");
    else{
        printf("\n----- MI CARRITO -----\n");
        int i = 1;
        for(q = cola.h; q != NULL ; q = q->sig){
            if(q->miArticulo->visible){
                printf("\nDatos del Articulo [%d]:\n Nombre: %s\nMarca: %s\n Precio:%.2f \n Cantidad: %i\n", i, q->miArticulo->nombre, q->miArticulo->marca, q->miArticulo->precio, q->miArticulo->cantidad);
                i++;
                }
            }
        }
    printf("\n");
}

char *borrarArticulo(Cola *cola, int *n){
    char *dato;
    Nodo *q = cola->h;
    //Nodo *aux;
    if(!colaVacia(*cola)){
        if(cola->h == cola->t)
            cola->h = cola->t = NULL;
        else{
            for(int i = 0; i < (*n)-1; i++)q = q->sig;
            q->miArticulo->visible = 0;
        }
        //cola->h = cola->h->sig;
        dato = q->miArticulo->nombre; //EXTRAE LA INFORMACIÓN
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
    for(q = cola->h; q != NULL; q = q->sig){
        if(q->miArticulo->visible){
            total += ((q->miArticulo->precio)*(q->miArticulo->cantidad));
        }
    }
    return total;
}
//funciones para liberar la memoria
//se utilizaran al momento de salir el programa o se vera su uso cuando veamos como queda el main.
void liberarClase(Clase *clase){
    if(clase == NULL) return;
    //Libera la memoria de belleza
    if(clase->belleza != NULL){
        free(clase->belleza->nombre);
        free(clase->belleza->marca);
        free(clase->belleza->precio);
        free(clase->belleza->sobrante);
        free(clase->belleza);
    }
    //Libera la memoria de comida
    if(clase->farmacia != NULL){
        free(clase->farmacia->nombre);
        free(clase->farmacia->marca);
        free(clase->farmacia->precio);
        free(clase->farmacia->sobrante);
        free(clase->farmacia);
    }
    //Libera la memoria de herramientas
    if(clase->herramientas != NULL){
        free(clase->herramientas->nombre);
        free(clase->herramientas->marca);
        free(clase->herramientas->precio);
        free(clase->herramientas->sobrante);
        free(clase->herramientas);
    }
    //Libera la memoria de instrumentos
    if(clase->instrumentos != NULL){
        free(clase->instrumentos->nombre);
        free(clase->instrumentos->marca);
        free(clase->instrumentos->precio);
        free(clase->instrumentos->sobrante);
        free(clase->instrumentos);
    }
    //Libera la memoria de juguetes
    if(clase->juguetes != NULL){
        free(clase->juguetes->nombre);
        free(clase->juguetes->marca);
        free(clase->juguetes->precio);
        free(clase->juguetes->sobrante);
        free(clase->juguetes);
    }
    //Libera la memoria de ropa
    if(clase->ropa != NULL){
        free(clase->ropa->nombre);
        free(clase->ropa->marca);
        free(clase->ropa->precio);
        free(clase->ropa->sobrante);
        free(clase->ropa);
    }
    //Libera la estructura Clase
    free(clase);
}

void liberarCiudadDatos(CiudadDatos *ciudad){
    if(ciudad == NULL) return;
    free(ciudad->nombre);
    free(ciudad->ciudad);
    free(ciudad->calle);
    free(ciudad->dinero);
    // Libera la estructura Clase dentro de CiudadDatos
    liberarClase(ciudad->producto);
    // Libera la estructura CiudadDatos
    free(ciudad);
}

void liberarArticulo(Articulo *articulo){
    if(articulo == NULL) return;
    free(articulo->nombre);
    free(articulo->marca);
    free(articulo);
}

void liberarNodo(Nodo *nodo){
    if(nodo == NULL) return;
    liberarArticulo(nodo->miArticulo);
    free(nodo);
}

void liberarCola(Cola *cola){
    if(cola == NULL) return;
    Nodo *q = cola->h;  
    Nodo *sig;
    while (q != NULL){
        sig = q->sig;  
        q->sig = NULL;  
        liberarNodo(q);  
        q = sig; 
    }
    free(cola);
}

void liberarUsuario(Usuario *usuario){
    if(usuario == NULL) return;
    free(usuario->nombre);
    free(usuario->correo);
    free(usuario->password);
    free(usuario->tarjeta);
    free(usuario);
}

Usuario* crearUsuario(){
    Usuario *usuario = usuario = (Usuario *)calloc(1, sizeof(Usuario));
    if(!usuario) return NULL;
    usuario->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->correo = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->password = (char *)calloc(MAX_TEXTO, sizeof(char));
    usuario->tarjeta = (char *)calloc(17, sizeof(char));
    usuario->tipoTarjeta = (char *)calloc(11, sizeof(char));
    return usuario;
}

Usuario *miCuenta(Usuario *usuario){
    int opcion;
    do{
        printf("\n---- BIENVENIDO A SELLTRACK ----\n1) Iniciar sesión\n2) Registrarse\n3) Salir\nIngrese opción: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                usuario = iniciarSesion();
                return usuario;
                break;
            case 2:
                registrarse();
                break;
            case 3:
                exit(0);
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
        printf("Error al abrir el archivo");
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

    usuario->saldo = rand() % 1000;
    usuario->ID = rand() %  10000;

    fprintf(archivo, "%s,%s,%s,%ld,%s,%s,%.2f,%d\n", usuario->correo, usuario->password, usuario->nombre, usuario->telefono, usuario->tarjeta, usuario->tipoTarjeta, usuario->saldo, usuario->ID);
    fclose(archivo);
    printf("Sus datos han sido registrados correctamente\n");
    return 0;
}

int agregarTarjeta(Usuario *usuario){
    int opcion;
    printf("¿Desea agregar una tarjeta? \n1) Si \n2) No \nIngrese ocpión: ");
    scanf("%d", &opcion);
    if (opcion == 1){
        printf("Ingrese el número de tarjeta: ");
        scanf("%16s", usuario->tarjeta);
        while(!check(usuario->tarjeta)){
            printf("Ingrese un número de tarjeta válido: ");
            scanf("%16s", usuario->tarjeta);
        }
        usuario->tipoTarjeta = card_type(usuario->tarjeta);
    }
    return 0;
}

Usuario *iniciarSesion(){
    char auxcorreo[MAX_TEXTO];
    char auxpassword[MAX_TEXTO];
    char linea[MAX_LONGITUD];
    int intentos = 3;
    Usuario *usuario;

    while(intentos > 0){
        printf("\n---- INICIAR SESIÓN ----\n");

        // Solicitar credenciales
        printf("Ingrese su correo: ");
        getchar();
        fgets(auxcorreo, MAX_TEXTO, stdin);
        auxcorreo[strcspn(auxcorreo, "\n")] = '\0';

        printf("Ingrese su contraseña: ");
        fgets(auxpassword, MAX_TEXTO, stdin);
        auxpassword[strcspn(auxpassword, "\n")] = '\0';

        // Encriptar contraseña ingresada para comparación
        encriptarBasico(auxpassword);

        FILE *archivo = fopen("usuarios.csv", "r");
        if(archivo == NULL){
            printf("Error al abrir el archivo de usuarios\n");
            return NULL;
        }

        int encontrado = 0;
        while(fgets(linea, sizeof(linea), archivo)){
            linea[strcspn(linea, "\n")] = '\0';

            char *token = strtok(linea, ",");
            if (token && strcmp(token, auxcorreo) == 0){
                usuario = crearUsuario();
                if(usuario){
                    // Asignar campos con verificación
                    strcpy(usuario->correo, token);
                    
                    token = strtok(NULL, ",");
                    if (token) strcpy(usuario->password, token);
                    
                    token = strtok(NULL, ",");
                    if (token) strcpy(usuario->nombre, token);
                    
                    token = strtok(NULL, ",");
                    if (token) usuario->telefono = atol(token);
                    
                    token = strtok(NULL, ",");
                    if (token) strcpy(usuario->tarjeta, token);
                    
                    token = strtok(NULL, ",");
                    if (token) usuario->tipoTarjeta = strdup(token);
                    
                    token = strtok(NULL, ",");
                    if (token) usuario->saldo = atof(token);
                    
                    token = strtok(NULL, ",");
                    if (token) usuario->ID = atoi(token);

                    // Verificar contraseña
                    if (strcmp(usuario->password, auxpassword) == 0){
                        encontrado = 1;
                        desencriptarBasico(usuario->password);
                        break;
                    } else {
                        liberarUsuario(usuario);
                        usuario = NULL;
                    }
                }
            }
        }
        fclose(archivo);

        if(encontrado){
            return usuario;
        }else{
            intentos--;
            printf("\nSus datos son incorrectos.Intente de nuevo.\n");
        }
    }

    printf("\nDemasiados intentos fallidos. Vuelva a intentarlo más tarde.\n");
    exit(1);
}

void imprimirUsuario(Usuario *usuario){
    int longitud;
    printf("\n¡Hola %s!\n", usuario->nombre);
    printf("Correo: %s\n", usuario->correo);
    printf("Teléfono: %ld\n", usuario->telefono);
    longitud = strlen(usuario->tarjeta);
    if(longitud == 16){
        printf("Método de pago: ************%.4s %s\n", usuario->tarjeta + longitud - 4, usuario->tipoTarjeta);
    }else{
        printf("No tiene tarjeta registrada\n");
    }
    printf("Saldo disponible: $%.2f\n", usuario->saldo);
    printf("ID de usuario: %d\n", usuario->ID);
}

void encriptarBasico(char *texto){
    for(int i = 0; texto[i] != '\0'; i++) {
        if(isalnum(texto[i])) {
            texto[i] = texto[i] + 3;
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

int check(const char *card_number){ //Luhn algorithm
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
    return (add % 10 == 0);
}

const char *card_type(const char *card_number){
    int length = strlen(card_number);
    if((length == 15) && (card_number[0] == '3') && (card_number[1] == '4' || card_number[1] == '7')){
        return "AMEX";
    }else if((length == 16) && (card_number[0] == '5') && (card_number[1] >= '1' && card_number[1] <= '5')){
        return "MASTERCARD";
    }
    else if((length == 13 || length == 16) && (card_number[0] == '4')){
        return "VISA";
    }else{
        return "INVALID";
    }
}