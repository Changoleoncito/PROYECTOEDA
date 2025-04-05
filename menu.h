#define MAX_MENU 30

typedef struct{
    int opcion[MAX_MENU];
    int t;
} Pila;

void inicializar_pila(Pila *p);
int pila_vacia(Pila *p);
int insertar_pila(Pila *p, int opcion);
int pop(Pila *p);