#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
//------------------------------------------------------------------------------------------------------------------------
#define WIDE 57
#define HIGH 29
#define VISION 4
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define USE_ITEM 32
#define C_ITEM_MAX 10
#define H_ITEM_MAX 5
#define xr (VISION*VISION > (i + 0.5 - cy)*(i + 0.5 - cy) + (j + 0.5 - cx)*(j + 0.5 - cx))
//------------------------------------------------------------------------------------------------------------------------
int i = 0, j = 0;
char map[HIGH][WIDE];
//------------------------------------------------------------------------------------------------------------------------
void print_logo();
void print_UI(int have_item);
void print_clear(int *clear);
void create_item(int *item_count);
void scan_map();
void print_map(int cx, int cy);
void character_function(int cx, int cy, int *have_item, int *item_count);
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
	int item_count = 0;
	int have_item = 0;

	system("title ¿Ã±∏µøº∫");
	RemoveCursor();
	scan_map();
	print_logo();
	while (clear < 2)
	{
		while (clear != 1)
		{
			print_UI(have_item);
			create_item(&item_count);
			search_character(&character_x, &character_y);
			print_map(character_x, character_y);
			check_clear(&clear);
			character_function(character_x, character_y, &have_item, &item_count);
		}
		print_clear(&clear);
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
			if (getch() == 224)
				getch();
			break;
		}
	}
	system("cls");
}
void print_UI(int have_item)
{
	i = 0;
	gotoxy(114, 23);
	printf("¢∏ FINSH");
	gotoxy(116, 2);
	printf("How to play");
	gotoxy(116, 3);
	printf("°Ë : Turn UP");
	gotoxy(116, 4);
	printf("°Á : Turn LEFT");
	gotoxy(116, 5);
	printf("°Ê : Turn RIGHT");
	gotoxy(116, 6);
	printf("°È : Turn DOWN");
	gotoxy(116, 8);
	printf("Item : ");
	while (i != H_ITEM_MAX)
	{
		i++;
		if (have_item != 0)
		{
			printf("°·");
			have_item--;
		}
		else
			printf("°‡");
	}
}
void print_clear(int *clear)
{
	gotoxy(0, 0);
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			if (map[i][j] == '0')
				printf("  ");
			else if (map[i][j] == '1')
				printf("°·");
			else if (map[i][j] == '2')
				printf("ø ");
			else if (map[i][j] == '3')
				printf("®∆");
			Sleep(2);
		}
		printf("\n");
	}
	Sleep(500);
	system("cls");

	gotoxy(60, 10);
	printf("  ######  ##");
	gotoxy(60, 11);
	printf(" #        ##");
	gotoxy(60, 12);
	printf("#         ##   #####    ####    # ####");
	gotoxy(60, 13);
	printf("#         ##  #     #  #    #   ##    #");
	gotoxy(60, 14);
	printf("#         ##  ######  #     #   #");
	gotoxy(60, 15);
	printf(" #        ##  #       #    #    #");
	gotoxy(60, 16);
	printf("  ######  ##   #####   #### ##  #");
	gotoxy(0, 40);
	printf(" ");
	(*clear)++;
}
void create_item(int *item_count)
{
	int item_x;
	int item_y;

	srand(time(NULL));

	while (*item_count < C_ITEM_MAX)
	{
		item_x = rand() % WIDE;
		item_y = rand() % HIGH;

		if (map[item_y][item_x] == '0')
		{
			map[item_y][item_x] = '3';
			(*item_count)++;
		}
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
			//if (cy + VISION > i&&cy - VISION<i&&cx + VISION>j&&cx - VISION < j)
			if (xr)
			{
				if (map[i][j] == '0')
					printf("  ");
				else if (map[i][j] == '1')
					printf("°·");
				else if (map[i][j] == '2')
					printf("ø ");
				else if (map[i][j] == '3')
					printf("®∆");
			}
			else
				printf("  ");
		}
		printf("\n");
	}
}
void character_function(int cx, int cy, int *have_item, int *item_count)
{
	char key;

	key = _getch();
	if (key == 224)
		key = getch();

	if (key == UP)
	{
		if (map[cy - 1][cx] == '0' || map[cy - 1][cx] == '3')
		{
			if (map[cy - 1][cx] == '3'&&*have_item < H_ITEM_MAX)
			{
				(*have_item)++;
				(*item_count)--;
			}
			map[cy][cx] = '0';
			map[cy - 1][cx] = '2';
		}
	}
	else if (key == LEFT)
	{
		if (map[cy][cx - 1] == '0' || map[cy][cx - 1] == '3')
		{
			if (map[cy][cx - 1] == '3'&&*have_item < H_ITEM_MAX)
			{
				(*have_item)++;
				(*item_count)--;
			}
			map[cy][cx] = '0';
			map[cy][cx - 1] = '2';
		}
	}
	else if (key == RIGHT)
	{
		if (map[cy][cx + 1] == '0' || map[cy][cx + 1] == '3')
		{
			if (map[cy][cx + 1] == '3'&&*have_item < H_ITEM_MAX)
			{
				(*have_item)++;
				(*item_count)--;
			}
			map[cy][cx] = '0';
			map[cy][cx + 1] = '2';
		}
	}
	else if (key == DOWN)
	{
		if (map[cy + 1][cx] == '0' || map[cy + 1][cx] == '3')
		{
			if (map[cy + 1][cx] == '3'&&*have_item < H_ITEM_MAX)
			{
				(*have_item)++;
				(*item_count)--;
			}
			map[cy][cx] = '0';
			map[cy + 1][cx] = '2';
		}
	}
	else if (key == USE_ITEM)
	{
		if (*have_item > 0)
		{
			gotoxy(0, 0);
			for (i = 0;i < HIGH;i++)
			{
				for (j = 0;j < WIDE;j++)
				{
					if (map[i][j] == '0')
						printf("  ");
					else if (map[i][j] == '1')
						printf("°·");
					else if (map[i][j] == '2')
						printf("ø ");
					else if (map[i][j] == '3')
						printf("®∆");
				}
				printf("\n");
			}
			Sleep(1500);
			(*have_item)--;
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