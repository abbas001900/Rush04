# Mini-Shell - Projet Rush 10

## Description générale

Ce projet consiste à développer un mini-shell en langage C, capable de lire et d’exécuter des commandes utilisateur dans un terminal.  
Ce shell est une version simplifiée des shells Unix classiques (bash, zsh), conçu dans un contexte pédagogique.

---

## Objectifs du projet

- Comprendre les bases de la gestion des entrées/sorties en C.  
- Manipuler les chaînes de caractères pour analyser les commandes.  
- Gérer les processus via appels systèmes simples (ex : `system()`).  
- Implémenter une interface utilisateur interactive (prompt, message de bienvenue).  
- Travailler en équipe avec une répartition claire des tâches.  

---

## Répartition des tâches

1. **Lecture des commandes** Dan_salao_K  
   - Lecture de l’entrée utilisateur avec gestion mémoire dynamique (`read_input`)  
   - Nettoyage des entrées (suppression des espaces superflus)  
   - Parsing des commandes en tableau d’arguments (`parse_input`)  

2. **Exécution des commandes** Abdoul_Wahabou_BS  
   - Gestion des commandes internes (`cd`, `help`, `exit`)  
   - Appel au système pour les autres commandes via `system()`  
   - Gestion des erreurs lors de l’exécution  

3. **Interface et boucle principale** Abbas_IM
   - Assemblage et intégration des modules  
   - Boucle principale du shell : affichage du prompt, lecture et exécution  
   - Affichage d’un message de bienvenue à l’ouverture  
   - Prompt personnalisé affichant le chemin courant  
   - Gestion propre de la mémoire et sortie du programme  

---

## Fonctionnalités

- Lecture sécurisée de la ligne de commande (limite à 1024 caractères).  
- Nettoyage automatique des espaces en début et fin de ligne.  
- Parsing en arguments pour potentielle extension (ex : gestion d’arguments multiples).  
- Commandes internes gérées directement :  
  - `cd` avec gestion des erreurs de changement de répertoire.  
  - `help` pour afficher la liste des commandes supportées.  
  - `exit` pour quitter le shell proprement.  
- Commandes système supportées : `ls`, `echo`, `pwd`, `clear`, `date`, `mkdir`, `touch`.  
- Prompt dynamique affichant le répertoire courant avec des couleurs.  
- Gestion basique des erreurs (affichage de messages en rouge).   

---

## Explications techniques

- La lecture utilise `fgets` avec un buffer alloué dynamiquement pour éviter les débordements.  
- Le parsing utilise `strtok` pour séparer la ligne en arguments selon les espaces ou tabulations.  
- Les commandes internes sont reconnues via `strcmp` et traitées spécifiquement.  
- La fonction `executer_commande` appelle `system()` pour les commandes système.  
- La boucle principale continue tant que l’utilisateur ne tape pas `exit`.  
- L’affichage utilise des séquences ANSI pour la couleur (via constantes définies dans `shell.h`).  

---

## Installation et utilisation

### Prérequis

- Un compilateur C compatible (gcc)  
- Make (pour automatiser la compilation)  
- Un terminal compatible ANSI (Linux, macOS, Windows avec WSL ou PowerShell compatible)  

### Compilation

Dans le dossier racine, tapez :

```bash
make
