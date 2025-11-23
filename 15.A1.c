///INFORMATICA II : BRAVO PAULO MARTIN

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Estructura de registro para el archivo binario: num_linea, cant_palabras, cant_signos
typedef struct {
    int numero_linea;
    int cuenta_palabras;
    int cuenta_signos;
} RegistroContador;

// Función auxiliar para verificar si un carácter es un signo de puntuación definido
int es_puntuacion_especial(char c) {
    const char signos_a_contar[] = ".,;:?!()[]{}\"\'";
    for (int i = 0; signos_a_contar[i] != '\0'; i++) {
        if (c == signos_a_contar[i]) return 1;
    }
    return 0;
}

int main() {
    // Apertura de archivos (entrada: palabras.txt, salida: contador.dat)
    FILE *f_entrada = fopen("palabras.txt", "r");
    FILE *f_salida = fopen("contador.dat", "wb");

    // Manejo de errores de apertura
    if (!f_entrada) {
        printf("Error: No se pudo abrir palabras.txt (verifique que exista)\n");
        return 1;
    }
    if (!f_salida) {
        printf("Error: No se pudo crear contador.dat\n");
        fclose(f_entrada);
        return 1;
    }

    char linea_buffer[512]; 
    int contador_lineas = 0;

    // Bucle principal: Leer el archivo de texto línea por línea
    while (fgets(linea_buffer, sizeof(linea_buffer), f_entrada)) {
        contador_lineas++;

        RegistroContador registro_actual;
        registro_actual.numero_linea = contador_lineas;
        registro_actual.cuenta_palabras = 0;
        registro_actual.cuenta_signos = 0;

        int en_palabra = 0; // Bandera para el conteo de palabras

        // Iterar sobre cada carácter de la línea
        for (int i = 0; linea_buffer[i] != '\0'; i++) {
            char caracter = linea_buffer[i];

            // Contar signos de puntuación
            if (es_puntuacion_especial(caracter)) {
                registro_actual.cuenta_signos++;
            }

            // Lógica para contar palabras
            if (isspace(caracter)) {
                if (en_palabra) {
                    registro_actual.cuenta_palabras++;
                    en_palabra = 0; 
                }
            } else { 
                if (!en_palabra) en_palabra = 1; 
            }
        }

        // Finalizar el conteo si la línea termina con una palabra
        if (en_palabra) registro_actual.cuenta_palabras++;

        // Escribir el registro en el archivo binario
        fwrite(&registro_actual, sizeof(RegistroContador), 1, f_salida);
    }

    // Cierre de archivos
    fclose(f_entrada);
    fclose(f_salida);

    printf("Proceso completado. Se analizaron %d lineas y los resultados se guardaron en contador.dat\n", contador_lineas);

    return 0;
}