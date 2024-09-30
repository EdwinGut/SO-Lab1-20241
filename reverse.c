#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liberar_memoria(char **lineas, int num_lineas) {
    for (int i = 0; i < num_lineas; i++) {
        free(lineas[i]);
    }
    free(lineas);
}

int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;
    char *inputFileName = NULL;
    char *outputFileName = NULL;

    // Verificar número de argumentos
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Si hay archivo de entrada
    if (argc >= 2) {
        inputFileName = argv[1];
        inputFile = fopen(inputFileName, "r");
        if (inputFile == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", inputFileName);
            exit(1);
        }
    }

    // Si hay archivo de salida
    if (argc == 3) {
        outputFileName = argv[2];
        // Verificar que los archivos de entrada y salida no sean el mismo
        if (strcmp(inputFileName, outputFileName) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        outputFile = fopen(outputFileName, "w");
        if (outputFile == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", outputFileName);
            fclose(inputFile);
            exit(1);
        }
    }

    // Leer el archivo línea por línea
    char **lineas = NULL;
    char *linea = NULL;
    size_t tamano = 0;
    size_t leido;
    int num_lineas = 0;

    while ((leido = getline(&linea, &tamano, inputFile)) != -1) {
        char **temp = realloc(lineas, (num_lineas + 1) * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "malloc failed\n");
            liberar_memoria(lineas, num_lineas);
            free(linea);
            exit(1);
        }
        lineas = temp;
        lineas[num_lineas] = strdup(linea);
        if (lineas[num_lineas] == NULL) {
            fprintf(stderr, "malloc failed\n");
            liberar_memoria(lineas, num_lineas);
            free(linea);
            exit(1);
        }
        num_lineas++;
    }

    free(linea);
    fclose(inputFile);

    // Imprimir las líneas en orden inverso
    for (int i = num_lineas - 1; i >= 0; i--) {
        fprintf(outputFile, "%s", lineas[i]);
        free(lineas[i]);
    }

    free(lineas);
    if (outputFile != stdout) {
        fclose(outputFile);
    }

    return 0;
}
