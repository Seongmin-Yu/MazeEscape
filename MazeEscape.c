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
void RemoveCursor();
void gotoxy(int x, int y);
//------------------------------------------------------------
int main()
{
	int clear = 0;

	RemoveCursor();
	while (clear != 1)
	{
		scan_map();
		print_map();
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
	fclose;
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