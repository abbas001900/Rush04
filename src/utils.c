#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/shell.h"  // ou "executor.h" si tu y déclares la fonction

void executer_commande(const char *cmd) {
    // Copie de la commande pour pouvoir la modifier
    char commande[256];
    strncpy(commande, cmd, sizeof(commande));
    commande[sizeof(commande) - 1] = '\0';

    // Séparation de la commande et des arguments
    char *nom_cmd = strtok(commande, " ");
    char *arg = strtok(NULL, "");  // Prend tout le reste comme argument

    if (strcmp(nom_cmd, "help") == 0) {
        printf("\nCommandes disponibles :\n");
        printf("  ls       : Liste les fichiers du dossier courant\n");
        printf("  echo     : Affiche un message\n");
        printf("  pwd      : Affiche le répertoire courant\n");
        printf("  clear    : Efface l'écran\n");
        printf("  date     : Affiche la date et l'heure actuelles\n");
        printf("  mkdir    : Crée un nouveau dossier\n");
        printf("  touch    : Crée un nouveau fichier\n");
        printf("  cd [dir] : Change de répertoire\n");
        printf("  help     : Affiche cette aide\n");
        printf("  exit     : Quitter le mini-shell\n\n");
    }
    
    else if (strcmp(nom_cmd, "cd") == 0) {
        if (arg == NULL) {
            print_error("Usage : cd <répertoire>");
        } else {
            if (chdir(arg) != 0) {
                perror("Erreur lors du changement de répertoire");
            }
        }
    }

    else if (strcmp(nom_cmd, "date") == 0) {
    #ifdef _WIN32
        system("echo %DATE% %TIME%");
    #else
        system("date +\"%A %d %B %Y %T\"");
    #endif
    }

    else if (
        strcmp(nom_cmd, "ls") == 0 ||
        strcmp(nom_cmd, "echo") == 0 ||
        strcmp(nom_cmd, "pwd") == 0 ||
        strcmp(nom_cmd, "clear") == 0 ||
        strcmp(nom_cmd, "date") == 0 ||
        strcmp(nom_cmd, "mkdir") == 0 ||
        strcmp(nom_cmd, "touch") == 0
    ) {
        system(cmd);
    }
    else {
        printf("Commande non reconnue : %s\n", cmd);
        printf("Tapez 'help' pour voir la liste des commandes.\n");
    }
}


void print_welcome() {
    printf(COLOR_BLUE "═══════════════════════════════════\n");
    printf("    " COLOR_CYAN "Mini-Shell " COLOR_BLUE "v1.0\n");
    printf("═══════════════════════════════════\n");
    printf("Tapez " COLOR_CYAN "help" COLOR_BLUE " pour la liste des commandes\n");
    printf("═══════════════════════════════════\n" COLOR_RESET);
}

/* Affiche le prompt personnalisé */
void print_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd)); // Récupère le dossier courant
    
    printf(COLOR_GREEN "➜ " COLOR_CYAN "%s" COLOR_GREEN " $ " COLOR_RESET, cwd);
    fflush(stdout);
}

/* Affiche un message d'erreur */
void print_error(char *msg) {
    fprintf(stderr, COLOR_RED "✖ %s\n" COLOR_RESET, msg);
}
