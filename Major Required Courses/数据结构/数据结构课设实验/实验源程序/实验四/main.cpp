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
    int judge,judge1;         //�洢����ֵ���м���
    int i;             //��Ҫʹ�õ���ű���
    KeyType v,w;

    while(op1){
        system("cls");	printf("\n\n");
        printf("             ͼ����������ʾϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("            1.��ʾȫ��ͼ����\n");
        printf("            2.����һ��ͼ\n");
        printf("            3.ɾ��һ��ͼ\n");
        printf("            4.ѡ��ͼ���в���\n");
        printf("            0.�˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~4]:");
        scanf("%d",&op1);
        switch(op1){
        case 1:
            if(GraghsLength(Graghs)==0)
                printf("��ͼ\n");
            else
            {
                GraghsTraverse(Graghs);
                printf("\n");
            }
            /*if(Lists.length==0)
                printf("��ͼ\n");
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
            printf("��������Ҫ������ͼ��\n");
            scanf("%s",charname);
            /*judge=LocateList(Lists,charname);
            if(judge)
                printf("�Ѵ���ͬ��ͼ��\n");
            else
            {
                printf("����ͼ�Ķ����Լ���\n");
                judge1=AddList(Lists,charname);
                if(judge1==OK)
                    printf("����ͼ�ɹ�\n");
                else printf("����ͼʧ��\n");
            }*/
            judge1=GraghsAdd(Graghs,charname);
            if(judge1==OK)
                    printf("����ͼ�ɹ�\n");
                else printf("����ͼʧ��\n");
            getchar();getchar();
            break;
        case 3:
            printf("��������Ҫɾ����ͼ��\n");
            scanf("%s",charname);
            judge1=GraghsRemove(Graghs,charname);
            if(judge1==OK)
                printf("ɾ���ɹ�\n");
            else printf("ɾ��ʧ��\n");
            getchar();getchar();
            break;
        case 4:
            op=1;
            printf("����ѡ���ͼ\n");
            scanf("%s",charname);
            GraghLoc=GraghsLocate(Graghs,charname);
            if(GraghLoc)
            {
                while(op){
            system("cls");	printf("\n\n");
            printf("      Menu for Linear Table On Sequence Structure \n");
	        printf("-------------------------------------------------\n");
	        printf("    	  1.���Ҷ���              2.���㸳ֵ\n");
	        printf("    	  3.��õ�һ�ڽӵ�        4.�����һ�ڽӵ�\n");
	        printf("    	  5.���붥��              6.ɾ������ \n");
	        printf("    	  7.���뻡                8.ɾ����\n");
	        printf("    	  9.���������������      10.���������������\n");
	        printf("    	  11.�ļ���д             12.��ʾͼ\n");
	        printf("    	  0.���س����˵�\n");
        	printf("-------------------------------------------------\n");
        	printf("    ��ѡ����Ĳ���[0~9]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                printf("���������ȡ�Ķ���Ĺؼ��֡�\n");
                scanf("%d",&i);
                judge=LocateVex(GraghLoc->G,i);
                if(judge==-1)
                    printf("����ʧ�ܡ�\n");
                else printf("�ö���λ��Ϊ%d\n",judge);
                getchar();getchar();
                break;
            case 2:
                VertexType value;
                printf("������Ҫ��ֵ�Ķ���ؼ��֡�\n");
                scanf("%d",&i);

                if(LocateVex(GraghLoc->G,i)==-1)
                {
                    printf("�޸ö��㡣\n");
                    getchar();getchar();
                    break;
                }

                printf("�����޸ĵ�value.\n");
                scanf("%d%s",&value.key,value.others);
                judge=PutVex(GraghLoc->G,i,value);
                if(judge) printf("�ѳɹ���ֵ\n");
                else printf("��ֵʧ�ܣ�\n");
		        getchar();getchar();
	            break;
            case 3:
                printf("���������ȡ��һ�ڽӵ�Ķ���ؼ��֡�\n");
                scanf("%d",&i);
                judge=FirstAdjVex(GraghLoc->G,i);
                if(judge!=-1)  printf("�ɹ���ȡ��λ��Ϊ%d\n",judge);
                else printf("����ʧ��\n");
                getchar();getchar();
	            break;
        	case 4:
                printf("���������ȡ��һ�ڽӵ�Ķ���ؼ����Լ����ؼ��֡�\n");
                scanf("%d%d",&v,&w);
                judge=NextAdjVex(GraghLoc->G,v,w);
                if(judge!=-1)  printf("�ɹ���ȡ��λ��Ϊ%d\n",judge);
                else printf("����ʧ��\n");
                getchar();getchar();
	            break;
	        case 5:
	            printf("������Ҫ����Ķ���ֵ\n");
	            scanf("%d%s",&value.key,value.others);
                judge=InsertVex(GraghLoc->G,value);
                if(judge)
                    printf("����ɹ�\n");
                else printf("���붥��ʧ��\n");
             	getchar();getchar();
        	    break;
            case 6:
                printf("������Ҫɾ���Ķ���ؼ���\n");
                scanf("%d",&v);
                judge=DeleteVex(GraghLoc->G,v);
                if(judge)
                    printf("����ɾ���ɹ�\n");
                else printf("ɾ��ʧ��\n");
		        getchar();getchar();
                break;
	        case 7:
                printf("������Ҫ����Ļ������˹ؼ���\n");
                scanf("%d%d",&v,&w);
                judge=InsertArc(GraghLoc->G,v,w);
                if(judge)
                    printf("����ɹ�\n");
                else printf("����ʧ��\n");
        	    getchar();getchar();
                break;
	        case 8:
                printf("������Ҫɾ���Ļ������˹ؼ���\n");
                scanf("%d%d",&v,&w);
                judge=DeleteArc(GraghLoc->G,v,w);
                if(judge)
                    printf("ɾ���ɹ�\n");
                else printf("ɾ��ʧ��\n");
        	    getchar();getchar();
                break;
	        case 9:
                printf("������ȱ����������\n");
                DFSTraverse(GraghLoc->G,visit);
                printf("\n");
	            getchar();getchar();
                break;
	        case 10:
                printf("������ȱ����������\n");
                BFSTraverse(GraghLoc->G,visit);
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
                    if(SaveGraph(GraghLoc->G,filename)==OK)
                        printf("����ɹ���\n");
                    else printf("����ʧ�ܡ�\n");
                }
                else if(judge1==2)
                {
                    judge=LoadGraph(GraghLoc->G,filename);
                    if(judge==OK)
                        printf("��ȡ�ɹ���\n");
                    else if(judge==ERROR)
                        printf("�ļ������ڡ�\n");
                    else printf("��ȡʧ�ܡ�\n");
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
                printf("�޸�ͼ\n");
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
