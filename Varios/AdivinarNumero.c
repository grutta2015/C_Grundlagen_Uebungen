#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ask_play_again();

void clear_screen_portable()
{
    printf("\033[2J");
    printf("\033[1;1H");
    fflush(stdout);
}

void play_game()
{
    clear_screen_portable();

    int secretNumber;
    int intent = 0;
    int num_intent = 1;

    srand(time(NULL));

    secretNumber = rand() % 100 + 1;

    printf("\n--- Juego de Adivinar el Numero ---\n");
    printf("He pensado un numero entre 1 y 100.\n");
    printf("Intenta adivinarlo!\n");

    do
    {
        printf("Tu intento, ingresa un numero: ");

        while (scanf("%d", &intent) != 1)
        {
            printf("\nError: Entrada no valida. Solo se permiten numeros enteros.\n");
            printf("Tu intento, ingresa un numero: ");

            while (getchar() != '\n');
        }

        if (intent > secretNumber)
        {
            printf("\nMuy alto, vuelve a intentar.\n");
        }
        else if (intent < secretNumber)
        {
            printf("\nMuy bajo, vuelve a intentar.\n");
        }
        else
        {
            printf("\nFelicidades! Adivinaste el numero secreto!\n");
            printf("Lo lograste en %d intentos\n", num_intent);
        }

        num_intent++;
    }
    while (intent != secretNumber);

    ask_play_again();
}

void ask_play_again()
{
    char choice;

    printf("\nQuieres volver a jugar?\n");
    printf("Y/N: ");

    if (scanf(" %c", &choice) == 1)
    {
        if (choice == 'y' || choice == 'Y')
        {
            play_game();
        }
        else if (choice == 'n' || choice == 'N')
        {
            printf("\nGracias por jugar!\n");
        }
        else
        {
            printf("Respuesta no valida. Por favor, ingresa Y o N.\n");
            ask_play_again();
        }
    }
    else
    {
        printf("\nError de lectura. Terminando el juego.\n");
    }
}

int main()
{
    play_game();
    return 0;
}