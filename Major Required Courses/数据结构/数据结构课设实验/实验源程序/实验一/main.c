/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include"func.h"


/*-----page 19 on textbook ---------*/
status InitList(SqList *L);
status DestroyList(SqList *L);
status ClearList(SqList *L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType *e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType *pre);
status NextElem(SqList L,ElemType e,ElemType *next);
status ListInsert(SqList *L,int i,ElemType e);
status ListDelete(SqList *L,int i,ElemType *e);
status ListTrabverse(SqList L);  //�򻯹�
status AddList(LISTS *Lists,char ListName[]);
status RemoveList(LISTS *Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
status  SaveList(SqList L,char FileName[]);
status  LoadList(SqList *L,char FileName[]);

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
                    ListTrabverse(Lists.elem[i].L);
                    printf("\n");
                }

            }
            getchar();getchar();
            break;
        case 2:
            printf("��������Ҫ���������Ա���\n");
            scanf("%s",charname);
            judge1=AddList(&Lists,charname);
            if(judge1==OK)
                printf("�������Ա�ɹ�\n");
            else printf("�������Ա�ʧ��\n");
            getchar();getchar();
            break;
        case 3:
            printf("��������Ҫɾ�������Ա���\n");
            scanf("%s",charname);
            judge1=RemoveList(&Lists,charname);
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
            while(op){
            system("cls");	printf("\n\n");
            printf("      Menu for Linear Table On Sequence Structure \n");
	        printf("-------------------------------------------------\n");
	        printf("    	  1. InitList       7. LocateElem\n");
	        printf("    	  2. DestroyList    8. PriorElem\n");
	        printf("    	  3. ClearList      9. NextElem \n");
	        printf("    	  4. ListEmpty      10. ListInsert\n");
	        printf("    	  5. ListLength     11. ListDelete\n");
        	printf("    	  6. GetElem        12. ListTrabverse\n");
        	printf("          13.fileoperate    0. Return\n");
        	printf("-------------------------------------------------\n");
        	printf("    ��ѡ����Ĳ���[0~13]:");
        	scanf("%d",&op);
            switch(op){
            case 1:
                judge=InitList(&Lists.elem[elemnum-1].L);
                if(judge==OK) printf("���Ա����ɹ���\n");
                else if(judge==ERROR) printf("�Ѿ��������Ա�\n");
                else printf("���Ա���ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 2:
                if(DestroyList(&Lists.elem[elemnum-1].L)==OK) printf("���Ա�ɾ���ɹ���\n");
                else printf("���Ա�ɾ��ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 3:
                if(ClearList(&Lists.elem[elemnum-1].L)==OK) printf("���Ա�����ɹ���\n");
                else printf( "���Ա����ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 4:
                judge=ListEmpty(Lists.elem[elemnum-1].L);
                if(judge==TRUE) printf("���Ա�Ϊ�գ�\n");
                else if(judge==FALSE) printf("���Ա�ǿգ�\n");
                else printf("���Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 5:
                judge=ListLength(Lists.elem[elemnum-1].L);
                if(judge>=0) printf("���Ա���Ϊ%d\n",judge);
                else printf("���Ա����ڣ�\n");
		        getchar();getchar();
	            break;
        	case 6:
                printf("���������ȡ��Ԫ����š�\n");
                scanf("%d",&i);
                judge=GetElem(Lists.elem[elemnum-1].L,i,&e);
                if(judge==OK)  printf("�ɹ���ȡ��Ԫ�أ���%d��Ԫ��Ϊ%d\n",i,e);
                else if(judge==ERROR)  printf("����i���Ϸ��أ�\n");
                else printf("L�������أ�\n");
                getchar();getchar();
	            break;
	        case 7:
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
	        case 8:
                printf("�����������ǰ����Ԫ��\n");
                scanf("%d",&e);
                judge=PriorElem(Lists.elem[elemnum-1].L,e,&pre);
                if(judge==OK)
                    printf("ǰ��Ϊ%d��������pre��",pre);
                else if(judge==ERROR)
                    printf("û��ǰ��");
                else printf("L������");
        	    getchar();getchar();
                break;
	        case 9:
                printf("����������Һ�����Ԫ��\n");
                scanf("%d",&e);
                judge=NextElem(Lists.elem[elemnum-1].L,e,&next);
                if(judge==OK)
                    printf("����Ϊ%d��������next��",next);
                else if(judge==ERROR)
                    printf("û�к���");
                else printf("L������");
	            getchar();getchar();
                break;
	        case 10:
                printf("��������Ҫ�����Ԫ��\n");
                scanf("%d",&e);
                if(ListLength(Lists.elem[elemnum-1].L)==0)
                    printf("��Ϊ��Ԫ�أ�����ֱ����Ϊ��һ��Ԫ�ز��롣\n");
                else{printf("����Ҫ�����ڵڼ���Ԫ��֮ǰ\n");
                scanf("%d",&i);}
                judge=ListInsert(&Lists.elem[elemnum-1].L,i,e);
                if(judge==OK)
                    printf("Ԫ�ز���ɹ�\n");
                else if(judge==ERROR)
                printf("����λ�ò���ȷ\n");
                else printf("L������\n");
		        getchar();getchar();
		        break;
	        case 11:
                printf("������Ҫɾ����Ԫ����ţ�\n");
                scanf("%d",&i);
                judge=ListDelete(&Lists.elem[elemnum-1].L,i,&e);
                if(judge==OK)
                    printf("Ԫ��ɾ���ɹ���ɾ��Ԫ��%d������e��\n",e);
                else if(judge==ERROR)
                    printf("ɾ��λ�ò���ȷ\n");
                else printf("L������\n");
		        getchar();getchar();
                break;
	        case 12:
		        if(!ListTrabverse(Lists.elem[elemnum-1].L)) printf("���Ա��ǿձ�\n");
		        getchar();getchar();
		        break;
            case 13:
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
                    judge=LoadList(&Lists.elem[elemnum-1].L,filename);
                    if(judge==OK)
                        printf("��ȡ�ɹ���\n");
                    else if(judge==ERROR)
                        printf("���Ա����ڡ�\n");
                    else printf("��ȡʧ�ܡ�\n");
                }
                getchar();getchar();
                break;
	        case 0:
                break;
	        }//end of switch
	        }//end of while
            break;
        case 0:
            break;
            }
    }
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
return 0;
}       //end of main()
