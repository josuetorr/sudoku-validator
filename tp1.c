#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <ctype.h> // isdigit
#include <pthread.h>

// nombre maximal de caractere quon peut lire
#define MAX_INPUT_COUNT 1000
#define MAX_NOMBRE_SUDOKU 100
#define MAX_CHAR_SUDOKU 100

/**
 * Obtenir un pointeur de stream vers le fichier que nous voulons ouvrir
 *
 * @param chemin Le chemin vers le fichier. Peut etre absolu ou relatif
 *
 * @return un pointeur de type FILE vers le fichier a ouvrir. NULL si echec
 *         d'ouverture.      
 */
FILE *get_fichier (const char chemin[])
{
    FILE *fichier = fopen(chemin, "r");
    if (!fichier)
        return NULL;
    else
        return fichier;
}

/**
 * Enlever tout les espaces blancs a gauche de la chaine
 * 
 * @return un pointeur qui pointe vers le premier caractere qui n'est pas un espace blanc
 */
char *trim_left(char str[])
{
    char *probe = str;

    while (isspace(*probe))
        probe++;

    return probe;
}

/**
 * Enlever tout les espaces blancs a droit de la chaine
 *
 * @return un pointeur qui pointe vers le premier caractere qui n'est pas un espace blanc
 */
char *trim_right(char str[])
{
    char *probe = str + strlen(str) - 1;

    while (isspace(*probe))
        probe--;

    *(probe + 1) = '\0';

    return str;
}

/**
 * Enlever tout les espaces blancs a gauche et a droite de la chaine
 */
char *trim_str (char str[])
{
    return trim_left(trim_right(str));
}

/**
 * Retourne le contenu du fichier en une chaine de caracteres
 */
char *get_input_de_fichier (char str[], FILE *fichier)
{
    char c;
    int i = 0;
    while ((c = fgetc(fichier)) != EOF) {
        if (c != ' ')    
           str[i++] = c; 
    }

    return trim_str(str);
}

/**
 * Extrait la sous-chaine entre [0, fin[ de la chaine passee en parametre.
 *
 * @param fin   Indice final de la chaine. N'est pas inclu
 * @param source    La chaine dont nous voulons extraire la sous-chaine
 * @param substr    Pointeur vers la sous-chaine
 *
 * @return  Un pointeur vers la sous-chaine. Retourne NULL si la chaine principale est vide
 *          ou NULL
 */
char *sub_str (int fin, char source[], char substr[]) 
{
    if (strlen(source) == 0 || !source)
        return NULL;

    for (int i = 0; i < fin; i++) {
         substr[i] = source[i];
    } 

    substr[fin] = '\0'; 
    
    return substr;
}

/**
 * Extrait tous les sudokus d'une chaine de caracteres. Chaque sudoku doit etre
 * separe par un saut de ligne ('\n'). Etant donne que chaque rangee d'un sudoku
 * est separee par un saut de ligne, chaque sudoku est separe par deux saut de ligne
 * consecutifs.
 *
 * @param tous_sudoku       Liste de chaine de caracteres qui contiendra tous les sudokus
 * @param str               Chaine de caracteres d'ou nous voulons extraire les sudokus
 *
 * @return  Le nombre de sudokus lus
 */
int extraire_tous_sudokus (size_t max_char_par_sudoku, char tous_sudoku[][max_char_par_sudoku], char *str)
{
    const char *delim = "\n\n";
    int fin = 0;
    char *pos_delim;
    int nbSudoku = 0;
    while (*str != '\0' && pos_delim != NULL) {
       char sudoku[max_char_par_sudoku];
       pos_delim = strstr(str, delim);

       if (!pos_delim) {
            strcpy(tous_sudoku[nbSudoku++], str);
       } else {
           fin = pos_delim - str;
           sub_str(fin, str, sudoku);
           strcpy(tous_sudoku[nbSudoku++], sudoku);
           str = pos_delim + 2;
        } 
   }


    return nbSudoku;
}

int main (int argc, char *argv[])
{
    if (argc != 2) {

        fprintf(stderr, "%s: Usage: <nom-fichier>\n", argv[0]);
        exit(1);

    }

    FILE *fichier = get_fichier(argv[1]);
    if (!fichier) {

        fprintf(stderr, "%s: Erreur: Fichier \"%s\" n'existe pas\n", argv[0], argv[1]);
        exit(1);

    }

    // Lecture du fichier contenant les sudokus
    char entree_fichier_non_formatter[MAX_INPUT_COUNT] = {0};
    char *entree_fichier = get_input_de_fichier(entree_fichier_non_formatter, fichier);
    fclose(fichier);

    // extraire tous les sudokus de la chaine de caractere qui provient du fichier
    char tous_sudoku[MAX_NOMBRE_SUDOKU][MAX_CHAR_SUDOKU];
    int nbSudoku = extraire_tous_sudokus(MAX_CHAR_SUDOKU, tous_sudoku, entree_fichier);

    return 0;
}
