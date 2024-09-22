#include <stdio.h>
#include <string.h>  // Para manejo de cadenas
#include <stdlib.h>  // Para usar malloc y free

#define MAX_LINE_LENGTH 1024  // Definir un valor máximo para las líneas

int main() {
    char buffer[MAX_LINE_LENGTH];  // Declarar un buffer para almacenar las líneas
    char *lineas[100];  // Un arreglo de punteros para almacenar varias líneas
    int contador = 0;

    // Leer líneas desde la entrada estándar
    while (fgets(buffer, MAX_LINE_LENGTH, stdin)) {
        lineas[contador] = strdup(buffer);  // Copiar la línea al arreglo
        contador++;
    }

    // Imprimir las líneas en orden inverso
    for (int i = contador - 1; i >= 0; i--) {
        printf("%s", lineas[i]);  // Imprimir cada línea en orden inverso
        free(lineas[i]);  // Liberar la memoria después de imprimir
    }

    return 0;
}
