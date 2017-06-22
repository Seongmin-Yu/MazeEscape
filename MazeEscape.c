//------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
//------------------------------------------------------------------------------------------------------------------------
#define WIDE 57
#define HIGH 29
#define VISION 4
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define xr (VISION*VISION > (i + 0.5 - cy)*(i + 0.5 - cy) + (j + 0.5 - cx)*(j + 0.5 - cx))
//------------------------------------------------------------------------------------------------------------------------
int i = 0, j = 0;
char map[HIGH][WIDE];
//------------------------------------------------------------------------------------------------------------------------
void print_logo();
void print_UI();
void scan_map();
void print_map(int cx, int cy);
void move_character(int cx,int cy);
void search_character(int *x, int*y);
void check_clear(int *clear);
void RemoveCursor();
void gotoxy(int x, int y);
//------------------------------------------------------------------------------------------------------------------------
int main()
{
	int clear = 0;
	int character_y;
	int character_x;

	RemoveCursor();
	scan_map();
	print_logo();
	while (clear != 1)
	{
		print_UI();
		search_character(&character_x, &character_y);
		print_map(character_x, character_y);
		check_clear(&clear);
		move_character(character_x, character_y);
	}
}
//------------------------------------------------------------------------------------------------------------------------
void print_logo()
{
	gotoxy(40, 10);
	printf("      @   @                           @@@@@@@");
	gotoxy(40, 11);
	printf("     @ @ @ @   @@@@     @@@@@   @@@@  @        @@@@@   @@@@@   @@@@     @@@@   @@@@ ");
	gotoxy(40, 12);
	printf("    @   @  @  @    @       @   @    @ @       @       @       @    @    @   @ @    @");
	gotoxy(40, 13);
	printf("   @       @ @     @      @    @@@@@@ @@@@@@@  @@@@  @       @     @    @   @ @@@@@@");
	gotoxy(40, 14);
	printf("  @        @ @     @@    @     @      @            @  @      @     @@   @@@@  @     ");
	gotoxy(40, 15);
	printf(" @         @  @@@@  @@  @@@@@   @@@@  @@@@@@@ @@@@@    @@@@@  @@@@  @@  @      @@@@ ");
	gotoxy(40, 16);
	printf("                                                                        @           ");
	gotoxy(40, 17);
	printf("                                                                        @           ");
	while (1)
	{
		gotoxy(74, 23);
		printf("Preas any key...");
		Sleep(500);
		gotoxy(74, 23);
		printf("                 ");
		Sleep(200);
		if (kbhit())
		{
			getch();
			getch();
			break;
		}
	}
	system("cls");
}
void print_UI()
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
			//if (cy + VISION > i&&cy - VISION<i&&cx + VISION>j&&cx - VISION < j)
			if (xr)
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