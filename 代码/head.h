//o-ֱ��ʤ�� p-ֱ������ c-�浵  �ո�-����
#include"stdafx.h"
#include <graphics.h>
#include <string.h>
#include <stdio.h>
#define man 100        //����
#define oldman 101      //����
#define shopman 102      //����
#define myfriend 103        //С͵�����ѣ�
#define shopman1 104   //������������(��һ��������ʱ��)
#define shopman2 105
#define myfriend_end 106  //���ⷽ�棬���ǲ����ܴ򹤵�..
#define oldman_end 107      //��ȹ�����������ħ��
//�뵱�꣬������Ӣ��...̾����������ӣ����ܷ���..
#define shopman_end 108     //����Ƥ�ﳧ��������ԭ��200���Ǯ��������ͳͳ20��..
//�Ҵ���û����Ǯ���Ҷ�Ǯû����Ȥ
#define shopman1_end 109    //����˵�����ܣ�����ĸ�����..
#define shopman2_end 110    //����˵�����ܣ�����Ķ�����..
#define woman 111      //����
#define npc 112       //��û����
#define road 0        //·
#define wall 1      //ǽ
#define yellowdoor 2//����2
#define bluedoor 3//����3
#define reddoor 4//����4
#define bossdoor 5//�ƹ���5
#define medoor 6//������6
#define yellowkey 7    //��Կ��
#define bluekey 8        //��Կ��
#define redkey 9         //��Կ��
#define bloodbottle 10    //Ѫƿ
#define uproad 11     //��¥
#define downroad 12      //��¥
#define redstone 13     //������ʯ
#define bluestone 14   //������ʯ
#define fire 15      //�ҽ�
//�����Ǹ��� ��ɫʷ��ķ-1 ��ɫʷ��ķ-2
//С���� -3 ������ʦ-4 ������-5
//����ʿ��-6 ��������-7 ���öӳ�-8
//��Ѫ��-9 ����ʦ-10
//ħ��-30
//������ 20 ��ʥ��51 ��ʥ��52 ������53 ����ѥ54
void printnum(void);    //������������
void readmap(int mapnum);//��ȡ�ļ��õ���ͼ
void printmap(PIMAGE, PIMAGE); //��ӡ��ͼ
void begingame(void);           //��Ϸ�����ʼ��,��ֵ��ʼ��
void printone(int choice, int x, int y, PIMAGE, PIMAGE, int);//��ӡһ��
int play(PIMAGE imgwall, PIMAGE imgroad);//����������
void monbegin(void);  //������ֵ��ʼ��
void print_mon(int kind, int order, PIMAGE imgroad, PIMAGE imgwall); //��ӡ���¹�����Ϣ
void clean(void);     //������ֿ�
void cleanmon(int choice);  //�������װ����Ϣ
int talkbox(int kind, char words[]);  //�Ի���
int talk(int mankind);      //�Ի�
void print_equip(int choice);   //��ӡװ��
void endgame(int choice);         //������Ϸ
int fight(int mkind, PIMAGE imgwall, PIMAGE imgroad, int newx, int newy);  //ս��
void savemap(void);                       //��ŵ�ͼ
int startgamepage(int kind);                 //��ʼ����,��kind��Ϊ����
void printhelp(int choice);                //������ӡ
void print_tr(int choice, int flag = 1);    //��ӡ��������
void savegame(void);            //�浵
void readgame(void);               //����
void swapmap(FILE *fp1, FILE *fp2);  //�浵ʱ���Ƶ�ͼ
void manwalk(int newx, int newy, PIMAGE imgroad, PIMAGE imgwall, PIMAGE imgnman);//�������ߺ���
int nextwalk(int newx, int newy, PIMAGE imgroad, PIMAGE imgwall, PIMAGE imgnman);//������һ�ߵ���λ��������ͬ��ѡ��
int mapt[11][11];//�����������ǽ��13*13
int win = 0;  //��¼ħ���Ƿ�����
int ifpass[51];//��¼�Ƿ񾭹�
int music_flag = 1;//��¼�����Ƿ���
int sec_kill = 1;//��¼��ɱ�Ƿ���,1ʱ��һ�¼�10000��-1ʱ��һ�¼�10000
int ifload = 0;  //�Ƿ�����浵
int site = 1;   //��¼¥��
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
mouse_msg msg = { 0 };//��������Ϣ
MUSIC mus;//����һ�����ֶ���
MUSIC musdoor;
MUSIC muswel;
MUSIC musget;
MUSIC mushit;
struct person {      //��������ṹ
	int x; int y;//����˵�����
	int atk; int def;//��������
	int double_atk;//������
	int miss;//������
	int blood;
	int ykeynum;
	int bkeynum;
	int rkeynum;
	int money;
	int dir;           //���巽��     1-ǰ 2-�� 3-�� 4-��
	int tr[10] = { 0 };//�Ƿ��б��1-���䣬2-����һ�㣬3-��������4-���� 5-��ʥ��
	int equip[2];      //������
}pe;
struct monster {       //�������ṹ
	int blood;
	int atk; int def;
	int double_atk;
	int money;
	int miss;
	char name[16];
}mon[31];