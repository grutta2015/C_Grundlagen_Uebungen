#ifndef UTILIDADES_H
#define UTILIDADES_H

#define MAX_LONGITUD 50

void quitarSalto(char* cadena);
void limpiarCadenaAlfanumerica(char* cadena);
void aMinusculas(char* cadena);
void limpiar_buffer();
void borrarPantalla();
int validarCadenaAlpha(const char* cadena);
void capitalizarNombre(char* nombre);

void incrementar_aciertos();
int obtener_aciertos();
void resetear_aciertos();

int esBufferSoloEnter();

int continuarJuego(); // <<< ¡Sintaxis Corregida!


#endif // UTILIDADES_H