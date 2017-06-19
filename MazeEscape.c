//------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
//------------------------------------------------------------
#define WIDE 57
#define HIGH 29
#define VISION 8
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
//------------------------------------------------------------
int i = 0, j = 0;
char map[HIGH][WIDE];
//------------------------------------------------------------
void scan_map();
void print_map();
void move_character(int cx,int cy);
void search_character(int *x, int*y);
void check_clear(int *clear);
void RemoveCursor();
void gotoxy(int x, int y);
//------------------------------------------------------------
int main()
{
	RemoveCursor();

	int clear = 0;
	int character_y;
	int character_x;

	scan_map();
	while (clear != 1)
	{
		search_character(&character_x, &character_y);
		print_map();
		move_character(character_x, character_y);
		check_clear(&clear);
	}
}
//------------------------------------------------------------
void scan_map()
{
	FILE *fp = fopen("MazeMap1.txt", "r");

	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			fscanf(fp, "%c", &map[i][j]);
		}
	}
	fclose(fp);
}
void print_map()
{
	gotoxy(0, 0);
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			if (map[i][j] == '0')
				printf("  ");
			else if (map[i][j] == '1')
				printf("¡á");
			else if (map[i][j] == '2')
				printf("¿Ê");
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