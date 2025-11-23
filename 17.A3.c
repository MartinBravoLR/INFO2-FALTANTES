//BRAVO PAULO MARTIN - INFO II

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nombre del fichero binario
#define NOMBRE_FICHERO "personas.dat"
#define MAX_REGISTROS_LISTA 10

// Estructura de datos para un registro
typedef struct {
    int id_documento;
    char nombre_persona[30];
} TRegistro;

// Nodo de la lista enlazada
typedef struct NodoLista {
    TRegistro dato;
    struct NodoLista *siguiente;
} TNodo;

// Prototipos de funciones
void anexar_registro(FILE *fichero);
void buscar_y_modificar(FILE *fichero);
TNodo* cargar_a_lista(FILE *fichero);
void mostrar_lista(TNodo *lista);
void liberar_lista(TNodo *lista);

int main() {
    FILE *fichero_datos;
    int opcion_menu;

    // Apertura del fichero en modo lectura/escritura binario. Si no existe, lo crea.
    fichero_datos = fopen(NOMBRE_FICHERO, "r+b");
    if (!fichero_datos) {
        fichero_datos = fopen(NOMBRE_FICHERO, "w+b");
        if (!fichero_datos) {
            printf("Error critico: No se pudo abrir o crear el fichero de datos.\n");
            return 1;
        }
    }

    do {
        printf("\n--- MENU DE GESTION DE PERSONAS ---\n");
        printf("1. Agregar nuevo registro\n");
        printf("2. Buscar por Documento y modificar Nombre\n");
        printf("3. Cargar primeros %d registros a una lista\n", MAX_REGISTROS_LISTA);
        printf("4. Salir\n");
        printf("Opcion: ");
        
        // Manejo de entrada no numérica
        if (scanf("%d", &opcion_menu) != 1) {
            while (getchar() != '\n'); 
            opcion_menu = 0; 
            continue;
        }

        switch(opcion_menu) {
            case 1:
                anexar_registro(fichero_datos);
                break;
            case 2:
                buscar_y_modificar(fichero_datos);
                break;
            case 3: {
                // Se crea la lista, se muestra y luego se libera la memoria
                TNodo *lista_personas = cargar_a_lista(fichero_datos);
                mostrar_lista(lista_personas);
                liberar_lista(lista_personas); // Liberar memoria es crucial
                break;
            }
            case 4:
                printf("\nSaliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion_menu != 4);

    fclose(fichero_datos);
    return 0;
}

// Agrega un nuevo registro al final del fichero
void anexar_registro(FILE *fichero) {
    TRegistro nuevo_registro;

    printf("\nIngrese numero de Documento: ");
    if (scanf("%d", &nuevo_registro.id_documento) != 1) return; 

    printf("Ingrese nombre: ");
    scanf("%s", nuevo_registro.nombre_persona); 

    fseek(fichero, 0, SEEK_END);
    fwrite(&nuevo_registro, sizeof(TRegistro), 1, fichero);

    printf("Registro agregado con Documento %d.\n", nuevo_registro.id_documento);
}

// Busca un registro por ID y permite modificar el nombre
void buscar_y_modificar(FILE *fichero) {
    int doc_a_buscar, encontrado = 0;
    TRegistro registro_leido;

    printf("\nDocumento a buscar para modificar: ");
    if (scanf("%d", &doc_a_buscar) != 1) return;

    rewind(fichero); // Volver al inicio del fichero

    while (fread(&registro_leido, sizeof(TRegistro), 1, fichero)) {
        if (registro_leido.id_documento == doc_a_buscar) {
            encontrado = 1;

            printf("Documento encontrado. Nombre actual: %s\n", registro_leido.nombre_persona);
            printf("Ingrese Nuevo Nombre: ");
            scanf("%s", registro_leido.nombre_persona);

            // Mover el puntero de archivo atrás un registro y sobrescribir
            fseek(fichero, -sizeof(TRegistro), SEEK_CUR);
            fwrite(&registro_leido, sizeof(TRegistro), 1, fichero);

            printf("Nombre modificado con exito.\n");
            break;
        }
    }

    if (!encontrado)
        printf("No se encontro el documento %d.\n", doc_a_buscar);
}

// Carga los primeros N (MAX_REGISTROS_LISTA) registros en una lista enlazada
TNodo* cargar_a_lista(FILE *fichero) {
    rewind(fichero);
    TNodo *lista = NULL, *nuevo_nodo, *ultimo_nodo = NULL;
    TRegistro registro_leido;
    int contador = 0;

    printf("\nIntentando cargar los primeros %d registros...\n", MAX_REGISTROS_LISTA);

    while (contador < MAX_REGISTROS_LISTA && fread(&registro_leido, sizeof(TRegistro), 1, fichero)) {
        nuevo_nodo = (TNodo*) malloc(sizeof(TNodo));
        if (!nuevo_nodo) {
            printf("Error de memoria al crear nodo.\n");
            return lista; // Devuelve la lista parcial
        }
        
        // Asignar datos y enlazar
        nuevo_nodo->dato = registro_leido;
        nuevo_nodo->siguiente = NULL;

        if (!lista) {
            lista = nuevo_nodo; // Primer nodo
        } else {
            ultimo_nodo->siguiente = nuevo_nodo; // Enlazar al final
        }

        ultimo_nodo = nuevo_nodo;
        contador++;
    }
    printf("Cargados %d registros en la lista.\n", contador);
    return lista;
}

// Muestra el contenido de la lista enlazada
void mostrar_lista(TNodo *lista) {
    printf("\n--- LISTA (Contenido) ---\n");
    if (!lista) {
        printf("La lista esta vacia.\n");
        return;
    }
    while (lista) {
        printf("Doc: %d | Nombre: %s\n",
               lista->dato.id_documento,
               lista->dato.nombre_persona);
        lista = lista->siguiente;
    }
}

// Libera la memoria asignada a la lista
void liberar_lista(TNodo *lista) {
    TNodo *temp;
    while (lista) {
        temp = lista;
        lista = lista->siguiente;
        free(temp);
    }
}