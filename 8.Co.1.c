///INFORMATICA II - ALUMNO: BRAVO PAULO MARTIN UTN-FRLR

#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo de la cola
typedef struct NodoCola {
    int dato;
    struct NodoCola *siguiente;
} TNodoCola;

// Estructura principal de la cola
typedef struct {
    TNodoCola *frente; // Primer elemento (por donde se desencola)
    TNodoCola *final;  // Último elemento (por donde se encola)
} TCola;

// Prototipos de funciones
void inicializar_cola(TCola *c);
int cola_vacia(TCola *c);
void encolar(TCola *c, int nuevo_dato);
int desencolar(TCola *c);

// Inicializa la cola
void inicializar_cola(TCola *c) {
    c->frente = NULL;
    c->final = NULL;
}

// Verifica si la cola está vacía
int cola_vacia(TCola *c) {
    return (c->frente == NULL);
}

// Agrega un elemento al final de la cola
void encolar(TCola *c, int nuevo_dato) {
    TNodoCola *nuevo_nodo = (TNodoCola*) malloc(sizeof(TNodoCola));
    if (nuevo_nodo == NULL) {
        printf("Error de memoria (encolar).\n");
        exit(1);
    }
    nuevo_nodo->dato = nuevo_dato;
    nuevo_nodo->siguiente = NULL;

    if (cola_vacia(c)) {
        c->frente = nuevo_nodo;
        c->final = nuevo_nodo;
    } else {
        c->final->siguiente = nuevo_nodo;
        c->final = nuevo_nodo;
    }
}

// Extrae y retorna el elemento del frente de la cola
int desencolar(TCola *c) {
    if (cola_vacia(c)) {
        printf("Error: Cola vacia. No se puede desencolar.\n");
        return -1; 
    }
    TNodoCola *temp = c->frente;
    int valor = temp->dato;

    c->frente = c->frente->siguiente;
    if (c->frente == NULL) {
        c->final = NULL; // Si queda vacía, el final también es NULL
    }
    free(temp);
    return valor;
}

int main() {
    TCola mi_cola;
    int valor, suma = 0;
    const int N = 10;

    // Inicialización de la cola
    inicializar_cola(&mi_cola);

    printf("--- Consigna 8: Cola Dinamica ---\n");
    
    // 1. Ingresar N (10) números a la cola
    printf("1. Llenando la cola con %d numeros:\n", N);
    for (int i = 0; i < N; i++) {
        printf("Ingrese numero %d: ", i + 1);
        scanf("%d", &valor);
        encolar(&mi_cola, valor);
    }

    // 2. Realizar la suma de los elementos que se van extrayendo
    printf("\n2. Extrayendo y sumando elementos...\n");
    while (!cola_vacia(&mi_cola)) {
        valor = desencolar(&mi_cola);
        printf("Desencolado: %d\n", valor);
        suma += valor;
    }

    printf("\n--- RESULTADO ---\n");
    printf("La suma total de los elementos extraidos es: %d\n", suma);

    return 0;
}