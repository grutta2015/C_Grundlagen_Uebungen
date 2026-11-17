#ifndef AGENDA_H
#define AGENDA_H



// Deshabilita las advertencias de seguridad C4996 en Visual Studio
#pragma warning(disable:4996) 

// --- Constantes de la Agenda ---
#define MAX_CONTACTOS 100
#define MAX_NOMBRE 50
#define MAX_TELEFONO 20
#define MIN_BUSQUEDA 3

// --- Estructura de Datos ---
typedef struct {
    char nombre[MAX_NOMBRE];
    char telefono[MAX_TELEFONO];
} Contacto;

// --- Variables Globales ---
Contacto agenda[MAX_CONTACTOS];
int totalContactos = 0;

// ===========================================
//         FUNCIONES DE UTILIDAD
// ===========================================

void quitarSalto(char* cadena) {
    cadena[strcspn(cadena, "\n")] = '\0';
}

void aMinusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        cadena[i] = tolower((unsigned char)cadena[i]);
    }
}

void capitalizarNombre(char* nombre) {
    aMinusculas(nombre);

    int i;
    int nuevaPalabra = 1;

    for (i = 0; nombre[i] != '\0'; i++) {
        if (isspace((unsigned char)nombre[i]) || nombre[i] == '-' || nombre[i] == '\'') {
            nuevaPalabra = 1;
        }
        else if (nuevaPalabra && isalpha((unsigned char)nombre[i])) {
            nombre[i] = toupper((unsigned char)nombre[i]);
            nuevaPalabra = 0;
        }
    }
}

int validarNombre(const char* nombre) {
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (isalpha((unsigned char)nombre[i]) || isspace((unsigned char)nombre[i]) ||
            nombre[i] == '-' || nombre[i] == '\'') {
            continue;
        }
        return 0;
    }
    return 1;
}

int validarTelefono(const char* telefono) {
    if (strlen(telefono) > (MAX_TELEFONO - 1)) {
        return 0;
    }
    for (int i = 0; i < strlen(telefono); i++) {
        if (!isdigit(telefono[i])) {
            return 0;
        }
    }
    return 1;
}


int buscarCoincidencias(const char* cadenaAbuscar, int* coincidenciasEncontradas) {
    if (strlen(cadenaAbuscar) < MIN_BUSQUEDA) {
        printf("ADVERTENCIA: Búsqueda demasiado corta. Ingrese al menos %d caracteres.\n", MIN_BUSQUEDA);
        return 0;
    }

    char nombreAgendaTemp[MAX_NOMBRE];
    char busquedaTemp[MAX_NOMBRE];
    int coincidencias = 0;

    strcpy(busquedaTemp, cadenaAbuscar);
    aMinusculas(busquedaTemp);

    for (int i = 0; i < totalContactos; i++) {
        strcpy(nombreAgendaTemp, agenda[i].nombre);
        aMinusculas(nombreAgendaTemp);

        if (strstr(nombreAgendaTemp, busquedaTemp) != NULL) {
            coincidenciasEncontradas[coincidencias] = i;
            coincidencias++;
        }
    }
    return coincidencias;
}


int seleccionarContacto(const char* cadenaBusqueda) {
    char nombreCadena[MAX_NOMBRE];
    int coincidenciasEncontradas[MAX_CONTACTOS];
    int numCoincidencias;
    int seleccion;

    // A. Búsqueda y Manejo de Error
    printf("%s (mín. %d caracteres): ", cadenaBusqueda, MIN_BUSQUEDA);
    fgets(nombreCadena, MAX_NOMBRE, stdin);
    quitarSalto(nombreCadena);

    numCoincidencias = buscarCoincidencias(nombreCadena, coincidenciasEncontradas);

    if (numCoincidencias == 0) {
        if (strlen(nombreCadena) >= MIN_BUSQUEDA) {
            printf("No encontrado.\n");
        }
        return -1; // No se encontró nada
    }

    // B. Mostrar las coincidencias
    printf("\n--- %d Coincidencia(s) Encontrada(s) ---\n", numCoincidencias);
    for (int j = 0; j < numCoincidencias; j++) {
        int i = coincidenciasEncontradas[j];
        printf("%d. Nombre: %s | Teléfono: %s\n", j + 1, agenda[i].nombre, agenda[i].telefono);
    }
    printf("-----------------------------------------\n");

    // C. Pedir la selección
    printf("Seleccione el número (1 a %d) o 0 para cancelar: ", numCoincidencias);
    if (scanf("%d", &seleccion) != 1) {
        seleccion = 0; // Si la entrada no es un número, se trata como cancelar
    }
    int c; while ((c = getchar()) != '\n' && c != EOF); // Limpiar buffer después de scanf

    if (seleccion < 1 || seleccion > numCoincidencias) {
        printf("Operación cancelada o selección inválida.\n");
        return -1; // Cancelar
    }

    // D. Devolver el índice real
    return coincidenciasEncontradas[seleccion - 1];
}


// -------------------------------------------
//         FUNCIONES DE ORDENAMIENTO
// -------------------------------------------

int compararContactos(const void* a, const void* b) {
    const Contacto* contactoA = (const Contacto*)a;
    const Contacto* contactoB = (const Contacto*)b;
    return strcmp(contactoA->nombre, contactoB->nombre);
}

void ordenarAgenda() {
    qsort(agenda, totalContactos, sizeof(Contacto), compararContactos);
}

// ===========================================
//         FUNCIONES DE LA AGENDA
// ===========================================

void insertar() {
    if (totalContactos >= MAX_CONTACTOS) {
        printf("La agenda está llena.\n");
        return;
    }

    do {
        printf("Nombre: ");
        fgets(agenda[totalContactos].nombre, MAX_NOMBRE, stdin);
        quitarSalto(agenda[totalContactos].nombre);

        if (!validarNombre(agenda[totalContactos].nombre)) {
            printf("ERROR: Nombre inválido. Solo se permiten letras, espacios, guiones (-) o apóstrofes ('). Por favor, reintente.\n");
        }
        else {
            capitalizarNombre(agenda[totalContactos].nombre);
            break;
        }
    } while (1);


    do {
        printf("Teléfono: ");
        fgets(agenda[totalContactos].telefono, MAX_TELEFONO, stdin);
        quitarSalto(agenda[totalContactos].telefono);

        if (!validarTelefono(agenda[totalContactos].telefono)) {
            printf("ERROR: Teléfono inválido. Por favor, reintente.\n");
        }
        else {
            break;
        }
    } while (1);

    totalContactos++;
    ordenarAgenda();
    printf("\nContacto añadido.\n");
}

// 2. Buscar contacto
void buscar() {
    char cadenaNombre[MAX_NOMBRE];
    int coincidenciasEncontradas[MAX_CONTACTOS];
    int numCoincidencias;

    printf("Buscar (mín. %d caracteres): ", MIN_BUSQUEDA);
    fgets(cadenaNombre, MAX_NOMBRE, stdin);
    quitarSalto(cadenaNombre);

    numCoincidencias = buscarCoincidencias(cadenaNombre, coincidenciasEncontradas);

    if (numCoincidencias > 0) {
        printf("\n--- %d Coincidencia(s) Encontrada(s) ---\n", numCoincidencias);
        for (int j = 0; j < numCoincidencias; j++) {
            int i = coincidenciasEncontradas[j];
            printf("Nombre: %s\nTeléfono: %s\n", agenda[i].nombre, agenda[i].telefono);
            if (j < numCoincidencias - 1) {
                printf("-----------------------------------------\n");
            }
        }
        printf("-----------------------------------------\n");
    }
    else {
        if (strlen(cadenaNombre) >= MIN_BUSQUEDA) {
            printf("\nNo se encontraron coincidencias para \"%s\".\n", cadenaNombre);
        }
    }
}


// 3. Actualizar contacto
void actualizar() {
    char confirmacion[5];

    // Paso 1: Buscar y Seleccionar el Contacto
    int indiceReal = seleccionarContacto("Nombre del contacto a Actualizar (o fragmento)");

    if (indiceReal == -1) {
        return; // Sale si la selección falló o fue cancelada
    }

    // Paso 2: Pedir confirmación
    printf("\nNombre a actualizar: %s\n", agenda[indiceReal].nombre);
    printf("¿Está seguro S/N? ");
    fgets(confirmacion, 5, stdin);
    quitarSalto(confirmacion);
    aMinusculas(confirmacion);

    if (strcmp(confirmacion, "s") != 0) {
        printf("Actualización cancelada por el usuario.\n");
        return;
    }

    // Paso 3: Lógica única de Actualizar (Bucle para nuevo teléfono)
    char nuevoTelefono[MAX_TELEFONO];
    do {
        printf("Nuevo teléfono (Solo números, máx. %d dígitos): ", MAX_TELEFONO - 1);
        fgets(nuevoTelefono, MAX_TELEFONO, stdin);
        quitarSalto(nuevoTelefono);

        if (!validarTelefono(nuevoTelefono)) {
            printf("\nERROR: Teléfono inválido. Por favor, reintente.\n");
        }
        else {
            strcpy(agenda[indiceReal].telefono, nuevoTelefono);
            printf("\nContacto actualizado: %s\n", agenda[indiceReal].nombre);
            return;
        }
    } while (1);
}

// 4. Eliminar contacto
void eliminar() {
    char confirmacion[5];

    // Paso 1: Buscar y Seleccionar el Contacto
    int indiceReal = seleccionarContacto("Nombre del contacto a Eliminar (o fragmento)");

    if (indiceReal == -1) {
        return; // Sale si la selección falló o fue cancelada
    }

    // Paso 2: Pedir confirmación
    printf("\nNombre a eliminar: %s\n", agenda[indiceReal].nombre);
    printf("¿Está seguro S/N? ");
    fgets(confirmacion, 5, stdin);
    quitarSalto(confirmacion);
    aMinusculas(confirmacion);

    if (strcmp(confirmacion, "s") != 0) {
        printf("\nEliminación cancelada por el usuario.\n");
        return;
    }

    // Paso 3: Lógica única de Eliminar
    if (indiceReal != totalContactos - 1) {
        // Mueve el último elemento al lugar del elemento borrado (optimización)
        agenda[indiceReal] = agenda[totalContactos - 1];
    }

    totalContactos--;
    ordenarAgenda();

    printf("\nContacto eliminado y agenda reordenada.\n");
}

// 5. Mostrar contactos
void mostrar() {
    if (totalContactos == 0) {
        printf("\nAgenda vacía.\n");
        return;
    }

    printf("\n--- Lista de Contactos Ordenada (%d) ---\n", totalContactos);
    for (int i = 0; i < totalContactos; i++) {
        printf("%d. %s - %s\n", i + 1, agenda[i].nombre, agenda[i].telefono);
    }
    printf("-----------------------------------------\n");
}

#endif