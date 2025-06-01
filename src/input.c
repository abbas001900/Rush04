#define _GNU_SOURCE  // Pour activer certaines fonctionnalités GNU, notamment getline (non utilisée ici mais souvent utile)

#include <stdio.h>      // Pour fgets, fprintf
#include <stdlib.h>     // Pour malloc, free, exit
#include <string.h>     // Pour strlen, strtok, strdup, memmove
#include <ctype.h>      // Pour isspace (test des espaces, tabulations, etc.)
#include "../includes/shell.h"  // Inclusion des définitions propres à ton projet

// Fonction pour lire une ligne entrée par l'utilisateur depuis l'entrée standard
char *read_input(void) {
    // Allocation dynamique d'un buffer de taille MAX_INPUT (défini ailleurs)
    char *buffer = malloc(MAX_INPUT);
    if (!buffer) {
        fprintf(stderr, "Erreur allocation mémoire\n");  // Message d'erreur si malloc échoue
        exit(EXIT_FAILURE);
    }

    // Lecture de la ligne depuis stdin, avec taille maximale MAX_INPUT
    if (fgets(buffer, MAX_INPUT, stdin) == NULL) {
        free(buffer);  // En cas d'erreur ou EOF, libérer la mémoire
        return NULL;   // Retourner NULL pour signaler la fin ou erreur
    }

    // Suppression du caractère retour à la ligne '\n' à la fin de la chaîne, s'il est présent
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Retourne la chaîne lue, prête à être traitée
    return buffer;
}

// Fonction qui découpe la ligne entrée en arguments (tokens) séparés par espaces ou tabulations
char **parse_input(char *input) {
    // Allocation d'un tableau de pointeurs vers chaînes, taille MAX_ARGS (défini ailleurs)
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (!args) {
        print_error("Erreur d'allocation mémoire");  // Message d'erreur si malloc échoue
        exit(EXIT_FAILURE);
    }

    int i = 0;
    // Découpage de la chaîne en tokens séparés par espaces ou tabulations
    char *token = strtok(input, " \t");

    // Tant qu'il y a un token et que la limite d'arguments n'est pas atteinte
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = strdup(token);  // Duplique le token dans une nouvelle chaîne
        if (!args[i]) {
            print_error("Erreur de duplication de chaîne");  // Erreur si strdup échoue
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, " \t");  // Passe au token suivant
    }
    args[i] = NULL;  // Marque la fin du tableau par un pointeur NULL

    return args;  // Retourne le tableau d'arguments
}

// Fonction qui supprime les espaces blancs en début et fin de chaîne
void clean_input(char *input) {
    char *start = input;

    // Avance start tant que le caractère pointé est un espace
    while (isspace((unsigned char)*start)) start++;

    // Pointe end sur le dernier caractère de la chaîne (avant '\0')
    char *end = input + strlen(input) - 1;

    // Recule end tant que le caractère pointé est un espace et qu'on n'a pas dépassé start
    while (end > start && isspace((unsigned char)*end)) end--;

    // Place la fin de chaîne juste après le dernier caractère non-espace
    *(end + 1) = '\0';

    // Si des espaces ont été supprimés en début, on décale la chaîne vers le début
    if (start != input) {
        memmove(input, start, end - start + 2); // +2 pour inclure le '\0'
    }
}
