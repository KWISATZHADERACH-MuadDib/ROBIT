#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mtg.h"

#define MY_W    	10 + 2  //width
#define MY_H    	20 + 2  //height
#define MY_WALL 	0
#define MY_BLANK    1
#define MY_BLOCK    2
#define MY_PATSIZE  7       //pattern size

#define MY_LEFT     75
#define MY_RIGHT    77
#define MY_UP       72
#define MY_DOWN      80
#define MY_SPACE    32

int point = 0;

typedef struct
{
	int x;
	int y;
}POS;

int g_data[MY_H][MY_W];
POS g_type[MY_PATSIZE][4][4] = { //[블록] [방향] [모양(x,y)]
	{
		{0,0,1,0,2,0,3,0}, // pos strunr {int x, int y}
		{0,0,0,1,0,2,0,3},
		{0,0,1,0,2,0,3,0},
		{0,0,0,1,0,2,0,3}
	},
	{
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1}, // ㅁ
		{0,0,1,0,0,1,1,1}
	},
	{
		{0,0,1,0,1,1,2,1},
		{1,0,0,1,1,1,0,2},
		{0,0,1,0,1,1,2,1},
		{1,0,0,1,1,1,0,2}
	},
	{
		{1,0,2,0,0,1,1,1},
		{0,0,0,1,1,1,1,2},
		{1,0,2,0,0,1,1,1},
		{0,0,0,1,1,1,1,2}
	},
	{
		{0,0,1,0,2,0,1,1}, //t
		{1,0,0,1,1,1,1,2},
		{1,0,0,1,1,1,2,1},
		{0,0,0,1,1,1,0,2}
	},
	{
		{0,0,0,1,1,1,2,1},
		{0,0,1,0,0,1,0,2},
		{0,0,1,0,2,0,2,1},
		{1,0,1,1,0,2,1,2}
	},
	{
		{2,0,0,1,1,1,2,1},
		{0,0,0,1,0,2,1,2},
		{0,0,1,0,2,0,0,1},
		{0,0,1,0,1,1,1,2}
	}
};
int g_dir = 0;
int g_patindex = 0;
POS g_pos = {1,1};  // 자료형: POS 블럭의 위치
int g_score = 0;
int time_cnt = 100;  //시간재한

int Check_block(int dx, int dy, int dir); //dx, dy: 다음 블럭의 위치 , dir:블럭의 방향
int Move_block();
void Copy_block();
void Get_newblock();
void Check_sameblock();
void Move_end();
int Timer_check();
void Data_init();
void Draw_map();
void Game_Run();
int Run_Key();
void Draw();
void Draw_block();
void Draw_info();
void Game_init();
void Down_block(int y);


int Check_block(int dx, int dy, int dir) // 블럭이 갈수 있는지 없는지 체크
{
	int x, y;
	int i;
							// 블럭의 기준은 왼쪽 위
	for(i = 0; i < 4; i++) // 하나의 블럭이 4개로 이루어져있기 때문
	{
		x = dx + g_type[g_patindex][dir][i].x; // g_tye 는 POS struct
		y = dy + g_type[g_patindex][dir][i].y;

		if(MY_BLANK != g_data[y][x])
		{
			return -1;
		}
	}
	return 0;
}

int Move_block()
{
	if(0 == Check_block(g_pos.x, g_pos.y+1, g_dir)) // 블럭이 움직일수 있다면
	{
		g_pos.y++;
		return 0;
	}
	return -1; // 블럭이 움직일수 없다면
}

void Copy_block() // 맵의 일부로 만듬
{
	int x, y;
	int i;

	for(i = 0; i < 4; i++)
	{
		x = g_pos.x + g_type[g_patindex][g_dir][i].x;// 4개의 블럭의 좌표가 들어감
		y = g_pos.y + g_type[g_patindex][g_dir][i].y;

		g_data[y][x] = MY_BLOCK;
	}
}

void Get_newblock() // 새로운 블럭을 만듬
{
	srand(time(NULL));
	g_pos.x = 1+rand() % (MY_W-5);
	g_pos.y = 1;
	g_dir = rand()%4;
	g_patindex = rand() % MY_PATSIZE;

	printf("%d", g_dir);
}

void Move_end() //spacebar를 누르면 끝까지 내려감 즉시 고정
{
	while(1)
	{
		if(-1 == Move_block())
		{
			Copy_block();
			Check_sameblock();
			Get_newblock();

			break;
		}
	}
}

int Timer_check()
{
	static long oldT=0; // static 이 붙으면 다시 호출할때 값이 남아있음
	long newT; // long = 변수형 정수
	static int timer_stop = 0; //게임을 종료하고 아무일도 안생기게 하기위함

	if(-1 == timer_stop)
	{
		return 1;
	}

	newT = GetTickCount(); // 밀리초 1000밀리초 = 1초

	if(500 > abs(newT-oldT)) // abs = absolute(절대값)
	{
		return 1;
	}
	else
	{
		oldT=newT;
	}
	if(-1 == Move_block())
	{
		Copy_block();
		Check_sameblock();
		Get_newblock();

		if(-1 == Move_block())
		{
			_Invalidate();
			timer_stop=-1;
			_MessageBox(40,15,20,5,"Game Over!");
			return 0;
		}
	}
	_Invalidate();
}

int Check_time()
{
	static long oldtime;
	static long newtime;

	newtime = _GetTickCount();

	if(abs(newtime - oldtime) >= 1000)
	{
		oldtime = newtime;
		time_cnt--;
		if(time_cnt < 0)
		{
			return 0;
		}
	}
	return 1;
}
void Display_time()
{
	char time_temp[80];

	sprintf(time_temp, "time:%d", time_cnt);
	_DrawText(32, 16, time_temp);
}

void Data_init()
{
	int x, y;

	for(y = 0; y<MY_H; y++)
	{
		for(x = 0; x < MY_W; x++)
		{
			if(0 == x|| 0 == y || (x+1) == MY_W || (y+1) == MY_H)
			{
				g_data[y][x] = MY_WALL;
			}
			else
			{
				g_data[y][x]= MY_BLANK;
			}
		}
	}
}

void Draw_map()
{
	int x, y;

	for(y = 0; y < MY_H; y++)
	{
		for(x = 0; x < MY_W; x++)
		{
			if(MY_WALL == g_data[y][x])
			{
				_DrawText(x*2, y, " □ ");
			}
			else if(MY_BLANK == g_data[y][x])
			{
				_DrawText(x*2, y, ".");
			}
			else
			{
				_DrawText(x*2, y, " ■ ");
			}
		}
	}
}

void Draw_block()
{
	int x, y, i;

	for(i = 0; i < 4; i++)
	{
		x = g_pos.x + g_type[g_patindex][g_dir][i].x;
		y = g_pos.y + g_type[g_patindex][g_dir][i].y;
		_DrawText(x*2, y,"■  ");
	}
}

void Draw_info()
{
	_DrawText(32, 10, "Tetris ver 0.1"); // 이름, 버젼
	_DrawText(32, 11, "q : exit/ left, right : move/ up, down: rotation");
}

void Display_score()
{
	char score_temp[80];

	sprintf(score_temp, "Score:%d", g_score);
	_DrawText(32, 14, score_temp);
}

void Draw()
{
	Draw_map();
	Draw_block();
	Draw_info();
	Display_score();
	Display_time();
}

void Game_init()
{
	Data_init();
	_Invalidate();
}

int Run_Key()
{
	char k;

	k=_GetKey();

	if(-1==k)
	{
		return 0;
	}
	if('q'==k)
	{
		return -1;
	}
	if(MY_LEFT == k)
	{
		if(0 == Check_block(g_pos.x-1, g_pos.y, g_dir))
		{
			g_pos.x--;
		}
	}
	else if(MY_RIGHT == k)
	{
		if(0 == Check_block(g_pos.x+1, g_pos.y, g_dir))
		{
			g_pos.x++;
		}
	}
	else if(MY_SPACE == k)
	{
		Move_end();
	}
	else if(MY_UP == k)
	{
		int dir = g_dir;

		dir ++;
		if(3 < dir)
		{
			dir = 0;
		}
		if(0 == Check_block(g_pos.x, g_pos.y, dir))
		{
			g_dir = dir;

			_Invalidate();
		}
	}
	else if(MY_DOWN == k)
	{
  		int dir = g_dir;

		dir--;
		if(dir<0)
		{
			dir = 3;
		}
		if(0 == Check_block(g_pos.x, g_pos.y, dir))
		{
			g_dir = dir;

			_Invalidate();
		}
	}
	else
	{

	}

	_Invalidate();

	return 0;
}

void Check_sameblock()
{
	int x, y;


	for(y = MY_H-2; 0 < y; y--) // MY_H -1까지는 벽이기 떄문(공백이 생길수 있는 가장 아랫줄)
	{
		int same=0;
		for(x = 1; x < MY_W -1; x++)
		{
			if(MY_BLOCK != g_data[y][x])
			{
				same = -1;
				break;
			}
		}
		if(0 == same)
		{
			Down_block(y);
			g_score += 100;
			y++;
		}
	}


}

void Down_block(int y)
{
	int x;

	for( ; 1 <= y; y--)
	{
		for(x = 1; x < MY_W -1; x++)
		{
			if(1==y)
			{
				g_data[y][x] = MY_BLANK;
			}
			else
			{
				g_data[y][x] = g_data[y-1][x];
			}
		}
	}
}

void Game_Run()
{
	Game_init();
	while(1)
	{
		Timer_check();

 		_Invalidate();

		if(Check_time() == 0)
		{
			_MessageBox(50, 15, 40, 5, "Time Out!");
			break;
		}

		if(-1 == Run_Key())
		{
			break;
		}
		if(Timer_check() == 0)
			break;
	}
}

int main()
{
	_BeginWindow();
	Game_Run();
	//_EndWindow();

	return 0;
}
