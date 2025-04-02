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
};

typedef struct comida
{
    char *nombre;
    char *bebida;
    char *cantidad;
    int *sobrante;
}comida;
typedef struct belleza{
    char *nombre;
    char *marca;
    char *precio;
    int *sobrante;

    
}belleza;
typedef struct herramientas{
    char *nombre;
    char *marca;
    char *precio;
    int *sobrante;

}herramientas;
typedef struct ropa
{
    char *nombre;
    char *marca;
    char *precio;
    int *sobrante;
    
}ropa;
typedef struct juguetes{
    char *nombre;
    char *marca;
    char *precio;
    int *sobrante;

}juguetes;
typedef struct instrumentos
{
    char *nombre;
    char *marca;
    char *precio;
    int *sobrante;
}instrumentos;
Clase *crearclase(Clase *clasenueva);



























#endif // FUNCIONES_H_INCLUDED
