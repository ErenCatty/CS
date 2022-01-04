#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED


#include"def.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*--------page 23 on textbook --------------------*/
status InitList(SqList *L){
    if(L->elem)
        return ERROR;
	L->elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
	L->length=0;
    L->listsize=LIST_INIT_SIZE;
	return OK;
}
status ListTrabverse(SqList L){
    int i;
    for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
    return L.length;
}
status DestroyList(SqList *L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L->elem)
    {
        free(L->elem);
        L->elem=NULL;
        L->length=0;
        L->listsize=0;
        return OK;
    }
    else
        return INFEASIBLE;
}
int ListLength(SqList L)
{
    if(L.elem)
        return L.length;
    else
        return INFEASIBLE;
}
status ClearList(SqList *L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if(L->elem==NULL)
        return INFEASIBLE;
    L->length=0;
    return OK;
}
status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL)
    return INFEASIBLE;
    else
    {
        if(L.length)
            return FALSE;
        else
            return TRUE;
    }
}
status GetElem(SqList L,int i,ElemType *e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL)
        return INFEASIBLE;
    if(i>L.length||i<=0)
        return ERROR;
    *e=*(L.elem+i-1);
    return OK;
}
status LocateElem(SqList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų�����OK�����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    if(L.elem==NULL)
        return INFEASIBLE;
    ElemType *p;
    int i=1;
    p=L.elem;
    while(i<=L.length&&!(*p++==e))  i++;
        if(i <= L.length)
                return  i;    //����λ��
        else
                return ERROR;
}
status PriorElem(SqList L,ElemType e,ElemType *pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL)
        return INFEASIBLE;
    ElemType *p;
    int i=1;
    p=L.elem;
    if(*(L.elem)==e)
        return ERROR;
    if(L.length==1)
        return ERROR;
    while(*p!=e&&i<L.length)
    {p++;i++;}
    if(i>0&&i<=L.length)
    {
        *pre=*(p-1);
        return OK;
    }
    else
    {
        return ERROR;
    }
}
status NextElem(SqList L,ElemType e,ElemType *next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL)
    return INFEASIBLE;
    if(L.length==1)
        return ERROR;
    ElemType *p,i=1;
    p=L.elem;
    while(*p!=e&&i<=L.length)
    {p++;i++;}
    if(i==L.length||i==L.length+1)
        return ERROR;
    *next=*(p+1);
    return OK;
}
status ListInsert(SqList *L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L->elem==NULL)
    return INFEASIBLE;
    ElemType *newbase,*q,*p;
    if(L->length==0)
    {
        L->elem[0]=e;
        L->length++;
        return OK;
    }
    if(i<1||i>L->length+1)               //L->length��ʼΪ0
        return ERROR;
    if(L->length>=L->listsize)
    {
        newbase=(ElemType *) realloc(L->elem, (L->listsize+LISTINCREMENT) *sizeof(ElemType));
        if(!newbase)
            return ERROR;
        L->elem=newbase;      //�»�ַ
        L->listsize+=LISTINCREMENT;  //���Ӵ洢����
    }
    q=L->elem+i-1;    //      qΪ����λ��
    for(p=L->elem+L->length-1;p>=q;--p) /* ����λ�ü�֮���Ԫ������ */
        *(p+1)=*p;
    *q=e;
    ++L->length;
    return OK;
}
status ListDelete(SqList *L,int i,ElemType *e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L->elem==NULL)
    return INFEASIBLE;
    ElemType *q,*p;
    if(i<1||i>L->length)
        return ERROR;
    p=L->elem+L->length-1;
    q=L->elem+i-1;
    *e=*q;
    for(q;q<p;q++)
        *q=*(q+1);
    --L->length;
    return OK;
}

status SaveList(SqList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem==NULL)
        return INFEASIBLE;
    ElemType i=0;
    FILE *fp1;
    if((fp1=fopen(FileName,"w+"))==NULL)
     return ERROR;
    for(i=0;i<L.length;i++)
    {
        fprintf(fp1,"%d ",L.elem[i]);
    }
    fclose(fp1);
    return OK;
}
status LoadList(SqList *L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    FILE *fp2;
    if((fp2=fopen(FileName,"r+"))==NULL)
        return ERROR;
    L->elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L->elem)
        return ERROR;
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    ElemType i=0;
    while((fscanf(fp2,"%d",&L->elem[i])!=EOF))
        i++;
    L->length+=i;
    fclose(fp2);
    return OK;
}

status AddList(LISTS *Lists,char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    int j=-1;
    SqList L1;
    L1.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    L1.length=0;
    L1.listsize=LIST_INIT_SIZE;
    Lists->elem[Lists->length].L=L1;
    while(Lists->elem[Lists->length].name[j]=ListName[++j]);
    if(Lists->elem[Lists->length].L.elem==NULL)
        return INFEASIBLE;
    else
    {
        Lists->length++;
        return OK;
    }
}


status RemoveList(LISTS *Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    int i,j,flag;
    char ch;
    for(i=0;i<Lists->length;i++)                      //p������Ҫɾ�������Ա�
    {
        j=0;
        flag=1;
        while(ch=ListName[j])                        //�ж����Ա����Ƿ����Ҫ��
        {
            if((Lists->elem[i]).name[j]!=ch)
                flag=0;
            j++;
        }
        if(flag==1)
        {
            DestroyList(&Lists->elem[i].L);
            for(j=i;j<(Lists->length-1);j++)
            {
                Lists->elem[j]=Lists->elem[j+1];
            }
            Lists->length--;
            return OK;
        }
    }
    return ERROR;
}


int LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    int i,j,flag;
    char ch;
    for(i=0;i<Lists.length;i++)
    {
        j=0;
        flag=1;
        while(ch=ListName[j])
        {
            if((Lists.elem[i]).name[j]!=ch)
                flag=0;
            j++;
        }
        if(flag==1)
            return i+1;
    }
    if(i==Lists.length)
        return 0;
}


#endif // FUNC_H_INCLUDED
