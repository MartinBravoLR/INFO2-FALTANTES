//Informatica II: Alumno BRAVO PAULO MARTIN

#include <stdio.h>
#include <string.h>
#include <math.h>

void to_bin(int num, char bits[])
{
    for (int i = 7; i >= 0; i--)
    {
        bits[7 - i] = ((num >> i) & 1) + '0';
    }
    bits[8] = '\0';
}

char calc_paridad_impar(const char bits[])
{
    int contador_unos = 0;

    for (int i = 0; i < 8; i++)
    {
        if (bits[i] == '1')
            contador_unos++;
    }

    return (contador_unos % 2 == 0) ? '1' : '0';
}

int main()
{
    char palabra[50];
    char bits_datos[9];

    printf("Ingrese una palabra: ");
    scanf("%s", palabra);

    printf("\nSecuencia de bits a transmitir (8 bits + paridad impar):\n");

    for (int i = 0; i < strlen(palabra); i++)
    {
        int valor_ascii = (int)palabra[i];

        to_bin(valor_ascii, bits_datos);

        char bit_paridad = calc_paridad_impar(bits_datos);

        printf("\nCaracter: '%c' | ASCII: %d\n", palabra[i], valor_ascii);
        printf("Datos (8 bits): %s\n", bits_datos);
        printf("Paridad (Impar): %c\n", bit_paridad);
        printf("Secuencia TX: %s%c\n", bits_datos, bit_paridad);
    }

    return 0;
}