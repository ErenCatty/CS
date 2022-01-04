#include "func.h"
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L)
        return INFEASIBLE;
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p;
    while(L)
    {
        p=L->next;
        free(L);
        L=p;
    }
    return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next,q;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    else if(L->next==NULL)
        return TRUE;
    else return FALSE;
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L;
    int i=0;     //循环计数变量
    while(p)
    {
        p=p->next;
        i++;
    }
    return i-1;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L;
    if(i<1)
        return ERROR;
    while(p&&(i>=0))
    {
        if(i==0)
        {
            e=p->data;
            return OK;
        }
        p=p->next;
        i--;
    }
    if(i)
        return ERROR;
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next;
    int i=0;     //位置序号
    while(p)
    {
        i++;
        if(p->data==e)
            return i;
        p=p->next;
    }
    if(p==NULL)
        return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next,q=L;
    if(p==NULL)
        return ERROR;
    if(p->data==e)
        return ERROR;
    q=p;p=p->next;
    while(p)
    {
        if(p->data==e)
        {
            pre=q->data;
            return OK;
        }
        q=p;
        p=p->next;
    }
    if(p==NULL)
        return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next,q=L;
    if(p==NULL)             //线性表判空
        return ERROR;
    while(p)
    {
        q=p;
        p=p->next;
        if(q->data==e&&p!=NULL)
        {
            next=p->data;
            return OK;
        }
    }
    if(p==NULL)
        return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L)
        return INFEASIBLE;

    LinkList p = L;

    while (p && i-- > 0) {
        if (i == 0) {
            LinkList temp = p->next;
            p->next = (LinkList)malloc(sizeof(LNode));
            p->next->data = e;
            p->next->next = temp;
            return OK;
        }
        p = p->next;
    }

    return ERROR;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next,q=L;
    int j=1;          //循环变量
    if(i<1)
        return ERROR;
    while(p)
    {
        if(j==i)
        {
            e=p->data;
            q->next=p->next;
            free(p);
            return OK;
        }
        else
        {
            q=p;
            p=p->next;
            j++;
        }
    }
    if(p==NULL)
        return ERROR;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next;
    if(p==NULL)
        return OK;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    FILE *fp1;
    LinkList p=L->next;
    fp1=fopen(FileName,"w+");
    while(p)
    {
        fprintf(fp1,"%d ",p->data);
        p=p->next;
    }
    fclose(fp1);
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 线性表存在就直接覆盖
{
    /*if(L)
        return INFEASIBLE;*/
    FILE *fp2;
    if((fp2=fopen(FileName,"r"))==NULL)
        return ERROR;
    L=(LinkList)malloc(sizeof(LNode));
    LinkList p,q=L,s;
    while(!feof(fp2))
    {
        p=(LinkList)malloc(sizeof(LNode));
        fscanf(fp2,"%d",&p->data);
        s=q;
        q->next=p;
        q=p;
    }
    free(p);
    s->next=NULL;
    fclose(fp2);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    if(Lists.length==LISTS_INIT_SIZE)
        return ERROR;
    int i = 0;
    do {
        Lists.elem[Lists.length].name[i]=ListName[i];
    } while (ListName[i++]);

    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}


status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int i,j,flag;
    char ch;
    for(i=0;i<Lists.length;i++)                      //p查找需要删除的线性表
    {
        j=0;
        flag=1;
        while(ch=ListName[j])                        //判断线性表名是否符合要求
        {
            if((Lists.elem[i]).name[j]!=ch)
                flag=0;
            j++;
        }
        if(flag==1)
        {
            DestroyList(Lists.elem[i].L);
            for(j=i;j<(Lists.length-1);j++)
            {
                Lists.elem[j]=Lists.elem[j+1];
            }
            Lists.length--;
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

