#define MAX_TEXTO 50
#define MAX_LONGITUD 256
#define MAX_CALLES 6
#define MAX_ALCALDIAS 4
extern const char *alcaldias[MAX_ALCALDIAS];
extern const char *calles[MAX_CALLES];

//ESTRUCTURAS
typedef struct{
    int tipo;
    char *nombre;
    char *marca;
    float precio;
    int stock;
    int visible;
    int ventas;
}Articulo;

typedef struct Nodo{
    Articulo *art;
    struct Nodo *sig;
}Nodo;

typedef struct{
    Nodo *h, *t;
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

//FUNCIONES DE CREACION
Articulo *crearArticulo();

//FUNCIONES DE COLA
Cola *crearCola();
int miCarrito(Cola *cola, Usuario *usuario);
Articulo *buscarArticulo(Cola *cola);
Articulo *buscarArchivo(FILE *archivo, const char *articulo);
int colaVacia(Cola cola);
void insertar(Cola *cola, Articulo *articulo);
void listar(Cola cola);
void listarArticulos(int tipo, Articulo *dispArticulos);
void capturarArticulo(Articulo *articulo);
void estadisticas();
float promedio(int datos[], int n);
float promedioFloat(float datos[], int n);
char *borrarArticulo(Cola *cola, int *n);
float comprar(Cola *cola);
void actualizarSaldo(Usuario *usuario);

//FUNCIONES DE PILA
Pila *crearPila();
void listarPila(Pila pila);
int pilaVacia(Pila pila);
void push(Pila *pila, const char *calle);
void pop(Pila *pila);
void viajeEmpleado();

//FUNCIONES DE USUARIO
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

//FUNCIONES DE LIBERACION
void liberarArticulo(Articulo *articulo);
void liberarNodo(Nodo *nodo);
void liberarCola(Cola *cola);
void liberarUsuario(Usuario *usuario);
void liberarTarjeta(Tarjeta *tarjeta);
void liberarPila(Pila *pila);