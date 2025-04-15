#ifndef FUNCIONES_H_INCLUDED
#define  FUNCIONES_H_INCLUDED
#define MAX_TEXTO 100
#define MAX_LONGITUD 256

//ESTRUCTURAS

typedef struct{
    int max;
    int tope;
    char **arr;

}PILA;
typedef struct{
    int tipo;
    char *nombre;
    char *marca;
    float precio;
    int cantidad;
    int visible;
}Articulo;
typedef struct nodo{
    Articulo *miArticulo;
    struct nodo *sig;
}Nodo;

typedef struct{
    Nodo *h,*t;
}Cola;

typedef struct{
    char nombre[10];
    char *correo;
    int pedidos;
    float saldo;
    int ID;
    
}Usuario;
/*
Clase *crearclase();
CiudadDatos *crearCiudadDatos();
void CapturarDatos();*/

void listarArticulos(int tipo, Articulo *dispArticulos);
void capturarArticulo(Articulo *miArticulo);
Articulo *crearArticulo();
int colaVacia(Cola cola);
Cola *crearCola();
void insertar(Cola *cola,Articulo *miarticulo);
void listar(Cola cola);
char *borrarArticulo(Cola *cola,int *n);
void inicializarCola(Cola *cola);
void liberarArticulo(Articulo *articulo);
void liberarNodo(Nodo *nodo);
void liberarCola(Cola *cola);
float pagar(Cola *cola);
Usuario *crearUsuario();
void imprimirDatos(Usuario usuario);
PILA *crearPila(int max);
void listarPILA(PILA pila);
void ViajeEmpleado();






















#endif // FUNCIONES_H_INCLUDED
