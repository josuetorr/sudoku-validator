#ifndef __MATRIX_UTILS__
#define __MATRIX_UTILS__

#include <string.h>

/* on a choisi de faire un sudoku un matrice de 10x10 au lieu de 9x9 */
/* comme ca on peut facilement savoir si le nombre de caracteres dans */
/* ce sudoku sont valide ou non. Si on trouve un caractere dans la 10ieme */
/* rangee ou dans la 10ieme columne, alors on sait que le sudoku est invalide. */
#define MAX_NUM_ROWS 10
#define MAX_NUM_COLS 10

#define NUM_ROWS 9
#define NUM_COLS 9

#define SKD_ERROR_SIZE 1
#define SKD_ERROR_CHAR 2
#define SKD_ERROR_DOUBLE 3
#define SKD_SUCCESS 0
typedef struct Sudoku 
{
   char matrix[MAX_NUM_ROWS][MAX_NUM_COLS]; 
   int current_num_rows;
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
char *sudoku_get_col(Sudoku *s, int index, char *colcpy);

/**
 * Retourne une copie de la chaine de caractere a la index-ieme rangee
 */
char *sudoku_get_row(Sudoku *s, int index, char *rowcpy);

/**
 * Retourne une copie du (row, col) 3x3. Row et Col sont les coordornnees de 
 * la premiere position de ce 3x3
 */
char *sudoku_get_square(Sudoku *s, int row, int col, char *squarecpy);

/**
 * Retourne 1 si le sudoku a une taille de 9x9. Autrement retourne 0
 */
int sudoku_is_valid_size(Sudoku *s);

/**
 * Verifier si la rangee selectionnee est valide ou non.
 * Retourne l'indice qui n'est pas valide si on en trouve un, sinon retourne -1
 */
int sudoku_is_valid_row(Sudoku *s, int row_index);

/**
 * Verifier si la colomne selectionnee est valide
 * Retourne l'indice qui n'est pas valide si on en trouve un, sinon retourne -1
 */
int sudoku_is_valid_col(Sudoku *s, int col_index);

/**
 * Verifier si un 3x3 est valide. Retourne 1 si ou, 0 sinon
 */
int sudoku_is_valid_square(Sudoku *s, int row, int col);

/**
 * Verifie si le caractere est valid
 */
int sudoku_is_valid_char(char c);

#endif
