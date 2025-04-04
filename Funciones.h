#ifndef FUNCIONES_H_INCLUDED
#define  FUNCIONES_H_INCLUDED

#define MAX_TEXTO 30

//Estructuras
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
Clase *crearclase();
CiudadDatos *crearCiudadDatos();
void CapturarDatos();



























#endif // FUNCIONES_H_INCLUDED
