#include <stdio.h>
#include <string.h>

// Definición de una constante para el límite de caracteres del nombre de la materia
#define MAX_NOMBRE 35

void calcularPromedio()
{
    int n;

    // Pedir cantidad de materias hasta que el dato sea correcto
    while (1)
    {
        printf("Cantidad de materias a ingresar: ");

        if (scanf("%d", &n) != 1)
        {
            printf("Error: Debes ingresar un numero entero positivo.\n");
            while (getchar() != '\n');
            continue;
        }

        // Limpiar el salto de línea pendiente DESPUÉS de un scanf exitoso
        while (getchar() != '\n');

        if (n <= 1)
        {
            printf("Numero invalido. Debes ingresar al menos 2 materias.\n");
            continue;
        }

        break;
    }

    // Arrays de longitud variable (VLA)
    char materias[n][MAX_NOMBRE];
    double notas[n];
    double suma = 0;

    // Iteración para solicitar nombres y notas
    for (int i = 0; i < n; i++)
    {
        printf("\nNombre de la materia %d: ", i + 1);

        // Leer nombre completo de la materia
        if (fgets(materias[i], sizeof(materias[i]), stdin) == NULL)
        {
            fprintf(stderr, "Error al leer el nombre de la materia.\n");
            i--;
            continue;
        }

        // Quitar salto de línea final
        materias[i][strcspn(materias[i], "\n")] = '\0';

        while (1)
        {
            printf("Nota de %s (0-10, use punto para decimales): ", materias[i]);

            if (scanf("%lf", &notas[i]) != 1)
            {
                printf("Error: Debes ingresar un numero.\n");
                while (getchar() != '\n');
                continue;
            }

            // Limpiar buffer
            while (getchar() != '\n');

            if (notas[i] < 0.0 || notas[i] > 10.0)
            {
                printf("La nota debe estar entre 0 y 10.\n");
                continue;
            }

            break;
        }

        suma += notas[i];
    }

    double promedio = suma / n;

    // Mostrar resultados
    printf("\n--- Resultados ---\n");

    for (int i = 0; i < n; i++)
    {
        printf("Materia: %s | Nota: %.2f\n", materias[i], notas[i]);
    }

    printf("Promedio general: %.2f\n", promedio);
}

int main()
{
    calcularPromedio();
    return 0;
}