#ifndef __MATRIX_UTILS__
#define __MATRIX_UTILS__

#include <string.h>

/* on a choisi de faire un sudoku un matrice de 10x10 au lieu de 9x9 */
/* comme ca on peut facilement savoir si le nombre de caracteres dans */
/* ce sudoku sont valide ou non. Si on trouve un caractere dans la 10ieme */
/* rangee ou dans la 10ieme columne, alors on sait que le sudoku est invalide. */
#define MAX_NUM_ROW 10
#define MAX_NUM_COL 10

typedef struct Sudoku 
{
   char matrix[MAX_NUM_ROW][MAX_NUM_COL]; 
   int current_empty_row;
} Sudoku;

/**
 * On insert une chaine de caractere dans le sudoku uniquement si
 * le sudoku n'est pas rempli. Il est rempli si current_empty_row
 * est strictement plus petit que MAX_NUM_ROW. "row" doit contenir au plus
 * 10 caracteres.
 *
 * @param s     Sudoku dans lequel on insert une rangee
 * @param row   Chaine de caractere a insere
 *
 * @return      1 si la chaine a ete inseree. Autrement, retourne 0
 */
int sudoku_insert_row(Sudoku* s, const char *row);

/**
 * Retourne une copie de la chaine de caractere a la index-ieme columne
 */
const char *sudoku_get_col(Sudoku *s, int index);

/**
 * Retourne une copie de la chaine de caractere a la index-ieme rangee
 */
const char *sudoku_get_row(Sudoku *s, int index);

/**
 * Retourne une copie (chaine de caractere) du index-ieme 3x3. Index croit de la gauche vers la droite
 * et du haut vers le bas.
 */
const char *sudoku_get_3x3(Sudoku *s, int index);

/**
 * Retourne 1 si le sudoku a une taille de 9x9. Autrement retourne 0
 */
int sudoku_valid_size(Sudoku *s);

#endif
