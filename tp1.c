/**
 * Auteur: Josue Torres
 * Courriel: josue.dtorres@gmail.com
 * Code Permanent: TORJ16029201
 *
 * Version: 26 oct 2019
 *
 * Professeur: Ammar Hammad
 *
 * Objectif: Valider un ou plusieurs sudoku(s) en utilisant plusieurs threads
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <ctype.h> // isdigit
#include <pthread.h>

#include "sudoku.h"
#include "errors_sudoku.h"

#define MAX_NUM_SUDOKUS 10

typedef struct Params
{
    Sudoku *s;
    int index_s;
} Params;


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
 * Retourne un chaine de caractere contenant le contenu du stream passe en parametre.
 * On ignore tout les espaces blanc (' ').
 *
 * @param file  pointeur vers le fichier
 * @param str   la chaine dans laquelle on stocke le contenu du fichier
 *
 * @return Le pointeur vers la chaine de caractere.
 */
char *get_file_content(FILE *file, char str[])
{
    int i = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c != ' ')
            str[i++] = c;
    }

    str[i] = '\0';

    return trim_str(str);
}

/**
 * Lors de la premiere appel de cette fonction, on doit fournir une chaine
 * de caractere non vide. Cette fonction va extraire un sudoku ligne par ligne.
 * Elle va extraire meme si le sudoku n'a pas un format valide. Lors de la deuxieme
 * appel (pour extraire le prochaine sudoku), on doit fournir la valeur NULL
 * afin de poursuivre l'extraction de sudoku. Cette fonction a un comportement 
 * similaire a celui de strtok.
 *
 * @param str   Chaine dans laquelle on extrait le(s) sudoku(s)
 * @param s     Le sudoku dans lequelle on copira les valeurs de str
 *
 * @return L'adresse du derniere caractere lu. Si celui-ci est '\0' (fin de la chaine),
 * alors on retourne NULL.
 */
char *read_sudoku(char *str, Sudoku *s)
{
    static char *probe;

    if (str)
        probe = str;
    else if (probe)
        probe++;

    // premiere caractere non blanc
    while (isspace(*probe))
        probe++;

    int i = 0;
    while ((*probe != '\n' && *(probe + 1) != '\n') && *probe != '\0') {
        char row[MAX_NUM_ROWS];
        while (*probe != '\n') {
           row[i++] = *(probe++);
        }
        sudoku_insert_row(s, row);
        i = 0;
        probe++;
    }
   
   if (*probe == '\0') 
       return NULL;

    return probe;
}

/**
 * Extraire tout les sudokus de la chaine de caracteres
 */
int read_all_sudokus(char *str, Sudoku *list_sudoku)
{
    int num_sudokus = 0;
    
    Sudoku s = {.current_num_rows = 0};
    char *probe = read_sudoku(str, &s);
    list_sudoku[num_sudokus++] = s;
    s.current_num_rows = 0;

    while (probe) {
        probe = read_sudoku(NULL, &s);
        list_sudoku[num_sudokus++] = s;
        s.current_num_rows = 0;
    }

    return num_sudokus;
}

void *validate_sudoku(void *arg)
{
    Params *params = (Params*)arg;
    Sudoku *s = params -> s;
    int index_s = params -> index_s;
    if (!sudoku_is_valid_size(s)) {
        fprintf(stderr, "La taille de la grille du Sudoku (%d) devrait etre 9x9\n", index_s + 1);
        free(params);
        pthread_exit(0);
    }

    int col = 0;
    for (int row = 0; row < NUM_ROWS; row++) {
       if ((col = sudoku_is_valid_row(s, row)) != -1) {
        fprintf(stderr, "La case %d, %d du Sudoku (%d) contient un caractere non-entier ou un caractere special non admis\n", row, col, index_s + 1);
        free(params);
        pthread_exit(0);
       }
    }

    free(params);
    pthread_exit(0);
}

int main(int argc, char *argv[])
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

    char buffer[1500];
    char *file_content = get_file_content(file, buffer);
    fclose(file);

    Sudoku list_sudoku[MAX_NUM_SUDOKUS];
    int num_sudoku = read_all_sudokus(file_content, list_sudoku);

    pthread_t threads[num_sudoku];

    // Lauch threads
    for (int i = 0; i < num_sudoku; i++) {
        Params *params = (Params*) malloc(sizeof(Params*));
        params -> s = &list_sudoku[i];
        params -> index_s = i;
        pthread_create(&threads[i], NULL, validate_sudoku, params);
    }

    // Wait on threads
    for (int i = 0; i < num_sudoku; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
