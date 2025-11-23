//Informatica II: Alumno BRAVO PAULO MARTIN

#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *elemento1, int *elemento2) {
    int temporal = *elemento1;
    *elemento1 = *elemento2;
    *elemento2 = temporal;
}

void ordenar_vector_recursivo(int arreglo[], int tamanio)
{
    if (tamanio == 1)
        return;
        
    for (int indice = 0; indice < tamanio - 1; indice++)
    {
        if (arreglo[indice] > arreglo[indice + 1])
        {
            intercambiar(&arreglo[indice], &arreglo[indice + 1]);
        }
    }
    
    ordenar_vector_recursivo(arreglo, tamanio - 1);
}

void mostrar_vector(int arreglo[], int tamanio)
{
    for (int indice = 0; indice < tamanio; indice++)
        printf("%d ", arreglo[indice]);
    printf("\n");
}

int main()
{
    int vector_a_ordenar[] = {5, 1, 9, 3, 2, 7, 4, 8, 6};
    int longitud = sizeof(vector_a_ordenar) / sizeof(vector_a_ordenar[0]);

    printf("Vector original:\n");
    mostrar_vector(vector_a_ordenar, longitud);

    ordenar_vector_recursivo(vector_a_ordenar, longitud);

    printf("Vector ordenado (Recursivo):\n");
    mostrar_vector(vector_a_ordenar, longitud);

    return 0;
}