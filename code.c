#include <ncurses.h>
#include "code.h"
#include <string.h>

void init(int *grid, int row, int column) {			//initializes all the elements in the grid to 0
	int count = 0;
	while(count < row * column) {
		*grid = 0;
		grid++;
		count++;
	}
}

void display(int *grid, int row, int column, int *flag) {			//displays the grid
	int count = 0, chk;
	int x, y, indent, i = 0;
	indent = (COLS - (4 * (column - 1) + 1)) / 2;
	x = indent;
	y = ((LINES - (2 * (row - 1) + 1)) / 2);
	move(y, x);
	attrset(COLOR_PAIR(4));
	//attron(A_REVERSE);
	while(count < row * column) {
		move(y, x);
		if(*grid) {
			chk = *flag;
			attrset(COLOR_PAIR(chk));
			printw("%d", *grid);
			x = x + 4;
			refresh();
		}
		else {
			printw("_");
			x = x + 4;
			refresh();
			//attrset(COLOR_PAIR(pcount));
		}
		attrset(COLOR_PAIR(4));
		if(i == 0) {
			//attroff(A_REVERSE);
			i++;
		}
		grid++;
		flag++;
		count++;
		if(count % column == 0) {
			y = y + 2;
			x = indent;
			refresh();
		}
	}
}

void place(int *grid, int row, int column, int r, int c, int *flag) {
	if(r < 0 || r >= row || c < 0 || c >= column) {
		return;
	} 
	
	
	int *p = grid;
	int *q = flag;					//	
	
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			grid++;
			flag++;				//			
		}
	}
	for(i = 0; i < c; i++) {
		grid++;
		flag++;				//		
	}
	
	if(r == 0 || r == row - 1 || c == 0 || c == column - 1) {
		if((r == 0 && c == 0) || (r == row - 1 && c == 0) || (r == 0 && c == column - 1) || (r == row - 1 && c == column - 1)) {
			if(*grid == 0) {
				expand(grid, flag);
			}
			else{
				explode(p, row, column, r, c, q);
			}
		}
		else {
			if(*grid == 0 || *grid == 1) {
				expand(grid, flag);
			}
			else{
				explode(p, row, column, r, c, q);
			}
		}
	}
	else if(*grid == 0 || *grid == 1 || *grid == 2) {
		expand(grid, flag);
	}
	else { 
		explode(p, row, column, r, c, q);		
	}
}

void expand(int *grid, int *flag) {						//increase the no. of elements at grid[r][c] by 1;
	napms(100);
	(*grid)++;		
	*flag = pcount;					//		
}


void explode(int *grid, int row, int column, int r, int c, int *flag) {				//grid[row][column] contains 3 elements
	napms(100);
	int *p = grid;
	int *q = flag;					//		
	
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			grid++;
			flag++;				//			
		}
	}
	for(i = 0; i < c; i++) {
		grid++;
		flag++;				//
	}	
	
	(*grid) = 0;
	(*flag) = 0;					//
	
	napms(100);	
	place(p, row, column, r - 1, c, q);				//place an element at grid[r - 1][c];
	place(p, row, column, r, c + 1, q);				//place an element at grid[r][c + 1];
	place(p, row, column, r + 1, c, q);				//place an element at grid[r + 1][c];
	place(p, row, column, r, c - 1, q);				//place an element at grid[r][c - 1];
	
}

/*
void select(int row, int column) {
	int x, y, indent, i = 0;
	int ch;
	//char c;
	indent = (COLS - (4 * (column - 1) + 1)) / 2;
	x = indent;
	y = ((LINES - (2 * (row - 1) + 1)) / 2);
	move(y, x);
	keypad(stdscr, TRUE);
	noecho();
	do {
		//scanw("%d", &c);
		ch = getch();
		//ch = 's';//KEY_DOWN;
		switch(ch) {
			case KEY_DOWN:
				attroff(A_REVERSE);
				y = y + 2;
				move(y, x);
				attron(A_REVERSE);
				break;
			
			case KEY_UP:
				attroff(A_REVERSE);
				y = y - 2;
				move(y, x);
				attron(A_REVERSE);
				break;	
				
			case KEY_RIGHT:
				attroff(A_REVERSE);
				x = x + 4;
				move(y, x);
				attron(A_REVERSE);
				break;	
				
			case KEY_LEFT:
				attroff(A_REVERSE);
				x = x - 4;
				move(y, x);
				attron(A_REVERSE);
				break;	
				
			default : 
				break;
		}
		refresh();
	}while(ch != '\n');
	echo();
}	
*/
void initflag(int *flag, int row, int column) {
	int count = 0;
	while(count < row * column) {
		*flag = 0;
		flag++;
		count++;
	}
}

void displayflag(int *flag, int row, int column) {			//displays the grid
	int count = 0;
	int x, y, indent, i = 0;
	indent = (COLS - (4 * (column - 1) + 1)) / 2;
	indent = indent + 20;					//to be removed
	x = indent;
	y = ((LINES - (2 * (row - 1) + 1)) / 2);
	move(y, x);
	//attron(A_REVERSE);
	while(count < row * column) {
		move(y, x);
		//if(*grid) {
			printw("%d", *flag);
			x = x + 4;
		/*	refresh();
		}
		else {
			printw("_");
			x = x + 4;
			refresh();
		}
		if(i == 0) {
			attroff(A_REVERSE);
			i++;
		}*/
		flag++;
		count++;
		if(count % column == 0) {
			//printw("\n\n\t\t");
			y = y + 2;
			x = indent;
			refresh();
		}
	}
}

int check(int *flag, int row, int column, int r, int c) {
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			flag++;				//			
		}
	}
	for(i = 0; i < c; i++) {
		flag++;				//		
	}

	if(*flag == 1) {
		return PLAYER1;
	}
	if(*flag == 2) {
		return PLAYER2;
	}
	return 0;
}

int checkwon(int *flag, int row, int column) {
	int player, count = 0;
	while(count < row * column) {
		if(*flag) {
			player = *flag;
			flag++;
			count++;
			break;
		}
		flag++;
		count++;
	}
	while(count < row * column) {
		if(*flag && *flag != player) {
			return 0;
		}
		flag++;
		count++;
	}
	return player;
}

#define X ((COLS - strlen(menu[c])) / 2)
int printmenu() {
	char menu[3][16] = {"PLAY",  "INSTRUCTIONS", "EXIT"};
	int key, menuitem = 0, c, x, y;
	x = (COLS - 40) / 2;
	y = (LINES - 5) / 2;
	for(c = 0;c < 3; c++) {
		if(c == menuitem) {
			attron(A_REVERSE);
		}
		mvaddstr(y + (c * 2), X, menu[c]);
		attroff(A_REVERSE);
	}
	keypad(stdscr,TRUE);
	noecho();
	do {
		key = getch();
		switch(key) {
			case KEY_DOWN:
				menuitem++;
				if(menuitem > 3-1) {
					menuitem = 0;
				}
				break;

			case KEY_UP:
				menuitem--;
				if(menuitem < 0) {
					menuitem = 3-1;
				}
				break;

			default: break;

		}
		for(c = 0;c < 3; c++) {
			if(c == menuitem) {
				attron(A_REVERSE);
			}
			mvaddstr(y + (c * 2), X, menu[c]);
			attroff(A_REVERSE);
		}

	} while(key != '\n');
	echo();
	if(menuitem == 0) {
		return 1;
	}
	else {
		return 0;
	}
}








	
