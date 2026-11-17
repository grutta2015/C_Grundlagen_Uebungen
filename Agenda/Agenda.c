#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h> // Necesario para SetConsoleOutputCP
#include <locale.h>  // Necesario para setlocale
#include "agenda.h"

// ===========================================
//               MENÚ PRINCIPAL
// ===========================================

int main() {
    int opcion;

    // 1. Configurar el locale de C para que las funciones I/O manejen caracteres no ASCII (acentos)
    setlocale(LC_ALL, ""); // Usa la configuración regional del sistema (ej: español)

    // 2. Configurar la salida de la consola a UTF-8 (código 65001)
    SetConsoleOutputCP(CP_UTF8);

    // 3. Forzar a la consola (CMD/PowerShell) a usar la página de códigos 65001 (UTF-8)
    system("chcp 65001");

    ordenarAgenda();

    do {
        printf("\n==================================\n");
        printf("       AGENDA DE CONTACTOS EN C      \n");
        printf("==================================\n");
        printf("\n1. Insertar nuevo contacto\n");
        printf("2. Buscar contacto por nombre/fragmento\n");
        printf("3. Actualizar contacto (teléfono)\n");
        printf("4. Eliminar contacto\n");
        printf("5. Mostrar todos los contactos\n");
        printf("6. Salir del programa\n");
        printf("\n----------------------------------\n");
        printf("Total de contactos: %d / %d\n", totalContactos, MAX_CONTACTOS);
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion) {
        case 1: insertar(); break;
        case 2: buscar(); break;
        case 3: actualizar(); break;
        case 4: eliminar(); break;
        case 5: mostrar(); break;
        case 6: printf("¡Adiós!\n"); break;
        default: printf("Opción inválida.\n");
        }
    } while (opcion != 6);

    return 0;
}