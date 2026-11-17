#include "utilidades.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // Necesario para exit()


static int contador_aciertos = 0;

// Quita el salto de línea que agrega fgets.
void quitarSalto(char* cadena) {
    cadena[strcspn(cadena, "\n")] = '\0';
}

void limpiarCadenaAlfanumerica(char* cadena) {
    int i, j = 0;

    for (i = 0; cadena[i] != '\0'; i++) {
        // isalnum() es true si el carácter es alfabético (A-Z, a-z) o numérico (0-9).
        if (isalnum((unsigned char)cadena[i])) {
            // Solo copiamos los caracteres deseados
            cadena[j] = cadena[i];
            j++; // Avanzamos el índice de la nueva cadena
        }
    }

    // Aseguramos la terminación nula de la nueva cadena limpia.
    cadena[j] = '\0';
}

// Convierte toda la cadena a minúsculas.
void aMinusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        // Asegurarse de la conversión a unsigned char para evitar problemas con tolower en algunos sistemas.
        cadena[i] = tolower((unsigned char)cadena[i]);
    }
}

int validarCadenaAlpha(const char* cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isalpha((unsigned char)cadena[i]) || isspace((unsigned char)cadena[i]) ||
            cadena[i] == '-' || cadena[i] == '\'') {
            continue;
        }
        return 0;
    }
    return 1;
}

void capitalizarNombre(char* cadenaPalabra) {
    aMinusculas(cadenaPalabra);
    int i;
    int nuevaPalabra = 1;

    for (i = 0; cadenaPalabra[i] != '\0'; i++) {
        if (isspace((unsigned char)cadenaPalabra[i]) || cadenaPalabra[i] == '-' || cadenaPalabra[i] == '\'') {
            nuevaPalabra = 1;
        }
        else if (nuevaPalabra && isalpha((unsigned char)cadenaPalabra[i])) {
            cadenaPalabra[i] = toupper((unsigned char)cadenaPalabra[i]);
            nuevaPalabra = 0;
        }
    }
}


// Función para limpiar el búfer de entrada después de leer un número
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void borrarPantalla() {
   
#ifdef _WIN32
    system("cls"); // Para sistemas Windows
#else
    system("clear"); // Para Linux y macOS
#endif
}

int esBufferSoloEnter() {
    int c = fgetc(stdin); // Lee el primer carácter del buffer
    ungetc(c, stdin);     // Lo devuelve inmediatamente al buffer

    // Si el primer carácter es un salto de línea, o si la entrada falló (EOF),
    // asumimos que el usuario solo presionó Enter.
    if (c == '\n' || c == EOF) {
        return 1; // True (es buffer vacío o solo Enter)
    }
    return 0; // False (hay algo para leer)
}

// Implementación de las nuevas funciones de contador
void incrementar_aciertos() {
    contador_aciertos++;
}

int obtener_aciertos() {
    return contador_aciertos;
}

void resetear_aciertos() {
    contador_aciertos = 0;
}

// CORREGIDO: Elimina la recursión y devuelve la opción.
int continuarJuego() {
    int opcion = 0;

    // Se eliminó el bucle do-while y el switch con la llamada a main()
    printf("\n---------------------------------\n");
    printf("\nCantidad de aciertos: %d \n", contador_aciertos);
    printf("\n==================================\n");

    printf("\n1. Continuar Jugando\n");
    printf("2. Volver al Menu Principal\n");
    printf("3. Salir del programa\n");
    printf("\n----------------------------------\n");

    printf("Seleccione una opción: ");

    if (scanf_s("%d", &opcion) != 1) {
        opcion = 0;
    }

    limpiar_buffer(); // Usamos la función estándar para limpiar

    // Manejo de la opción de SALIR (CORRECCIÓN CRÍTICA)
    if (opcion == 3) {
        printf("¡Adiós! El programa ha terminado.\n");
        exit(0); // Termina el programa inmediatamente.
    }

    // Si la opción no es 1 o 2, la forzamos a 2 (Volver al Menú Principal)
    if (opcion < 1 || opcion > 3) {
        return 2;
    }

    return opcion;
}