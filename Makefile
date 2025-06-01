# Compilateur à utiliser
CC = gcc

# Options de compilation :
# -Wall : active tous les warnings importants
# -Wextra : active des warnings supplémentaires
# -g : ajoute les informations de debug pour gdb
CFLAGS = -Wall -Wextra -g

# Répertoire des fichiers d'en-tête à inclure lors de la compilation
INCLUDES = -I includes/

# Liste des fichiers sources du projet
SRC = src/main.c src/input.c src/utils.c

# Génération automatique des fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Nom de l'exécutable final
EXEC = Shell-Rush10

# Cible par défaut appelée quand on tape juste "make"
all: $(EXEC)

# Règle pour créer l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Règle générique pour compiler un fichier source en fichier objet
# $< = premier prérequis (fichier .c)
# $@ = cible (fichier .o)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage : supprime les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)

# Rebuild : nettoyage puis compilation complète
re: clean all

# Règle pour exécuter directement le programme compilé
run: $(EXEC)
	./$(EXEC)

# Déclare les cibles "all", "clean", "re", "run" comme ne correspondant pas à des fichiers
.PHONY: all clean re run
