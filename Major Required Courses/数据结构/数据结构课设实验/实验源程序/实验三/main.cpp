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
    int elemnum;              //存储选取二叉树的序号
    int i;             //需要使用的序号变量
    BiTree tempT;       //中间存储二叉树指针
    for(i=0;i<LISTS_INIT_SIZE; i++) {
        Lists.elem[i].T = NULL;
    }
    while(op1){
        system("cls");	printf("\n\n");
        printf("          基于二叉树的基本操作演示系统\n");
        printf("-------------------------------------------------\n");
        printf("            1.显示全部二叉树名字\n");
        printf("            2.增加一个二叉树\n");
        printf("            3.删除一个二叉树\n");
        printf("            4.选择二叉树进行操作\n");
        printf("            0.退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~4]:");
        scanf("%d",&op1);
        switch(op1){
        case 1:
            if(Lists.length==0)
                printf("无二叉树\n");
            else
            {
                for(i=0;i<Lists.length;i++)
                {
                    printf("%s ",Lists.elem[i].name);
                    printf("\n");
                }
            }
            getchar();getchar();
            break;
        case 2:
            printf("请输入你要创建的二叉树名\n");
            scanf("%s",charname);
            judge=LocateList(Lists,charname);
            if(judge)
                printf("已存在同名树。\n");
            else
            {
                judge1=AddList(Lists,charname);
                if(judge1==OK)
                    printf("创建二叉树成功\n");
                else printf("创建二叉树失败\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("请输入你要删除的二叉树名\n");
            scanf("%s",charname);
            judge1=RemoveList(Lists,charname);
            if(judge1==OK)
                printf("删除成功\n");
            else printf("删除失败\n");
            getchar();getchar();
            break;
        case 4:
            op=1;
            printf("输入选择的二叉树\n");
            scanf("%s",charname);
            elemnum=LocateList(Lists,charname);
            if(elemnum)
            {
                while(op){
            system("cls");	printf("\n\n");
            printf("      Menu for Linear Table On Sequence Structure \n");
	        printf("-------------------------------------------------\n");
	        printf("    	  1.求二叉树深度       2.查找结点\n");
	        printf("    	  3.结点赋值            4.获得兄弟结点\n");
	        printf("    	  5.插入结点            6.删除节点 \n");
	        printf("    	  7.先序遍历            8.中序遍历\n");
	        printf("    	  9.后序遍历            10.按层遍历\n");
	        printf("    	  11.文件读写           0.返回初级菜单\n");
        	printf("-------------------------------------------------\n");
        	printf("    请选择你的操作[0~9]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                judge=BiTreeDepth(Lists.elem[elemnum-1].T);
                printf( "二叉树深度为%d\n",judge);
                getchar();getchar();
                break;
            case 2:
                printf("输入你想获取的元素的关键字。\n");
                scanf("%d",&i);
                tempT=LocateNode(Lists.elem[elemnum-1].T,i);
                if(tempT)  printf("成功提取，为%d,%s\n",tempT->data.key,tempT->data.others);
                else printf("查找失败\n");
                getchar();getchar();
	            break;
            case 3:
                TElemType value;
                printf("输入想要赋值的结点关键字。\n");
                scanf("%d",&i);
                printf("输入修改的value.\n");
                scanf("%d%s",&value.key,value.others);
                judge=Assign(Lists.elem[elemnum-1].T,i,value);
                if(judge) printf("已成功赋值\n");
                else printf("赋值失败！\n");
		        getchar();getchar();
	            break;
        	case 4:
                printf("输入你想获取兄弟节点的结点关键字。\n");
                scanf("%d",&i);
                tempT=GetSibling(Lists.elem[elemnum-1].T,i);
                if(tempT)  printf("成功提取，为%d,%s\n",tempT->data.key,tempT->data.others);
                else printf("查找失败\n");
                getchar();getchar();
	            break;
	        case 5:
	            printf("输入e、LR、c\n");
	            printf("e是和T中结点关键字类型相同的给定值,LR为0或1,c是待插入结点\n");
                printf("根据LR为0或者1，插入结点c到T中,作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树\n");
                printf("当LR为-1时，作为根结点插入,原根结点作为c的右子树。\n");

                int e,LR;
                TElemType c;
                scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
                judge=InsertNode(Lists.elem[elemnum-1].T,e,LR,c);
                if(judge)
                    printf("插入成功\n");
                else printf("插入结点失败\n");
             	getchar();getchar();
        	    break;
            case 6:
                printf("输入想要删除的节点关键字\n");
                scanf("%d",&i);
                judge=DeleteNode(Lists.elem[elemnum-1].T,i);
                if(judge)
                    printf("结点删除成功\n");
                else printf("无该结点\n");
		        getchar();getchar();
                break;
	        case 7:
                printf("先序遍历结果如下：\n");
                PreOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
        	    getchar();getchar();
                break;
	        case 8:
                printf("中序遍历结果如下\n");
                InOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
	            getchar();getchar();
                break;
	        case 9:
                printf("后序遍历结果如下\n");
                PostOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
	            getchar();getchar();
                break;
	        case 10:
                printf("按层遍历结果如下\n");
                LevelOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
	            getchar();getchar();
                break;
            case 11:
                printf("输入1以进行读入操作，输入2以进行读取操作。\n");
                scanf("%d",&judge1);
                printf("输入文件名。\n");
                scanf("%s",filename);
                if(judge1==1)
                {
                    if(SaveBiTree(Lists.elem[elemnum-1].T,filename)==OK)
                        printf("读入成功。\n");
                    else printf("读入失败。\n");
                }
                else if(judge1==2)
                {
                    judge=LoadBiTree(Lists.elem[elemnum-1].T,filename);
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
                printf("无该二叉树\n");
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
