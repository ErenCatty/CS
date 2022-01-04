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
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
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
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L->elem==NULL)
        return INFEASIBLE;
    L->length=0;
    return OK;
}
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem==NULL)
        return INFEASIBLE;
    if(i>L.length||i<=0)
        return ERROR;
    *e=*(L.elem+i-1);
    return OK;
}
status LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L.elem==NULL)
        return INFEASIBLE;
    ElemType *p;
    int i=1;
    p=L.elem;
    while(i<=L.length&&!(*p++==e))  i++;
        if(i <= L.length)
                return  i;    //返回位置
        else
                return ERROR;
}
status PriorElem(SqList L,ElemType e,ElemType *pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
    if(i<1||i>L->length+1)               //L->length初始为0
        return ERROR;
    if(L->length>=L->listsize)
    {
        newbase=(ElemType *) realloc(L->elem, (L->listsize+LISTINCREMENT) *sizeof(ElemType));
        if(!newbase)
            return ERROR;
        L->elem=newbase;      //新基址
        L->listsize+=LISTINCREMENT;  //增加存储容量
    }
    q=L->elem+i-1;    //      q为插入位置
    for(p=L->elem+L->length-1;p>=q;--p) /* 插入位置及之后的元素右移 */
        *(p+1)=*p;
    *q=e;
    ++L->length;
    return OK;
}
status ListDelete(SqList *L,int i,ElemType *e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
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
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
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
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
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
// Lists中删除一个名称为ListName的线性表
{
    int i,j,flag;
    char ch;
    for(i=0;i<Lists->length;i++)                      //p查找需要删除的线性表
    {
        j=0;
        flag=1;
        while(ch=ListName[j])                        //判断线性表名是否符合要求
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
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
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
