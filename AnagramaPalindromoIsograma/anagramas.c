#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "anagramas.h"
#include "utilidades.h" 

// <<< MAX_LONGITUD se toma de utilidades.h (50)


int comparar_caracteres(const void* a, const void* b) {
    return *(const char*)a - *(const char*)b;
}

/**
 * @brief Comprueba si word1 y word2 son anagramas usando qsort (insensible a mayúsculas y quitando \n).
 */
int son_anagramas_qsort(const char* word1, const char* word2) {

    // Uso de arreglos en la pila
    char cadenaTemp1[MAX_LONGITUD];
    char cadenaTemp2[MAX_LONGITUD];

    // ... (El resto de la función son_anagramas_qsort se mantiene igual)

    // **VERIFICACIÓN DE SEGURIDAD**
    if (strlen(word1) >= MAX_LONGITUD || strlen(word2) >= MAX_LONGITUD) {
        return 0;
    }

    // 1. Copia de las cadenas
    strcpy(cadenaTemp1, word1);
    strcpy(cadenaTemp2, word2);

    // 2. Limpieza y Transformación
    quitarSalto(cadenaTemp1);
    aMinusculas(cadenaTemp1);
    quitarSalto(cadenaTemp2);
    aMinusculas(cadenaTemp2);

    // 3. Obtener la longitud FINAL después de la limpieza
    size_t len1 = strlen(cadenaTemp1);
    size_t len2 = strlen(cadenaTemp2);

    // 4. Validación de Longitud (es el chequeo fundamental para anagramas)
    if (len1 != len2) {
        return 0;
    }

    // 5. Ordenamiento (Usando la longitud final, len1/len2)
    qsort(cadenaTemp1, len1, sizeof(char), comparar_caracteres);
    qsort(cadenaTemp2, len2, sizeof(char), comparar_caracteres);


    // 6. Comparación, Conteo de Puntos y Resultado
    int anagrama = (strcmp(cadenaTemp1, cadenaTemp2) == 0);

    if (anagrama) {
        incrementar_aciertos();
    }

    return anagrama;
}

void ejecutar_anagramas() {

    char word1_a[MAX_LONGITUD];
    char word2_a[MAX_LONGITUD];
    int opcion_continuar;

    // Bucle para "quedarse en el nivel"
    do {
        borrarPantalla();

        printf("**************************************\n");
        printf("*             ANAGRAMAS              *\n");
        printf("**************************************\n");

        // >>>>>>>>>>>>>>>>> ENTRADA Y VALIDACIÓN DE word1_a <<<<<<<<<<<<<<<<<<<<
        do {
            printf("Ingresa 1er Palabra: ");
            fgets(word1_a, MAX_LONGITUD, stdin);

            // 1. Limpieza de anagrama (quita \n, deja solo alfanuméricos)
            limpiarCadenaAlfanumerica(word1_a);

            // Si el usuario presiona solo ENTER, strlen(word1_a) es 0 después de limpiar.
            // Si ingresa números, !validarCadenaAlpha(word1_a) es true.
            if (strlen(word1_a) == 0 || !validarCadenaAlpha(word1_a)) {
                printf("ERROR: Solo se permiten letras y no puede estar vacía. Por favor, reintente.\n");
                // *** ¡IMPORTANTE! Se ELIMINA la llamada a limpiar_buffer() ***
                // *** ya que fgets ya consumió la línea. ***
            }

            else {
                capitalizarNombre(word1_a);
                break;
            }
        } while (1);

        // >>>>>>>>>>>>>>>>> ENTRADA Y VALIDACIÓN DE word2_a <<<<<<<<<<<<<<<<<<<<
        do {
            printf("Ingresa 2er Palabra: ");
            fgets(word2_a, MAX_LONGITUD, stdin);

            limpiarCadenaAlfanumerica(word2_a);

            if (strlen(word2_a) == 0 || !validarCadenaAlpha(word2_a)) {
                printf("ERROR: Solo se permiten letras y no puede estar vacía. Por favor, reintente.\n");
                // *** ¡IMPORTANTE! Se ELIMINA la llamada a limpiar_buffer() ***
            }
            else {
                capitalizarNombre(word2_a);
                break;
            }
        } while (1);


        printf("¿\"%s\" es anagrama de \"%s\"?: %s\n",
            word1_a, word2_a, son_anagramas_qsort(word1_a, word2_a) ? "Si" : "No");

        opcion_continuar = continuarJuego(); // Captura la opción

    } while (opcion_continuar == 1);
}