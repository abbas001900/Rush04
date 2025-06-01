CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -I includes/

SRC = src/main.c src/input.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = Shell-Rush10

# Cible par défaut
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compilation des fichiers .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)

# Rebuild
re: clean all

# Exécution
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean re run
