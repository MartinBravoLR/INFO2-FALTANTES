#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// La ficha del alumno (legajo, nombre, la Nota y el Desvío)
typedef struct Alumno {
    int legajo;
    char nombre[50];
    float calificacion; // La Nota
    float desviacion;   // El Desvío
    struct Alumno *sig;
} Alumno;

// Mete al alumno y lo deja ORDENADO
void insertar(Alumno **lista, int legajo, char nombre[], float calificacion) {
    Alumno *nuevo = (Alumno *)malloc(sizeof(Alumno));
    if (nuevo == NULL) {
        printf("Error: No hay memoria.\n");
        return;
    }
    
    nuevo->legajo = legajo;
    strcpy(nuevo->nombre, nombre);
    nuevo->calificacion = calificacion;
    nuevo->desviacion = 0.0;
    nuevo->sig = NULL;

    Alumno *actual = *lista;
    Alumno *anterior = NULL;


    while (actual != NULL && actual->legajo < legajo) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        // Al inicio
        nuevo->sig = *lista;
        *lista = nuevo;
    } else {
        // En el medio o al final
        anterior->sig = nuevo;
        nuevo->sig = actual;
    }
    printf("Alumno %s insertado.\n", nombre);
}

// Calcula el promedio de todas las Notas
float calcular_promedio(Alumno *lista) {
    int contador = 0;
    float suma_calificaciones = 0.0;
    Alumno *actual = lista;

    while (actual != NULL) {
        suma_calificaciones += actual->calificacion;
        contador++;
        actual = actual->sig;
    }

    // Calcula el promedio (suma / cantidad)
    return (contador > 0) ? (suma_calificaciones / contador) : 0.0;
}

// Calcula el Desvío (Nota menos el promedio) y lo guarda
void calcular_desviacion(Alumno *lista, float promedio) {
    Alumno *actual = lista;
    while (actual != NULL) {
        // Acá se hace la resta y se guarda
        actual->desviacion = actual->calificacion - promedio; 
        actual = actual->sig;
    }
    printf("Desvíos calculados. Promedio: %.2f\n", promedio);
}

// Muestra la lista con Nombre, Legajo, Nota y Desvío
void listar_alumnos(Alumno *lista, float promedio) {
    Alumno *actual = lista;
    if (!actual) {
        printf("Lista vacia.\n");
        return;
    }
    
    printf("\n--- LISTADO DE ALUMNOS ---\n");
    printf("Promedio General: %.2f\n", promedio);
    printf("%-8s | %-20s | %-12s | %-12s\n", 
           "LEGAJO", "NOMBRE", "NOTA", "DESVÍO");
    printf("----------------------------------------------------------------\n");
    
    while (actual != NULL) {
        printf("%-8d | %-20s | %-12.2f | %-12.2f\n",
               actual->legajo, actual->nombre, 
               actual->calificacion, actual->desviacion);
        actual = actual->sig;
    }
    printf("----------------------------------------------------------------\n");
}

// Busca por legajo y MODIFICA los datos (Nota y Nombre)
void modificar(Alumno *lista, int legajo) {
    Alumno *actual = lista;
    while (actual != NULL) {
        if (actual->legajo == legajo) {
            printf("¡Alumno encontrado! Nuevos datos:\n");
            printf("Nuevo nombre: ");
            scanf(" %[^\n]", actual->nombre);
            printf("Nueva Nota: ");
            scanf("%f", &actual->calificacion);
            printf("Alumno modificado.\n");
            return;
        }
        actual = actual->sig;
    }
    printf("No se encontro alumno %d\n", legajo);
}

// Busca por legajo y ELIMINA al alumno
void eliminar(Alumno **lista, int legajo) {
    Alumno *actual = *lista;
    Alumno *anterior = NULL;
    
    // Lo busca
    while (actual != NULL && actual->legajo != legajo) {
        anterior = actual;
        actual = actual->sig;
    }
    
    if (actual == NULL) {
        printf("No se encontro el alumno %d\n", legajo);
        return;
    }
    
    // Si es el primero
    if (actual == *lista) { 
        *lista = actual->sig;
    } 
    // Si es otro
    else { 
        anterior->sig = actual->sig;
    }
    
    free(actual); // ¡Memoria libre!
    printf("Alumno %d eliminado.\n", legajo);
}

// Limpia toda la memoria de la lista antes de salir
void liberar_memoria(Alumno *lista) {
    Alumno *actual = lista;
    Alumno *siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }
}

int main() {
    Alumno *lista = NULL;
    int opcion, legajo;
    float calificacion;
    char nombre[50];
    float promedio_actual = 0.0;

    do {
        printf("\n--- MENU GENERAL ---\n");
        printf("1. Insertar alumno\n");
        printf("2. Mostrar listado\n");
        printf("3. Modificar alumno\n");
        printf("4. Eliminar alumno\n");
        printf("5. Recalcular Promedio y Desvíos\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); 
            opcion = -1;
        }
        
        int debe_recalcular = 0; // Si esto es 1, actualiza los números

        switch (opcion) {
            case 1:
                printf("\n--- Insertar ---\n");
                printf("Legajo: "); scanf("%d", &legajo);
                printf("Nombre: "); scanf(" %[^\n]", nombre);
                printf("Nota: "); scanf("%f", &calificacion);
                insertar(&lista, legajo, nombre, calificacion);
                debe_recalcular = 1;
                break;
                
            case 2:
                listar_alumnos(lista, promedio_actual);
                break;
                
            case 3:
                printf("\n--- Modificar ---\n");
                printf("Legajo a modificar: "); 
                scanf("%d", &legajo);
                modificar(lista, legajo);
                debe_recalcular = 1;
                break;
                
            case 4:
                printf("\n--- Eliminar ---\n");
                printf("Legajo a eliminar: "); 
                scanf("%d", &legajo);
                eliminar(&lista, legajo);
                debe_recalcular = 1;
                break;

            case 5:
                debe_recalcular = 1;
                break;
                
            case 0:
                printf("Saliendo...\n");
                break;
                
            default:
                printf("Opcion invalida.\n");
        }
        
        // Si se alteró la lista 
        if (debe_recalcular) {
            promedio_actual = calcular_promedio(lista);
            if (promedio_actual > 0) {
                 calcular_desviacion(lista, promedio_actual);
            } else if (opcion != 0) {
                 printf("Lista vacia, promedio reseteado.\n");
            }
        }
    } while (opcion != 0);

    liberar_memoria(lista);
    return 0;
}