#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define N 20
#define M 20
#define TRUE 1
#define FALSE -1

typedef int BOOL;

void intro(void);//引导界面
void init_carte(void); //初始化卡
void display_card(void);//显示卡
BOOL move_character(int [][M],int [][1]);//角色移动

struct pos {
	int x;//行坐标
	int y;//列坐标
	int health;//生命
	int gold;//钱
	int key;//钥匙
	int LX;
	int RX;
	int LY;
	int RY;
	int FLAGMOVEMENT;//坐标变动
	int YN;//FLAG
};
int map[N][M];//地图
int x[1][1];//角色
struct pos player;//角色

int main(void)
{
	
	intro();
	init_carte();
	display_card();
	while (move_character(map,x) != FALSE)
	{
		display_card();
		if (move_character(map, x) == 9)
			init_carte();
		display_card();

	}
	exit(0);
}

void init_carte(void)
{
	srand((unsigned int)time(0));//初始化种子
	player = {
		0,
		0,
		10,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};//初始化
	for (int n = 0;n< 20;n++)//随机初始化地图
	{
		for (int m = 0;m < 20;m++)
		{
			map[n][m] = rand()%10;
			if (map[n][m] == 5)
				map[n][m] = 0;
		}
	}
	for (int i = 0;i < 15;i++)//随机设置15个金币
	{
		map[rand() % 20][rand() % 20] = 5;
	}
	
	return;
}

void intro(void)
{
	printf("\n\n\n\n\n\t\t\t\t\tWelcome\n\t\t\t\tPress Enter to start game\n\n\n\t\t\t\t0 : grass 草\n\t\t\t\t1 : a flower 一朵花\n\t\t\t\t2 : an obstacle : a tree 障碍物：树\n\t\t\t\t3 : an obstacle : a rock 障碍物：岩石\n\t\t\t\t4 : an object : a key 一个物品：一把钥匙\n\t\t\t\t5 : an object : a gold coin 一个物品：金币\n\t\t\t\t6 : an object : a padlock 一个物品：挂锁\n\t\t\t\t7 : a trap 一个陷阱\n\t\t\t\t8 : a monster 一个怪物\n\t\t\t\t9 : a Treasure chest 一个宝箱");
	_getch();
}
void display_card(void)
{
	system("cls");
	printf("Press 0 to exit.\nPress R to Retry.\n2=down 4=left 6=right 8=up\nDO NOT REACH THE EDGE!\n\n");
	printf("Health:%d\tGold:%d\tKey:%d\n", player.health, player.gold,player.key);
	
	for (int n = 0;n < 20;n++)//z 输出20*20方阵
	{
		for (int m = 0;m < 20;m++)
		{
			if (n == player.x && m == player.y)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED);
				map[n][m] = 'X';
				printf(" %c ", map[n][m]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
			printf(" %d ", map[n][m]);	
		
		}
		printf("\n");
	}
	
	return;
}

BOOL move_character(int[][M], int[][1])
{
	char movement;
	movement = _getch();
	if (movement == 'R'|| movement == 'r' )
		return 9;
	map[player.x][player.y] = 0;
	switch (movement)//移动
	{
	case'8':player.x -= 1;player.LX = 1;player.FLAGMOVEMENT = 1;break;
	case'2':player.x += 1;player.RX =-1;player.FLAGMOVEMENT = 2;break;
	case'6':player.y += 1;player.RY =-1;player.FLAGMOVEMENT = 3;break;
	case'4':player.y -= 1;player.LY = 1;player.FLAGMOVEMENT = 4;break;
	case'0':return FALSE;
	default:break;
	}
	switch (map[player.x][player.y])//地图反馈
	{
	case 0:
	case 1:break;
	case 2:
	case 3:MessageBoxA(NULL, "Can't get through", "Blocked", MB_OK);player.YN = 1;break;
	case 4:MessageBoxA(NULL, "You got a key! Maybe it can unlock somthing?", "Suprise", MB_OK);player.key += 1;break;
	case 6:MessageBoxA(NULL, "A lock!OMG.", "Suprise", MB_OK);player.YN = 2;break;
	case 5:MessageBoxA(NULL, "You got a gold coin!", "Treasure!", MB_OK);player.gold += 1;break;
	case 7:
	case 8:MessageBoxA(NULL,"Ouch!","",MB_OK);player.health -= 1;break;
	case 9:MessageBoxA(NULL, "Some gold coins!", "Treasure!", MB_OK);srand((unsigned int)time(0));player.gold += (rand() % 2)+1;break;
	default:break;
	}
	if (player.x < 0 || player.x >= 20)//判断是否结束
	{
		MessageBoxA(NULL, "You lose cause you fall into the abyss", "Lose", MB_OK);
		return FALSE;
	}if (player.y < 0 || player.y >= 20)
	{
		MessageBoxA(NULL, "You lose cause you fall into the abyss", "Lose", MB_OK);
		return FALSE;
	}
	if (player.health <= 0) {
		MessageBoxA(NULL, "You lose cause you run out of your health", "Lose", MB_OK);
		return FALSE;
	}
	if (player.gold >= 10)
	{
		MessageBoxA(NULL, "You win!Congratulations!", "WIN!", MB_OK);
		return FALSE;
	}
	//判断活动
	if (player.YN == 1)
	{
		if (player.FLAGMOVEMENT == 1)
			player.x += player.LX;
		if (player.FLAGMOVEMENT == 2)
			player.x += player.RX;
		if (player.FLAGMOVEMENT == 3)
			player.y += player.RY;
		if (player.FLAGMOVEMENT == 4)
			player.y += player.LY;
		player.YN = 0;
	}
	if (player.YN == 2)
	{
		if (player.key > 0)
		{
			MessageBoxA(NULL, "You got the key! And you got this lock!", "Unlock!", MB_OK);
			player.key -= 1;

		}
		else
		{
			MessageBoxA(NULL, "Nooooooo,You dont have the key", "Locked", MB_OK);
				if (player.FLAGMOVEMENT == 1)
					player.x += player.LX;
				if (player.FLAGMOVEMENT == 2)
					player.x += player.RX;
				if (player.FLAGMOVEMENT == 3)
					player.y += player.RY;
				if (player.FLAGMOVEMENT == 4)
					player.y += player.LY;
		}
		player.YN = 0;

	}

	return TRUE;
}