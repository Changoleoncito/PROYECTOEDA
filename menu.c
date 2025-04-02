#include <stdio.h>
#include "menu.h"

void inicializar_pila(Pila *p){
   p->t = -1;
}

int pila_vacia(Pila *p){
   return p->t == -1;
}

int insertar_pila(Pila *p, int opcion){
   if (p->t < MAX_MENU - 1) {
       p->opcion[++(p->t)] = opcion;
       return 1;
   }
   return 0;
}

int pop(Pila *p) {
   if (!pila_vacia(p)) {
       return p->opcion[(p->t)--];
   }
   return -1;
}