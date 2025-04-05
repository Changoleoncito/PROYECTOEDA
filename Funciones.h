#ifndef FUNCIONES_H_INCLUDED
#define  FUNCIONES_H_INCLUDED

#define MAX_TEXTO 30

//Estructuras
/*
typedef struct Clase
{
    comida *comida;
    belleza*belleza;
    herramientas *herramientas;
    ropa *ropa;
    juguetes *juguetes;
    instrumentos *instrumentos;
}Clase;
typedef struct CiudadDatos{
    char *nombre;
    char *ciudad;
    char *calle;
    Clase *producto;
    float *dinero;
}CiudadDatos;

typedef struct comida
{
    char *nombre;
    char *bebida;
    float *cantidad;
    float*sobrante;
}comida;
typedef struct belleza{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;

    
}belleza;
typedef struct herramientas{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;

}herramientas;
typedef struct ropa
{
    char *nombre;
    char *marca;
    float *precio;
    int *sobrante;
    
}ropa;
typedef struct juguetes{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;

}juguetes;
typedef struct instrumentos
{
    char *nombre;
    char *marca;
    float *precio;
    float *sobrante;
}instrumentos;
*/
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

/*
Clase *crearclase();
CiudadDatos *crearCiudadDatos();
void CapturarDatos();*/

int listarArticulos(int tipo, Articulo *dispArticulos,int *n);
void capturarArticulo(Articulo *miArticulo);
Articulo *crearArticulo();
int colaVacia(Cola cola);
Cola *crearCola();
void insertar(Cola *cola,Articulo *miarticulo);
void listar(Cola cola);
char *borrarArticulo(Cola *cola,int *n);
void inicializarCola(Cola *cola);
























#endif // FUNCIONES_H_INCLUDED
