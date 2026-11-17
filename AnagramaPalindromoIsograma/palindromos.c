#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> 
#include "utilidades.h" 
#include "palindromos.h"


// --- Función Principal de Palíndromo ---

/**
 * @brief Comprueba si una cadena es un palíndromo, ignorando espacios, puntuación y caso.
 * @param cadena La cadena de entrada (puede ser una palabra o frase).
 * @return true si es un palíndromo, false en caso contrario.
 */
bool esPalindromo(char* cadena) {

    // Buffer temporal para la copia de entrada
    char cadenaTemp[MAX_LONGITUD];

    // Buffer final que solo contendrá las letras para la comparación
    char cadenaLimpia[MAX_LONGITUD];
    int j = 0; // Índice para cadenaLimpia

    // 1. Copia Segura (Se utiliza la longitud MAX_LONGITUD de utilidades.h)
    strncpy(cadenaTemp, cadena, MAX_LONGITUD - 1);
    cadenaTemp[MAX_LONGITUD - 1] = '\0';

    // 2. Limpieza de Preprocesamiento
    quitarSalto(cadenaTemp);

    // 3. Limpieza de Palíndromo: Solo mantener letras y convertir a minúsculas
    for (int i = 0; cadenaTemp[i] != '\0'; i++) {
        // CORRECCIÓN CLAVE: Solo copiamos caracteres alfabéticos (ignoramos espacios, puntuación, números)
        if (isalpha((unsigned char)cadenaTemp[i])) {
            // Convertir a minúscula y guardar en el buffer limpio
            cadenaLimpia[j] = tolower((unsigned char)cadenaTemp[i]);
            j++;
        }
    }
    cadenaLimpia[j] = '\0'; // Asegurar terminación


    // 4. Comprobación del Palíndromo sobre cadenaLimpia
    size_t longitud = strlen(cadenaLimpia);
    size_t inicio = 0;
    size_t fin = longitud - 1;

    while (inicio < fin) {
        // La comparación es directa ya que cadenaLimpia solo contiene minúsculas.
        if (cadenaLimpia[inicio] != cadenaLimpia[fin]) {
            return false;
        }
        inicio++;
        fin--;
    }

    // Si es palíndromo, sumar el punto
    incrementar_aciertos();
    return true;
}

void ejecutar_palindromos() {
    char word1_a[MAX_LONGITUD];
    bool resultado;
    int opcion_continuar;

    // Bucle para "quedarse en el nivel"
    do {
        borrarPantalla();

        printf("**************************************\n");
        printf("*            PALINDROMOS             *\n");
        printf("**************************************\n");

        // BUCLE DE VALIDACIÓN DE ENTRADA (Solo permite letras y espacios)
        do {
            printf("Ingresa Palabra o frase: ");
            fgets(word1_a, MAX_LONGITUD, stdin);

            // Solo quitamos el salto de línea para validar
            quitarSalto(word1_a);

            // Usamos validarCadenaAlpha, que permite letras, espacios, guiones y apóstrofes.
            if (!validarCadenaAlpha(word1_a)) {
                printf("ERROR: Solo se permiten letras, espacios y puntuación básica. Números no.\n");
                limpiar_buffer();
            }
            else {
                // Si es válido, aplicamos el formato (capitalizar) y salimos del bucle de entrada
                capitalizarNombre(word1_a);
                break;
            }
        } while (1);

        // La verificación de palíndromo ocurre después de una entrada válida
        resultado = esPalindromo(word1_a);
        printf("'%s' es un palindromo? %s\n", word1_a, resultado ? "Si" : "No");

        // Pregunta para continuar jugando o volver al menú
        opcion_continuar = continuarJuego();

    } while (opcion_continuar == 1); // Continúa si la opción es 1
}