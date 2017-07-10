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
#define ENTER 13
#define USE_ITEM 32
#define C_ITEM_MAX 10
#define H_ITEM_MAX 5
#define Squre (cy + VISION > i&&cy - VISION<i&&cx + VISION>j&&cx - VISION < j)
#define Circle (VISION*VISION > (i + 0.5 - cy)*(i + 0.5 - cy) + (j + 0.5 - cx)*(j + 0.5 - cx))
//------------------------------------------------------------------------------------------------------------------------
int i = 0, j = 0;
char map[HIGH][WIDE];
//------------------------------------------------------------------------------------------------------------------------
int Logo_UI(int *regame);
void scan_map(int select_map);
void Exit_UI();
void create_item(int *item_count);
void search_character(int *x, int*y);
void print_UI(int have_item);
void print_map(int cx, int cy);
void character_function(int cx, int cy, int *have_item, int *item_count);
void check_clear(int *clear, int select_map);
void print_clear();
void RemoveCursor();
void gotoxy(int x, int y);
int main()
{
	int item_count = 0;
	int have_item = 0;
	int clear = 1;
	int character_y;
	int character_x;
	int select_map = 0;
	int regame = 1;

	while (regame)
	{
		RemoveCursor();
		select_map = Logo_UI(&regame);
		system("cls");
		if (regame == 1)
		{
			scan_map(select_map);
			while (clear)
			{
				create_item(&item_count);
				search_character(&character_x, &character_y);
				print_UI(have_item);
				print_map(character_x, character_y);
				character_function(character_x, character_y, &have_item, &item_count);
				check_clear(&clear, select_map);
			}
			print_clear();
		}
	}
	Exit_UI();
}
int Logo_UI(int *regame)
{
	int sel_map = 0;
	char key;

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
		if (kbhit())
		{
			key = getch();
			if (key == ENTER)
			{
				if (sel_map == 2)
					*regame = 0;
				return sel_map;
				break;
			}
			else if (key == UP)
			{
				if (sel_map > 0)
					sel_map -= 1;
			}
			else if (key == DOWN)
			{
				if (sel_map < 2)
					sel_map += 1;
			}
		}
		if (sel_map == 0)
		{
			gotoxy(74, 23);
			printf("¢º Easy");
			gotoxy(74, 24);
			printf("   Nomal");
			gotoxy(74, 25);
			printf("   Exit");
			Sleep(200);
			gotoxy(74, 23);
			printf("   Easy");
			Sleep(200);

		}
		else if (sel_map == 1)
		{
			gotoxy(74, 23);
			printf("   Easy");
			gotoxy(74, 24);
			printf("¢º Nomal");
			gotoxy(74, 25);
			printf("   Exit");
			Sleep(200);
			gotoxy(74, 24);
			printf("   Nomal");
			Sleep(200);
		}
		else if (sel_map == 2)
		{
			gotoxy(74, 23);
			printf("   Easy");
			gotoxy(74, 24);
			printf("   Nomal");
			gotoxy(74, 25);
			printf("¢º Exit");
			Sleep(200);
			gotoxy(74, 25);
			printf("   Exit");
			Sleep(200);
		}
	}
	system("cls");
}
void scan_map(int select_map)
{
	if (select_map == 0)
	{
		FILE *map_f1 = fopen("MazeMap1.txt", "r");
		for (i = 0;i < HIGH;i++)
		{
			for (j = 0;j < WIDE;j++)
			{
				fscanf(map_f1, "%c", &map[i][j]);
			}
		}
		fclose(map_f1);
	}
	else if (select_map == 1)
	{
		FILE *map_f2 = fopen("MazeMap2.txt", "r");
		for (i = 0;i < HIGH;i++)
		{
			for (j = 0;j < WIDE;j++)
			{
				fscanf(map_f2, "%c", &map[i][j]);
			}
		}
		fclose(map_f2);
	}
}
void Exit_UI()
{
	system("cls");
	gotoxy(70, 13);
	printf("@@@@@@@@              @");
	gotoxy(70, 14);
	printf("@                @    @");
	gotoxy(70, 15);
	printf("@                   @@@@@");
	gotoxy(70, 16);
	printf("@@@@@@@@  @  @   @    @");
	gotoxy(70, 17);
	printf("@          @@    @    @");
	gotoxy(70, 18);
	printf("@          @@    @    @");
	gotoxy(70, 19);
	printf("@@@@@@@@  @  @   @    @");
	gotoxy(0, 40);
	printf(" ");
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
void print_UI(int have_item)
{
	i = 0;
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
	gotoxy(116, 8);
	printf("Item : ");
	while (i != H_ITEM_MAX)
	{
		i++;
		if (have_item != 0)
		{
			printf("¡á");
			have_item--;
		}
		else
			printf("¡à");
	}
}
void print_map(int cx, int cy)
{
	gotoxy(0, 0);
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			//if (Squre)
			if (Circle)
			{
				if (map[i][j] == '0')
					printf("  ");
				else if (map[i][j] == '1')
					printf("¡á");
				else if (map[i][j] == '2')
					printf("¿Ê");
				else if (map[i][j] == '3')
					printf("¨Æ");
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
						printf("¡á");
					else if (map[i][j] == '2')
						printf("¿Ê");
					else if (map[i][j] == '3')
						printf("¨Æ");
				}
				printf("\n");
			}
			Sleep(1500);
			(*have_item)--;
		}
	}
}
void check_clear(int *clear, int select_map)
{
	if (select_map == 0)
	{
		if (map[23][55] == '2')
			*clear = 0;
	}
	else if (select_map == 1)
	{
		if (map[6][56] == '2')
			*clear = 0;
	}
}
void print_clear()
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
			else if (map[i][j] == '3')
				printf("¨Æ");
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