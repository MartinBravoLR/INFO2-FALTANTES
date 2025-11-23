/// Informatica II: Alumno: Bravo Paulo Martin

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int es_primo(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }

    for (int divisor = 3; divisor <= (int)sqrt(n); divisor += 2) {
        if (n % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int num;

    do {
        printf("Ingrese un numero entero POSITIVO para verificar que sea primo: ");
        
        if (scanf("%d", &num) != 1) {
            printf("\nError de entrada. Por favor, ingrese un numero entero valido.\n");
            while (getchar() != '\n'); 
            num = 0; 
            continue;
        }
        
        if (num <= 0) {
            printf("\nEl numero debe ser POSITIVO. Intente de nuevo.\n");
        }
    } while (num <= 0); 

    if (es_primo(num)) {
        printf("\nEl numero %d es un numero primo.\n", num);
    } else {
        printf("\nEl numero %d no es un numero primo.\n", num);
    }

    return 0;
}