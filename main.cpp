#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// Estructura que contiene los parámetros para el hilo
struct parametros {
    int id;
    float escalar;
    float matriz[3][3];
};

// Función para inicializar la matriz con valores aleatorios
void init(float m[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = rand() % 100;  // Usar rand() en lugar de random()
        }
    }
}

// Función que multiplica cada elemento de la matriz por un escalar
void* matrizporescalar(void *arg) {
    struct parametros *p = (struct parametros *) arg;
    int i, j;
    for (i = 0; i < 3; i++) {
        printf("Hilo %d multiplicando fila %d\n", p->id, i);
        for (j = 0; j < 3; j++) {
            p->matriz[i][j] = p->matriz[i][j] * p->escalar;
            sleep(1);  // Reducir el tiempo de espera para pruebas más rápidas
        }
    }
    return NULL;
}

// Función para imprimir el contenido de la matriz
void print_matriz(float m[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%8.2f ", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    pthread_t thread;
    struct parametros p;
    p.id = 1;
    p.escalar = 2.5;
    
    init(p.matriz); // Inicializar la matriz
    printf("Matriz antes de la multiplicación:\n");
    print_matriz(p.matriz);

    // Crear hilo para multiplicar la matriz por el escalar
    pthread_create(&thread, NULL, matrizporescalar, &p);
    pthread_join(thread, NULL);

    printf("Matriz después de la multiplicación:\n");
    print_matriz(p.matriz);
    return 0;
}
