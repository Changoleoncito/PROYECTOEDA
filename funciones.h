#define MAX_TEXTO 50
#define MAX_LONGITUD 256
#define MAX_MENU 20

//ESTRUCTURAS
typedef struct{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;
}Herramientas;

typedef struct{
    char *nombre;
    char *marca;
    float *precio;
    int *sobrante;
}Ropa;

typedef struct{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;
}Juguetes;

typedef struct{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;
}Instrumentos;

typedef struct{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;
}Belleza;

typedef struct{
    char *nombre;
    char *marca;
    float *precio;
    float*sobrante;
}Farmacia;

typedef struct{
    Farmacia *farmacia;
    Belleza*belleza;
    Herramientas *herramientas;
    Ropa *ropa;
    Juguetes *juguetes;
    Instrumentos *instrumentos;
}Clase;

typedef struct{
    char *nombre;
    char *ciudad;
    char *calle;
    Clase *producto;
    float *dinero;
}CiudadDatos;

typedef struct{
    int tipo;
    char *nombre;
    char *marca;
    float precio;
    int cantidad;
    int visible;
}Articulo;

typedef struct Nodo{
    Articulo *miArticulo;
    struct Nodo *sig;
}Nodo;

typedef struct{
    Nodo *h,*t;
}Cola;

typedef struct{
    char *nombre;
    char *correo;
    char *password;
    long telefono;
    int pedidos;
    char *tarjeta;
    const char *tipoTarjeta;
    float saldo;
    int ID;
}Usuario;

Clase *crearclase();
CiudadDatos *crearCiudadDatos();
void CapturarDatos();

void listarArticulos(int tipo, Articulo *dispArticulos);
void capturarArticulo(Articulo *miArticulo);
Articulo *crearArticulo();
int colaVacia(Cola cola);
Cola *crearCola();
void insertar(Cola *cola, Articulo *miarticulo);
void listar(Cola cola);
char *borrarArticulo(Cola *cola, int *n);
void inicializarCola(Cola *cola);

//FUNCIONES DE LIBERACION
void liberarClase(Clase *clase);
void liberarCiudadDatos(CiudadDatos *ciudad);
void liberarArticulo(Articulo *articulo);
void liberarNodo(Nodo *nodo);
void liberarCola(Cola *cola);
void liberarUsuario(Usuario *usuario);

float pagar(Cola *cola);
Usuario *crearUsuario();
int miCuenta(Usuario *usuario);
int registrarse(Usuario *usuario);
int agregarTarjeta(Usuario *usuario);
int iniciarSesion(Usuario *usuario);
void imprimirUsuario(Usuario *usuario);
void encriptarBasico(char *password);
void desencriptarBasico(char *password);
int check(const char *card_number);
const char *card_type(const char *card_number);