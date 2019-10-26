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

int sudoku_valid_size(Sudoku *s)
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
