#include <stdio.h>      // Pour printf, fprintf, perror
#include <unistd.h>     // Pour chdir, getcwd
#include <stdlib.h>     // Pour system, malloc, free
#include <string.h>     // Pour strcmp, strncpy, strtok
#include "../includes/shell.h"  // Inclusion de l'en-tête local, contient les déclarations des fonctions (ou "executor.h" selon l'organisation)

// Fonction principale d'exécution d'une commande passée en argument
void executer_commande(const char *cmd) {
    // Copie sécurisée de la commande dans un buffer modifiable de taille fixe
    char commande[256];
    strncpy(commande, cmd, sizeof(commande));
    commande[sizeof(commande) - 1] = '\0'; // Assure la terminaison nulle

    // Découpage de la commande en nom de commande et arguments
    char *nom_cmd = strtok(commande, " ");  // Extraction du premier mot (commande)
    char *arg = strtok(NULL, "");            // Extraction du reste de la chaîne (arguments)

    // Gestion de la commande "help" : affiche la liste des commandes disponibles
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
    
    // Gestion de la commande "cd" : changement de répertoire
    else if (strcmp(nom_cmd, "cd") == 0) {
        if (arg == NULL) {
            // Pas d'argument fourni : affiche un message d'erreur avec usage correct
            print_error("Usage : cd <répertoire>");
        } else {
            // Tente de changer de répertoire ; en cas d'erreur affiche un message système
            if (chdir(arg) != 0) {
                perror("Erreur lors du changement de répertoire");
            }
        }
    }

    // Gestion de la commande "date" avec prise en charge des différences Windows / Unix
    else if (strcmp(nom_cmd, "date") == 0) {
    #ifdef _WIN32
        system("echo %DATE% %TIME%");  // Windows : affiche la date et l'heure
    #else
        system("date +\"%A %d %B %Y %T\"");  // Unix : format personnalisé de la date
    #endif
    }

    // Pour ces commandes courantes, on délègue directement au système via system()
    else if (
        strcmp(nom_cmd, "ls") == 0 ||
        strcmp(nom_cmd, "echo") == 0 ||
        strcmp(nom_cmd, "pwd") == 0 ||
        strcmp(nom_cmd, "clear") == 0 ||
        strcmp(nom_cmd, "date") == 0 ||
        strcmp(nom_cmd, "mkdir") == 0 ||
        strcmp(nom_cmd, "touch") == 0
    ) {
        system(cmd);  // Exécute la commande brute dans un shell système
    }

    // Si la commande n'est pas reconnue
    else {
        printf("Commande non reconnue : %s\n", cmd);
        printf("Tapez 'help' pour voir la liste des commandes.\n");
    }
}

// Fonction qui affiche un message de bienvenue coloré au lancement du mini-shell
void print_welcome() {
    printf(COLOR_BLUE "═══════════════════════════════════\n");
    printf("    " COLOR_CYAN "Mini-Shell " COLOR_BLUE "v1.0\n");
    printf("═══════════════════════════════════\n");
    printf("Tapez " COLOR_CYAN "help" COLOR_BLUE " pour la liste des commandes\n");
    printf("═══════════════════════════════════\n" COLOR_RESET);
}

/* Affiche un prompt personnalisé avec le répertoire courant et des couleurs */
void print_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd)); // Récupère le chemin absolu du dossier courant
    
    // Affiche une flèche verte, le chemin en cyan, suivi d'un $ vert, puis reset des couleurs
    printf(COLOR_GREEN "➜ " COLOR_CYAN "%s" COLOR_GREEN " $ " COLOR_RESET, cwd);
    fflush(stdout);  // Force l'affichage immédiat du prompt
}

/* Affiche un message d'erreur coloré sur la sortie d'erreur */
void print_error(char *msg) {
    fprintf(stderr, COLOR_RED "✖ %s\n" COLOR_RESET, msg);
}
