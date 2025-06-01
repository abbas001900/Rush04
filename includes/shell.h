#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */
#define MAX_INPUT 1024
#define MAX_ARGS 64

/* Couleurs ANSI */
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

/* Fonctions - input.c */
char *read_input(void);
char **parse_input(char *input);
void clean_input(char *input);

/* Fonctions - utils.c */
void print_welcome(void);
void print_prompt(void);
void print_error(char *msg);
void executer_commande(const char *cmd); // adapté à ton utils.c

#endif /* SHELL_H */
