//------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
//------------------------------------------------------------------------------------------------------------------------
#define playMUSIC TEXT("play.wav")
#define logoMUSIC TEXT("logo.wav")
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
int time_limit = 60;
char map[HIGH][WIDE];
//------------------------------------------------------------------------------------------------------------------------
void limit_time(void *i);
void logo_MUSIC();
void play_MUSIC();
int Logo_UI(int *regame,int *sel_vi, int *sel_map);
void print_UI(int have_item, int select_map,int time);
void Exit_UI();
void scan_map(int select_map);
void print_map(int cx, int cy, int sel_vi);
void print_clear();
void print_fail();
void search_character(int *x, int*y);
void check_clear(int *clear);
void character_function(int cx, int cy, int *have_item, int *item_count);
void create_item(int *item_count);
void RemoveCursor();
void gotoxy(int x, int y);
//------------------------------------------------------------------------------------------------------------------------
int main()
{
	system("title MazeEscape");
	system("mode con:cols=190 lines=45");

	int item_count = 0;
	int have_item = 0;
	int clear = 1;
	int character_y;
	int character_x;
	int select_map = 0;
	int select_vision = 0;
	int regame = 1;

	while (regame)
	{
		logo_MUSIC();
		RemoveCursor();
		Logo_UI(&regame,&select_vision,&select_map);
		system("cls");
		PlaySound(0, 0, 0);
		if (regame == 1)
		{
			play_MUSIC();
			scan_map(select_map);
			time_limit = 60;
			_beginthread(limit_time, 0, NULL);
			while (clear && time_limit != 0)
			{
				create_item(&item_count);
				search_character(&character_x, &character_y);
				print_UI(have_item, select_map, time_limit);
				print_map(character_x, character_y, select_vision);
				check_clear(&clear);
				character_function(character_x, character_y, &have_item, &item_count);
			}
			if (time_limit != 0)
				print_clear();
			else
				print_fail();
			PlaySound(0, 0, 0);
			clear = 1;
			item_count = 0;
		}
	}
	Exit_UI();
}
//------------------------------------------------------------------------------------------------------------------------
void limit_time(void *i)
{
	while (time_limit != 0)
	{
		time_limit--;
		Sleep(1000);
	}
}
void logo_MUSIC()
{
	PlaySound(logoMUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void play_MUSIC()
{
	PlaySound(playMUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
int Logo_UI(int *regame, int *sel_vi, int *sel_map)
{
	int status = 1;
	int select_map = 0;
	int select_vision = 0;
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
	
	while (status)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ENTER)
			{
				if (select_map == 3)
				{
					*regame = 0;
					return 0;
				}
				status = 0;
			}
			else if (key == UP)
			{
				if (select_map > 0)
					select_map -= 1;
			}
			else if (key == DOWN)
			{
				if (select_map < 3)
					select_map += 1;
			}
		}
		if (select_map == 0)
		{
			gotoxy(74, 22);
			printf("忙式式式式忖");
			gotoxy(74, 23);
			printf("弛Ⅱ Easy 弛");
			gotoxy(74, 24);
			printf("弛   Nomal弛");
			gotoxy(74, 25);
			printf("弛   Hard 弛");
			gotoxy(74, 26);
			printf("弛   Exit 弛");
			gotoxy(74, 27);
			printf("戌式式式式戎");

		}
		else if (select_map == 1)
		{
			gotoxy(74, 22);
			printf("忙式式式式忖");
			gotoxy(74, 23);
			printf("弛   Easy 弛");
			gotoxy(74, 24);
			printf("弛Ⅱ Nomal弛");
			gotoxy(74, 25);
			printf("弛   Hard 弛");
			gotoxy(74, 26);
			printf("弛   Exit 弛");
			gotoxy(74, 27);
			printf("戌式式式式戎");
		}
		else if (select_map == 2)
		{
			gotoxy(74, 22);
			printf("忙式式式式忖");
			gotoxy(74, 23);
			printf("弛   Easy 弛");
			gotoxy(74, 24);
			printf("弛   Nomal弛");
			gotoxy(74, 25);
			printf("弛Ⅱ Hard 弛");
			gotoxy(74, 26);
			printf("弛   Exit 弛");
			gotoxy(74, 27);
			printf("戌式式式式戎");
		}
		else if (select_map == 3)
		{
			gotoxy(74, 22);
			printf("忙式式式式忖");
			gotoxy(74, 23);
			printf("弛   Easy 弛");
			gotoxy(74, 24);
			printf("弛   Nomal弛");
			gotoxy(74, 25);
			printf("弛   Hard 弛");
			gotoxy(74, 26);
			printf("弛Ⅱ Exit 弛");
			gotoxy(74, 27);
			printf("戌式式式式戎");
		}
	}
	status = 1;
	gotoxy(74, 25);
	printf("           ");
	gotoxy(74, 26);
	printf("           ");
	gotoxy(74, 27);
	printf("           ");
	while (status)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ENTER)
				status = 0;
			else if (key == UP)
				select_vision = 0;
			else if (key == DOWN)
				select_vision = 1;
		}
		if (select_vision == 0)
		{
			gotoxy(74, 22);
			printf("忙式式式式式忖");
			gotoxy(74, 23);
			printf("弛Ⅱ Squre  弛");
			gotoxy(74, 24);
			printf("弛   Circle 弛");
			gotoxy(74, 25);
			printf("戌式式式式式戎");

		}
		else if (select_vision == 1)
		{
			gotoxy(74, 22);
			printf("忙式式式式式忖");
			gotoxy(74, 23);
			printf("弛   Squre  弛");
			gotoxy(74, 24);
			printf("弛Ⅱ Circle 弛");
			gotoxy(74, 25);
			printf("戌式式式式式戎");
		}
	}
	system("cls");
	*sel_vi = select_vision;
	*sel_map = select_map;
}
void print_UI(int have_item, int select_map,int time)
{
	i = 0;
	gotoxy(116, 2);
	printf("How to play");
	gotoxy(116, 3);
	printf("∟ : Turn UP");
	gotoxy(116, 4);
	printf("∠ : Turn LEFT");
	gotoxy(116, 5);
	printf("⊥ : Turn RIGHT");
	gotoxy(116, 6);
	printf("⊿ : Turn DOWN");
	gotoxy(116, 7);
	printf("Space : Use Item");
	gotoxy(116, 10);
	printf("Item : ");
	while (i != H_ITEM_MAX)
	{
		i++;
		if (have_item != 0)
		{
			printf("﹥");
			have_item--;
		}
		else
			printf("﹤");
	}
	gotoxy(114, 23);
	printf("９ FINSH");
	gotoxy(116, 11);
	printf("TIME : %2d", time_limit);
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
	else if (select_map == 2)
	{
		FILE *map_f3 = fopen("MazeMap3.txt", "r");
		for (i = 0;i < HIGH;i++)
		{
			for (j = 0;j < WIDE;j++)
			{
				fscanf(map_f3, "%c", &map[i][j]);
			}
		}
		fclose(map_f3);
	}
}
void print_map(int cx, int cy, int sel_vi)
{
	gotoxy(0, 0);
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			if (sel_vi == 0)
			{
				if (Squre)
				{
					if (map[i][j] == '0')
						printf("  ");
					else if (map[i][j] == '1')
						printf("﹥");
					else if (map[i][j] == '2')
						printf("褡");
					else if (map[i][j] == '3')
						printf("事");
				}
				else
					printf("  ");
			}
			else if (sel_vi == 1)
			{
				if (Circle)
				{
					if (map[i][j] == '0')
						printf("  ");
					else if (map[i][j] == '1')
						printf("﹥");
					else if (map[i][j] == '2')
						printf("褡");
					else if (map[i][j] == '3')
						printf("事");
				}
				else
					printf("  ");
			}
		}
		printf("\n");
	}
}
void print_clear()
{
	int status = 1;
	time_limit = 1000;

	gotoxy(0, 0);
	for (i = 0;i < HIGH;i++)
	{
		for (j = 0;j < WIDE;j++)
		{
			if (map[i][j] == '0')
				printf("  ");
			else if (map[i][j] == '1')
				printf("﹥");
			else if (map[i][j] == '2')
				printf("褡");
			else if (map[i][j] == '3')
				printf("事");
			Sleep(1);
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
	Sleep(2000);
}
void print_fail()
{
	int status = 1;

	system("cls");

	gotoxy(75, 10);
	printf("@@@@@@@            @  @");
	gotoxy(75, 11);
	printf("@                     @");
	gotoxy(75, 12);
	printf("@         @@@      @  @");
	gotoxy(75, 13);
	printf("@@@@@@@  @   @     @  @");
	gotoxy(75, 14);
	printf("@       @     @    @  @");
	gotoxy(75, 15);
	printf("@       @    @@    @  @");
	gotoxy(75, 16);
	printf("@        @@@@  @@  @  @");
	Sleep(2000);
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
			*clear = 0;
}
void character_function(int cx, int cy, int *have_item, int *item_count)
{
	char key;

	if (kbhit())
	{
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
							printf("﹥");
						else if (map[i][j] == '2')
							printf("褡");
						else if (map[i][j] == '3')
							printf("事");
					}
					printf("\n");
				}
				gotoxy(116, 11);
				printf("TIME : %2d", time_limit);
				Sleep(1500);
				(*have_item)--;
			}
		}
	}
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
//------------------------------------------------------------------------------------------------------------------------