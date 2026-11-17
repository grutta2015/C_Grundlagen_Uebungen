#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>  

#include "anagramas.h"
#include "palindromos.h"
#include "utilidades.h"


// La variable error_en_menu se ELIMINA para simplificar.


int main() {
    int opcion = -1; // Inicializar a un valor inválido para la primera ejecución
    int error_detectado; // Variable local para controlar el mensaje de error

    // 1. Configuración de la consola
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");


    do {
        // Al inicio de la iteración, asumimos que no hay error, y reseteamos el contador.
        error_detectado = 0;
        resetear_aciertos();

        // BORRAR PANTALLA
        borrarPantalla();

        printf("**************************************\n");
        printf("*             BIENVENIDO             *\n");
        printf("**************************************\n");

        printf("\n\n---- JUGAR: ----\n");
        printf("1. Anagramas\n");
        printf("2. Palíndromos\n");
        printf("0. Salir\n");

        // >>>>>>>>>>>>>>>>> BUCLE DE LECTURA Y VALIDACIÓN <<<<<<<<<<<<<<<<<<<<
        do {
            // Imprimir el prompt de entrada
            if (error_detectado > 0) {
                printf("\n¡Opción no válida! Ingrese una opción válida (0-2): ");
            }
            else {
                printf("Seleccione una opción: ");
            }

            // A. VERIFICACIÓN ANTES DE SCANF_S: ¿Solo se presionó Enter?
            if (esBufferSoloEnter()) {
                // Si solo hay un \n en el buffer, forzamos un error
                limpiar_buffer(); // Limpiamos ese \n
                opcion = -1;
            }
            // B. Si no es buffer vacío, intentamos leer el número
            else if (scanf_s("%d", &opcion) != 1) {
                // Falla: Se ingresó una letra o símbolo.
                limpiar_buffer(); // Limpiar el carácter no numérico restante y el \n
                opcion = -1;      // Forzar la repetición
            }
            // C. Si es un número válido (éxito de scanf_s)
            else {
                limpiar_buffer(); // Limpiar el \n restante después del número
            }

            // Si la opción está fuera del rango [0, 2], es un error
            if (opcion < 0 || opcion > 2) {
                error_detectado++;
            }
            else {
                error_detectado = 0;
            }

        } while (opcion < 0 || opcion > 2);

        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        switch (opcion) {
        case 1:
            ejecutar_anagramas();
            break;
        case 2:
            ejecutar_palindromos();
            break;
        case 0:
            printf("\n¡Adiós! El programa ha terminado.\n");
            break;
        default:
            // Este caso ya no es necesario, pero se mantiene por seguridad
            break;
        }
        // El bucle principal repite si la opción no fue Salir (0)
    } while (opcion != 0);

    return 0;
}