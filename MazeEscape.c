//------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
//------------------------------------------------------------
#define WIDE 57
#define HIGH 29
#define VISION 4
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
//------------------------------------------------------------
int i = 0, j = 0;
char map[HIGH][WIDE];
//------------------------------------------------------------
void print_UI(int menu,int *select_menu);
void scan_map();
void print_map(int cx, int cy);
void move_character(int cx,int cy);
void search_character(int *x, int*y);
void check_clear(int *clear);
void RemoveCursor();
void gotoxy(int x, int y);
//------------------------------------------------------------
int main()
{
	int select_menu = 0;
	int clear = 0;
	int character_y;
	int character_x;

	RemoveCursor();
	scan_map();
	print_UI(select_menu,&select_menu);
	while (clear != 1)
	{
		print_UI(select_menu, &select_menu);
		search_character(&character_x, &character_y);
		print_map(character_x, character_y);
		check_clear(&clear);
		move_character(character_x, character_y);
	}
}
//------------------------------------------------------------
void print_UI(int menu,int *select_menu)
{
	char a;
	if (menu == 0)
	{
		gotoxy(40, 5);
		printf("      #   #                           #######");
		gotoxy(40, 6);
		printf("     # # # #   ####     #####   ####  #        #####   #####   ####     ####   #### ");
		gotoxy(40, 7);
		printf("    #   #  #  #    #       #   #    # #       #       #       #    #    #   # #    #");
		gotoxy(40, 8);
		printf("   #       # #     #      #    ###### #######  ####  #       #     #    #   # ######");
		gotoxy(40, 9);
		printf("  #        # #     ##    #     #      #            #  #      #     ##   ####  #     ");
		gotoxy(40, 10);
		printf(" #         #  ####  ##  #####   ####  ####### #####    #####  ####  ##  #      #### ");
		gotoxy(40, 11);
		printf("                                                                        #           ");
		gotoxy(40, 12);
		printf("                                                                        #           ");
		gotoxy(74, 16);
		printf("Preas any key...");
		a = getch();
		if (a != '-')
			*select_menu = 1;
		system("cls");
	}
	else if (menu == 1)
	{
		gotoxy(114, 23);
		printf("¢¸ FINSH");
		gotoxy(116, 2);
		printf("How to play");
		gotoxy(116, 3);
		printf("¡è : Turn UP");
		gotoxy(116, 4);
		printf("¡ç : Turn LEFT");
		gotoxy(116, 5);
		printf("¡æ : Turn RIGHT");
		gotoxy(116, 6);
		printf("¡é : Turn DOWN");
	}
}
void scan_map()
{
	FILE *map_f = fopen("MazeMap1.txt", "r");

	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			fscanf(map_f, "%c", &map[i][j]);
		}
	}
	fclose(map_f);
}
void print_map(int cx, int cy)
{
	gotoxy(0, 0);
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			if (cy + VISION > i&&cy - VISION<i&&cx + VISION>j&&cx - VISION < j)
			{
				if (map[i][j] == '0')
					printf("  ");
				else if (map[i][j] == '1')
					printf("¡á");
				else if (map[i][j] == '2')
					printf("¿Ê");
			}
			else
				printf("  ");
		}
		printf("\n");
	}
}
void move_character(int cx, int cy)
{
	char key;

	key = _getch();

	if (key == UP)
	{
		if (map[cy - 1][cx] == '0')
		{
			map[cy][cx] = '0';
			map[cy - 1][cx] = '2';
		}
	}
	else if (key == LEFT)
	{
		if (map[cy][cx - 1] == '0')
		{
			map[cy][cx] = '0';
			map[cy][cx - 1] = '2';
		}
	}
	else if (key == RIGHT)
	{
		if (map[cy][cx + 1] == '0')
		{
			map[cy][cx] = '0';
			map[cy][cx + 1] = '2';
		}
	}
	else if (key == DOWN)
	{
		if (map[cy + 1][cx] == '0')
		{
			map[cy][cx] = '0';
			map[cy + 1][cx] = '2';
		}
	}
}
void search_character(int *x, int*y)
{
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			if (map[i][j] == '2')
			{
				*x = j;
				*y = i;
			}
		}
	}
}
void check_clear(int *clear)
{
	if (map[23][55] == '2')
		*clear = 1;
}
void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}