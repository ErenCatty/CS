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
char GoodName[10] = { 0 };   //存储输入货物名
int GoodNumber;            //存储货物编号
int number;                //货物改变量
int ratelist[N] = { 0 };   //排序数组
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
		printf("请输入用户名：");
		scanf("%s", inputname);
		printf("请输入密码：");
		scanf("%s", inputcode);
		if ((strcmp(username, inputname) && strcmp(password, inputcode))==0)
			break;
		printf("输入用户名或者密码错误\n");
		getchar();getchar();
	}*/

	int op = 1;
	while (op!=9) {
		system("cls");
		printf("             商品信息系统\n");
		printf("-------------------------------------------------\n");
		printf("1.查找商品                          2.出货\n");
		printf("3.进货                              4.计算利润率\n");
		printf("5.根据商品利润率排序                6.添加新商品\n");
		printf("9.退出\n");
		printf("-------------------------------------------------\n");
		printf("请选择你的操作:");
		scanf_s("%d", &op);
		switch (op) {
		case 1:
			printf("请输入商品名：");
			scanf("%s", GoodName);
			findGoods(GoodTotal, GA);
			if (GoodNumber == -1)
				printf("无该货物\n");
			else {
				printf("货物名：%s\n", GA[GoodNumber].GOODSNAME);
				printf("进价：%d\n", GA[GoodNumber].BUYPRICE);
				printf("售价：%d\n", GA[GoodNumber].SELLPRICE);
				printf("购货量：%d\n", GA[GoodNumber].BUYNUM);
				printf("出货量：%d\n", GA[GoodNumber].SELLNUM);
				printf("利润率：%d\n", GA[GoodNumber].RATE);
			}
			getchar();getchar();
			break;
		case 2:
			printf("请输入商品名：");
			scanf("%s", GoodName);
			printf("请输入出货量：");
			scanf("%d", &number);
			findGoods(GoodTotal, GA);
			sellGoods();
			getchar();getchar();
			break;
		case 3:
			printf("请输入商品名：");
			scanf("%s", GoodName);
			printf("请输入购货量：");
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
			printf("请输入新加入商品名:");
			scanf("%s", GoodName);
			findGoods(GoodTotal, GA);
			if (GoodNumber != -1) {
				printf("已存在该货物。\n");
				getchar();getchar();
				break;
			}
			strcpy(GA[GoodTotal].GOODSNAME, GoodName);
			printf("请输入商品进价：");
			scanf("%hd", &GA[GoodTotal].BUYPRICE);
			printf("请输入商品售价：");
			scanf("%hd", &GA[GoodTotal].SELLPRICE);
			printf("请输入商品进货量：");
			scanf("%hd", &GA[GoodTotal].BUYNUM);
			printf("请输入商品出货量：");
			scanf("%hd", &GA[GoodTotal].SELLNUM);
			if (GA[GoodTotal].BUYNUM < GA[GoodTotal].SELLNUM) {
				printf("输入不合理。\n");
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
	printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main