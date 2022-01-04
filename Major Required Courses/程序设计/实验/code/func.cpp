#include "func.h"
/////////////////////////初始化操作//////////////////////////////
status InitCNF(CNF &S)
{
    S.clanum=0;
    S.litnum=0;
    S.CNFhead=(ClaNode*)malloc(sizeof(ClaNode));
    return OK;
}

status InitResultList(ResList &L)
{
    L=(ResNode*)malloc(sizeof(ResNode));
    L->data=0;
    L->next=NULL;
    return OK;
}

status InitDivideList(DivideList &DL)
{
    DL=(DivideNode*)malloc(sizeof(DivideNode));
    DL->data=0;
    DL->next=NULL;
    return OK;
}

status InitMOMList(MOMList &ML,int litnum)  //MOM初始化
{
    ML=(MOMNode*)malloc(sizeof(MOMNode));
    ML->lit=0;
    ML->data=0;                              //头结点初始化

    MOMList p=ML,q;
    int i;
    for(i=1;i<=litnum;i++)
    {
        q=(MOMNode*)malloc(sizeof(MOMNode));
        q->lit=i;
        q->flag=1;
        q->data=0;
        p->next=q;
        p=q;
    }
    p->next=NULL;
    return OK;
}
///////////////////////CNF操作函数///////////////////////////////
status ShowCNF(CNF S)              //测试文件读写是否成功函数
{
    if(S.CNFhead==NULL)
        return ERROR;
    int i;
    ClaLink q=S.CNFhead;
    LitLink p;
    printf("%d %d \n",S.litnum,S.clanum);

    for(i=0;i<S.clanum;i++)
    {
        q=q->next;
        printf("%d%d %d %d ",q->data,q->flag,q->lnum,q->flagchange);
        p=q->firstlit;
        while((p=p->next)!=NULL)
            printf("%d%d ",p->litseq,p->flag);
        printf("\n");
    }
    return OK;
}

status LoadCNF(CNF &S, char FileName[])
//读入文件FileName的子句以及文字数据，创建邻接链表
{
    FILE *fp;
    char words1[20],words2[20];        //用于存放注释的数组
    int lit;                           //临时存放数字的变量
    int counter;                       //记录子句中文字数目变量
    if((fp=fopen(FileName,"r"))==NULL)
        return ERROR;
    fscanf(fp,"%s",words2);
    do
    {
        strcpy(words1,words2);
        fscanf(fp,"%s",words2);
    } while(strcmp(words1,"p")&&strcmp(words2,"cnf"));    //将c注释全部忽略直至p cnf
    fscanf(fp,"%d %d",&S.litnum,&S.clanum);         //将文字、子句数读入

    int i;                           //循环变量
    LitLink lp,ltemp;                      //用于新建的两个文字指针
    ClaLink cp,ctemp;                      //用于新建的两个子句指针


    cp=S.CNFhead;
    for(i=0;i<S.clanum;i++)                //子句读取控制
    {
        lp=(LitNode*)malloc(sizeof(LitNode));
        ctemp=(ClaNode*)malloc(sizeof(ClaNode));
        ctemp->data=i+1;
        ctemp->flag=1;
        ctemp->flagchange=0;
        ctemp->firstlit=lp;

        cp->next=ctemp;
        counter=0;
        while(fscanf(fp,"%d",&lit)&&(lit!=0))     //文字读取控制
        {
            counter++;
            ltemp=(LitNode*)malloc(sizeof(LitNode));
            ltemp->litseq=lit;
            ltemp->flag=1;
            lp->next=ltemp;
            lp=ltemp;
        }
        lp->next=NULL;
        cp=ctemp;
        cp->lnum=counter;
    }
    cp->next=NULL;
    fclose(fp);
    return OK;
}
//////////////////////////////////MOM链表操作/////////////////////////
MOMList LocateMOMNode(MOMList ML,int lit)
{
    MOMList p=ML->next;
    while(p)
    {
        if(p->lit==abs(lit))
            return p;
        p=p->next;
    }
    return NULL;
}

status MOMListAssign(MOMList &ML,CNF S)
{
    int i,j;
    double temp;
    ClaLink q=S.CNFhead;
    LitLink p;
    MOMList mp;

    for(i=0;i<S.clanum;i++)
    {
        q=q->next;
        p=q->firstlit;
        while((p=p->next)!=NULL)
        {
            mp=LocateMOMNode(ML,abs(p->litseq));
            temp=1;
            for(j=0;j<q->lnum;j++)
                temp=temp/2;
            mp->data+=temp;
        }
    }
    return OK;
    /*int i;                  //出现最多次原则
    ClaLink q=S.CNFhead;
    LitLink p;
    MOMList mp;

    for(i=0;i<S.clanum;i++)
    {
        q=q->next;
        p=q->firstlit;
        while((p=p->next)!=NULL)
        {
            mp=LocateMOMNode(ML,abs(p->litseq));
            mp->data++;
        }
    }
    return OK;*/
}

status LiteraltoMOM(MOMList &ML,int lit)     //将MOM链表中文字设为已清除
{
    MOMList mp=LocateMOMNode(ML,abs(lit));
    mp->flag=0;                   //表示该文字已被清除
    return 0;
}

status LiteraloffMOM(MOMList &ML,int lit)     //将MOM链表中文字设为未清除
{
    MOMList mp=LocateMOMNode(ML,abs(lit));
    mp->flag=1;                   //表示该文字未被清除
    return 0;
}

status MOMListTraverse(MOMList ML)
{
    if(ML==NULL)
        return INFEASIBLE;
    MOMList p=ML->next;
    if(p==NULL)
        return OK;
    while(p)
    {
        printf("%d %f %d ",p->lit,p->data,p->flag);
        p=p->next;
    }
    printf("\n");
    return OK;
}
///////////////////////////////////////结果链表操作函数//////////////////////
status InsertResNode(ResList &L,int lit)
{
    ResList p=L,q;
    while((p->next!=NULL))
        p=p->next;
    q=(ResNode*)malloc(sizeof(ResNode));
    q->data=lit;
    q->next=NULL;
    p->next=q;
    L->data++;
    return OK;
}

int RecallResList(ResList &L)
{
    int ret;
    ResList q=L,p=q->next;
    while(p->next)
    {
        q=p;
        p=p->next;
    }
    ret=p->data;
    free(p);
    q->next=NULL;
    L->data--;
    return ret;
}

status ResListTraverse(ResList L)
// 如果结果表存在，依次显示元素，每个元素间空一格，返回OK；如果表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    ResList p=L->next;
    if(p==NULL)
        return OK;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}
////////////////////////DivideList操作函数/////////////////////
status PushDivideNode(DivideList &L,int lit)
{
    DivideList p=L,q;
    while((p->next!=NULL))
        p=p->next;
    q=(DivideNode*)malloc(sizeof(DivideNode));
    q->data=lit;
    q->next=NULL;
    p->next=q;
    return OK;
}

int PopDivideList(DivideList &L)
{
    int ret;
    DivideList q=L,p=q->next;
    while(p->next)
    {
        q=p;
        p=p->next;
    }
    ret=p->data;
    free(p);
    q->next=NULL;
    return ret;
}

status DivideListTraverse(DivideList L)
// 如果表存在，依次显示元素，每个元素间空一格，返回OK；如果表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    DivideList p=L->next;
    if(p==NULL)
        return OK;
    printf("dividelist:");
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}
///////////////////////////////CNF子句文字操作函数////////////////////////
ClaLink LocateClause(CNF S,int cla)
{
    ClaLink cp=S.CNFhead;
    int i;
    for(i=1;i<=S.clanum;i++)
    {
        cp=cp->next;
        if(i==cla)
            return cp;
    }
    return NULL;
}

status IsUnitClause(ClaLink C)    //判断目标子句是否为单子句，是则返回TRUE，否则返回FALSE
{
    if(C->data==0)
        return FALSE;
    if(C->lnum==1)
        return OK;
    return FALSE;
}

int LocateUnitClause(CNF S)     //查找并定位单子句,查找成功便返回子句序号，失败则返回ERROR
{
    ClaLink p=S.CNFhead;
    int i;
    for(i=1;i<=S.clanum;i++)
    {
        p=p->next;
        if(p->flag==0)
            continue;
        if(IsUnitClause(p))
            return i;
    }
    return ERROR;
}

status DestroyClause(CNF &S,int cla,int lit)  //目标子句flag设为0
{
    if(cla<1||cla>S.clanum)
        return INFEASIBLE;
    ClaLink cp;
    cp=LocateClause(S,cla);
    if(cp&&cp->flag!=0)
    {
        cp->flag=0;
        cp->flagchange=lit;
        return OK;
    }
    return ERROR;
}

status ExistNonClause(CNF S)                //是否存在空子句
{
    ClaLink p=S.CNFhead;
    int i;
    for(i=0;i<S.clanum;i++)
    {
        p=p->next;
        if(p->lnum==0&&p->flag==1)
            return i+1;
    }
    return FALSE;
}

status AddClausetoLast(CNF &S,int lit)
{
    ClaLink cp1=LocateClause(S,S.clanum);
    ClaLink cp2;
    LitLink lp;
    S.clanum++;
    cp2=(ClaNode*)malloc(sizeof(ClaNode));
    cp2->data=S.clanum;
    cp2->flag=1;
    cp2->lnum=1;
    lp=(LitNode*)malloc(sizeof(LitNode));
    lp->next=NULL;
    lp->litseq=lit;
    lp->flag=1;
    cp2->firstlit=(LitNode*)malloc(sizeof(LitNode));
    cp2->firstlit->next=lp;
    cp1->next=cp2;
    return OK;
}

status RemoveLastClause(CNF &S)
{
    ClaLink cp1=LocateClause(S,S.clanum-1);
    free(cp1->next);
    cp1->next=NULL;
    S.clanum--;
    return OK;
}

int FindFirstLiteral(ClaLink L)
{
    LitLink p=L->firstlit->next;
    while(p)
    {
        if(p->flag==1)
            return p->litseq;
        p=p->next;
    }
    return ERROR;
}

status ExistClause(CNF S)
{
    int i;
    ClaLink cp;

    for(i=1;i<=S.clanum;i++)
    {
        cp=LocateClause(S,i);
        if(cp->flag==1&&cp->lnum!=0)
            return TRUE;
    }
    return FALSE;
}

status ClearLiteral(CNF &S,int lit)   //单子句规则实现，传入lit为文字值，执行完后返回OK
{
    int i;
    LitLink lp1;
    ClaLink cp1=S.CNFhead;

    for(i=1;i<=S.clanum;i++)
    {
        cp1=LocateClause(S,i);
        if(cp1==NULL)
            break;
        lp1=cp1->firstlit;
        while((lp1=lp1->next)!=NULL)
        {
            if(lp1->litseq==-lit)           //包含文字非L的状况
            {
                lp1->flag=0;
                cp1->lnum--;
                break;
            }
            if(lp1->litseq==lit)
            {
                DestroyClause(S,cp1->data,lit);
                break;
            }
        }
    }
    return OK;
}
/////////////////////////////分裂策略函数/////////////////////////////////
int SimpleDivideStrategy(ResList L,CNF S)
//简单的分裂策略：选取第一个未在结果链表中出现的文字作为分裂策略
{
    ResList p;
    int i;
    for(i=1;i<=S.litnum;i++)
    {
        p=L->next;
        while(p)
        {
            if(p->data==i||p->data==-i)
                break;
            p=p->next;
        }
        if(p==NULL)
            return -i;
    }
    return 0;
}

int MOMDivideStrategy(ResList L,CNF S,MOMList ML)
//最短子句出现频率最大优先
{
    MOMList mp=ML->next;
    while(mp)
    {
        if(mp->flag)
            return mp->lit;
        mp=mp->next;
    }
    return 0;
}
/////////////////////////////////回溯操作函数///////////////////////
status MOMBacktracking(CNF &S,ResList &L,MOMList &ML,int lit)          //总回溯流程
{
    int temp=0;
    while(temp!=lit)
    {
        temp=RecallResList(L);
        RecallCNF(S,temp);
        LiteraloffMOM(ML,temp);
    }
    return OK;
}

int BacktrackingbyLoop(CNF &S,ResList &L,MOMList &ML,DivideList &DL)          //总回溯流程
{
    int temp=0;
    int lit=PopDivideList(DL);
    while(temp!=lit)
    {
        temp=RecallResList(L);
        RecallCNF(S,temp);
        LiteraloffMOM(ML,temp);
    }
    return lit;
}

status Backtracking(CNF &S,ResList &L,int lit)          //总回溯流程（改进前
{
    int temp=0;
    int i;
    ClaLink cp;
    while(temp!=lit)
    {
        temp=RecallResList(L);
        RecallCNF(S,temp);
    }

    for(i=S.clanum;i>0;i--)
    {
        cp=LocateClause(S,i);
        if(FindFirstLiteral(cp)==lit)
        {
            RemoveLastClause(S);
            break;
        }
        RemoveLastClause(S);
    }
    return OK;
}

status RecallCNF(CNF &S,int lit)
{
    int i;
    ClaLink q=S.CNFhead;
    LitLink p;

    for(i=0;i<S.clanum;i++)
    {
        q=q->next;
        p=q->firstlit;
        while((p=p->next)!=NULL)
        {
            if(p->litseq==-lit)
            {
                p->flag=1;
                q->lnum++;
                break;
            }
            if(p->litseq==lit&&q->flagchange==lit)
            {
                q->flag=1;
                break;
            }
        }
    }
    return OK;
}

///////////////////////DPLL求解部分//////////////////////////
status DPLLbyLoop(CNF &S,ResList &L,MOMList &ML,DivideList &DL)       //非递归实现DPLL
{
    int cla,lit;
    ClaLink cp;
    int temp;
    int flag;
    while(ExistClause(S))
    {
        flag=1;
        while(cla=LocateUnitClause(S))
        {
            cp=LocateClause(S,cla);
            lit=FindFirstLiteral(cp);
            ClearLiteral(S,lit);
            InsertResNode(L,lit);
            LiteraltoMOM(ML,lit);
            if(ExistNonClause(S))
            {
                lit=BacktrackingbyLoop(S,L,ML,DL);
                if(L->next==NULL)
                    return FALSE;
                ClearLiteral(S,-lit);
                InsertResNode(L,-lit);
                LiteraltoMOM(ML,lit);
                flag=0;
                break;
            }
            if(ExistClause(S)==0)
                return OK;
        }

        if(flag==1)
        {
            lit=MOMDivideStrategy(L,S,ML);
            PushDivideNode(DL,lit);
            ClearLiteral(S,lit);
            InsertResNode(L,lit);
            LiteraltoMOM(ML,lit);
        }

    }
    return OK;
}

status MOMDPLL(CNF &S,ResList &L,MOMList &ML)                //升级DPLL算法
//传入CNF，结果链表L，MOM排序表ML，分裂策略传递文字literal
{
    int cla=LocateUnitClause(S),lit;
    int i;
    ClaLink cp;
    int temp;                    //状态储存变量
    while(cla)
    {
        cp=LocateClause(S,cla);
        lit=FindFirstLiteral(cp);
        ClearLiteral(S,lit);                   //清除文字
        InsertResNode(L,lit);                  //结果链表中插入已清除文字
        LiteraltoMOM(ML,lit);
        if(ExistClause(S)==0)
            return TRUE;
        else if(i=ExistNonClause(S))
            return FALSE;
        cla=LocateUnitClause(S);
    }
    lit=MOMDivideStrategy(L,S,ML);
    ClearLiteral(S,lit);
    InsertResNode(L,lit);
    LiteraltoMOM(ML,lit);
    temp=MOMDPLL(S,L,ML);
    if(temp)
        return TRUE;
    MOMBacktracking(S,L,ML,lit);
    ClearLiteral(S,-lit);
    InsertResNode(L,-lit);
    LiteraltoMOM(ML,-lit);
    return MOMDPLL(S,L,ML);
}

status DPLL(CNF &S,ResList &L)                //初级DPLL算法
{
    int cla=LocateUnitClause(S),lit;
    ClaLink cp;
    int temp;                    //状态储存变量
    while(cla)
    {
        cp=LocateClause(S,cla);
        lit=FindFirstLiteral(cp);
        ClearLiteral(S,lit);
        InsertResNode(L,lit);
        if(ExistClause(S)==0)
            return TRUE;
        else if(ExistNonClause(S))
            return FALSE;
        cla=LocateUnitClause(S);
    }
    lit=SimpleDivideStrategy(L,S);
    AddClausetoLast(S,lit);
    temp=DPLL(S,L);
    if(temp)
        return TRUE;
    Backtracking(S,L,lit);
    AddClausetoLast(S,-lit);
    return DPLL(S,L);
}

/////////////////////////////////排序算法///////////////////////////////////
void BubbleSortR(ResList &List)
{
    ResList p,q,tail;

    tail = NULL;

    while((List->next->next) != tail)
    {
        p = List;
        q = List->next;
        while(q->next != tail)
        {
            if(abs(q->data) > abs(q->next->data))
            {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
                q = p->next;
            }
            q = q->next;
            p = p->next;
        }
        tail = q;
    }
}

void BubbleSortM(MOMList &List)
{
    MOMList p,q,tail;

    tail = NULL;

    while((List->next->next) != tail)
    {
        p = List;
        q = List->next;
        while(q->next != tail)
        {
            if(q->data < q->next->data)
            {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
                q = p->next;
            }
            q = q->next;
            p = p->next;
        }
        tail = q;
    }
}
//////////////////////////////////////结果输出函数//////////////////////////
status ResultPrint(ResList L,int satisfy)
{
    printf("s %d\n",satisfy);
    printf("v ");
    BubbleSortR(L);
    printf("t ");
    ResListTraverse(L);
    return OK;
}

int ResWrite(int satisfy,double time,ResList L,char filename[])
{
    ResList p=L->next;
    int i=1;
    while(filename[i]!='\0') i++;
	filename[i-3]='r';    //只改变文件的扩展名
	filename[i-2]='e';
	filename[i-1]='s';
	FILE *fp;
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("打开文件失败\n");
		return ERROR;
	}
	fprintf(fp,"s %d\n",satisfy);    //res是求解结果，1表示满足，0表示不满足，-1未定
	fprintf(fp,"v\n");
	while(p)
    {
        i++;
        if(i%10==0)  fprintf(fp,"\n");
        fprintf(fp,"%5d",p->data);
        p=p->next;
    }
	fprintf(fp,"\nt %f ms\n",time);
	fclose(fp);
	return OK;
}
