#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void __stdcall findGoods(int, struct GOODS*);
extern void __stdcall sellGoods();
extern void __stdcall buyGoods();
extern void __stdcall calculate(int, struct GOODS*);
extern void __stdcall rank(int, struct GOODS*);
extern void __stdcall rateprint(int, struct GOODS*);

#define N 30
char username[10] = "zhongyi\0";
char password[15] = "U201914978\0";
char inputname[10] = { 0 };
char inputcode[15] = { 0 };
char GoodName[10] = { 0 };   //�洢���������
int GoodNumber;            //�洢������
int number;                //����ı���
int ratelist[N] = { 0 };   //��������
int GoodTotal = 4;
struct GOODS {
	char GOODSNAME[10];
	short BUYPRICE ;
	short SELLPRICE;
	short BUYNUM;
	short SELLNUM;
	short RATE;
};
struct GOODS GA[N]={
	{"PEN\0", 15, 20, 70, 25, 0},
	{"PENCIL\0", 2, 3, 100, 50, 0},
	{"BOOK\0", 30, 40, 25, 5, 0},
	{"RULER\0",3,4,200,150,0}
};

int main(){
	/*while (1) {
		system("cls");
		printf("�������û�����");
		scanf("%s", inputname);
		printf("���������룺");
		scanf("%s", inputcode);
		if ((strcmp(username, inputname) && strcmp(password, inputcode))==0)
			break;
		printf("�����û��������������\n");
		getchar();getchar();
	}*/

	int op = 1;
	while (op!=9) {
		system("cls");
		printf("             ��Ʒ��Ϣϵͳ\n");
		printf("-------------------------------------------------\n");
		printf("1.������Ʒ                          2.����\n");
		printf("3.����                              4.����������\n");
		printf("5.������Ʒ����������                6.�������Ʒ\n");
		printf("9.�˳�\n");
		printf("-------------------------------------------------\n");
		printf("��ѡ����Ĳ���:");
		scanf_s("%d", &op);
		switch (op) {
		case 1:
			printf("��������Ʒ����");
			scanf("%s", GoodName);
			findGoods(GoodTotal, GA);
			if (GoodNumber == -1)
				printf("�޸û���\n");
			else {
				printf("��������%s\n", GA[GoodNumber].GOODSNAME);
				printf("���ۣ�%d\n", GA[GoodNumber].BUYPRICE);
				printf("�ۼۣ�%d\n", GA[GoodNumber].SELLPRICE);
				printf("��������%d\n", GA[GoodNumber].BUYNUM);
				printf("��������%d\n", GA[GoodNumber].SELLNUM);
				printf("�����ʣ�%d\n", GA[GoodNumber].RATE);
			}
			getchar();getchar();
			break;
		case 2:
			printf("��������Ʒ����");
			scanf("%s", GoodName);
			printf("�������������");
			scanf("%d", &number);
			findGoods(GoodTotal, GA);
			sellGoods();
			getchar();getchar();
			break;
		case 3:
			printf("��������Ʒ����");
			scanf("%s", GoodName);
			printf("�����빺������");
			scanf("%d", &number);
			findGoods(GoodTotal, GA);
			buyGoods();
			getchar();getchar();
			break;
		case 4:
			calculate(GoodTotal, GA);
			getchar();getchar();
			break;
		case 5:
			for (int i = 0;i < GoodTotal;i++)
				ratelist[i] = i;
			rank(GoodTotal-1, GA);
			rateprint(GoodTotal, GA);
			getchar();getchar();
			break;
		case 6:
			printf("�������¼�����Ʒ��:");
			scanf("%s", GoodName);
			findGoods(GoodTotal, GA);
			if (GoodNumber != -1) {
				printf("�Ѵ��ڸû��\n");
				getchar();getchar();
				break;
			}
			strcpy(GA[GoodTotal].GOODSNAME, GoodName);
			printf("��������Ʒ���ۣ�");
			scanf("%hd", &GA[GoodTotal].BUYPRICE);
			printf("��������Ʒ�ۼۣ�");
			scanf("%hd", &GA[GoodTotal].SELLPRICE);
			printf("��������Ʒ��������");
			scanf("%hd", &GA[GoodTotal].BUYNUM);
			printf("��������Ʒ��������");
			scanf("%hd", &GA[GoodTotal].SELLNUM);
			if (GA[GoodTotal].BUYNUM < GA[GoodTotal].SELLNUM) {
				printf("���벻����\n");
				getchar();getchar();
				break;
			}
			GA[GoodTotal].RATE = 0;
			GoodTotal++;
			getchar();getchar();
			break;
		case 9:
			break;
		}//end of switch(op)
	}//end of while(op)
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main