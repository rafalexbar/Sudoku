#include <iostream>

#define EMPTY  0
#define SQUARE 3
#define SUDOKU 9

bool validRow(int sudoku[SUDOKU][SUDOKU], int row, int number)
{
    for (int column = 0; column < SUDOKU; column++)
        if (sudoku[row][column] == number)
            return false;
    
    return true;
}

bool validColumn(int sudoku[SUDOKU][SUDOKU], int column, int number)
{
    for (int row = 0; row < SUDOKU; row++)
        if (sudoku[row][column] == number)
            return false;
    
    return true;
}

bool validSquare(int sudoku[SUDOKU][SUDOKU], int startingRow, int startingColumn, int number)
{
    for (int row = startingRow; row < startingRow + SQUARE; row++)
        for (int column = startingColumn; column < startingColumn + SQUARE; column++)
            if (sudoku[row][column] == number)
                return false;
    
    return true;
}

bool solveSudoku(int sudoku[SUDOKU][SUDOKU], int row, int column)
{
    if (row == SUDOKU)
        return true;
    
    int nextRow = (column + 1 == SUDOKU) ? row + 1 : row;
    int nextColumn = (column + 1) % SUDOKU;
    
    if (sudoku[row][column] != EMPTY)
        return solveSudoku(sudoku, nextRow, nextColumn);
    
    for (int number = 1; number <= SUDOKU; number++)
    {
        if (!validRow(sudoku, row, number))
            continue;
        
        if (!validColumn(sudoku, column, number))
            continue;
        
        if (!validSquare(sudoku, row - row % SQUARE, column - column % SQUARE, number))
            continue;
        
        sudoku[row][column] = number;

        if (solveSudoku(sudoku, nextRow, nextColumn))
            return true;
        
        sudoku[row][column] = EMPTY;
    }

    return false;
}

void showSudoku(int sudoku[SUDOKU][SUDOKU])
{
    for (int row = 0; row < SUDOKU; row++)
    {
        for (int column = 0; column < SUDOKU; column++)
            std::cout << sudoku[row][column] << " ";
        
        std::cout << std::endl;
    }
}

int main(int argc, char const * argv[])
{
    int sudoku[SUDOKU][SUDOKU] = {
        { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
        { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
        { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
        { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
        { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
        { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
        { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
        { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
        { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
    };
    
    solveSudoku(sudoku, 0, 0);
    
    showSudoku(sudoku);

    return 0;
}
