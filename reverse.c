#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invertir_lineas(FILE *entrada, FILE *salida) {
    char *lineas[100];
    char buffer[256];
    int contador = 0;

    // Leer las líneas del archivo de entrada
    while (fgets(buffer, sizeof(buffer), entrada) != NULL && contador < 100) {
        lineas[contador] = strdup(buffer);  // Guardar copia de cada línea
        contador++;
    }

    // Escribir las líneas en orden inverso en el archivo de salida
    for (int i = contador - 1; i >= 0; i--) {
        fprintf(salida, "%s", lineas[i]);   // Imprimir cada línea respetando los saltos de línea
        free(lineas[i]);                    // Liberar memoria después de usar la línea
    }
}

int main(int argc, char *argv[]) {
    FILE *entrada = stdin;  // Entrada por defecto es stdin
    FILE *salida = stdout;  // Salida por defecto es stdout

    if (argc == 1) {
        // Caso 1: Sin argumentos, leer de stdin y escribir en stdout
        printf("Introduce líneas de texto y presiona Ctrl + D para finalizar:\n");
        invertir_lineas(entrada, salida);
    } else if (argc == 2) {
        // Caso 2: Un argumento, leer de un archivo y escribir en stdout
        entrada = fopen(argv[1], "r");
        if (entrada == NULL) {
            perror("Error al abrir el archivo de entrada");
            return 1;
        }
        invertir_lineas(entrada, salida);
        fclose(entrada);
    } else if (argc == 3) {
        // Caso 3: Dos argumentos, leer de un archivo y escribir en otro archivo
        entrada = fopen(argv[1], "r");
        if (entrada == NULL) {
            perror("Error al abrir el archivo de entrada");
            return 1;
        }
        salida = fopen(argv[2], "w");
        if (salida == NULL) {
            perror("Error al abrir el archivo de salida");
            fclose(entrada);
            return 1;
        }
        invertir_lineas(entrada, salida);
        fclose(entrada);
        fclose(salida);
    } else {
        // Más de dos argumentos, mostrar error
        fprintf(stderr, "Uso: %s [archivo_entrada] [archivo_salida]\n", argv[0]);
        return 1;
    }

    return 0;
}
