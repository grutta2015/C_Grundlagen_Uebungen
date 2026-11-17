#include <stdio.h>

#define MAX_FILAS 30
#define MAX_COLS 20

// Variables Globales: Almacenan el estado y el tamaño actual de la sala.
char sala[MAX_FILAS][MAX_COLS];
int num_filas = 0;
int num_columnas = 0;

// ---------------------------------------------------------------------
// FUNCIÓN 1: Inicializa el tamaño de la sala y todas las butacas a 'L'
// ---------------------------------------------------------------------
void inicializar_sala()
{
    printf("---< CONFIGURACION INICIAL >---\n");

    // Validar Filas
    do
    {
        printf("Introduce la cantidad de Filas (1 a %d): ", MAX_FILAS);
        scanf("%d", &num_filas);

        if (num_filas <= 0 || num_filas > MAX_FILAS)
        {
            printf("Error: Ingresa un numero de Filas valido (1 a %d).\n", MAX_FILAS);
        }
    }
    while (num_filas <= 0 || num_filas > MAX_FILAS);

    // Validar Columnas
    do
    {
        printf("Introduce la cantidad de Columnas (1 a %d): ", MAX_COLS);
        scanf("%d", &num_columnas);

        if (num_columnas <= 0 || num_columnas > MAX_COLS)
        {
            printf("Error: Ingresa un numero de Columnas valido (1 a %d).\n", MAX_COLS);
        }
    }
    while (num_columnas <= 0 || num_columnas > MAX_COLS);

    // Llenar la matriz con 'L' (Libre)
    for (int i = 0; i < num_filas; i++)
    {
        for (int j = 0; j < num_columnas; j++)
        {
            sala[i][j] = 'L';
        }
    }
}

// ---------------------------------------------------------------------
// FUNCIÓN 2: Muestra el estado actual de las butacas
// ---------------------------------------------------------------------
void mostrar_sala()
{
    printf("\n---< ESTADO ACTUAL DE LA SALA >---\n");

    // Encabezado de Columnas
    printf("   ");

    for (int c = 0; c < num_columnas; c++)
    {
        printf(" %2d", c + 1);
    }

    printf("\n");

    // Borde Superior
    printf("   o");

    for (int c = 0; c < num_columnas; c++)
    {
        printf("___");
    }

    printf(" o\n");

    // Impresión de Filas y Butacas
    for (int f = 0; f < num_filas; f++)
    {
        printf("%2d | ", f + 1);

        for (int c = 0; c < num_columnas; c++)
        {
            printf("%c  ", sala[f][c]);
        }

        printf("|\n");
    }

    // Borde Inferior
    printf("   o");

    for (int c = 0; c < num_columnas; c++)
    {
        printf("___");
    }

    printf(" o\n\n");
}

// ---------------------------------------------------------------------
// FUNCIÓN 3: Permite al usuario ocupar, liberar o salir
// ---------------------------------------------------------------------
int gestionar_butaca()
{
    int fila;
    int columna;
    char confirmacion;
    int continuar = 1;

    printf("\n---< GESTIONANDO BUTACA >---\n");
    printf("\n(Pulsa 0 para SALIR)\n");

    // 1. SOLICITAR Y VALIDAR FILA
    do
    {
        printf("Introduce la fila (1 a %d): ", num_filas);

        if (scanf("%d", &fila) != 1)
        {
            printf("Error: Ingresa un numero.\n");

            while (getchar() != '\n');

            fila = -1;
        }
        else if (fila == 0)
        {
            return 0;
        }
        else if (fila < 1 || fila > num_filas)
        {
            printf("Error: Fila fuera de los limites definidos.\n");
        }
    }
    while (fila < 1 || fila > num_filas);

    // 2. SOLICITAR Y VALIDAR COLUMNA
    do
    {
        printf("Introduce la columna (1 a %d): ", num_columnas);

        if (scanf("%d", &columna) != 1)
        {
            printf("Error: Ingresa un numero.\n");

            while (getchar() != '\n');

            columna = -1;
        }
        else if (columna == 0)
        {
            return 0;
        }
        else if (columna < 1 || columna > num_columnas)
        {
            printf("Error: Columna fuera de los limites definidos.\n");
        }
    }
    while (columna < 1 || columna > num_columnas);

    // Conversión de índices
    int i = fila - 1;
    int j = columna - 1;

    // 3. CAMBIAR EL ESTADO
    if (sala[i][j] == 'L')
    {
        sala[i][j] = 'X';
        printf("Butaca (%d, %d) ocupada.\n", fila, columna);
    }
    else
    {
        printf("La butaca (%d, %d) ya esta ocupada.\n", fila, columna);

        do
        {
            printf("Deseas liberarla? (s/n): ");

            while (getchar() != '\n');

            if (scanf(" %c", &confirmacion) != 1)
            {
                confirmacion = ' ';
            }

            if (confirmacion == 's' || confirmacion == 'S')
            {
                sala[i][j] = 'L';
                printf("Butaca (%d, %d) liberada.\n", fila, columna);
                break;
            }
            else if (confirmacion == 'n' || confirmacion == 'N')
            {
                printf("Butaca (%d, %d) mantenida como ocupada.\n", fila, columna);
                break;
            }
            else
            {
                printf("Error. Ingresa S o N.\n");
            }
        }
        while (1);
    }

    return continuar;
}

// ---------------------------------------------------------------------
// FUNCIÓN 4: Principal
// ---------------------------------------------------------------------
int main()
{
    int continuar = 1;

    inicializar_sala();

    do
    {
        mostrar_sala();

        continuar = gestionar_butaca();

        printf("\n____________________________________________\n");
        printf("\n********************************************\n");
    }
    while (continuar != 0);

    printf("Saliendo del programa. Gracias por usar la gestion de sala.\n");

    return 0;
}