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
#define Logo_MUSIC TEXT("logo.wav")
#define Map1_MUSIC TEXT("Map1.wav")
#define Map2_MUSIC TEXT("Map2.wav")
#define Map3_MUSIC TEXT("Map3.wav")
#define Map4_MUSIC TEXT("Map4.wav")
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
int time_limit;
char map[HIGH][WIDE];
//------------------------------------------------------------------------------------------------------------------------
void limit_time(void *i);
void play_MUSIC(int status);
int logo_UI(int *regame, int *sel_vi, int *sel_map);
void how_to_play();
void game_UI(int have_item, int select_map, int time);
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
	int select_menu = 0;
	int select_map = 0;
	int select_vision = 0;
	int regame = 1;

	while (regame)
	{
		select_map = 4;
		play_MUSIC(select_map);
		RemoveCursor();
		logo_UI(&regame, &select_vision, &select_map);
		system("cls");
		PlaySound(0, 0, 0);
		if (regame == 1)
		{
			play_MUSIC(select_map);
			scan_map(select_map);
			time_limit = 1;
			_beginthread(limit_time, 0, NULL);
			while (clear && time_limit != 0)
			{
				create_item(&item_count);
				search_character(&character_x, &character_y);
				game_UI(have_item, select_map, time_limit);
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
void play_MUSIC(int status)
{
	if (status == 4)
		PlaySound(Logo_MUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (status == 0)
		PlaySound(Map1_MUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (status == 1)
		PlaySound(Map2_MUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (status == 2)
		PlaySound(Map3_MUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (status == 3)
		PlaySound(Map4_MUSIC, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
int logo_UI(int *regame, int *sel_vi, int *sel_map)
{
	int status = 1;
	int select_menu = 0;
	int select_map = 0;
	int select_vision = 0;
	char key;

	gotoxy(38, 9);
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(38, 10);
	printf("弛       @   @                           @@@@@@@                                          弛");
	gotoxy(38, 11);
	printf("弛      @ @ @ @   @@@@     @@@@@   @@@@  @        @@@@@   @@@@@   @@@@     @@@@   @@@@    弛");
	gotoxy(38, 12);
	printf("弛     @   @  @  @    @       @   @    @ @       @       @       @    @    @   @ @    @   弛");
	gotoxy(38, 13);
	printf("弛    @       @ @     @      @    @@@@@@ @@@@@@@  @@@@  @       @     @    @   @ @@@@@@   弛");
	gotoxy(38, 14);
	printf("弛   @        @ @     @@    @     @      @            @  @      @     @@   @@@@  @        弛");
	gotoxy(38, 15);
	printf("弛  @         @  @@@@  @@  @@@@@   @@@@  @@@@@@@ @@@@@    @@@@@  @@@@  @@  @      @@@@    弛");
	gotoxy(38, 16);
	printf("弛                                                                         @              弛");
	gotoxy(38, 17);
	printf("弛                                                                         @              弛");
	gotoxy(38, 18);
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
	//詭檣 詭景
	while (status)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ENTER)
			{
				if (select_menu == 2)
				{
					*regame = 0;
					return 0;
				}
				else if (select_menu == 1)
					how_to_play();
				else if (select_menu == 0)
					status = 0;
			}
			else if (key == UP && select_menu > 0)
				select_menu -= 1;
			else if (key == DOWN && select_menu < 2)
				select_menu += 1;
		}
		if (select_menu == 0)
		{
			gotoxy(74, 22);
			printf("忙式式式式式式式忖");
			gotoxy(74, 23);
			printf("弛Ⅱ Start      弛");
			gotoxy(74, 24);
			printf("弛   How to play弛");
			gotoxy(74, 25);
			printf("弛   Exit       弛");
			gotoxy(74, 26);
			printf("戌式式式式式式式戎");

		}
		else if (select_menu == 1)
		{
			gotoxy(74, 22);
			printf("忙式式式式式式式忖");
			gotoxy(74, 23);
			printf("弛   Start      弛");
			gotoxy(74, 24);
			printf("弛Ⅱ How to play弛");
			gotoxy(74, 25);
			printf("弛   Exit       弛");
			gotoxy(74, 26);
			printf("戌式式式式式式式戎");
		}
		else if (select_menu == 2)
		{
			gotoxy(74, 22);
			printf("忙式式式式式式式忖");
			gotoxy(74, 23);
			printf("弛   Start      弛");
			gotoxy(74, 24);
			printf("弛   How to play弛");
			gotoxy(74, 25);
			printf("弛Ⅱ Exit       弛");
			gotoxy(74, 26);
			printf("戌式式式式式式式戎");
		}
	}
	status = 1;
	//裘 摹鷗ж晦
	while (status)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ENTER)
				status = 0;
			else if (key == UP && select_map > 0)
				select_map -= 1;
			else if (key == DOWN && select_map < 3)
				select_map += 1;
		}
		if (select_map == 0)
		{
			gotoxy(74, 22);
			printf("忙式式式式式忖            ");
			gotoxy(74, 23);
			printf("弛Ⅱ Map 1  弛                ");
			gotoxy(74, 24);
			printf("弛   Map 2  弛                ");
			gotoxy(74, 25);
			printf("弛   Map 3  弛                ");
			gotoxy(74, 26);
			printf("弛   Map 4  弛                ");
			gotoxy(74, 27);
			printf("戌式式式式式戎           ");

		}
		else if (select_map == 1)
		{
			gotoxy(74, 22);
			printf("忙式式式式式忖                ");
			gotoxy(74, 23);
			printf("弛   Map 1  弛                ");
			gotoxy(74, 24);
			printf("弛Ⅱ Map 2  弛                ");
			gotoxy(74, 25);
			printf("弛   Map 3  弛                ");
			gotoxy(74, 26);
			printf("弛   Map 4  弛                ");
			gotoxy(74, 27);
			printf("戌式式式式式戎                ");
		}
		else if (select_map == 2)
		{
			gotoxy(74, 22);
			printf("忙式式式式式忖                ");
			gotoxy(74, 23);
			printf("弛   Map 1  弛                ");
			gotoxy(74, 24);
			printf("弛   Map 2  弛                ");
			gotoxy(74, 25);
			printf("弛Ⅱ Map 3  弛                ");
			gotoxy(74, 26);
			printf("弛   Map 4  弛                ");
			gotoxy(74, 27);
			printf("戌式式式式式戎                ");
		}
		else if (select_map == 3)
		{
			gotoxy(74, 22);
			printf("忙式式式式式忖                ");
			gotoxy(74, 23);
			printf("弛   Map 1  弛                ");
			gotoxy(74, 24);
			printf("弛   Map 2  弛                ");
			gotoxy(74, 25);
			printf("弛   Map 3  弛                ");
			gotoxy(74, 26);
			printf("弛Ⅱ Map 4  弛                ");
			gotoxy(74, 27);
			printf("戌式式式式式戎                ");
		}
	}
	status = 1;
	gotoxy(74, 25);
	printf("                           ");
	gotoxy(74, 26);
	printf("                           ");
	gotoxy(74, 27);
	printf("                           ");
	//衛撿 賅曄 摹鷗ж晦
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
void how_to_play()
{
	system("cls");
	gotoxy(68, 15);
	printf(" 忙式式式式式式式式式式式式忖");
	gotoxy(68, 16);
	printf("  弛      How to play     弛");
	gotoxy(68, 17);
	printf(" 戌式式式式式式式式式式式式戎");
	gotoxy(64, 19);
	printf("忙式式式式式式式式式式式式式式式式式忖");
	gotoxy(64, 20);
	printf(" 弛                                弛");
	gotoxy(64, 21);
	printf(" 弛         ∟ : Turn UP           弛");
	gotoxy(64, 22);
	printf(" 弛         ∠ : Turn LEFT         弛");
	gotoxy(64, 23);
	printf(" 弛         ⊥ : Turn RIGHT        弛");
	gotoxy(64, 24);
	printf(" 弛         ⊿ : Turn DOWN         弛");
	gotoxy(64, 25);
	printf(" 弛        戌戎: Use item          弛");
	gotoxy(64, 26);
	printf(" 弛                                弛");
	gotoxy(64, 27);
	printf(" 弛    事 : After receiving the    弛");
	gotoxy(64, 28);
	printf(" 弛         item, show the map     弛");
	gotoxy(64, 29);
	printf(" 弛         for 1 second           弛");
	gotoxy(64, 30);
	printf(" 弛                                弛");
	gotoxy(64, 31);
	printf(" 弛     Escape within time limits  弛");
	gotoxy(64, 32);
	printf(" 弛                                弛");
	gotoxy(64, 33);
	printf("戌式式式式式式式式式式式式式式式式式戎");
	getch();
	system("cls");
}
void game_UI(int have_item, int select_map, int time)
{
	i = 0;

	gotoxy(115, 8);
	printf("忙式式式式式式式式式忖");
	gotoxy(115, 9);
	printf("弛ITEM : ");
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
	printf(" 弛");
	gotoxy(115, 10);
	printf("戍式式式式式成式式式戎");
	gotoxy(115, 11);
	printf("弛TIME : %3d弛", time_limit);
	gotoxy(115, 12);
	printf("戌式式式式式戎");
	gotoxy(115, 22);
	printf("忙式式式式忖");
	gotoxy(115, 23);
	printf("弛９ FINSH弛");
	gotoxy(115, 24);
	printf("戌式式式式戎");
}
void Exit_UI()
{
	system("cls");
	gotoxy(68, 12);
	printf("忙式式式式式式式式式式式式式式忖");
	gotoxy(68, 13);
	printf("弛 @@@@@@@@              @    弛");
	gotoxy(68, 14);
	printf("弛 @                @    @    弛");
	gotoxy(68, 15);
	printf("弛 @                   @@@@@  弛");
	gotoxy(68, 16);
	printf("弛 @@@@@@@@  @  @   @    @    弛");
	gotoxy(68, 17);
	printf("弛 @          @@    @    @    弛");
	gotoxy(68, 18);
	printf("弛 @          @@    @    @    弛");
	gotoxy(68, 19);
	printf("弛 @@@@@@@@  @  @   @    @    弛");
	gotoxy(68, 20);
	printf("戌式式式式式式式式式式式式式式戎");
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
	else if (select_map == 3)
	{
		FILE *map_f4 = fopen("MazeMap4.txt", "r");
		for (i = 0;i < HIGH;i++)
		{
			for (j = 0;j < WIDE;j++)
			{
				fscanf(map_f4, "%c", &map[i][j]);
			}
		}
		fclose(map_f4);
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

	gotoxy(60, 9);
	printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(60, 10);
	printf("弛   ######  ##                             弛");
	gotoxy(60, 11);
	printf("弛  #        ##                             弛");
	gotoxy(60, 12);
	printf("弛 #         ##   #####    ####    # ####   弛");
	gotoxy(60, 13);
	printf("弛 #         ##  #     #  #    #   ##    #  弛");
	gotoxy(60, 14);
	printf("弛 #         ##  ######  #     #   #        弛");
	gotoxy(60, 15);
	printf("弛  #        ##  #       #    #    #        弛");
	gotoxy(60, 16);
	printf("弛   ######  ##   #####   #### ##  #        弛");
	gotoxy(60, 17);
	printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
	Sleep(2000);
}
void print_fail()
{
	int status = 1;

	system("cls");

	gotoxy(73, 9);
	printf("忙式式式式式式式式式式式式式忖");
	gotoxy(73, 10);
	printf("弛 @@@@@@@            @  @  弛");
	gotoxy(73, 11);
	printf("弛 @                     @  弛");
	gotoxy(73, 12);
	printf("弛 @         @@@      @  @  弛");
	gotoxy(73, 13);
	printf("弛 @@@@@@@  @   @     @  @  弛");
	gotoxy(73, 14);
	printf("弛 @       @     @    @  @  弛");
	gotoxy(73, 15);
	printf("弛 @       @    @@    @  @  弛");
	gotoxy(73, 16);
	printf("弛 @        @@@@  @@  @  @  弛");
	gotoxy(73, 17);
	printf("戌式式式式式式式式式式式式式戎");
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
				printf("TIME :  %2d", time_limit);
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