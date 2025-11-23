///INFORMATICA II - ALUMNO: BRAVO PAULO MARTIN UTN-FRLR

/* L.1 - Introduzca una función para localizar un alumno determinado
   por su Legajo para modificar sus datos o para eliminarlo. */
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   
   // Estructura de Alumno 
   typedef struct Alumno {
       int legajo;
       char nombre[50];
       float calificacion;
       float desviacion;
       struct Alumno *sig;
   } Alumno;
   
   // 1. Insertar alumno en una lista ORDENADA por legajo
   void insertar(Alumno **lista, int legajo, char nombre[], float calificacion) {
       Alumno *nuevo = (Alumno *)malloc(sizeof(Alumno));
       if (nuevo == NULL) {
           printf("Error: No se pudo asignar memoria.\n");
           return;
       }
       
       nuevo->legajo = legajo;
       strcpy(nuevo->nombre, nombre);
       nuevo->calificacion = calificacion;
       nuevo->desviacion = 0.0;
       nuevo->sig = NULL;
   
       Alumno *actual = *lista;
       Alumno *anterior = NULL;
   
       // Buscar la posición de inserción para mantener el ORDEN por legajo
       while (actual != NULL && actual->legajo < legajo) {
           anterior = actual;
           actual = actual->sig;
       }
   
       if (anterior == NULL) {
           // Insertar al inicio
           nuevo->sig = *lista;
           *lista = nuevo;
       } else {
           // Insertar en medio o al final
           anterior->sig = nuevo;
           nuevo->sig = actual;
       }
       printf("Alumno %s insertado en lista ordenada.\n", nombre);
   }
   
   // 2. Calcular el promedio de todas las calificaciones
   float calcular_promedio(Alumno *lista) {
       int contador = 0;
       float suma_calificaciones = 0.0;
       Alumno *actual = lista;
   
       while (actual != NULL) {
           suma_calificaciones += actual->calificacion;
           contador++;
           actual = actual->sig;
       }
   
       return (contador > 0) ? (suma_calificaciones / contador) : 0.0;
   }
   
   // 3. Determinar la desviación de cada nota (Nota - Promedio) y almacenarla
   void calcular_desviacion(Alumno *lista, float promedio) {
       Alumno *actual = lista;
       while (actual != NULL) {
           actual->desviacion = actual->calificacion - promedio;
           actual = actual->sig;
       }
       printf("Desviaciones calculadas. Promedio: %.2f\n", promedio);
   }
   
   // 4. Listar nombre, legajo, calificación y desviación.
   void listar_alumnos(Alumno *lista, float promedio) {
       Alumno *actual = lista;
       if (!actual) {
           printf("La lista esta vacia.\n");
           return;
       }
       
       printf("\n--- LISTADO DE ALUMNOS (L.1) ---\n");
       printf("Promedio General: %.2f\n", promedio);
       printf("%-8s | %-20s | %-12s | %-12s\n", 
              "LEGAJO", "NOMBRE", "CALIFICACION", "DESVIACION");
       printf("----------------------------------------------------------------\n");
       
       while (actual != NULL) {
           printf("%-8d | %-20s | %-12.2f | %-12.2f\n",
                  actual->legajo, actual->nombre, 
                  actual->calificacion, actual->desviacion);
           actual = actual->sig;
       }
       printf("----------------------------------------------------------------\n");
   }
   
   // Función para liberar la memoria al finalizar el programa
   void liberar_memoria(Alumno *lista) {
       Alumno *actual = lista;
       Alumno *siguiente = NULL;
       while (actual != NULL) {
           siguiente = actual->sig;
           free(actual);
           actual = siguiente;
       }
   }
   
   // Programa principal
   int main() {
       Alumno *lista = NULL;
       int opcion, legajo;
       float calificacion;
       char nombre[50];
       float promedio_actual = 0.0;
   
       do {
           printf("\n--- MENU (Solo L.1) ---\n");
           printf("1. Insertar alumno (Lista Ordenada)\n");
           printf("2. Calcular Promedio y Desviaciones\n");
           printf("3. Mostrar listado y resultados\n");
           printf("0. Salir\n");
           printf("Opcion: ");
           
           if (scanf("%d", &opcion) != 1) {
               while (getchar() != '\n'); 
               opcion = -1;
           }
   
           switch (opcion) {
               case 1:
                   printf("\n--- Insertar Alumno ---\n");
                   printf("Legajo: "); scanf("%d", &legajo);
                   printf("Nombre: "); scanf(" %[^\n]", nombre);
                   printf("Calificacion: "); scanf("%f", &calificacion);
                   insertar(&lista, legajo, nombre, calificacion);
                   
                   // Opción: Recalcular automáticamente después de insertar
                   promedio_actual = calcular_promedio(lista);
                   if (promedio_actual > 0) calcular_desviacion(lista, promedio_actual);
                   break;
                   
               case 2:
                   printf("\n--- Recalculo de L.1 ---\n");
                   promedio_actual = calcular_promedio(lista);
                   if (promedio_actual > 0) {
                        calcular_desviacion(lista, promedio_actual);
                   } else {
                        printf("No hay alumnos para calcular el promedio.\n");
                   }
                   break;
   
               case 3:
                   listar_alumnos(lista, promedio_actual);
                   break;
                   
               case 0:
                   printf("Saliendo...\n");
                   break;
                   
               default:
                   printf("Opcion invalida.\n");
           }
       } while (opcion != 0);
   
       liberar_memoria(lista);
       return 0;
   }