#include <stdio.h>

#define N 9
#define UNASSIGNED 0

int is_exist_row(int grid[N][N], int row, int num){
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_col(int grid[N][N], int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_box(int grid[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			} 
		}
	}
	return 0;
}

int is_safe_num(int grid[N][N], int row, int col, int num) {
	return !is_exist_row(grid, row, num) 
			&& !is_exist_col(grid, col, num) 
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int grid[N][N], int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int grid[N][N]) {
	
	int row = 0;
	int col = 0;
	
	if (!find_unassigned(grid, &row, &col)){
		return 1;
	}
	
	for (int num = 1; num <= N; num++ ) {
		
		if (is_safe_num(grid, row, col, num)) {
			grid[row][col] = num;
			
			if (solve(grid)) {
				return 1;
			}
			
			grid[row][col] = UNASSIGNED;
		}
	}
	
	return 0;
}

void print_grid(int grid[N][N]) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			printf("%2d", grid[row][col]);
		}
		printf("\n");
	}
}

void getSudokuFromFile(int grid[][9]){
	int row, column;
    FILE *fp = fopen ("/home/ricky/Documents/Sudoku/SudokuFile1.txt", "r" );
    if ( fp == NULL )
    {
        printf("Couldnt open file.\nAre you sure that the program and file are in the same folder?\n\n");
	}
    while (!feof(fp))
    {
	    for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                fscanf(fp, "%d ", &grid[row][column]);
            }
        }
    }
    fclose(fp);
    printf("Loaded Sudoku:\n");
}

void main() {
	int grid[N][N];
	getSudokuFromFile(grid);
	print_grid(grid);
	if (solve(grid)) {
		printf("\n Solved sudoku: \n");
		print_grid(grid);
	} else {
		printf("no solution");
	}
}
