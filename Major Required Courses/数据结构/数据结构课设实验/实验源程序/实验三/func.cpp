#include "func.h"

int hasDuplicates(TElemType* definition)   //�ж��Ƿ��ظ�
{
    for (int i = 0; definition[i].key != -1; i++) {
        for (int j = i + 1; definition[j].key != -1; j++) {
            if (definition[i].key == definition[j].key && definition[i].key)
                return TRUE;
        }
    }
    return FALSE;
}

void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

status CreateBiTree(BiTree &T,TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    if (hasDuplicates(definition))
        return ERROR;

    int i=0;
    BiTree st[20];
    int nodenum[20]={0};
    int top=0,root=0;
    while(definition[i].key!=-1)
    {
        if(definition[i].key==0)
            nodenum[i]=2;
        st[i]=(BiTNode*)malloc(sizeof(BiTNode));
        st[i]->data=definition[i];
        st[i]->lchild=NULL;
        st[i]->rchild=NULL;
        i++;
    }
    T=st[0];
    for(top=1;top<i;top++)
    {
        if(st[top]->data.key!=0)
        {
            if(nodenum[root]==0)
            {
                nodenum[root]++;
                st[root]->lchild=st[top];
                root=top;
            }
            if(nodenum[root]==1)
            {
                nodenum[root]++;
                st[root]->rchild=st[top];
                root=top;
            }
        }
        if(st[top]->data.key==0)
        {
            nodenum[root]++;
            nodenum[top]=2;
        }
        while(nodenum[root]==2&&root>0)
            root--;
    }
    return OK;
}

status ClearBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    if(T==NULL)
        return 0;
    if(T->lchild)
    {
        ClearBiTree(T->lchild);
        T->lchild=NULL;
    }
    if(T->rchild)
    {
        ClearBiTree(T->rchild);
        T->rchild=NULL;
    }
    if(T)
    {
        free(T);
        T=NULL;
    }
}

int BiTreeDepth(BiTree T)
//�������T�����
{
    int i,j;    //�ֱ�洢���ҵ����
    if(T)
    {
        i=BiTreeDepth(T->lchild);
        j=BiTreeDepth(T->rchild);
        if(i>=j)
            return i+1;
        else
            return j+1;
    }
    else
        return 0;
}

BiTNode* LocateNode(BiTree T,KeyType e)
//���ҽ��
{
    if (!T)
        return NULL;
    if (T->data.key==e)
        return T;
    BiTree temp = LocateNode(T->lchild,e);
    if(temp)
        return temp;
    return LocateNode(T->rchild, e);
}

status Assign(BiTree& T, KeyType e, TElemType value)
{
    //ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
    BiTree p=LocateNode(T, e);
    if(!p) return ERROR;
    BiTree duplicate = LocateNode(T,value.key);

    if (duplicate&&p!=duplicate)
        return ERROR;

    p->data = value;

    return OK;
}

BiTNode* GetSibling(BiTree T,KeyType e)
//ʵ�ֻ���ֵܽ��
{
    if(!T)
        return NULL;

    if(T->lchild&&T->lchild->data.key==e)
        return T->rchild;
    if(T->rchild&&T->rchild->data.key==e)
        return T->lchild;

    BiTree temp=GetSibling(T->lchild,e);
    if(temp)
        return temp;
    return GetSibling(T->rchild,e);
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//�����㡣��������ͨ������������������ʵ�ֱ�������
{
    BiTree temp;
    temp=LocateNode(T,e);
    if(!temp)
        return ERROR;
    if(e==c.key)
        return ERROR;

    if(LR==0)
    {
        BiTree newnode;
        newnode=(BiTree)malloc(sizeof(BiTNode));
        newnode->data=c;
        newnode->lchild=NULL;
        newnode->rchild=temp->lchild;
        temp->lchild=newnode;
        return OK;
    }
    if(LR==1)
    {
        BiTree newnode;
        newnode=(BiTree)malloc(sizeof(BiTNode));
        newnode->data=c;
        newnode->lchild=NULL;
        newnode->rchild=temp->rchild;
        temp->rchild=newnode;
        return OK;
    }
    if(LR==-1)
    {
        BiTree newnode;
        newnode=(BiTree)malloc(sizeof(BiTNode));
        newnode->data=c;
        newnode->lchild=NULL;
        newnode->rchild=T;
        T=newnode;
        return OK;
    }
}

BiTNode* GetParent(BiTree T,KeyType e)
{
    if(!T)
        return NULL;
    if(T->lchild)
    {
         if(T->lchild->data.key==e)
            return T;
    }
    if(T->rchild)
    {
        if(T->rchild->data.key==e)
            return T;
    }
    BiTree temp=GetParent(T->lchild,e);
    if(temp)
        return temp;
    return GetParent(T->rchild,e);
}

status DeleteNode(BiTree &T,KeyType e)
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
{
    BiTree temp=LocateNode(T,e);
    if(!temp)
        return ERROR;

    BiTree father=GetParent(T,e);

    if(!temp->lchild&&!temp->rchild)
    {
        if(!father)
        {
            free(temp);
            temp=NULL;
            return OK;
        }
        if(father->lchild->data.key==temp->data.key)
            father->lchild=NULL;
        if(father->rchild->data.key==temp->data.key)
            father->rchild=NULL;
        free(temp);
        temp=NULL;
        return OK;
    }
    if(temp->lchild&&!temp->rchild)
    {
        BiTree temp2=temp->lchild;
        temp->lchild=temp->lchild->lchild;
        temp->rchild=temp->lchild->rchild;
        temp->data=temp->lchild->data;
        free(temp2);
        temp2=NULL;
        return OK;
    }
    if(temp->rchild&&!temp->lchild)
    {
        BiTree temp2=temp->rchild;
        temp->lchild=temp->rchild->lchild;
        temp->data=temp->rchild->data;
        temp->rchild=temp->rchild->rchild;

        free(temp2);
        temp2=NULL;
        return OK;
    }
    if(temp->lchild&&temp->rchild)
    {
        BiTree temp2=temp->lchild;
        BiTree ptr=temp->lchild;
        while(ptr->rchild)
        {
            ptr=ptr->rchild;
        }
        ptr->rchild=temp->rchild;
        temp->rchild=temp->lchild->rchild;
        temp->data=temp->lchild->data;
        temp->lchild=temp->lchild->lchild;
        free(temp2);
        temp2=NULL;
        return OK;
    }
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T���ݹ飩
{
    if (T)
    {
        visit(T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
    }
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T���ǵݹ飩
{
    /*if(T)             //�ݹ��㷨
    {
        InOrderTraverse(T->lchild,visit);
        visit(T);
        InOrderTraverse(T->rchild,visit);
    }*/
    BiTree st[100];
    int top=0;
    do{
        while(T){
            if(top==100)
                exit(OVERFLOW);
            st[top++]=T;
            T=T->lchild;
        }

        if(top)
        {
            T=st[--top];
            visit(T);
            T=T->rchild;
        }
    }while(top||T);
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    if(T)
    {
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
        visit(T);
    }
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    BiTree temp[100];
    int inp=0;int oup=0;     //input&output

    temp[inp++]=T;

    while(inp>oup)
    {
        if(temp[oup])
        {
            visit(temp[oup]);
            temp[inp++]=temp[oup]->lchild;
            temp[inp++]=temp[oup]->rchild;
        }
        oup++;
    }
}

status PreOrderSave(BiTree T, FILE* fp)
{
    //����������������T
    if (!T) {
        fprintf(fp, "0 NULL ");
        return OK;
    } else
        fprintf(fp, "%d %s ", T->data.key, T->data.others);
    PreOrderSave(T->lchild, fp);
    PreOrderSave(T->rchild, fp);
    return OK;
}

int PreOrderLoad(BiTree f, FILE* fp, int flag)
{
    //�ļ���ȡ���򴴽�������T
    TElemType data;
    if (fscanf(fp, "%d %s", &data.key, data.others) != 2)
        return OK;
    if (data.key == 0) {
        if (flag) {
            f->rchild = NULL;
        } else {
            f->lchild = NULL;
        }
        return OK;
    }
    BiTree child = (BiTree)malloc(sizeof(BiTNode));
    child->data.key = data.key;
    strcpy(child->data.others, data.others);
    if (flag) {
        f->rchild = child;
    } else {
        f->lchild = child;
    }
    PreOrderLoad(child, fp, 0);
    PreOrderLoad(child, fp, 1);
    return OK;
}

status SaveBiTree(BiTree T, char FileName[])
{
    //���������Ľ������д�뵽�ļ�FileName��
    FILE* fp = NULL;
    if ((fp = fopen(FileName, "w")) == NULL) {
        return ERROR;
    }
    status flag = PreOrderSave(T, fp);
    fclose(fp);
    return flag;
}

status LoadBiTree(BiTree& T, char FileName[])
{
    //�����ļ�FileName�Ľ�����ݣ�����������
    /*if (T)
        return ERROR;*/
    FILE* fp = NULL;
    if ((fp = fopen(FileName, "r")) == NULL) {
        return ERROR;
    }
    TElemType data;
    fscanf(fp, "%d", &data.key);
    fscanf(fp, "%s", data.others);
    if (data.key == 0) {
        T = NULL;
        return OK;
    }
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data.key = data.key;
    strcpy(T->data.others, data.others);
    PreOrderLoad(T, fp, 0);
    PreOrderLoad(T, fp, 1);
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�����������봴�����ݡ�
{
    if(Lists.length==LISTS_INIT_SIZE)
        return ERROR;
    int i = 0;
    do {
        Lists.elem[Lists.length].name[i]=ListName[i];
    } while (ListName[i++]);

    TElemType definition[100];
    printf("���������������definition��\n");
    int ans;
    i=0;
    do {
	    scanf("%d%s",&definition[i].key,definition[i].others);
    } while (definition[i++].key!=-1);
    ans=CreateBiTree(Lists.elem[Lists.length].T,definition);
    if(ans==OK)
    {
        Lists.length++;
        return OK;
    }
    else
        return ERROR;
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
            ClearBiTree(Lists.elem[i].T);
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
