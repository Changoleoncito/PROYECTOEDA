#include <stdlib.h>
#include "Funciones.h"
Clase *crearclase(){
    Clase *clasenueva;
    clasenueva=(Clase*)malloc(sizeof(Clase));
    if(clasenueva==NULL){
        printf("No se pudo asigar memoria...");
    }
    clasenueva->belleza=( belleza*)malloc(sizeof(belleza));

}