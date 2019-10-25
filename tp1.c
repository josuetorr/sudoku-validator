#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <ctype.h> // isdigit
#include <pthread.h>

#include "sudoku.h"
#include "errors_sudoku.h"

/**
 * Retourne un chaine de caractere contenant le contenu du stream passe en parametre.
 * On ignore tout les espaces blanc (' ').
 *
 * @param file  pointeur vers le fichier
 * @param str   la chaine dans laquelle on stocke le contenu du fichier
 *
 * @return Le pointeur vers la chaine de caractere.
 */
char *get_file_content (FILE *file, char str[])
{
    int i = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c != ' ')
            str[i++] = c;
    }

    str[i] = '\0';

    return str;
}

int main (int argc, char *argv[])
{
    // On doit fournir un nom de fichier en argument au programme
    if (argc != 2) {

        fprintf(stderr, "%s: Usage: <nom-fichier>\n", argv[0]);
        exit(ERROR_ARG_MISSING);

    }

    // Ouvrir le fichier
    FILE *file = fopen(argv[1], "r");

    if (!file) {

        fprintf(stderr, 
                "%s: Erreur: Fichier \"%s\" n'existe pas ou n'a pas pu etre ouvert\n",
                argv[0],
                argv[1]);
        exit(ERROR_FILE);

    }

    char file_content[1500];
    get_file_content(file, file_content);

    return 0;
}
