#define _GNU_SOURCE
#include <stdio.h>      // pour getline
#include <stdlib.h>     // pour malloc, free
#include <string.h>     // pour strlen, strtok, etc.
#include <ctype.h>      // pour isspace
#include "../includes/shell.h"


// Lecture de la ligne entrée par l'utilisateur
char *read_input(void) {
    char *buffer = malloc(MAX_INPUT);
    if (!buffer) {
        fprintf(stderr, "Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    if (fgets(buffer, MAX_INPUT, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    // Supprimer le retour à la ligne
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

// Découpe la ligne en arguments (tableau de chaînes)
char **parse_input(char *input) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (!args) {
        print_error("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *token = strtok(input, " \t");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = strdup(token);
        if (!args[i]) {
            print_error("Erreur de duplication de chaîne");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;

    return args;
}

// Supprime les espaces en début et fin de ligne
void clean_input(char *input) {
    char *start = input;
    while (isspace((unsigned char)*start)) start++;

    char *end = input + strlen(input) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    if (start != input) {
        memmove(input, start, end - start + 2);
    }
}
