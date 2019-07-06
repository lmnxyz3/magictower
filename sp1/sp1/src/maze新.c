#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define row 25
#define col 50
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
void check(void);//防止产生多条可行的路 
int yourmove(void);	//实现自己操控 
void printone(int color);//擦除以及打印路径 
void printtime(void);//输出时间 
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
	x=rand()%(row-4)+2;
	y=rand()%(col-4)+2;
	make(x,y);
	map[1][0]=map[row-2][col-1]=map[1][1]=map[row-2][col-2]=1;
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
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|FOREGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_RED);
	puts("                   输入上下左右移动，按空格自动导路,自动寻路时输入1到9调整移速                      ");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(5,2*col+1);
	printf("不识庐山真面目");
	gotoxy(7,2*col+2);
	printf("只缘身在此山中");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_GREEN);
gotoxy(9,2*col+1);
printf("■未探索");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED);
gotoxy(11,2*col+1);
printf("■已探索且为");
gotoxy(12,2*col+1);
printf("有效路径");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_GREEN|FOREGROUND_BLUE);
gotoxy(14,2*col+1);
printf("■已探索");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); 
gotoxy(16,2*col+1);
printf("■墙");
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
	printtime();
}
void printtime(void){
	gotoxy(row+1,0);
	end=clock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED | FOREGROUND_GREEN);
	printf("time:%d   \n",(end-begin)/ CLOCKS_PER_SEC);
}
void start(void){//初始化map数组的值全为0，后调用make函数将某些值改为1，即形成路 
	int i,j;yourx=1;youry=0;flag=0;win=0;
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
	static speed=1;
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
	check();
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
		if(x2>row-1||y2>col-1||x2<0||y2<0||map[x1][y1]==1){//防止越界 
			continue;
		}
		if(map[x3][y3]==1||map[2*x1-x3][2*y1-y3]==1||map[x2][y2]==1){//防止田字型路段 
			wall[x1][y1]=1;
		} 
		if(wall[x1][y1]==1)continue;
		if(map[x2][y2]==0){
			make(x1,y1);
		}
	}
}
void check(void){ //保证周围已经有三格路的墙不被拆 
	int i,j,t,count;
	int next[4][2];
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			count=0;
			for(t=0;t<4;t++){
				next[t][0]=i+onemove[t][0];next[t][1]=j+onemove[t][1];
				if(map[next[t][0]][next[t][1]])count++;
			}
			if(count==3){
				for(t=0;t<4;t++)if(map[next[t][0]][next[t][1]]==0)wall[next[t][0]][next[t][1]]=1;
			}
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
