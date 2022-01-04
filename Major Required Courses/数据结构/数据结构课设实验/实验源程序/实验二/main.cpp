/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include"func.h"


int main(void)
{
    int op,op1=1;
    char charname[10],filename[20];
    LISTS Lists;
    Lists.length=0;
    int judge,judge1;         //存储返回值的中间量
    int elemnum;              //存储选取线性表的序号
    int e;             //寄存元素的变量
    int i;             //需要使用的序号变量
    for(i=0;i<LISTS_INIT_SIZE; i++) {
        Lists.elem[i].L = NULL;
    }
    int pre,next;      //前驱与后驱存放变量
    while(op1){
        system("cls");	printf("\n\n");
        printf("          基于顺序结构的线性表基本操作演示系统\n");
        printf("-------------------------------------------------\n");
        printf("            1.显示全部线性表\n");
        printf("            2.增加一个线性表\n");
        printf("            3.删除一个线性表\n");
        printf("            4.选择线性表进行操作\n");
        printf("            0.退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~4]:");
        scanf("%d",&op1);
        switch(op1){
        case 1:
            if(Lists.length==0)
                printf("无线性表\n");
            else
            {
                for(i=0;i<Lists.length;i++)
                {
                    printf("%s ",Lists.elem[i].name);
                    ListTraverse(Lists.elem[i].L);
                    printf("\n");
                }
            }
            getchar();getchar();
            break;
        case 2:
            printf("请输入你要创建的线性表名\n");
            scanf("%s",charname);
            judge=LocateList(Lists,charname);
            if(judge)
                printf("已存在同名表。\n");
            else
            {
                judge1=AddList(Lists,charname);
                if(judge1==OK)
                    printf("创建线性表成功\n");
                else printf("创建线性表失败\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("请输入你要删除的线性表名\n");
            scanf("%s",charname);
            judge1=RemoveList(Lists,charname);
            if(judge1==OK)
                printf("删除成功\n");
            else printf("删除失败\n");
            getchar();getchar();
            break;
        case 4:
            op=1;
            printf("输入选择的线性表\n");
            scanf("%s",charname);
            elemnum=LocateList(Lists,charname);
            if(elemnum)
            {
                while(op){
            system("cls");	printf("\n\n");
            printf("      Menu for Linear Table On Sequence Structure \n");
	        printf("-------------------------------------------------\n");
	        printf("    	  1. ClearList       7.PriorElem\n");
	        printf("    	  2. ListEmpty       8. NextElem\n");
	        printf("    	  3. ListLength      9. ListInsert \n");
	        printf("    	  4. GetElem         10.ListDelete\n");
	        printf("    	  5. LocateElem      11.fileoperateReturn\n");
	        printf("    	  6.ListTraverse     0.Return\n");
        	printf("-------------------------------------------------\n");
        	printf("    请选择你的操作[0~9]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                if(ClearList(Lists.elem[elemnum-1].L)==OK) printf("线性表清除成功！\n");
                else printf( "线性表清除失败！\n");
                getchar();getchar();
                break;
            case 2:
                judge=ListEmpty(Lists.elem[elemnum-1].L);
                if(judge==TRUE) printf("线性表为空！\n");
                else if(judge==FALSE) printf("线性表非空！\n");
                else printf("线性表不存在！\n");
                getchar();getchar();
                break;
            case 3:
                judge=ListLength(Lists.elem[elemnum-1].L);
                if(judge>=0) printf("线性表长度为%d\n",judge);
                else printf("线性表不存在！\n");
		        getchar();getchar();
	            break;
        	case 4:
                printf("输入你想获取的元素序号。\n");
                scanf("%d",&i);
                judge=GetElem(Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)  printf("成功提取出元素，第%d个元素为%d\n",i,e);
                else if(judge==ERROR)  printf("输入i不合法呢！\n");
                else printf("L不存在呢！\n");
                getchar();getchar();
	            break;
	        case 5:
                printf("输入你想查找的元素\n");
                scanf("%d",&e);
                judge=LocateElem(Lists.elem[elemnum-1].L,e);
                if(judge>0)
                    printf("查找元素在位置%d处\n",judge);
                else if(judge==0)
                    printf("e不存在\n");
                else printf("L不存在\n");
             	getchar();getchar();
        	    break;
            case 6:
                if(ListTraverse(Lists.elem[elemnum-1].L)==1);
                else
                    printf("线性表无元素");
                getchar();getchar();
                break;
	        case 7:
                printf("输入你想查找前驱的元素\n");
                scanf("%d",&e);
                judge=PriorElem(Lists.elem[elemnum-1].L,e,pre);
                if(judge==OK)
                    printf("前驱为%d，储存在pre中",pre);
                else if(judge==ERROR)
                    printf("没有前驱");
                else printf("L不存在");
        	    getchar();getchar();
                break;
	        case 8:
                printf("输入你想查找后驱的元素\n");
                scanf("%d",&e);
                judge=NextElem(Lists.elem[elemnum-1].L,e,next);
                if(judge==OK)
                    printf("后驱为%d，储存在next中",next);
                else if(judge==ERROR)
                    printf("没有后驱");
                else printf("L不存在");
	            getchar();getchar();
                break;
	        case 9:
                printf("输入你想要插入的元素\n");
                scanf("%d",&e);
                if(ListLength(Lists.elem[elemnum-1].L)==0)
                {
                    printf("因为无元素，所以直接作为第一个元素插入。\n");
                    i=1;
                }
                else{printf("你想要插入在第几个元素之前\n");
                scanf("%d",&i);}
                judge=ListInsert(Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)
                    printf("元素插入成功\n");
                else if(judge==ERROR)
                printf("插入位置不正确\n");
                else printf("L不存在\n");
		        getchar();getchar();
		        break;
	        case 10:
                printf("输入想要删除的元素序号！\n");
                scanf("%d",&i);
                judge=ListDelete(Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)
                    printf("元素删除成功，删除元素%d保存在e中\n",e);
                else if(judge==ERROR)
                    printf("删除位置不正确\n");
                else printf("L不存在\n");
		        getchar();getchar();
                break;
            case 11:
                printf("输入1以进行读入操作，输入2以进行读取操作。\n");
                scanf("%d",&judge1);
                printf("输入文件名。\n");
                scanf("%s",filename);
                if(judge1==1)
                {
                    if(SaveList(Lists.elem[elemnum-1].L,filename)==OK)
                        printf("读入成功。\n");
                    else printf("读入失败。\n");
                }
                else if(judge1==2)
                {
                    judge=LoadList(Lists.elem[elemnum-1].L,filename);
                    if(judge==OK)
                        printf("读取成功。\n");
                    else if(judge==ERROR)
                        printf("文件不存在。\n");
                    else printf("读取失败。\n");
                }
                getchar();getchar();
                break;
	        case 0:
                break;
	        }//end of switch
	        }//end of while
            }  //end of if(elemnum)
            else
            {
                printf("无该线性表\n");
                getchar();getchar();
                break;
            }
        case 0:
            break;
            }
    }
printf("欢迎下次再使用本系统！\n");
return 0;
}       //end of main()
