#include "func.h"
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L)
        return INFEASIBLE;
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}

status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L==NULL)
        return INFEASIBLE;
    else if(L->next==NULL)
        return TRUE;
    else return FALSE;
}

int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L;
    int i=0;     //ѭ����������
    while(p)
    {
        p=p->next;
        i++;
    }
    return i-1;
}

status GetElem(LinkList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next;
    int i=0;     //λ�����
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next,q=L;
    if(p==NULL)             //���Ա��п�
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next,q=L;
    int j=1;          //ѭ������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ���Ա���ھ�ֱ�Ӹ���
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
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
// Lists��ɾ��һ������ΪListName�����Ա�
{
    int i,j,flag;
    char ch;
    for(i=0;i<Lists.length;i++)                      //p������Ҫɾ�������Ա�
    {
        j=0;
        flag=1;
        while(ch=ListName[j])                        //�ж����Ա����Ƿ����Ҫ��
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

