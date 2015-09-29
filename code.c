//works for boundary
#include <stdio.h>
#include "code.h"

void init(int *grid, int row, int column) {			//initializes all the elements in the grid to 0
	int count = 0;
	while(count < row * column) {
		*grid = 0;
		grid++;
		count++;
	}
}

void display(int *grid, int row, int column) {			//displays the grid
	int count = 0;
	printf("\n");
	while(count < row * column) {
		if(*grid) {
			printf("%d   ", *grid);
		}
		else {
			printf("_   ");
		}
		grid++;
		count++;
		if(count % column == 0) {
			printf("\n\n");
		}
	}
}

void place(int *grid, int row, int column, int r, int c) {
	if(r < 0 || r >= row || c < 0 || c >= column) {
		return;
	} 
	
	
	
	int *p = grid;
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			grid++;
		}
	}
	for(i = 0; i < c; i++) {
		grid++;
	}
	
	if(*grid == 0 || *grid == 1 || *grid == 2) {
		expand(grid);
	}
	else { 
		explode(p, row, column, r, c);		
	}
}

void expand(int *grid) {						//increase the no. of elements at grid[r][c] by 1;
	(*grid)++;		
}


void explode(int *grid, int row, int column, int r, int c) {				//grid[row][column] contains 3 elements
	int *p = grid;
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			grid++;
		}
	}
	for(i = 0; i < c; i++) {
		grid++;
	}	
	
	(*grid) = 0;
	place(p, row, column, r - 1, c);				//place an element at grid[r - 1][c];
	place(p, row, column, r, c + 1);				//place an element at grid[r][c + 1];
	place(p, row, column, r + 1, c);				//place an element at grid[r + 1][c];
	place(p, row, column, r, c - 1);				//place an element at grid[r][c - 1];
	
}

	
