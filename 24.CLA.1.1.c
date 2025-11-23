//Informatica II: Alumno BRAVO PAULO MARTIN

#include <stdio.h>

// Definición de la estructura para representar el tiempo
struct Tiempo {
    int hrs;      // Almacena horas
    int mins;     // Almacena minutos
    int segs;     // Almacena segundos
};

// --- Funciones para manipular la estructura ---

// Asigna nuevos valores a los miembros de la estructura
void establecer_tiempo(struct Tiempo *t, int h, int m, int s) {
    t->hrs = h;
    t->mins = m;
    t->segs = s;
}

// Muestra el tiempo en formato HH:MM:SS
void imprimir_tiempo(struct Tiempo t) {
    printf("%02d:%02d:%02d\n", t.hrs, t.mins, t.segs);
}

// Constructor por defecto: Inicializa el tiempo a 00:00:00
struct Tiempo crear_tiempo_cero() {
    struct Tiempo t_nuevo;
    t_nuevo.hrs = 0;
    t_nuevo.mins = 0;
    t_nuevo.segs = 0;
    return t_nuevo;
}

// Constructor con parámetros: Inicializa el tiempo con valores dados
struct Tiempo crear_tiempo(int h, int m, int s) {
    struct Tiempo t_nuevo;
    t_nuevo.hrs = h;
    t_nuevo.mins = m;
    t_nuevo.segs = s;
    return t_nuevo;
}

int main() {
    // Uso del constructor por defecto (00:00:00)
    struct Tiempo t1 = crear_tiempo_cero(); 
    // Uso del constructor con parámetros
    struct Tiempo t2 = crear_tiempo(12, 45, 30); 

    // Muestra el tiempo inicial de t1 y t2
    imprimir_tiempo(t1);
    imprimir_tiempo(t2);

    // Modifica los valores de t1 usando el puntero
    establecer_tiempo(&t1, 8, 5, 9); 
    // Muestra el nuevo tiempo de t1
    imprimir_tiempo(t1);

    return 0;
}