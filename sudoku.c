#include "sudoku.h"

int sudoku_insert_row(Sudoku *s, const char *row)
{
    if ((s -> current_empty_row) < MAX_NUM_ROW) {
        strcpy(s -> matrix[s -> current_empty_row], row);
        s -> current_empty_row++;

        return 1;
    }

    return 0;
}
