#ifndef PALINDROMOS_H
#define PALINDROMOS_H

#include <stdbool.h> // Necesario si se usa 'bool' en la declaración

// Declaración de la función de palíndromos
bool esPalindromo(char* cadena); // Cambiado a 'char*' ya que la función lo modifica

// Declaración de la función que ejecuta el menú de palíndromos
void ejecutar_palindromos();

#endif // PALINDROMOS_H