///INFORMATICA II: BRAVO PAULO MARTIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de datos para un registro
struct Entrada {
    char nombre_persona[50];
    int valor_entero;
};

// Nombre del archivo de almacenamiento
#define NOMBRE_FICHERO "datos_almacenados.txt"

// Prototipos de funciones del menú
void imprimir_menu();
void inicializar_fichero();
void insertar_entrada();
void leer_entradas();

int main() {
    int eleccion;

    // Bucle principal del menú
    do {
        imprimir_menu();
        printf("Ingrese su opcion: ");
        
        // Manejo de entrada no numérica
        if (scanf("%d", &eleccion) != 1) {
            while (getchar() != '\n'); // Limpia el buffer de entrada
            eleccion = 0; 
        }
        
        // Selector de opciones
        switch (eleccion) {
            case 1:
                inicializar_fichero();
                break;
            case 2:
                insertar_entrada();
                break;
            case 3:
                leer_entradas();
                break;
            case 4:
                printf("\nSaliendo del programa de gestion.\n");
                break;
            default:
                printf("\nOpcion no valida. Por favor, intente de nuevo.\n");
                break;
        }
        printf("\n----------------------------------------\n");
    } while (eleccion != 4);

    return 0;
}

// Muestra las opciones disponibles
void imprimir_menu() {
    printf("\n--- MENU DE GESTION DE FICHEROS ---\n");
    printf("1. Crear/Inicializar Fichero\n");
    printf("2. Insertar Nueva Entrada (Agregar Registro)\n");
    printf("3. Leer Entradas Almacenadas (Visualizar Registros)\n");
    printf("4. Salir\n");
}

// Inicializa o sobrescribe el archivo
void inicializar_fichero() {
    FILE *archivo_salida;
    
    archivo_salida = fopen(NOMBRE_FICHERO, "w");

    if (archivo_salida == NULL) {
        printf("ERROR: No se pudo crear el fichero %s.\n", NOMBRE_FICHERO);
    } else {
        printf("Fichero '%s' inicializado correctamente.\n", NOMBRE_FICHERO);
        fclose(archivo_salida);
    }
}

// Agrega un nuevo registro al final del archivo
void insertar_entrada() {
    FILE *archivo_salida;
    struct Entrada nueva_entrada;

    archivo_salida = fopen(NOMBRE_FICHERO, "a");

    if (archivo_salida == NULL) {
        printf("ERROR: No se pudo abrir el fichero %s para anadir datos.\n", NOMBRE_FICHERO);
        return;
    }

    printf("\nINSERTAR NUEVA ENTRADA\n");
    
    printf("Ingrese Nombre: ");
    while (getchar() != '\n'); // Limpia buffer antes de leer string
    fgets(nueva_entrada.nombre_persona, sizeof(nueva_entrada.nombre_persona), stdin);
    
    // Eliminar el caracter de nueva linea si fgets lo capturo
    nueva_entrada.nombre_persona[strcspn(nueva_entrada.nombre_persona, "\n")] = 0; 
    
    printf("Ingrese Valor Entero (Edad): ");
    // Manejo de entrada para el entero
    while (scanf("%d", &nueva_entrada.valor_entero) != 1) {
        printf("Entrada invalida. Ingrese un numero entero: ");
        while (getchar() != '\n'); 
    }

    // Escribir los datos en el fichero, separados por coma
    fprintf(archivo_salida, "%s,%d\n", nueva_entrada.nombre_persona, nueva_entrada.valor_entero);
    
    fclose(archivo_salida);
    printf("Entrada de '%s' agregada con exito.\n", nueva_entrada.nombre_persona);
}

// Lee y muestra todos los registros del archivo
void leer_entradas() {
    FILE *archivo_entrada;
    struct Entrada entrada_leida;
    int contador_entradas = 0;
    
    archivo_entrada = fopen(NOMBRE_FICHERO, "r");

    if (archivo_entrada == NULL) {
        printf("No se pudo abrir el fichero %s. Intente crearlo primero (Opcion 1).\n", NOMBRE_FICHERO);
        return;
    }

    printf("\n--- ENTRADAS ALMACENADAS ---\n");
    printf("| %-25s | %-10s |\n", "NOMBRE", "VALOR");
    printf("|---------------------------|------------|\n");

    // Lectura del fichero (formato: Nombre,Valor\n)
    while (fscanf(archivo_entrada, "%49[^,],%d\n", entrada_leida.nombre_persona, &entrada_leida.valor_entero) == 2) {
        
        printf("| %-25s | %-10d |\n", entrada_leida.nombre_persona, entrada_leida.valor_entero);
        contador_entradas++;
    }

    fclose(archivo_entrada);
    
    if (contador_entradas == 0) {
        printf("| %-36s |\n", "El fichero esta vacio.");
    } else {
        printf("|---------------------------|------------|\n");
        printf("Total de entradas: %d.\n", contador_entradas);
    }
}