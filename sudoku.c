#include "sudoku.h"

int sudoku_insert_row(Sudoku *s, const char *row)
{
    if ((s -> current_num_rows) < MAX_NUM_ROWS) {
        strcpy(s -> matrix[s -> current_num_rows], row);
        s -> current_num_rows++;

        return 1;
    }

    return 0;
}

char * sudoku_get_col(Sudoku *s, int index, char *colcpy)
{
    int i;
    for (i = 0; i < (s -> current_num_rows); i++) {
        colcpy[i] = s -> matrix[i][index];    
    }
    
    colcpy[i] = '\0';
    return colcpy;
}

char *sudoku_get_row(Sudoku *s, int index, char *rowcpy)
{
   strcpy(rowcpy, (s -> matrix[index])); 
   return rowcpy;
}

char *sudoku_get_square(Sudoku *s, int row, int col, char *squarecpy)
{
    int k = 0;
    for (int i = row; i < (row + 3); i++) {
        for (int j = col; j < (col + 3); j++) {
            squarecpy[k++] = s -> matrix[i][j]; 
        }
    }

    squarecpy[k] = '\0';

    return squarecpy;
}

int sudoku_is_valid_size(Sudoku *s)
{
   if ((s -> current_num_rows) != NUM_ROWS)
       return 0;

   // Verifier qu'on a 9 columnes
   for (int i = 0; i < (s -> current_num_rows); i++) {
       if (strlen(s -> matrix[i]) != NUM_COLS)
           return 0;
   }

   return 1;
}

int sudoku_is_valid_row(Sudoku *s, int row_index)
{
    char row[NUM_COLS];
    sudoku_get_row(s, row_index, row);
    for (int i = 0; i < NUM_COLS; i++) {
        if (!sudoku_is_valid_char(row[i])) 
            return i;
    }

    return -1;
}

int sudoku_is_valid_col(Sudoku *s, int col_index)
{
    char col[NUM_ROWS];
    sudoku_get_col(s, col_index, col);
    for (int i = 0; i < NUM_ROWS; i++) {
        if (!sudoku_is_valid_char(col[i])) 
            return i;
    }

    return -1;
}

int sudoku_is_valid_square(Sudoku *s, int row, int col)
{
    char square[NUM_ROWS];
    sudoku_get_square(s, row, col, square);

    for (int i = 0; i < NUM_ROWS; i++) {
        if (!sudoku_is_valid_char(square[i]))
            return 0;
    }

    return 1;
}

int sudoku_is_valid_char(char c)
{
    return c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
        || c == '6' || c == '7' || c == '8' || c == '9' || c == '0';
}
