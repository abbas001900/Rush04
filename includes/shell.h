#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>  // Pour les définitions de taille (size_t)
#include <stdio.h>   // Pour les fonctions d’entrée/sortie standard
#include <stdlib.h>  // Pour malloc, free, exit
#include <string.h>  // Pour les fonctions de manipulation de chaînes

/* Constantes */

// Taille maximale autorisée pour une ligne de commande entrée par l’utilisateur
#define MAX_INPUT 1024

// Nombre maximum d’arguments qu’une commande peut contenir
#define MAX_ARGS 64

/* Codes couleurs ANSI pour l’affichage en terminal */

// Rouge (souvent utilisé pour erreurs)
#define COLOR_RED     "\x1b[31m"

// Vert (souvent utilisé pour succès ou prompt)
#define COLOR_GREEN   "\x1b[32m"

// Jaune (avertissements, etc.)
#define COLOR_YELLOW  "\x1b[33m"

// Bleu
#define COLOR_BLUE    "\x1b[34m"

// Magenta
#define COLOR_MAGENTA "\x1b[35m"

// Cyan (texte informatif, prompt)
#define COLOR_CYAN    "\x1b[36m"

// Réinitialisation des couleurs à la valeur par défaut du terminal
#define COLOR_RESET   "\x1b[0m"

/* Prototypes des fonctions définies dans input.c */

// Lit une ligne complète entrée par l’utilisateur (stdin) et retourne un pointeur vers la chaîne allouée dynamiquement
char *read_input(void);

// Découpe la chaîne entrée en tableau d’arguments (tokens séparés par espaces et tabulations)
char **parse_input(char *input);

// Supprime les espaces en début et fin de la chaîne passée en paramètre
void clean_input(char *input);

/* Prototypes des fonctions définies dans utils.c */

// Affiche un message de bienvenue et d’introduction au mini-shell
void print_welcome(void);

// Affiche le prompt personnalisé avec répertoire courant et couleurs
void print_prompt(void);

// Affiche un message d’erreur formaté et coloré sur la sortie d’erreur
void print_error(char *msg);

// Exécute la commande passée en paramètre (chaîne complète)
void executer_commande(const char *cmd);

#endif /* SHELL_H */
