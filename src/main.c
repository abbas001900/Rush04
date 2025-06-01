#include "../includes/shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    print_welcome();

    while (1) {
        print_prompt();

        char *input = read_input();

        if (!input) {
            printf("\n");
            break;
        }

        // Optionnel : gestion de la commande "exit" ici
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        executer_commande(input);

        free(input);
    }

    return 0;
}
