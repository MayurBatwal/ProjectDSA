#include <stdio.h>
#include "code.h"
int main() {
	int row, column, r, c;
	printf("Enter no of rows and columns : ");
	scanf("%d%d", &row, &column);
	int grid[row][column];
	init(&grid[0][0], row, column);	
	display(&grid[0][0], row, column);
	while(1) {
		printf("Enter row and column at which element is to be placed: ");
		scanf("%d%d", &r, &c);
		place(&grid[0][0], row, column, r - 1, c - 1);	
		display(&grid[0][0], row, column);
	}
	return 0;	
}
