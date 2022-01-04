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
    int judge,judge1;         //�洢����ֵ���м���
    int elemnum;              //�洢ѡȡ�����������
    int i;             //��Ҫʹ�õ���ű���
    BiTree tempT;       //�м�洢������ָ��
    for(i=0;i<LISTS_INIT_SIZE; i++) {
        Lists.elem[i].T = NULL;
    }
    while(op1){
        system("cls");	printf("\n\n");
        printf("          ���ڶ������Ļ���������ʾϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("            1.��ʾȫ������������\n");
        printf("            2.����һ��������\n");
        printf("            3.ɾ��һ��������\n");
        printf("            4.ѡ����������в���\n");
        printf("            0.�˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~4]:");
        scanf("%d",&op1);
        switch(op1){
        case 1:
            if(Lists.length==0)
                printf("�޶�����\n");
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
            printf("��������Ҫ�����Ķ�������\n");
            scanf("%s",charname);
            judge=LocateList(Lists,charname);
            if(judge)
                printf("�Ѵ���ͬ������\n");
            else
            {
                judge1=AddList(Lists,charname);
                if(judge1==OK)
                    printf("�����������ɹ�\n");
                else printf("����������ʧ��\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("��������Ҫɾ���Ķ�������\n");
            scanf("%s",charname);
            judge1=RemoveList(Lists,charname);
            if(judge1==OK)
                printf("ɾ���ɹ�\n");
            else printf("ɾ��ʧ��\n");
            getchar();getchar();
            break;
        case 4:
            op=1;
            printf("����ѡ��Ķ�����\n");
            scanf("%s",charname);
            elemnum=LocateList(Lists,charname);
            if(elemnum)
            {
                while(op){
            system("cls");	printf("\n\n");
            printf("      Menu for Linear Table On Sequence Structure \n");
	        printf("-------------------------------------------------\n");
	        printf("    	  1.����������       2.���ҽ��\n");
	        printf("    	  3.��㸳ֵ            4.����ֵܽ��\n");
	        printf("    	  5.������            6.ɾ���ڵ� \n");
	        printf("    	  7.�������            8.�������\n");
	        printf("    	  9.�������            10.�������\n");
	        printf("    	  11.�ļ���д           0.���س����˵�\n");
        	printf("-------------------------------------------------\n");
        	printf("    ��ѡ����Ĳ���[0~9]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                judge=BiTreeDepth(Lists.elem[elemnum-1].T);
                printf( "���������Ϊ%d\n",judge);
                getchar();getchar();
                break;
            case 2:
                printf("���������ȡ��Ԫ�صĹؼ��֡�\n");
                scanf("%d",&i);
                tempT=LocateNode(Lists.elem[elemnum-1].T,i);
                if(tempT)  printf("�ɹ���ȡ��Ϊ%d,%s\n",tempT->data.key,tempT->data.others);
                else printf("����ʧ��\n");
                getchar();getchar();
	            break;
            case 3:
                TElemType value;
                printf("������Ҫ��ֵ�Ľ��ؼ��֡�\n");
                scanf("%d",&i);
                printf("�����޸ĵ�value.\n");
                scanf("%d%s",&value.key,value.others);
                judge=Assign(Lists.elem[elemnum-1].T,i,value);
                if(judge) printf("�ѳɹ���ֵ\n");
                else printf("��ֵʧ�ܣ�\n");
		        getchar();getchar();
	            break;
        	case 4:
                printf("���������ȡ�ֵܽڵ�Ľ��ؼ��֡�\n");
                scanf("%d",&i);
                tempT=GetSibling(Lists.elem[elemnum-1].T,i);
                if(tempT)  printf("�ɹ���ȡ��Ϊ%d,%s\n",tempT->data.key,tempT->data.others);
                else printf("����ʧ��\n");
                getchar();getchar();
	            break;
	        case 5:
	            printf("����e��LR��c\n");
	            printf("e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ,LRΪ0��1,c�Ǵ�������\n");
                printf("����LRΪ0����1��������c��T��,��Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬���e��ԭ������������������Ϊ���c��������\n");
                printf("��LRΪ-1ʱ����Ϊ��������,ԭ�������Ϊc����������\n");

                int e,LR;
                TElemType c;
                scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
                judge=InsertNode(Lists.elem[elemnum-1].T,e,LR,c);
                if(judge)
                    printf("����ɹ�\n");
                else printf("������ʧ��\n");
             	getchar();getchar();
        	    break;
            case 6:
                printf("������Ҫɾ���Ľڵ�ؼ���\n");
                scanf("%d",&i);
                judge=DeleteNode(Lists.elem[elemnum-1].T,i);
                if(judge)
                    printf("���ɾ���ɹ�\n");
                else printf("�޸ý��\n");
		        getchar();getchar();
                break;
	        case 7:
                printf("�������������£�\n");
                PreOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
        	    getchar();getchar();
                break;
	        case 8:
                printf("��������������\n");
                InOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
	            getchar();getchar();
                break;
	        case 9:
                printf("��������������\n");
                PostOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
	            getchar();getchar();
                break;
	        case 10:
                printf("��������������\n");
                LevelOrderTraverse(Lists.elem[elemnum-1].T,visit);
                printf("\n");
	            getchar();getchar();
                break;
            case 11:
                printf("����1�Խ��ж������������2�Խ��ж�ȡ������\n");
                scanf("%d",&judge1);
                printf("�����ļ�����\n");
                scanf("%s",filename);
                if(judge1==1)
                {
                    if(SaveBiTree(Lists.elem[elemnum-1].T,filename)==OK)
                        printf("����ɹ���\n");
                    else printf("����ʧ�ܡ�\n");
                }
                else if(judge1==2)
                {
                    judge=LoadBiTree(Lists.elem[elemnum-1].T,filename);
                    if(judge==OK)
                        printf("��ȡ�ɹ���\n");
                    else if(judge==ERROR)
                        printf("�ļ������ڡ�\n");
                    else printf("��ȡʧ�ܡ�\n");
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
                printf("�޸ö�����\n");
                getchar();getchar();
                break;
            }
        case 0:
            break;
            }
    }
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
return 0;
}       //end of main()
