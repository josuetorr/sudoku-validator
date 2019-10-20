#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <ctype.h> // isdigit
#include <pthread.h>

// nombre maximal de caractere quon peut lire
#define MAX_INPUT_COUNT 1000

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
char *get_input_de_fichier (char str[], FILE *fichier)
{
    char ligne[20];
    while (fgets(ligne, sizeof ligne, fichier))
        strcat(str, ligne);

    return str;
}

/**
 * Extrait un sudoku d'une chaine de caracteres peut importe si la chaine est
 * un sudoku valide ou non. Afin de synchroniser les coordonnes de la matrice,
 * on simule la chaine "str" comme une matrice en utilisant la formule pour 
 * indice = i*dimension + j, ou i et j sont les coordonnees de la matrice.
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
            if (!isspace(str[indice_str]))
                sudoku[i][j] = str[indice_str];

        }
    }
}

/**
 * Extrait une sous-chaine de "str" a partir du debut de "str" 
 * jusqu'a la position "fin". Cette fonction modifie le pointeur str.
 * Afin de preserver la chaine de caractere, on suggere de copier str
 * dans une autre chaine avec strcpy
 *
 * @param str   Chaine original
 * @param fin   Derniere position de la sous-chaine
 *
 * @return  La sous-chaine correspondante. Si "fin" est plus grand
 *          que la longueur de "str", alors on retourne NULL
 */
char *sub_str (const char *str, char* substr, int fin)
{
    if (fin > strlen(str)) 
       return NULL;

    for (int i = 0; i < fin; i++)
        substr[i] = str[i];
    substr[fin] = 0;

    str = str + fin;

    return substr;
}

/**
 * Extraire tout les sudokus d'une chaine de caractere.
 * Un sudoku est delimite par deux caracteres de retours consecutifs.
 * Les sudokus seront stockes dans une liste ayant comme longueur le nombre
 * de sudoku dans la chaine passee en parametre
 *
 * @param str   Chaine d'ou on veut extraire les sudokus
 * @param liste Le tableau dans lequel les sudokus seront stockes
 */
void extraire_all_sudoku(char str[])
{
    const char *delim = "\n\n";
    const char *pos_of_delim = strstr(str, delim);
    char substr[pos_of_delim - str];
    sub_str(str, substr, pos_of_delim - str);
    
    
}

void print_sudoku(size_t size, char sudoku[size][size])
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", sudoku[i][j]);
        }
        printf("\n");
    }
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
    get_input_de_fichier(entree_fichier, fichier);
    fclose(fichier);

    extraire_all_sudoku(entree_fichier);
    printf("Original after sub_str:\n%s\n", entree_fichier);

    /* char sudoku[DIMENSION_SUDOKU][DIMENSION_SUDOKU] = {0}; */
    /* extraire_sudoku(DIMENSION_SUDOKU, sudoku, entree_fichier); */

    /* /1* printf("%s", entree_fichier); *1/ */
    /* print_sudoku(DIMENSION_SUDOKU, sudoku); */

    return 0;
}
