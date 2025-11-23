/// Informatica II: Alumno: Bravo Paulo Martin

#include <stdio.h>
#define SIZE 3

int main()
{
    double A[SIZE][SIZE];
    double B[SIZE][SIZE];
    double C[SIZE][SIZE];
    
    int fila, columna, indice_suma;

    printf("Introduce los datos de la primera matriz (A, tamaño %dx%d):\n", SIZE, SIZE);
    for (fila = 0; fila < SIZE; fila++)
    {
        for (columna = 0; columna < SIZE; columna++)
        {
            printf("Elemento A(%d,%d): ", fila + 1, columna + 1);
            scanf("%lf", &A[fila][columna]);
        }
    }

    printf("\nIntroduce los datos de la segunda matriz (B, tamaño %dx%d):\n", SIZE, SIZE);
    for (fila = 0; fila < SIZE; fila++)
    {
        for (columna = 0; columna < SIZE; columna++)
        {
            printf("Elemento B(%d,%d): ", fila + 1, columna + 1);
            scanf("%lf", &B[fila][columna]);
        }
    }

    for (fila = 0; fila < SIZE; fila++)
    {
        for (columna = 0; columna < SIZE; columna++)
        {
            C[fila][columna] = 0;
            for (indice_suma = 0; indice_suma < SIZE; indice_suma++)
            {
                C[fila][columna] += A[fila][indice_suma] * B[indice_suma][columna];
            }
        }
    }

    printf("\nLa matriz resultado C = A * B es:\n");
    for (fila = 0; fila < SIZE; fila++)
    {
        for (columna = 0; columna < SIZE; columna++)
        {
            printf("%10.4lf ", C[fila][columna]);
        }
        printf("\n");
    }

    return 0;
}