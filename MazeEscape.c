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
char logo[6][79];
//------------------------------------------------------------
void scan_logo();
void print_UI(int menu);
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
	while (clear != 1)
	{
		print_UI(select_menu);
		search_character(&character_x, &character_y);
		//print_map(character_x, character_y);
		check_clear(&clear);
		move_character(character_x, character_y);
	}
}
//------------------------------------------------------------
void scan_logo()
{
	FILE *logo_f = fopen("Logo.txt", "r");

	for (i = 0;i < 6;i++)
	{
		for (j = 0;j < 79;j++)
		{
			fscanf(logo_f, "%c", &logo[i][j]);
		}
	}
	fclose(logo_f);
}
void print_UI(int menu)
{
	if (menu == 0)
	{
		gotoxy(0, 5);
		for (i = 0;i < 7;i++)
		{
			for (j = 0;j < 79;j++)
			{
				if (logo[i][j] == '0')
					printf(" ");
				else if (logo[i][j] == "1")
					printf("#");
			}
		}
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

	key = getch();

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