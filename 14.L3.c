///INFORMATICA II - ALUMNO: BRAVO PAULO MARTIN UTN-FRLR

#include <stdio.h>
#include <stdlib.h>

// datos a float para cálculos precisos
typedef struct nodo {
    float corriente;
    float resistencia;
    float potencia;
    float voltios;
    struct nodo *siguiente;
} nodo;

// Función para liberar la memoria 
void liberar_memoria(nodo *inicio) {
    nodo *actual = inicio;
    nodo *siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

int main() {
    nodo *inicio = NULL;
    nodo *nuevo = NULL;
    nodo *aux = NULL;

    int opcion = 0;

    while (opcion != 4) {
        printf("\n1. Ingresar datos\n");
        printf("2. Mostrar datos (TABLA)\n");
        printf("3. Maximos y Minimos (Potencia)\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); 
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                nuevo = (nodo *)malloc(sizeof(nodo));
                if (nuevo == NULL) {
                    printf("Error: Memoria insuficiente.\n");
                    break;
                }
                
                printf("Ingrese la corriente: ");
                scanf("%f", &nuevo->corriente); // Usar %f para float
                printf("Ingrese la resistencia: ");
                scanf("%f", &nuevo->resistencia); // Usar %f para float

                // Voltios: producto de corriente por resistencia (V = I * R)
                nuevo->voltios = nuevo->corriente * nuevo->resistencia;
                
                // Potencia: cuadrado de la corriente por la resistencia (P = I^2 * R)
                nuevo->potencia = (nuevo->corriente * nuevo->corriente) * nuevo->resistencia;
                
                nuevo->siguiente = inicio;
                inicio = nuevo; 
                printf("Datos ingresados y calculados.\n");
                break;

            case 2:
                aux = inicio;
                if (!aux) {
                    printf("La lista esta vacia.\n");
                    break;
                }
                
                // Despliegue de la TABLA (Requisito de la consigna)
                printf("\n--- TABLA DE VALORES ---\n");
                printf("%-10s | %-12s | %-10s | %-10s\n", 
                       "CORRIENTE", "RESISTENCIA", "VOLTIOS", "POTENCIA");
                printf("----------------------------------------------------\n");

                while (aux != NULL) {
                    // Mostrar con 2 decimales
                    printf("%-10.2f | %-12.2f | %-10.2f | %-10.2f\n",
                           aux->corriente, aux->resistencia, aux->voltios, aux->potencia);
                    aux = aux->siguiente;
                }
                break;

            case 3:
                if (inicio == NULL) {
                    printf("La lista esta vacia.\n");
                    break;
                }
                
                float max, min; // Se usa float para que coincida con la potencia
                aux = inicio;
                max = min = aux->potencia;
                aux = aux->siguiente;

                while (aux != NULL) {
                    if (aux->potencia > max) max = aux->potencia;
                    if (aux->potencia < min) min = aux->potencia;
                    aux = aux->siguiente;
                }
                printf("Maximo: %.2f\n", max);
                printf("Minimo: %.2f\n", min);
                break;

            case 4:
                printf("Saliendo...\n");
                liberar_memoria(inicio);
                break;

            default:
                printf("Opcion invalida\n");
        }
    }

    return 0;
}