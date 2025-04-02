#include <stdlib.h>
#include <stdio.h>
#include "Funciones.h"
Clase *crearclase(){
    Clase *clasenueva;
    clasenueva=(Clase*)malloc(sizeof(Clase));
    if(clasenueva==NULL){
        printf("No se pudo asigar memoria para clase");
        exit(1);
    }
    clasenueva->belleza=( belleza*)calloc(1,sizeof(belleza));
    if(clasenueva->belleza==NULL){
        printf("No se pudo asigar memoria para belleza");
        exit(1);
    }
    clasenueva->belleza->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->belleza->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->belleza->precio=(float*)calloc(1,sizeof(float));
    clasenueva->belleza->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->belleza->nombre==NULL|| clasenueva->belleza->marca==NULL||clasenueva->belleza->precio==NULL||clasenueva->belleza->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de belleza");
        exit(1);
    }

    clasenueva->comida=(comida*)calloc(1,sizeof(comida));
    if(clasenueva->comida==NULL){
        printf("No se pudo asigar memoria para comida");
        exit(1);
    }
    clasenueva->comida->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->comida->bebida=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->comida->cantidad=(float*)calloc(1,sizeof(float));
    clasenueva->comida->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->comida->bebida==NULL|| clasenueva->comida->cantidad==NULL||clasenueva->comida->nombre==NULL||clasenueva->comida->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de comida");
        exit(1);
    }
    clasenueva->herramientas=(herramientas*)calloc(1,sizeof(herramientas));
    if(clasenueva->herramientas==NULL){
        printf("No se pudo asignar memoria para herramientas");
    }
    clasenueva->herramientas->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->herramientas->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->herramientas->precio=(float*)calloc(1,sizeof(float));
    clasenueva->herramientas->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->herramientas->nombre==NULL|| clasenueva->herramientas->marca==NULL||clasenueva->herramientas->precio==NULL||clasenueva->herramientas->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de herramienta");
        exit(1);
    }
    clasenueva->instrumentos=(instrumentos*)calloc(1,sizeof(instrumentos));
    if(clasenueva->instrumentos==NULL){
        printf("No se pudo asigar memoria para instrumentos");
        exit(1);   
    }
    clasenueva->instrumentos->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->instrumentos->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->instrumentos->precio=(float*)calloc(1,sizeof(float));
    clasenueva->instrumentos->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->instrumentos->nombre==NULL|| clasenueva->instrumentos->marca==NULL||clasenueva->instrumentos->precio==NULL||clasenueva->instrumentos->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de herramienta");
        exit(1);
    }
    clasenueva->juguetes=(juguetes*)calloc(1,sizeof(juguetes));
    if(clasenueva->juguetes==NULL){
        printf("No se pudo asigar memoria para juguetes");
        exit(1);
    }
    clasenueva->juguetes->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->juguetes->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->juguetes->precio=(float*)calloc(1,sizeof(float));
    clasenueva->juguetes->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->juguetes->nombre==NULL|| clasenueva->juguetes->marca==NULL||clasenueva->juguetes->precio==NULL||clasenueva->juguetes->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de juguetes");
        exit(1);
    }
    clasenueva->ropa=(ropa*)calloc(1,sizeof(ropa));
    if(clasenueva->ropa==NULL){
        printf("No se pudo asigar memoria para ropa");
        exit(1);
    }
    clasenueva->ropa->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->ropa->marca=(char*)calloc(MAX_TEXTO,sizeof(char));
    clasenueva->ropa->precio=(float*)calloc(1,sizeof(float));
    clasenueva->ropa->sobrante=(float*)calloc(1,sizeof(float));
    if(clasenueva->ropa->nombre==NULL|| clasenueva->ropa->marca==NULL||clasenueva->ropa->precio==NULL||clasenueva->ropa->sobrante==NULL){
        printf("No se pudo asigar memoria para los datos de juguetes");
        exit(1);
    }
    return clasenueva;
}
CiudadDatos *crearCiudadDatos(){
    CiudadDatos *nuevaCiudadDatos;
    nuevaCiudadDatos=(CiudadDatos*)malloc(sizeof(CiudadDatos));
    if(nuevaCiudadDatos==NULL){
        printf("No se pudo asignar memoria a nuevaciudaddatos");
        exit(1);
    }
    nuevaCiudadDatos->calle=(char*)calloc(MAX_TEXTO,sizeof(char));
    if(nuevaCiudadDatos->calle==NULL){
        printf("No se pudo asignar memoria a calle");
        exit(1);
    }
    nuevaCiudadDatos->ciudad=(char*)calloc(MAX_TEXTO,sizeof(char));
    if(nuevaCiudadDatos->ciudad==NULL){
        printf("No se pudo asignar memoria a ciudad");
        exit(1);
    }
    nuevaCiudadDatos->dinero=(float*)calloc(1,sizeof(float));
    if(nuevaCiudadDatos->dinero==NULL){
        printf("No se pudo asignar memoria a dinero");
        exit(1);
    }
    nuevaCiudadDatos->nombre=(char*)calloc(MAX_TEXTO,sizeof(char));
    if(nuevaCiudadDatos->nombre==NULL){
        printf("No se pudo asignar memoria a nombre");
        exit(1);
    }
    nuevaCiudadDatos->producto=(Clase*)calloc(1,sizeof(Clase));
    if(nuevaCiudadDatos->producto==NULL){
        printf("No se pudo asignar memoria a producto");
        exit(1);
    }
    return nuevaCiudadDatos;
    
}