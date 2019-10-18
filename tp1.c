#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <ctype.h> // isdigit
#include <pthread.h>

// nombre maximal de caractere quon peut lire
#define MAX_INPUT_COUNT 1000

// On doit compter les espaces entre chaque caractere ainse
// que le caractere de retour (\n)
#define DIMENSION_SUDOKU 18

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
 * Retourne le contenu du fichier en une chaine de caracteres
 */
char *get_input (char str[], FILE *fichier)
{
    char ligne[20];
    while (fgets(ligne, sizeof ligne, fichier))
        strcat(str, ligne);

    return str;
}

/**
 * Extrait un sudoku d'une chaine de caracteres peut importe si la chaine est
 * un sudoku valide ou non.
 *
 * @param hauteur   Hauteur de la matrice
 * @param longueur  Longueur de la matrice
 * @param sudoku    La matrice qui represente le sudoku
 * @param str       la chaine de caractere d'ou on va extraire le sudoku
 *
 */
void extraire_sudoku (size_t dimension, char sudoku[dimension][dimension], char str[]) 
{
    int indice_str = 0;

    for (int i = 0; i < (dimension / 2); i++) {
        for (int j = 0; j < dimension; j++) {

            indice_str = i*dimension + j;
            sudoku[i][j] = str[indice_str];
        }
    }
}


void print_sudoku(size_t size, char sudoku[size][size])
{
    for (int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            printf("%c", sudoku[i][j]);

    /* printf("\n"); */
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

    // Lecture du fichie contenant les sudokus
    char entree_fichier[MAX_INPUT_COUNT] = {0};
    get_input(entree_fichier, fichier);
    fclose(fichier);

    char sudoku[DIMENSION_SUDOKU][DIMENSION_SUDOKU] = {0};
    extraire_sudoku(DIMENSION_SUDOKU, sudoku, entree_fichier);

    /* printf("%s", entree_fichier); */
    print_sudoku(DIMENSION_SUDOKU, sudoku);

    return 0;
}
