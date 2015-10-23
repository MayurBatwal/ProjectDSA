#include <ncurses.h>
#include "code.h"
int main() {
	initscr();
	start_color();	
	
	init_pair(PLAYER1, COLOR_RED, COLOR_BLACK);	
	init_pair(PLAYER2, COLOR_GREEN, COLOR_BLACK);	
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);											
	
	attrset(COLOR_PAIR(3));
	attron(A_BOLD);	
	int row, column, r, c;
	int x, y;
	int chk, cw, playerwon, i, g;
	
	char title[30] = "C H A I N   R E A C T I O N";
	x = (COLS - 27) / 2;
	y = (LINES) / 2;
	move(y, x);
	noecho();
	attrset(A_UNDERLINE);
	refresh();		
	
	i = 0;
	char *p = &title[0];
	while(*p) {
		addch(*p);
		refresh();
		napms(100);
		p++;
	}
	attroff(A_UNDERLINE);
	refresh();
	napms(500);
	move(y, x);
	deleteln();
	
	g = printmenu();
	if(g == 1) {
		clear();
		attrset(COLOR_PAIR(4));
		x = (COLS - 36) / 2;
		y = (LINES) / 2;
		move(y, x);
		printw("Enter no of rows and columns : ");
		refresh();
		scanw("%d%d", &row, &column);
		refresh();
		move(y, x);
		deleteln();
		refresh();
	
		int grid[row][column];
		init(&grid[0][0], row, column);	
	
		int flag[row][column];
		initflag(&flag[0][0], row, column);			//
	
		attrset(COLOR_PAIR(4));	
		display(&grid[0][0], row, column, &flag[0][0]);
	
		x = (COLS - 60) / 2;
		y = (LINES) - 3;
		pcount = PLAYER1;
		cw = 0;
		i = 0;
		while(1) {
			move(y, x);
			attrset(COLOR_PAIR(pcount));
			printw("Enter row and column at which element is to be placed: ");
			refresh();
			scanw("%d%d", &r, &c);
		
			if(r <= 0 || r > row || c <= 0 || c > column) {
				move(y, x);
				clrtoeol();
				continue;
			}
		
			//select(row, column);
			
			chk = check(&flag[0][0], row, column, r - 1, c - 1);
			if(chk == pcount || chk == 0) {
				place(&grid[0][0], row, column, r - 1, c - 1, &flag[0][0]);
				if(pcount == PLAYER1) {
					pcount = PLAYER2;
				}
				else {
					pcount = PLAYER1;
					cw++;
				}
			}	
			display(&grid[0][0], row, column, &flag[0][0]);
			refresh();
			move(y, x);
			clrtoeol();
			if((playerwon = checkwon(&flag[0][0], row, column)) && cw > 1) {
				break;
			}
			refresh();
		}
		move(y, x);
		clrtoeol();
		x = (COLS - 15) / 2;
		move(y, x);
		attrset(COLOR_PAIR(playerwon));
		printw("PLAYER %d ", playerwon);
		attrset(COLOR_PAIR(4));
		printw("WON!!!");
		getch();
	}
	
	//getch();
	endwin();
	return 0;	
}
