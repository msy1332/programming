#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#define MAX 100
#define SP 100
#define _CRT_SECURE_WARNINGS
enum Ch{up=72,down=80,left=75,right=77,enter=32};
struct point
{
	int x;
	int y;
};
struct Snake
{
	struct point xy[100];
	int x;
	int y;
	int lenght;
	Ch ch;
}snake;
struct Food
{
	struct point xy;
	int x;
	int y;
	int flag;
	int eatscore=0;
}food;
void snakdie()
{
	initgraph(800,800);
	IMAGE beiji;
	loadimage(&beiji,"游戏结束.jpg");
	putimage(0,0,&beiji);
	while(1);
} 
void initsnake()
{
	srand((unsigned int)time(NULL));
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;
	snake.xy[1].x = 10;
	snake.xy[1].y = 0;
	snake.xy[0].x = 20;
	snake.xy[0].y = 0;
	food.flag = 0;
	snake.lenght=3;
	snake.ch = right;
}
void gamesnake() //创建窗口 
{
	initgraph(800,800);
	setbkcolor(WHITE); 
	cleardevice();
}
void drawsnake()
{
	for(int i=0;i<snake.lenght;i++){
		setlinecolor(WHITE); //设置蛇边缘的线条颜色
    	setfillcolor(RED);  //设置蛇身的颜色
        fillrectangle(snake.xy[i].x,snake.xy[i].y,snake.xy[i].x+10,snake.xy[i].y+10);
    }
}
void way()
{
	for (int i = snake.lenght-1; i >0; i--)
	{
		snake.xy[i].x = snake.xy[i-1].x;
		snake.xy[i].y = snake.xy[i-1].y;
	}
	switch(snake.ch)
	{
        case up:
            snake.xy[0].y-=10;
            break;
        case down:
            snake.xy[0].y+=10;
            break;
        case left:
            snake.xy[0].x-=10;
            break;
        case right:
            snake.xy[0].x+=10;
            break;
    }
}
void keysnake()
{
	char key=0;
	key=_getch();
	switch (key)
    {
    case right:
    	if(snake.ch!=left)
        snake.ch = right;        
        break;
    case left:
    	if(snake.ch!=right)
        snake.ch = left;        
        break;
    case down:
    	if(snake.ch!=up)
        snake.ch = down;    
        break;
    case up:
    	if(snake.ch!=down)
        snake.ch = up;
        break;
    default:
        break;
    }
}
void initFood(){
    food.xy.x=rand()%80*10;
    food.xy.y=rand()%80*10;
    food.flag=1;
}
void DrawFood(){
    setfillcolor(YELLOW);
    fillroundrect(food.xy.x,food.xy.y,food.xy.x+10,food.xy.y+10,10,10);
}
void EatFood(){
    if(snake.xy[0].x==food.xy.x&&snake.xy[0].y==food.xy.y){
        snake.lenght++;
        food.flag=0;
        food.eatscore+=10;
    }
}
int snakeDie()
{
	if(snake.xy[0].x>800||snake.xy[0].x<0||snake.xy[0].y>800||snake.xy[0].y<0)
	{
		snakdie();
		return 1;
	}
	for(int i=1;i<snake.lenght;i++)
	{
		if(snake.xy[0].x==snake.xy[i].x&&snake.xy[0].y==snake.xy[i].y)
		{
			snakdie();
			return 1;
		}
	}
	return 0;
} 
int main()
{
	gamesnake();
	initsnake();
	while(1)
	{
		drawsnake();
		if(snakeDie())
		{
			break;
		}
		if(food.flag==0)
		{	
			initFood();
		}	
		EatFood();	
		DrawFood();
		way();
		while(_kbhit())
		{
			keysnake();
		}		
		Sleep(100);
		cleardevice();
		} 
		getch();
		closegraph(); 
	return 0;
}
