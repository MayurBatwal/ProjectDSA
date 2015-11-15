/*****************************************************************************
 * Copyright (C) Mayur.S.Batwal mayur.batwal@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 ***************************************************************************/


#define PLAYER1 1
#define PLAYER2 2
int pcount;

void init(int *grid, int row, int column);
void display(int *grid, int row, int column, int *flag);
void place(int *grid, int row, int column, int r, int c, int *flag);
void expand(int *grid, int *flag);
void explode(int *grid, int row, int column, int r, int c, int *flag);			
void select(int row, int column);

void initflag(int *flag, int row, int column);
void flag(int *flag, int row, int column);
void displayflag(int *flag, int row, int column);

int check(int *flag, int row, int column, int r, int c);

int checkwon(int *flag, int row, int column);

int printmenu();
