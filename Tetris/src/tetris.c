/**
 * Programarea Calculatoarelor 2011-2012
 * Tema #3 - Joc de Tetris
 *
 * Schelet pentru Tetris
 *
 * Autor: Adrian Scoica <adrian.sc@rosedu.org>
 *
 */

#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "tetris.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

void meniu1()
{
    mvaddstr(1,3,"New Game");
    mvaddstr(2,3,"Set Starting Level");
    mvaddstr(3,3,"Challenge Mode");
    mvaddstr(4,3,"Load Game");
    mvaddstr(5,3,"Quit");
}

void meniu2()
{
    mvaddstr(1,3,"Level 1");
    mvaddstr(2,3,"Level 2");
    mvaddstr(3,3,"Level 3");
    mvaddstr(4,3,"Level 4");
    mvaddstr(5,3,"Level 5");
    mvaddstr(6,3,"Level 6");
    mvaddstr(7,3,"Level 7");
    mvaddstr(8,3,"Level 8");
    mvaddstr(9,3,"Level 9");
    mvaddstr(10,3,"Level 10");
}

void challenge_mode()
{
    mvaddstr(1,3,"Challenge 1");
    mvaddstr(2,3,"Challenge 2");
    mvaddstr(3,3,"Challenge 3");
    refresh();
}

void preview(int tip_piesa)
{
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    init_pair(6,COLOR_CYAN,COLOR_BLACK);
    init_pair(7,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(tip_piesa));
    if(tip_piesa==1)
    {
        move(19,20);addch('@');move(19,21);addch('@');move(20,20);addch('@');move(20,21);addch('@');
    }
    if(tip_piesa==2)
    {
        move(20,20);addch('@');move(20,23);addch('@');move(20,21);addch('@');move(20,22);addch('@');
    }
    if(tip_piesa==3)
    {
        move(20,21);addch('@');move(19,21);addch('@');move(19,20);addch('@');move(18,20);addch('@');
    }
    if(tip_piesa==4)
    {
        move(20,20);addch('@');move(19,21);addch('@');move(19,20);addch('@');move(18,21);addch('@');
    }
    if(tip_piesa==5)
    {
        move(21,20);addch('@');move(20,20);addch('@');move(20,21);addch('@');move(20,22);addch('@');
    }
    if(tip_piesa==6)
    {
        move(21,22);addch('@');move(20,20);addch('@');move(20,21);addch('@');move(20,22);addch('@');
    }
    if(tip_piesa==7)
    {
        move(21,21);addch('@');move(20,20);addch('@');move(20,21);addch('@');move(20,22);addch('@');
    }
    attroff(COLOR_PAIR(tip_piesa));

    mvaddstr(17,20,"Q - Quit");
}

void printare_harta(int harta[][30],int level,int punctaj, time_t start_time)
{
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7,COLOR_GREEN,COLOR_BLACK);
    clear();
	int i,j,a=0;
	time_t current_time;
	current_time=time(NULL);
    for(i=3;i<=21;i++)
    {
            for(j=1;j<=12;j++)
            {
                if(i==21) {move(i,j);addch('-');}
                else    if((j==1)||(j==12)) {move(i,j);addch('|');}
                else    if(harta[i][j]==1)  {move(i,j);attron(COLOR_PAIR(1));addch('@');attroff(COLOR_PAIR(1));}
                else    if(harta[i][j]==2)  {move(i,j);attron(COLOR_PAIR(2));addch('@');attroff(COLOR_PAIR(2));}
                else    if(harta[i][j]==3)  {move(i,j);attron(COLOR_PAIR(3));addch('@');attroff(COLOR_PAIR(3));}
                else    if(harta[i][j]==4)  {move(i,j);attron(COLOR_PAIR(4));addch('@');attroff(COLOR_PAIR(4));}
                else    if(harta[i][j]==5)  {move(i,j);attron(COLOR_PAIR(5));addch('@');attroff(COLOR_PAIR(5));}
                else    if(harta[i][j]==6)  {move(i,j);attron(COLOR_PAIR(6));addch('@');attroff(COLOR_PAIR(6));}
                else    if(harta[i][j]==7)  {move(i,j);attron(COLOR_PAIR(7));addch('@');attroff(COLOR_PAIR(7));}
                else    {move(i,j);addch(' ');}
            }
    }
    a=current_time-start_time;
    move(3,20);printw("Made by");
    move(4,20);printw("Dimcica Tudor");
    move(5,20);printw("AKA Tedy");
    move(6,20);printw("311 CC");
    move(14,20);printw("Timp scurs: %d secunde",a);
    move(16,20);printw("Punctaj: %d",punctaj);
    move(13,20);printw("%s",ctime(&current_time));
	move(15,20);printw("Nivel: %d", level);

	refresh();
}

void printare_piesa(int row,int col,int tip_piesa,int tip_rotatie)
{
    start_color();
    init_pair(0,COLOR_YELLOW,COLOR_BLACK);
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(6,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(tip_piesa));
	if(tip_piesa==1)
	{
		move(row,col);addch('@');
		move(row+1,col);addch('@');
		move(row,col-1);addch('@');
		move(row+1,col-1);addch('@');
	}
	if(tip_piesa==2)
	{
	    move(row,col);addch('@');
	    if(tip_rotatie%2==0)    {move(row,col-1);addch('@');move(row,col+1);addch('@');move(row,col-2);addch('@');}
	    else                    {move(row-1,col);addch('@');move(row+1,col);addch('@');move(row+2,col);addch('@');}
	}
	if(tip_piesa==3)
    {
        move(row,col);addch('@');move(row,col+1);addch('@');
        if(tip_rotatie%2==0)    {move(row-1,col);addch('@');move(row+1,col+1);addch('@');}
        else                    {move(row+1,col);addch('@');move(row+1,col-1);addch('@');}
    }
    if(tip_piesa==4)
    {
        move(row,col);addch('@');move(row+1,col);addch('@');
        if(tip_rotatie%2==0)    {move(row,col+1);addch('@');move(row-1,col+1);addch('@');}
        else                    {move(row,col-1);addch('@');move(row+1,col+1);addch('@');}
    }
    if(tip_piesa==5)
    {
        move(row,col);addch('@');
        if(tip_rotatie%2==0)            {move(row,col-1);addch('@');move(row,col+1);addch('@');}
        else                            {move(row+1,col);addch('@');move(row-1,col);addch('@');}
        if(tip_rotatie%4==0)            {move(row+1,col-1);addch('@');}
        else if(tip_rotatie%4==1)       {move(row+1,col+1);addch('@');}
        else if(tip_rotatie%4==2)       {move(row-1,col+1);addch('@');}
        else if(tip_rotatie%4==3)       {move(row-1,col-1);addch('@');}
    }
    if(tip_piesa==6)
    {
        move(row,col);addch('@');
        if(tip_rotatie%2==0)            {move(row,col-1);addch('@');move(row,col+1);addch('@');}
        else                            {move(row+1,col);addch('@');move(row-1,col);addch('@');}
        if(tip_rotatie%4==0)            {move(row+1,col+1);addch('@');}
        else if(tip_rotatie%4==1)       {move(row-1,col+1);addch('@');}
        else if(tip_rotatie%4==2)       {move(row-1,col-1);addch('@');}
        else if(tip_rotatie%4==3)       {move(row+1,col-1);addch('@');}
    }
    if(tip_piesa==7)
    {
        move(row,col);addch('@');
        if(tip_rotatie%2==0)            {move(row,col-1);addch('@');move(row,col+1);addch('@');}
        else                            {move(row+1,col);addch('@');move(row-1,col);addch('@');}
        if(tip_rotatie%4==0)            {move(row+1,col);addch('@');}
        else if(tip_rotatie%4==1)       {move(row,col+1);addch('@');}
        else if(tip_rotatie%4==2)       {move(row-1,col);addch('@');}
        else if(tip_rotatie%4==3)       {move(row,col-1);addch('@');}
    }
	refresh();
	attroff(COLOR_PAIR(tip_piesa));
}

int verif_urm_poz(int harta[][30],int row, int col, int tip_piesa, int tip_rotatie)
{
    if(tip_piesa==1)
    {
        if(harta[row+2][col]!=0||harta[row+2][col-1]!=0) return 1;
        else return 0;
    }
    if(tip_piesa==2)
    {
        if(tip_rotatie%2==0)    if(harta[row+1][col]!=0||harta[row+1][col-1]!=0||harta[row+1][col-2]!=0||harta[row+1][col+1]!=0) return 1;
        if(tip_rotatie%2==1)    if(harta[row+3][col]!=0) return 1;
        return 0;
    }
    if(tip_piesa==3)
    {
        if(tip_rotatie%2==0)    {if(harta[row+1][col]!=0||harta[row+2][col+1]!=0) return 1;}
        else                    {if(harta[row+2][col-1]!=0||harta[row+2][col]!=0||harta[row+1][col+1]!=0) return 1;}
        return 0;
    }
    if(tip_piesa==4)
    {
        if(tip_rotatie%2==0)    {if(harta[row+2][col]!=0||harta[row+1][col+1]!=0) return 1;}
        else                    {if(harta[row+1][col-1]!=0||harta[row+2][col]!=0||harta[row+2][col+1]!=0) return 1;}
        return 0;
    }
    if(tip_piesa==5)
    {
        if(tip_rotatie%4==0)    {if(harta[row+1][col]!=0||harta[row+1][col+1]!=0||harta[row+2][col-1]!=0) return 1;}
        if(tip_rotatie%4==1)    {if(harta[row+2][col]!=0||harta[row+2][col+1]!=0) return 1;}
        if(tip_rotatie%4==2)    {if(harta[row+1][col]!=0||harta[row+1][col+1]!=0||harta[row+1][col-1]!=0) return 1;}
        if(tip_rotatie%4==3)    {if(harta[row][col-1]!=0||harta[row+2][col]!=0) return 1;}
        return 0;
    }
    if(tip_piesa==6)
    {
        if(tip_rotatie%4==0)    {if(harta[row+1][col]!=0||harta[row+1][col-1]!=0||harta[row+2][col+1]!=0) return 1;}
        if(tip_rotatie%4==1)    {if(harta[row+2][col]!=0||harta[row][col+1]!=0) return 1;}
        if(tip_rotatie%4==2)    {if(harta[row+1][col]!=0||harta[row+1][col+1]!=0||harta[row+1][col-1]!=0) return 1;}
        if(tip_rotatie%4==3)    {if(harta[row+2][col-1]!=0||harta[row+2][col]!=0) return 1;}
        return 0;
    }
    if(tip_piesa==7)
    {
        if(tip_rotatie%4==0)    {if(harta[row+1][col]!=0||harta[row+1][col-1]!=0||harta[row+2][col]!=0) return 1;}
        if(tip_rotatie%4==1)    {if(harta[row+2][col]!=0||harta[row+1][col+1]!=0) return 1;}
        if(tip_rotatie%4==2)    {if(harta[row+1][col]!=0||harta[row+1][col+1]!=0||harta[row+1][col-1]!=0) return 1;}
        if(tip_rotatie%4==3)    {if(harta[row+1][col-1]!=0||harta[row+2][col]!=0) return 1;}
        return 0;
    }
    return 0;
}

int verif_laterala(int harta[][30],int row, int col, int tip_piesa, int tip_rotatie, int directie)
{
    if(tip_piesa==1)
    {
        if (directie==1) {if(harta[row][col-2]!=0||harta[row+1][col-2]!=0) return 1;}
        if (directie==2) {if(harta[row][col+1]!=0||harta[row+1][col+1]!=0) return 1;}
        return 0;
    }
    if(tip_piesa==2)
    {
        if(tip_rotatie%2==0)    {
                                if(directie==1) {if(harta[row][col-3]!=0) return 1;}
                                if(directie==2) {if(harta[row][col+2]!=0) return 1;}
                                }
        else                    {
                                if(directie==1) {if(harta[row-1][col-1]!=0||harta[row][col-1]!=0||harta[row+1][col-1]!=0||harta[row+2][col-1]!=0) return 1;}
                                if(directie==2) {if(harta[row-1][col+1]!=0||harta[row][col+1]!=0||harta[row+1][col+1]!=0||harta[row+2][col+1]!=0) return 1;}
                                }
        return 0;
    }
    if(tip_piesa==3)
    {
        if(tip_rotatie%2==0)
        {
            if(directie==1)     {if(harta[row-1][col-1]!=0||harta[row][col-1]!=0||harta[row+1][col]!=0) return 1;}
            if(directie==2)     {if(harta[row][col+2]!=0||harta[row+1][col+2]!=0) return 1;}
        }
        else
        {
            if(directie==1)     {if(harta[row][col-1]!=0||harta[row+1][col-2]!=0) return 1;}
            if(directie==2)     {if(harta[row][col+2]!=0||harta[row+1][col+1]!=0) return 1;}
        }
        return 0;
    }
    if(tip_piesa==4)
    {
        if(tip_rotatie%2==0)
        {
            if(directie==1)     {if(harta[row][col-1]!=0||harta[row+1][col-1]!=0) return 1;}
            if(directie==2)     {if(harta[row][col+2]!=0||harta[row-1][col+2]!=0) return 1;}
        }
        else
        {
            if(directie==1)     {if(harta[row][col-2]!=0||harta[row+1][col-1]!=0) return 1;}
            if(directie==2)     {if(harta[row][col+1]!=0||harta[row+1][col+2]!=0) return 1;}
        }
        return 0;
    }
    if(tip_piesa==5)
    {
        if(tip_rotatie%2==0)    { if(directie==1) {if(harta[row][col-2]!=0) return 1;}
                                  if(directie==2) {if(harta[row][col+2]!=0) return 1;}  }
        else                    { if(directie==1) {if(harta[row][col-1]!=0||harta[row+1][col-1]!=0) return 1;}
                                  if(directie==2) {if(harta[row][col+1]!=0||harta[row-1][col+1]!=0) return 1;} }
        if(tip_rotatie%4==0)    { if(directie==1)  if(harta[row+1][col-2]!=0) return 1;
                                  if(directie==2)  if(harta[row+1][col]!=0)   return 1;}
        if(tip_rotatie%4==1)    { if(directie==1)  if(harta[row-1][col-1]!=0) return 1;
                                  if(directie==2)  if(harta[row+1][col+2]!=0) return 1;}
        if(tip_rotatie%4==2)    { if(directie==1)  if(harta[row-1][col]!=0)   return 1;
                                  if(directie==2)  if(harta[row-1][col+2]!=0) return 1;}
        if(tip_rotatie%4==3)    { if(directie==1)  if(harta[row-1][col-2]!=0) return 1;
                                  if(directie==2)  if(harta[row+1][col+1]!=0) return 1;}
    }
    if(tip_piesa==6)
    {
        if(tip_rotatie%2==0)    { if(directie==1) {if(harta[row][col-2]!=0) return 1;}
                                  if(directie==2) {if(harta[row][col+2]!=0) return 1;}  }
        else                    { if(directie==1) {if(harta[row][col-1]!=0||harta[row-1][col-1]!=0) return 1;}
                                  if(directie==2) {if(harta[row][col+1]!=0||harta[row+1][col+1]!=0) return 1;} }
        if(tip_rotatie%4==0)    { if(directie==1)  if(harta[row+1][col]!=0) return 1;
                                  if(directie==2)  if(harta[row+1][col+2]!=0)   return 1;}
        if(tip_rotatie%4==1)    { if(directie==1)  if(harta[row-1][col-1]!=0) return 1;
                                  if(directie==2)  if(harta[row-1][col+2]!=0) return 1;}
        if(tip_rotatie%4==2)    { if(directie==1)  if(harta[row-1][col-2]!=0)   return 1;
                                  if(directie==2)  if(harta[row-1][col]!=0) return 1;}
        if(tip_rotatie%4==3)    { if(directie==1)  if(harta[row+1][col-2]!=0) return 1;
                                  if(directie==2)  if(harta[row-1][col+1]!=0) return 1;}
    }
    if(tip_piesa==7)
    {
        if(tip_rotatie%2==0)    { if(directie==1) {if(harta[row][col-2]!=0) return 1;}
                                  if(directie==2) {if(harta[row][col+2]!=0) return 1;}  }
        else                    { if(directie==1) {if(harta[row+1][col-1]!=0||harta[row-1][col-1]!=0) return 1;}
                                  if(directie==2) {if(harta[row-1][col+1]!=0||harta[row+1][col+1]!=0) return 1;} }
        if(tip_rotatie%4==0)    { if(directie==1)  if(harta[row+1][col-1]!=0) return 1;
                                  if(directie==2)  if(harta[row+1][col+1]!=0)   return 1;}
        if(tip_rotatie%4==1)    { if(directie==1)  if(harta[row][col-1]!=0) return 1;
                                  if(directie==2)  if(harta[row][col+2]!=0) return 1;}
        if(tip_rotatie%4==2)    { if(directie==1)  if(harta[row-1][col-1]!=0)   return 1;
                                  if(directie==2)  if(harta[row-1][col+1]!=0) return 1;}
        if(tip_rotatie%4==3)    { if(directie==1)  if(harta[row][col-2]!=0) return 1;
                                  if(directie==2)  if(harta[row][col+1]!=0) return 1;}
    }
    return 0;
}

void scriere_matrice(int harta[][30],int row, int col, int tip_piesa, int tip_rotatie)
{
    if(tip_piesa==1)
    {
        harta[row][col]=1;
		harta[row+1][col]=1;
		harta[row][col-1]=1;
		harta[row+1][col-1]=1;
    }
    if(tip_piesa==2)
    {
        harta[row][col]=2;
        if(tip_rotatie%2==0) {harta[row][col-1]=2;harta[row][col-2]=2;harta[row][col+1]=2;}
        else {harta[row-1][col]=2;harta[row+1][col]=2;harta[row+2][col]=2;}
    }
    if(tip_piesa==3)
    {
        harta[row][col]=3;harta[row][col+1]=3;
        if(tip_rotatie%2==0)    {harta[row-1][col]=3;harta[row+1][col+1]=3;}
        else                    {harta[row+1][col]=3;harta[row+1][col-1]=3;}
    }
    if(tip_piesa==4)
    {
        harta[row][col]=4;harta[row+1][col]=4;
        if(tip_rotatie%2==0)    {harta[row][col+1]=4;harta[row-1][col+1]=4;}
        else                    {harta[row][col-1]=4;harta[row+1][col+1]=4;}
    }
    if(tip_piesa==5)
    {
        harta[row][col]=5;
        if(tip_rotatie%2==0)    {harta[row][col-1]=5;harta[row][col+1]=5;}
        else                    {harta[row-1][col]=5;harta[row+1][col]=5;}
        if(tip_rotatie%4==0)    {harta[row+1][col-1]=5;}
        if(tip_rotatie%4==1)    {harta[row+1][col+1]=5;}
        if(tip_rotatie%4==2)    {harta[row-1][col+1]=5;}
        if(tip_rotatie%4==3)    {harta[row-1][col-1]=5;}
    }
    if(tip_piesa==6)
    {
        harta[row][col]=6;
        if(tip_rotatie%2==0)    {harta[row][col-1]=6;harta[row][col+1]=6;}
        else                    {harta[row-1][col]=6;harta[row+1][col]=6;}
        if(tip_rotatie%4==0)    {harta[row+1][col+1]=6;}
        if(tip_rotatie%4==1)    {harta[row-1][col+1]=6;}
        if(tip_rotatie%4==2)    {harta[row-1][col-1]=6;}
        if(tip_rotatie%4==3)    {harta[row+1][col-1]=6;}
    }
    if(tip_piesa==7)
    {
        harta[row][col]=7;
        if(tip_rotatie%2==0)    {harta[row][col-1]=7;harta[row][col+1]=7;}
        else                    {harta[row-1][col]=7;harta[row+1][col]=7;}
        if(tip_rotatie%4==0)    {harta[row+1][col]=7;}
        if(tip_rotatie%4==1)    {harta[row][col+1]=7;}
        if(tip_rotatie%4==2)    {harta[row-1][col]=7;}
        if(tip_rotatie%4==3)    {harta[row][col-1]=7;}
    }

}

int rotatie_valabila(int harta[][30],int row, int col, int tip_piesa, int tip_rotatie)
{
    if(tip_piesa==2)
    {
        if(tip_rotatie%2==0)    {if(harta[row-1][col]!=0||harta[row+1][col]!=0||harta[row+2][col]!=0) return 0;}
        if(tip_rotatie%2==1)    {if(harta[row][col-2]!=0||harta[row][col-1]!=0||harta[row][col+1]!=0) return 0;}
        return 1;
    }
    if(tip_piesa==3)
    {
        if(tip_rotatie%2==0)    {if(harta[row+1][col]!=0||harta[row+1][col-1]!=0) return 0;}
        if(tip_rotatie%2==1)    {if(harta[row][col+1]!=0||harta[row-1][col+1]!=0) return 0;}
        return 1;
    }
    if(tip_piesa==4)
    {
        if(tip_rotatie%2==0)    {if(harta[row+1][col+1]!=0||harta[row][col-1]!=0) return 0;}
        if(tip_rotatie%2==1)    {if(harta[row][col+1]!=0||harta[row-1][col+1]!=0) return 0;}
        return 1;
    }
    if(tip_piesa==5)
    {
        if(tip_rotatie%4==0)    {if(harta[row-1][col]!=0||harta[row+1][col]!=0||harta[row+1][col+1]!=0) return 0;}
        if(tip_rotatie%4==1)    {if(harta[row][col-1]!=0||harta[row][col+1]!=0||harta[row-1][col+1]!=0) return 0;}
        if(tip_rotatie%4==2)    {if(harta[row-1][col]!=0||harta[row-1][col-1]!=0||harta[row+1][col]!=0) return 0;}
        if(tip_rotatie%4==3)    {if(harta[row][col-1]!=0||harta[row+1][col-1]!=0||harta[row][col+1]!=0) return 0;}
        return 1;
    }
    if(tip_piesa==6)
    {
        if(tip_rotatie%4==0)    {if(harta[row-1][col]!=0||harta[row+1][col]!=0||harta[row-1][col+1]!=0) return 0;}
        if(tip_rotatie%4==1)    {if(harta[row][col-1]!=0||harta[row][col+1]!=0||harta[row-1][col-1]!=0) return 0;}
        if(tip_rotatie%4==2)    {if(harta[row-1][col]!=0||harta[row+1][col-1]!=0||harta[row+1][col]!=0) return 0;}
        if(tip_rotatie%4==3)    {if(harta[row][col-1]!=0||harta[row+1][col+1]!=0||harta[row][col+1]!=0) return 0;}
        return 1;
    }
    if(tip_piesa==7)
    {
        if(tip_rotatie%4==0)    {if(harta[row-1][col]!=0) return 0;}
        if(tip_rotatie%4==1)    {if(harta[row][col-1]!=0) return 0;}
        if(tip_rotatie%4==2)    {if(harta[row+1][col]!=0) return 0;}
        if(tip_rotatie%4==3)    {if(harta[row][col+1]!=0) return 0;}
        return 1;
    }

    return 0;
}

void collapse(int harta[][30], int *punctaj, int level, int lungime, int latime)
{
    int i,j,semafor,s,contor_linii=0,p;
    semafor=1;
    for(i=lungime+2;i>=3;i--)
    {
        for(j=2;j<=latime+1;j++)
        {
            if(harta[i][j]==0) semafor=0;
        }
        if(semafor==1)
        {
            contor_linii++;
            for(s=i;s>=3;s--)
            {
                for(j=2;j<=latime+1;j++)
                {
                    harta[s][j]=harta[s-1][j];
                }
            }
            i=i+1;
        }
        else semafor=1;

    }
    p=5*level;
    for(i=0;i<contor_linii;i++)
    {
        *punctaj=*punctaj+p*(2+i);
    }
}


int main()
{
    WINDOW* wnd = initscr();
    long delay;
    int lungime=18, latime=10, harta[30][30];
    int urm_piesa=0, tip_piesa=0, tip_rotatie=0, stop=0;
    int clo, i, j, challenge=0, row, p, final=0, col, o, level, punctaj=0, k;
    time_t start_time;

    FILE *f;

    for(i=2;i<=lungime+3;i++)
        for(j=1;j<=latime+2;j++)
            harta[i][j]=0;
    for(i=3;i<=21;i++) {harta[i][1]=9;harta[i][latime+2]=9;}
    for(i=1;i<=12;i++) harta[lungime+3][i]=9;

    curs_set(0);
    clear();
    noecho();
    cbreak();
    keypad(wnd, TRUE);
    nodelay(wnd, TRUE);
    start_color();

    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_BLUE,COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7,COLOR_GREEN,COLOR_BLACK);

    meniu1();
    row=1;col=1;
    move(row,col);
    addch('*');
    refresh();


    while(1)
    {
       	p = get_key_pressed();
       	if (tolower(p) == KEY_UP)
       	{
           		move(row,col);
           		addch(' ');
           		row=MAX(row-1,1);
           		move(row,col);
           		addch('*');
       	}
       	else if(tolower(p) == KEY_DOWN)
       	{
           		move(row,col);
           		addch(' ');
           		row=MIN(row+1,5);
           		move(row,col);
           		addch('*');
       	}
       	else if((tolower(p) == 10)||(tolower(p) == 32))
       	{
           		o=row;
           		break;
       	}
       	refresh();
    }

    row=2;col=6;

    if(o==5) {endwin();return 0;}

    if(o==4)
    {
        f=fopen("saved_game","rb");
        fread(&row,sizeof(int),1,f);
        fread(&col,sizeof(int),1,f);
        fread(&tip_piesa,sizeof(int),1,f);
        fread(&urm_piesa,sizeof(int),1,f);
        fread(&tip_rotatie,sizeof(int),1,f);
        fread(&punctaj,sizeof(int),1,f);
        fread(&level,sizeof(int),1,f);
        fread(harta,sizeof(int),900,f);
        fclose(f);
    }

    if(o==3)
    {
        clear();
        row=1;col=1;move(row,col);addch('*');
        challenge_mode();
        while(1)
        {
            p = get_key_pressed();
            if (tolower(p) == KEY_UP)
            {
                move(row,col);
                addch(' ');
                row=MAX(row-1,1);
                move(row,col);
                addch('*');
            }
            else if(tolower(p) == KEY_DOWN)
            {
                move(row,col);
                addch(' ');
                row=MIN(row+1,3);
                move(row,col);
                addch('*');
            }
            else if((tolower(p) == 10)||(tolower(p) == 32))
            {
                challenge=row;
                break;
            }
        }
        row=2;col=6;level=1;
    }

    if(challenge!=0)
    {
        if(challenge==1)
        {
            f=fopen("challenge1","rb");
            fread(harta,sizeof(int),900,f);
            fclose(f);
        }
        if(challenge==2)
        {
            f=fopen("challenge2","rb");
            fread(harta,sizeof(int),900,f);
            fclose(f);
        }
        if(challenge==3)
        {
            f=fopen("challenge3","rb");
            fread(harta,sizeof(int),900,f);
            fclose(f);
        }
    }

    clear();


    if(o==2)
    {
       	meniu2();
       	row=1;col=1;
       	move(row,col);
       	addch('*');
       	while(1)
       	{
           		p = get_key_pressed();
           		if (tolower(p) == KEY_UP)
          		{
               		move(row,col);
               		addch(' ');
               		row=MAX(row-1,1);
               		move(row,col);
               		addch('*');
           		}
           		else if(tolower(p) == KEY_DOWN)
           		{
               		move(row,col);
               		addch(' ');
               		row=MIN(row+1,10);
               		move(row,col);
               		addch('*');
           		}
           		else if((tolower(p) == 10)||(tolower(p) == 32))
           		{
               		level=row;row=2;col=7;
               		break;
           		}
           		refresh();
        }
    }


    if(o==1) level=1;


    clear();
	start_time=time(NULL);

    if(o!=4)
    {
        srand(time(NULL));
        tip_piesa=rand()%7+1;
        srand(time(NULL)+1);
        urm_piesa=rand()%7+1;
    }

    printare_harta(harta,level,punctaj,start_time);preview(urm_piesa);
	printare_piesa(row,col,tip_piesa,tip_rotatie);
	refresh();


    clo=clock();

    while(1)
    {
        refresh();
       	p = get_key_pressed();
       	if(final!=1&&tolower(p)==KEY_RIGHT)
                                        {
                                            if(verif_laterala(harta,row,col,tip_piesa,tip_rotatie,2)==0)
                                            {
                                                if(tip_piesa==1)    col=MIN(col+1,latime+1);

                                                if(tip_piesa==2&&tip_rotatie%2==0)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==2&&tip_rotatie%2==1)    col=MIN(col+1,latime+1);

                                                if(tip_piesa==3&&tip_rotatie%2==0)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==3&&tip_rotatie%2==1)    col=MIN(col+1,latime+1);

                                                if(tip_piesa==4&&tip_rotatie%2==0)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==4&&tip_rotatie%2==1)    col=MIN(col+1,latime+1);

                                                if(tip_piesa==5&&tip_rotatie%4==0)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==5&&tip_rotatie%4==1)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==5&&tip_rotatie%4==2)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==5&&tip_rotatie%4==3)    col=MIN(col+1,latime+2);

                                                if(tip_piesa==6&&tip_rotatie%4==0)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==6&&tip_rotatie%4==1)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==6&&tip_rotatie%4==2)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==6&&tip_rotatie%4==3)    col=MIN(col+1,latime+2);

                                                if(tip_piesa==7&&tip_rotatie%4==0)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==7&&tip_rotatie%4==1)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==7&&tip_rotatie%4==2)    col=MIN(col+1,latime+1);
                                                if(tip_piesa==7&&tip_rotatie%4==3)    col=MIN(col+1,latime+2);

                                                move(row,col);
                                                clear();
                                                printare_harta(harta,level,punctaj,start_time); preview(urm_piesa);
                                                refresh();
                                                printare_piesa(row,col,tip_piesa,tip_rotatie);
                                                refresh();
                                                if(verif_urm_poz(harta,row,col,tip_piesa,tip_rotatie)==1)
                                                {
                                                    final=1;scriere_matrice(harta,row,col,tip_piesa,tip_rotatie);
                                                }

                                            }
         	                            }
       	else if(final!=1&&tolower(p)==KEY_LEFT)
                                        {
                                            if(verif_laterala(harta,row,col,tip_piesa,tip_rotatie,1)==0)
                                            {
                                                if(tip_piesa==1)    col=MAX(col-1,3);

                                                if(tip_piesa==2&&tip_rotatie%2==0)    col=MAX(col-1,4);
                                                if(tip_piesa==2&&tip_rotatie%2==1)    col=MAX(col-1,2);

                                                if(tip_piesa==3&&tip_rotatie%2==0)    col=MAX(col-1,2);
                                                if(tip_piesa==3&&tip_rotatie%2==1)    col=MAX(col-1,2);

                                                if(tip_piesa==4&&tip_rotatie%2==0)    col=MAX(col-1,2);
                                                if(tip_piesa==4&&tip_rotatie%2==1)    col=MAX(col-1,2);

                                                if(tip_piesa==5&&tip_rotatie%4==0)    col=MAX(col-1,2);
                                                if(tip_piesa==5&&tip_rotatie%4==1)    col=MAX(col-1,1);
                                                if(tip_piesa==5&&tip_rotatie%4==2)    col=MAX(col-1,2);
                                                if(tip_piesa==5&&tip_rotatie%4==3)    col=MAX(col-1,2);

                                                if(tip_piesa==6&&tip_rotatie%4==0)    col=MAX(col-1,2);
                                                if(tip_piesa==6&&tip_rotatie%4==1)    col=MAX(col-1,1);
                                                if(tip_piesa==6&&tip_rotatie%4==2)    col=MAX(col-1,2);
                                                if(tip_piesa==6&&tip_rotatie%4==3)    col=MAX(col-1,2);

                                                if(tip_piesa==7&&tip_rotatie%4==0)    col=MAX(col-1,2);
                                                if(tip_piesa==7&&tip_rotatie%4==1)    col=MAX(col-1,1);
                                                if(tip_piesa==7&&tip_rotatie%4==2)    col=MAX(col-1,2);
                                                if(tip_piesa==7&&tip_rotatie%4==3)    col=MAX(col-1,2);

                                                move(row,col);
                                                clear(); printare_harta(harta,level,punctaj,start_time); preview(urm_piesa);
                                                refresh();
                                                printare_piesa(row,col,tip_piesa,tip_rotatie);
                                                refresh();
                                                if(verif_urm_poz(harta,row,col,tip_piesa,tip_rotatie)==1)
                                                {
                                                    final=1;scriere_matrice(harta,row,col,tip_piesa,tip_rotatie);
                                                }

                                            }
                         	            }
       	else if(final!=1&&tolower(p)==KEY_DOWN)
                                        {
                                            row=MIN(row+1,lungime+3);
                                            move(row,col);
                                            clear(); printare_harta(harta,level,punctaj,start_time); preview(urm_piesa);
                                            refresh();
                                            printare_piesa(row,col,tip_piesa,tip_rotatie);
                                            refresh();
                                            if(verif_urm_poz(harta,row,col,tip_piesa,tip_rotatie)==1)
                                            {
                                                final=1;scriere_matrice(harta,row,col,tip_piesa,tip_rotatie);
                                            }

       	                                }
        else if(final!=1&&tolower(p)==KEY_UP)
                                        {
                                            if(rotatie_valabila(harta,row,col,tip_piesa,tip_rotatie)==1)
                                            {
                                                tip_rotatie++;
                                                move(row,col);clear();
                                                printare_harta(harta,level,punctaj,start_time); preview(urm_piesa);
                                                printare_piesa(row,col,tip_piesa,tip_rotatie);
                                                refresh();
                                                if(verif_urm_poz(harta,row,col,tip_piesa,tip_rotatie)==1)
                                                {
                                                    final=1;scriere_matrice(harta,row,col,tip_piesa,tip_rotatie);
                                                }

                                            }
                                        }
       	else if(tolower(p) == 'q') break;
       	else if(tolower(p) == 'p') {mvaddstr(9,20,"PAUZA");
                                    while(get_key_pressed()==NO_KEY_PRESSED){}
                                    }
        else if(tolower(p)=='s')
                                    {
                                        f=fopen("saved_game","wb");
                                        fwrite(&row,sizeof(int),1,f);
                                        fwrite(&col,sizeof(int),1,f);
                                        fwrite(&tip_piesa,sizeof(int),1,f);
                                        fwrite(&urm_piesa,sizeof(int),1,f);
                                        fwrite(&tip_rotatie,sizeof(int),1,f);
                                        fwrite(&punctaj,sizeof(int),1,f);
                                        fwrite(&level,sizeof(int),1,f);
                                        fwrite(harta,sizeof(int),900,f);
                                        fclose(f);
                                        mvaddstr(10,20,"JOC SALVAT");k=0;
                                    }
        if(verif_urm_poz(harta,row,col,tip_piesa,tip_rotatie)==1)
        {
            final=1;scriere_matrice(harta,row,col,tip_piesa,tip_rotatie);
        }

        delay=400000-31000*level;
        if(clock()-clo>delay)
        {
            row=MIN(row+1,lungime+3);
            move(row,col);
            clear(); k=MAX(k+1,10);
            printare_harta(harta,level,punctaj,start_time); preview(urm_piesa);
            printare_piesa(row,col,tip_piesa,tip_rotatie);
            refresh();
            clo=clock();
        }

        if(k<=15) mvaddstr(10,20,"JOC SALVAT");

        if(final==1)
        {
            collapse(harta,&punctaj,level,lungime,latime);
            if(punctaj>=level*level*100)  {if(level<10) level++;}
            row=2;col=7;final=0;tip_rotatie=0;
            tip_piesa=urm_piesa;
            urm_piesa=rand()%7+1;
        }

        if(verif_urm_poz(harta,row,col,tip_piesa,tip_rotatie)==1)
        {
            final=1;scriere_matrice(harta,row,col,tip_piesa,tip_rotatie);
        }

        p=0;

        for(j=2;j<=latime+1;j++)
        if(harta[3][j]!=0) stop=1;

        if(stop==1) {
                        mvaddstr(12,2,"GAME  OVER");
                        while(get_key_pressed()==NO_KEY_PRESSED){} break;
                    }


   	}

   	endwin();
   	return 0;
}
