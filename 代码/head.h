//o-直接胜利 p-直接死亡 c-存档  空格-帮助
#include"stdafx.h"
#include <graphics.h>
#include <string.h>
#include <stdio.h>
#define man 100        //主角
#define oldman 101      //老人
#define shopman 102      //商人
#define myfriend 103        //小偷（朋友）
#define shopman1 104   //两个辅助商人(当一层多个商人时用)
#define shopman2 105
#define myfriend_end 106  //打工这方面，打工是不可能打工的..
#define oldman_end 107      //想救公主，必须打败魔王
//想当年，我雄姿英发...叹如今，廉颇老矣，不能饭了..
#define shopman_end 108     //江南皮革厂倒闭啦，原价200多的钱包，现在统统20块..
//我从来没碰过钱，我对钱没有兴趣
#define shopman1_end 109    //跟你说个秘密，对面的镐贼钝..
#define shopman2_end 110    //跟你说个秘密，对面的盾贼脆..
#define woman 111      //公主
#define npc 112       //还没用上
#define road 0        //路
#define wall 1      //墙
#define yellowdoor 2//黄门2
#define bluedoor 3//蓝门3
#define reddoor 4//红门4
#define bossdoor 5//破怪门5
#define medoor 6//机关门6
#define yellowkey 7    //黄钥匙
#define bluekey 8        //蓝钥匙
#define redkey 9         //红钥匙
#define bloodbottle 10    //血瓶
#define uproad 11     //上楼
#define downroad 12      //下楼
#define redstone 13     //攻击宝石
#define bluestone 14   //防御宝石
#define fire 15      //岩浆
//怪物是负数 绿色史莱姆-1 红色史莱姆-2
//小蝙蝠 -3 初级法师-4 骷髅人-5
//骷髅士兵-6 初级卫兵-7 骷髅队长-8
//吸血鬼-9 黑巫师-10
//魔王-30
//升降机 20 神圣剑51 神圣盾52 屠龙刀53 轻羽靴54
void printnum(void);    //输入人物数据
void readmap(int mapnum);//读取文件得到地图
void printmap(PIMAGE, PIMAGE); //打印地图
void begingame(void);           //游戏界面初始化,数值初始化
void printone(int choice, int x, int y, PIMAGE, PIMAGE, int);//打印一个
int play(PIMAGE imgwall, PIMAGE imgroad);//操作主函数
void monbegin(void);  //怪物数值初始化
void print_mon(int kind, int order, PIMAGE imgroad, PIMAGE imgwall); //打印右下怪物信息
void clean(void);     //清除文字框
void cleanmon(int choice);  //清理怪物装备信息
int talkbox(int kind, char words[]);  //对话框
int talk(int mankind);      //对话
void print_equip(int choice);   //打印装备
void endgame(int choice);         //结束游戏
int fight(int mkind, PIMAGE imgwall, PIMAGE imgroad, int newx, int newy);  //战斗
void savemap(void);                       //存放地图
int startgamepage(int kind);                 //开始界面,由kind分为两用
void printhelp(int choice);                //帮助打印
void print_tr(int choice, int flag = 1);    //打印几件宝物
void savegame(void);            //存档
void readgame(void);               //读档
void swapmap(FILE *fp1, FILE *fp2);  //存档时复制地图
void manwalk(int newx, int newy, PIMAGE imgroad, PIMAGE imgwall, PIMAGE imgnman);//人物行走函数
int nextwalk(int newx, int newy, PIMAGE imgroad, PIMAGE imgwall, PIMAGE imgnman);//根据下一走到的位置作出不同的选择
int mapt[11][11];//加上外边两层墙，13*13
int win = 0;  //记录魔王是否死了
int ifpass[51];//记录是否经过
int music_flag = 1;//记录音乐是否开启
int sec_kill = 1;//记录秒杀是否开启,1时按一下加10000，-1时按一下减10000
int ifload = 0;  //是否载入存档
int site = 1;   //记录楼层
void clear(char *temp);
bool security_check(char *temp);
void encrypt(char *temp, char *backup);
void decrypt(char *temp);
int ID_check(FILE *fp);
int ID_search(FILE *fp);
void ID_store(FILE *fp);
void admin_initial(void);
void create_initial(void);
void keyboard_input(int flag, int signal);
void ID_create(FILE *fp);
void ID_identify(FILE *fp);
char ID[20] = { 0 };
char keyword[20] = { 0 };
char rekeyword[20] = { 0 };
char invisible_key[20] = { 0 };
char invisible_rekey[20] = { 0 };
int ID_ordinal = 0;
int keyword_ordinal = 0, invisible_key_ordinal = 0;
int rekeyword_ordinal = 0, invisible_rekey_ordinal = 0;
mouse_msg msg = { 0 };//存放鼠标信息
MUSIC mus;//定义一个音乐对象
MUSIC musdoor;
MUSIC muswel;
MUSIC musget;
MUSIC mushit;
struct person {      //定义人物结构
	int x; int y;//存放人的坐标
	int atk; int def;//攻击防御
	int double_atk;//暴击率
	int miss;//闪避率
	int blood;
	int ykeynum;
	int bkeynum;
	int rkeynum;
	int money;
	int dir;           //定义方向     1-前 2-左 3-右 4-后
	int tr[10] = { 0 };//是否有宝物，1-宝典，2-向下一层，3-升降机，4-镐子 5-神圣盾
	int equip[2];      //攻防具
}pe;
struct monster {       //定义怪物结构
	int blood;
	int atk; int def;
	int double_atk;
	int money;
	int miss;
	char name[16];
}mon[31];