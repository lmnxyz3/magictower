#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define row 10
#define col 10
int yourx=1,youry=0;//自己操控点的坐标 
int map[row][col];//地图 
int wall[row][col];//记录不能拆的墙 
int road[row][col];//存放已走过的路 
int onemove[4][2]={1,0,0,1,-1,0,0,-1};
int begin,end;/*两个时间参数*/
int flag,win;
void start(void);//初始化函数 
void print(void);//打印函数 
int move(int m,int n);//自动寻路函数 
void make(int x,int y);//制造迷宫 
int yourmove(void);	//实现自己操控 
void printone(int color);//擦除以及打印路径 
HANDLE hout;//以下为高级操作，原理不明 
void gotoxy(unsigned char x, unsigned char y)//通过此函数可实现光标移动，进而局部刷新 
{
    COORD cor;
    cor.X = y;
    cor.Y = x;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, cor);
}
int main(void){
	int x,y;
	char c;
	srand(time(0));
	while(1){
	start();
	x=7+(rand()%4)/2;
	y=4+(rand()%3)/2;
	make(x,y);
	map[7][4]=map[8][3]=map[8][5]=1;
	print();
	while(yourmove());
	if(win)goto ab;
	begin=clock();
	if(move(yourx,youry));
	else {
		gotoxy(row+1,16);
		puts("no way");
	}
	ab: gotoxy(row+2,0);
	puts("\a输入0退出，输入其它则再来一个");
	c=getch();
	if(c==48)return 0;
	}	
	return 0;
}
void print(void){
	system("cls");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if(map[i][j]==1){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|FOREGROUND_INTENSITY|BACKGROUND_GREEN|FOREGROUND_RED);
				printf("  ");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED|FOREGROUND_GREEN |FOREGROUND_BLUE);
			}
			else if(map[i][j]==0){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|FOREGROUND_INTENSITY|BACKGROUND_GREEN|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			printf("■");
			}
		}
		printf("\n");
	}

} 
void printone(int color){//打印对应颜色方块 
	if(color==1){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|FOREGROUND_INTENSITY|BACKGROUND_RED);
	printf("  ");
	}
	else{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN);
		printf("  ");
	}
}

void start(void){//初始化map数组的值全为0，后调用make函数将某些值改为1，即形成路 
	int i,j;yourx=7;youry=4;flag=0;win=0;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			road[i][j]=wall[i][j]=map[i][j]=0;
		}
	}
	//光标隐藏 
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
	hout= GetStdHandle(STD_OUTPUT_HANDLE);  // 获取控制台输出句柄
    SetConsoleCursorInfo(hout, &cursorInfo);  // 设置光标隐藏
}
int move(int m,int n){
	int i,p=1;
	static int speed=1;
	int stoptime1=250,stoptime2=100;
	if(kbhit()){
		p=getch();
		if(p>48&&p<58)speed=p-48;
	}
	gotoxy(2,2*col+1);
	printf("当前移速%d",speed);
	stoptime1=270-speed*22;stoptime2=110-10*speed;
	if(m==row-2&&n==col-1){
		gotoxy(m+1,2*n);
		printone(1);
		return 1;
	}
	for(i=1;i<=4;i++){
		//down
		if(i==1){
			if(map[m+1][n]!=0&&road[m+1][n]!=1&&road[m+1][n]!=2){
				road[m][n]=1;
				gotoxy(m+1,2*n);
				printone(1);
				Sleep(stoptime1);
				if(move(m+1,n))return 1;
			}
		}
		//right
		if(i==2){
			if(map[m][n+1]!=0&&road[m][n+1]!=1&&road[m][n+1]!=2){
				road[m][n]=1;
				gotoxy(m+1,2*n);
				printone(1);
				Sleep(stoptime1);
				if(move(m,n+1))return 1;
			}
		}
		//left
		if(i==3){
			if(map[m][n-1]!=0&&road[m][n-1]!=1&&road[m][n-1]!=2){
				road[m][n]=1;
				gotoxy(m+1,2*n);
				printone(1);
				Sleep(stoptime1);
				if(move(m,n-1))return 1;
			}
		}
		//up
		if(i==4){
			if(map[m-1][n]!=0&&road[m-1][n]!=1&&road[m-1][n]!=2){
				road[m][n]=1;
				gotoxy(m+1,2*n);
				printone(1);
				Sleep(stoptime1);
				if(move(m-1,n))return 1;
			}
		}
	}
	gotoxy(m+1,2*n);
	printone(0);
	Sleep(stoptime2);
	return 0;
}
void make(int x,int y){
	map[x][y]=1;
	int i;
	int dir;
	int x1,y1,x2,y2,x3,y3;
	int all[4]={0,0,0,0};
	int turn=rand()%2*2+1;
	dir=rand()%4;
	for(i=0;i<4;i++){
		dir=(dir+turn)%4;
		x1=x+onemove[dir][0];//向当前方向前进 1格 
		y1=y+onemove[dir][1]; 
		x2=x+2*onemove[dir][0];//向当前方向前进 2格 
		y2=y+2*onemove[dir][1];
		x3=x1+onemove[(dir+1)%4][0];//垂直方向 
		y3=y1+onemove[(dir+1)%4][1];
		
		if(x2>row-1||y2>col-1||x2<0||y2<0){//防止越界 
			continue;
		}
		if(map[x3][y3]==1||map[2*x1-x3][2*y1-y3]==1){//防止田字型路段 
			wall[x1][y1]=1;
		}
		if(wall[x1][y1]==1)continue;
		if(map[x2][y2]==0){
			make(x1,y1);
		}
	}
}

int yourmove(void){
	char cc;
	gotoxy(yourx+1,2*youry);
	printone(1);
	if(yourx==row-2&&youry==col-1){
		win=1;return 0;
	}
	cc=getch();
	if(flag==0)begin=clock();flag=1;
	switch(cc){
		/*up*/case 72:if(map[yourx-1][youry]){
			gotoxy(yourx+1,2*youry);
			printone(0);
			yourx-=1;
		}break;
		/*down*/case 80:if(map[yourx+1][youry]){
			gotoxy(yourx+1,2*youry);
			printone(0);
			yourx+=1;
		}break;
		/*left*/case 75:if(map[yourx][youry-1]){
			gotoxy(yourx+1,2*youry);
			printone(0);
			youry-=1;
		}break;
		/*right*/case 77:if(map[yourx][youry+1]){
			gotoxy(yourx+1,2*youry);
			printone(0);
			youry+=1;
		}break;
		case 32:return 0;
	}
	return 1;
}
