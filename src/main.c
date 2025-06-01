#include "../includes/shell.h"  // Inclusion du fichier d'en-tête local pour les prototypes et définitions liés au shell
#include <stdlib.h>             // Inclusion pour les fonctions standard (malloc, free, exit, etc.)
#include <stdio.h>              // Inclusion pour les fonctions d'entrée/sortie (printf, etc.)
#include <string.h>             // Inclusion pour les fonctions de manipulation de chaînes (strcmp, etc.)

int main() {
    print_welcome();  // Affiche un message de bienvenue au lancement du shell

    while (1) {  // Boucle infinie pour garder le shell actif tant que l'utilisateur ne quitte pas
        print_prompt();  // Affiche l'invite de commande à l'utilisateur

        char *input = read_input();  // Lit la saisie utilisateur et stocke la chaîne retournée dans input

        if (!input) {  // Si la lecture a échoué ou l'entrée est NULL (fin de fichier par exemple)
            printf("\n");  // Affiche un retour à la ligne pour l'esthétique
            break;         // Quitte la boucle et donc le programme
        }

        // Gestion optionnelle de la commande "exit" pour quitter explicitement le shell
        if (strcmp(input, "exit") == 0) {  
            free(input);  // Libère la mémoire allouée pour la saisie utilisateur
            break;        // Quitte la boucle principale
        }

        executer_commande(input);  // Exécute la commande saisie par l'utilisateur

        free(input);  // Libère la mémoire allouée pour la saisie utilisateur après exécution
    }

    return 0;  // Fin normale du programme
}
