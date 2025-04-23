#define MAX_TEXTO 50
#define MAX_LONGITUD 256
#define MAX_CALLES 6
#define MAX_ALCALDIAS 4
extern const char *alcaldias[MAX_ALCALDIAS];
extern const char *calles[MAX_CALLES];
extern const char *archivos[6];
extern const char *categorias[6];

//ESTRUCTURAS
typedef struct{
    char *nombre;
    char *marca;
    float precio;
    int stock;
    int visible;
    int ventas;
}Articulo;

typedef struct{
    Articulo *articulo;
    int capacidad;
    int tam;
}Arreglo;

typedef struct Nodo{
    Articulo *art;
    struct Nodo *sig;
}Nodo;

typedef struct{
    Nodo *h;
    Nodo *t;
}Cola;

typedef struct{
    int max;
    int t;
    char elementos[4][MAX_TEXTO];
}Pila;

typedef struct{
    char *tarjeta;
    const char *tipoTarjeta;
    float saldo;
}Tarjeta;

typedef struct{
    char *nombre;
    char *correo;
    char *password;
    long telefono;
    Tarjeta *tarjeta;
    int ID;
}Usuario;

// FUNCIONES DE ARREGLO
Arreglo *crearArreglo(int capacidad);
int pushArreglo(Arreglo *arreglo, Articulo art);
void listarArreglo(Arreglo *arreglo);

// FUNCIONES DE COLA
Cola *crearCola();
Articulo *crearArticulo();
int miCarrito(Cola *cola, Usuario *usuario);
void agregarCarrito(Cola *cola, Articulo articulo, int cantidad);
void *buscarArticulo(Cola *cola);
Articulo *buscarArchivo(FILE *archivo, const char *articulo);
int colaVacia(Cola cola);
void pushCola(Cola *cola, Articulo *articulo);
char *popCola(Cola *cola, int *n);
void listarCola(Cola cola);
int cargarInventario(int a, Arreglo *arreglo);
void explorar(Cola *cola, Usuario *usuario);
float comprar(Cola *cola);
void actualizarSaldo(Usuario *usuario);

// FUNCIONES ESTADISTICAS
void estadisticas(Usuario *usuario);
void mostrarMasVendido();
void mostrarMenosVendido();
void mostrarVentasPromedio();
void mostrarProductosComprables(Usuario *usuario);
void mostrarPrecioMayor();
void mostrarPrecioMenor();
void mostrarPrecioPromedio();
void mostrarMayorStock();
void mostrarMenorStock();
void mostrarStockPromedio();
float promedio(int datos[], int n);
float promedioFloat(float datos[], int n);

// FUNCIONES DE PILA
Pila *crearPila();
void listarPila(Pila pila);
int pilaVacia(Pila pila);
void pushPila(Pila *pila, const char *calle);
void popPila(Pila *pila);
void viajeEmpleado();

// FUNCIONES DE USUARIO
Usuario *crearUsuario();
Tarjeta *crearTarjeta();
Usuario *miCuenta(Usuario *usuario);
int registrarse();
int agregarTarjeta(Usuario *usuario);
Usuario *iniciarSesion();
void imprimirUsuario(Usuario *usuario);
void encriptarBasico(char *password);
void desencriptarBasico(char *password);
int check(const char *card_number);
const char *card_type(const char *card_number);

// FUNCIONES DE LIBERACION
void liberarArticulo(Articulo *articulo);
void liberarArreglo(Arreglo *arreglo);
void liberarNodo(Nodo *nodo);
void liberarCola(Cola *cola);
void liberarUsuario(Usuario *usuario);
void liberarTarjeta(Tarjeta *tarjeta);
void liberarPila(Pila *pila);