#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include"func.h"


int main(void)
{
    int op,op1=1;
    char charname[10],filename[20];
    GraghsLink Graghs;
    Graghs=(GraghsLink)malloc(sizeof(GraghNode));
    Graghs->next=NULL;
    GraghsLink GraghLoc;
    int judge,judge1;         //存储返回值的中间量
    int i;             //需要使用的序号变量
    KeyType v,w;

    while(op1){
        system("cls");	printf("\n\n");
        printf("             图基本操作演示系统\n");
        printf("-------------------------------------------------\n");
        printf("            1.显示全部图名字\n");
        printf("            2.增加一个图\n");
        printf("            3.删除一个图\n");
        printf("            4.选择图进行操作\n");
        printf("            0.退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~4]:");
        scanf("%d",&op1);
        switch(op1){
        case 1:
            if(GraghsLength(Graghs)==0)
                printf("无图\n");
            else
            {
                GraghsTraverse(Graghs);
                printf("\n");
            }
            /*if(Lists.length==0)
                printf("无图\n");
            else
            {
                for(i=0;i<Lists.length;i++)
                {
                    printf("%s ",Lists.elem[i].name);
                    printf("\n");
                }
            }*/
            getchar();getchar();
            break;
        case 2:
            printf("请输入你要创建的图名\n");
            scanf("%s",charname);
            /*judge=LocateList(Lists,charname);
            if(judge)
                printf("已存在同名图。\n");
            else
            {
                printf("输入图的顶点以及弧\n");
                judge1=AddList(Lists,charname);
                if(judge1==OK)
                    printf("创建图成功\n");
                else printf("创建图失败\n");
            }*/
            judge1=GraghsAdd(Graghs,charname);
            if(judge1==OK)
                    printf("创建图成功\n");
                else printf("创建图失败\n");
            getchar();getchar();
            break;
        case 3:
            printf("请输入你要删除的图名\n");
            scanf("%s",charname);
            judge1=GraghsRemove(Graghs,charname);
            if(judge1==OK)
                printf("删除成功\n");
            else printf("删除失败\n");
            getchar();getchar();
            break;
        case 4:
            op=1;
            printf("输入选择的图\n");
            scanf("%s",charname);
            GraghLoc=GraghsLocate(Graghs,charname);
            if(GraghLoc)
            {
                while(op){
            system("cls");	printf("\n\n");
            printf("      Menu for Linear Table On Sequence Structure \n");
	        printf("-------------------------------------------------\n");
	        printf("    	  1.查找顶点              2.顶点赋值\n");
	        printf("    	  3.获得第一邻接点        4.获得下一邻接点\n");
	        printf("    	  5.插入顶点              6.删除顶点 \n");
	        printf("    	  7.插入弧                8.删除弧\n");
	        printf("    	  9.深度优先搜索遍历      10.广度优先搜索遍历\n");
	        printf("    	  11.文件读写             12.显示图\n");
	        printf("    	  0.返回初级菜单\n");
        	printf("-------------------------------------------------\n");
        	printf("    请选择你的操作[0~9]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                printf("输入你想获取的顶点的关键字。\n");
                scanf("%d",&i);
                judge=LocateVex(GraghLoc->G,i);
                if(judge==-1)
                    printf("查找失败。\n");
                else printf("该顶点位序为%d\n",judge);
                getchar();getchar();
                break;
            case 2:
                VertexType value;
                printf("输入想要赋值的顶点关键字。\n");
                scanf("%d",&i);

                if(LocateVex(GraghLoc->G,i)==-1)
                {
                    printf("无该顶点。\n");
                    getchar();getchar();
                    break;
                }

                printf("输入修改的value.\n");
                scanf("%d%s",&value.key,value.others);
                judge=PutVex(GraghLoc->G,i,value);
                if(judge) printf("已成功赋值\n");
                else printf("赋值失败！\n");
		        getchar();getchar();
	            break;
            case 3:
                printf("输入你想获取第一邻接点的顶点关键字。\n");
                scanf("%d",&i);
                judge=FirstAdjVex(GraghLoc->G,i);
                if(judge!=-1)  printf("成功提取，位序为%d\n",judge);
                else printf("查找失败\n");
                getchar();getchar();
	            break;
        	case 4:
                printf("输入你想获取下一邻接点的顶点关键字以及结点关键字。\n");
                scanf("%d%d",&v,&w);
                judge=NextAdjVex(GraghLoc->G,v,w);
                if(judge!=-1)  printf("成功提取，位序为%d\n",judge);
                else printf("查找失败\n");
                getchar();getchar();
	            break;
	        case 5:
	            printf("输入想要插入的顶点值\n");
	            scanf("%d%s",&value.key,value.others);
                judge=InsertVex(GraghLoc->G,value);
                if(judge)
                    printf("插入成功\n");
                else printf("插入顶点失败\n");
             	getchar();getchar();
        	    break;
            case 6:
                printf("输入想要删除的顶点关键字\n");
                scanf("%d",&v);
                judge=DeleteVex(GraghLoc->G,v);
                if(judge)
                    printf("顶点删除成功\n");
                else printf("删除失败\n");
		        getchar();getchar();
                break;
	        case 7:
                printf("输入想要插入的弧的两端关键字\n");
                scanf("%d%d",&v,&w);
                judge=InsertArc(GraghLoc->G,v,w);
                if(judge)
                    printf("插入成功\n");
                else printf("插入失败\n");
        	    getchar();getchar();
                break;
	        case 8:
                printf("输入想要删除的弧的两端关键字\n");
                scanf("%d%d",&v,&w);
                judge=DeleteArc(GraghLoc->G,v,w);
                if(judge)
                    printf("删除成功\n");
                else printf("删除失败\n");
        	    getchar();getchar();
                break;
	        case 9:
                printf("深度优先遍历结果如下\n");
                DFSTraverse(GraghLoc->G,visit);
                printf("\n");
	            getchar();getchar();
                break;
	        case 10:
                printf("广度优先遍历结果如下\n");
                BFSTraverse(GraghLoc->G,visit);
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
                    if(SaveGraph(GraghLoc->G,filename)==OK)
                        printf("读入成功。\n");
                    else printf("读入失败。\n");
                }
                else if(judge1==2)
                {
                    judge=LoadGraph(GraghLoc->G,filename);
                    if(judge==OK)
                        printf("读取成功。\n");
                    else if(judge==ERROR)
                        printf("文件不存在。\n");
                    else printf("读取失败。\n");
                }
                getchar();getchar();
                break;
            case 12:
                ShowGragh(GraghLoc->G);
                printf("\n");
                getchar();getchar();
                break;
	        case 0:
                break;
	        }//end of switch
	        }//end of while
            }  //end of if(elemnum)
            else
            {
                printf("无该图\n");
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
