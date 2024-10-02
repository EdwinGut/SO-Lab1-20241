#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Función para invertir el orden de las líneas en el archivo
void reverseFile(FILE *inputFile, FILE *outputFile) {
    char **lines = NULL;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    size_t lineCount = 0;

    // Leer todas las líneas del archivo de entrada
    while ((read = getline(&line, &len, inputFile)) != -1) {
        lines = realloc(lines, sizeof(char*) * (lineCount + 1));
        if (!lines) {
            fprintf(stderr, "malloc failed\n");
            free(line);
            exit(1);
        }
        lines[lineCount] = strdup(line);  // Duplicar la línea
        if (!lines[lineCount]) {
            fprintf(stderr, "malloc failed\n");
            free(line);
            exit(1);
        }
        lineCount++;
    }

    // Escribir las líneas en orden inverso en el archivo de salida
    for (int i = lineCount - 1; i >= 0; i--) {
        fprintf(outputFile, "%s", lines[i]);
        free(lines[i]);  // Liberar la memoria asignada para cada línea
    }

    free(lines);  // Liberar el array de líneas
    free(line);   // Liberar el buffer usado por getline
}

int main(int argc, char *argv[]) {
    // Verificar el número de argumentos
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    // Variables para almacenar los nombres de archivos
    char *inputFileName = NULL;
    char *outputFileName = NULL;

    // Si hay al menos un argumento, tomar el archivo de entrada
    if (argc >= 2) {
        inputFileName = argv[1];
        inputFile = fopen(inputFileName, "r");
        if (!inputFile) {
            // Error al abrir el archivo de entrada
            fprintf(stderr, "reverse: cannot open file '%s'\n", inputFileName);
            return 1;
        }
    }

    // Si hay dos argumentos, tomar también el archivo de salida
    if (argc == 3) {
        outputFileName = argv[2];

        // Verificar si los archivos de entrada y salida son el mismo archivo
        struct stat inputStat, outputStat;
        if (stat(inputFileName, &inputStat) == 0 && stat(outputFileName, &outputStat) == 0) {
            if (inputStat.st_ino == outputStat.st_ino) {
                fprintf(stderr, "reverse: input and output file must differ\n");
                fclose(inputFile);
                return 1;
            }
        }

        outputFile = fopen(outputFileName, "w");
        if (!outputFile) {
            fclose(inputFile);
            fprintf(stderr, "reverse: cannot open file '%s'\n", outputFileName);
            return 1;
        }
    }

    // Invertir el archivo de entrada y escribir el resultado en el archivo de salida
    reverseFile(inputFile, outputFile);

    // Cerrar los archivos si no son stdin y stdout
    if (inputFile != stdin) fclose(inputFile);
    if (outputFile != stdout) fclose(outputFile);

    return 0;
}
