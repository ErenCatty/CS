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
    int judge,judge1;         //�洢����ֵ���м���
    int elemnum;              //�洢ѡȡ���Ա�����
    int e;             //�Ĵ�Ԫ�صı���
    int i;             //��Ҫʹ�õ���ű���
    for(i=0;i<LISTS_INIT_SIZE; i++) {
        Lists.elem[i].L = NULL;
    }
    int pre,next;      //ǰ���������ű���
    while(op1){
        system("cls");	printf("\n\n");
        printf("          ����˳��ṹ�����Ա����������ʾϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("            1.��ʾȫ�����Ա�\n");
        printf("            2.����һ�����Ա�\n");
        printf("            3.ɾ��һ�����Ա�\n");
        printf("            4.ѡ�����Ա���в���\n");
        printf("            0.�˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~4]:");
        scanf("%d",&op1);
        switch(op1){
        case 1:
            if(Lists.length==0)
                printf("�����Ա�\n");
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
            printf("��������Ҫ���������Ա���\n");
            scanf("%s",charname);
            judge=LocateList(Lists,charname);
            if(judge)
                printf("�Ѵ���ͬ����\n");
            else
            {
                judge1=AddList(Lists,charname);
                if(judge1==OK)
                    printf("�������Ա�ɹ�\n");
                else printf("�������Ա�ʧ��\n");
            }
            getchar();getchar();
            break;
        case 3:
            printf("��������Ҫɾ�������Ա���\n");
            scanf("%s",charname);
            judge1=RemoveList(Lists,charname);
            if(judge1==OK)
                printf("ɾ���ɹ�\n");
            else printf("ɾ��ʧ��\n");
            getchar();getchar();
            break;
        case 4:
            op=1;
            printf("����ѡ������Ա�\n");
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
        	printf("    ��ѡ����Ĳ���[0~9]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                if(ClearList(Lists.elem[elemnum-1].L)==OK) printf("���Ա�����ɹ���\n");
                else printf( "���Ա����ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 2:
                judge=ListEmpty(Lists.elem[elemnum-1].L);
                if(judge==TRUE) printf("���Ա�Ϊ�գ�\n");
                else if(judge==FALSE) printf("���Ա�ǿգ�\n");
                else printf("���Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 3:
                judge=ListLength(Lists.elem[elemnum-1].L);
                if(judge>=0) printf("���Ա���Ϊ%d\n",judge);
                else printf("���Ա����ڣ�\n");
		        getchar();getchar();
	            break;
        	case 4:
                printf("���������ȡ��Ԫ����š�\n");
                scanf("%d",&i);
                judge=GetElem(Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)  printf("�ɹ���ȡ��Ԫ�أ���%d��Ԫ��Ϊ%d\n",i,e);
                else if(judge==ERROR)  printf("����i���Ϸ��أ�\n");
                else printf("L�������أ�\n");
                getchar();getchar();
	            break;
	        case 5:
                printf("����������ҵ�Ԫ��\n");
                scanf("%d",&e);
                judge=LocateElem(Lists.elem[elemnum-1].L,e);
                if(judge>0)
                    printf("����Ԫ����λ��%d��\n",judge);
                else if(judge==0)
                    printf("e������\n");
                else printf("L������\n");
             	getchar();getchar();
        	    break;
            case 6:
                if(ListTraverse(Lists.elem[elemnum-1].L)==1);
                else
                    printf("���Ա���Ԫ��");
                getchar();getchar();
                break;
	        case 7:
                printf("�����������ǰ����Ԫ��\n");
                scanf("%d",&e);
                judge=PriorElem(Lists.elem[elemnum-1].L,e,pre);
                if(judge==OK)
                    printf("ǰ��Ϊ%d��������pre��",pre);
                else if(judge==ERROR)
                    printf("û��ǰ��");
                else printf("L������");
        	    getchar();getchar();
                break;
	        case 8:
                printf("����������Һ�����Ԫ��\n");
                scanf("%d",&e);
                judge=NextElem(Lists.elem[elemnum-1].L,e,next);
                if(judge==OK)
                    printf("����Ϊ%d��������next��",next);
                else if(judge==ERROR)
                    printf("û�к���");
                else printf("L������");
	            getchar();getchar();
                break;
	        case 9:
                printf("��������Ҫ�����Ԫ��\n");
                scanf("%d",&e);
                if(ListLength(Lists.elem[elemnum-1].L)==0)
                {
                    printf("��Ϊ��Ԫ�أ�����ֱ����Ϊ��һ��Ԫ�ز��롣\n");
                    i=1;
                }
                else{printf("����Ҫ�����ڵڼ���Ԫ��֮ǰ\n");
                scanf("%d",&i);}
                judge=ListInsert(Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)
                    printf("Ԫ�ز���ɹ�\n");
                else if(judge==ERROR)
                printf("����λ�ò���ȷ\n");
                else printf("L������\n");
		        getchar();getchar();
		        break;
	        case 10:
                printf("������Ҫɾ����Ԫ����ţ�\n");
                scanf("%d",&i);
                judge=ListDelete(Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)
                    printf("Ԫ��ɾ���ɹ���ɾ��Ԫ��%d������e��\n",e);
                else if(judge==ERROR)
                    printf("ɾ��λ�ò���ȷ\n");
                else printf("L������\n");
		        getchar();getchar();
                break;
            case 11:
                printf("����1�Խ��ж������������2�Խ��ж�ȡ������\n");
                scanf("%d",&judge1);
                printf("�����ļ�����\n");
                scanf("%s",filename);
                if(judge1==1)
                {
                    if(SaveList(Lists.elem[elemnum-1].L,filename)==OK)
                        printf("����ɹ���\n");
                    else printf("����ʧ�ܡ�\n");
                }
                else if(judge1==2)
                {
                    judge=LoadList(Lists.elem[elemnum-1].L,filename);
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
                printf("�޸����Ա�\n");
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
