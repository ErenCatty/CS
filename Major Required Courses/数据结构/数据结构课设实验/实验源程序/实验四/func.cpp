#include "func.h"


int hasDuplicate(ALGraph G,KeyType u)     //���غ���
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==u)
            return 0;
    }
    return 1;
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

void ShowGragh(ALGraph G)
{
    int i;
    for(i=0;i<G.vexnum;i++)
	{
         ArcNode *p=G.vertices[i].firstarc;
         printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
         while (p)
         {
             printf(" %d",p->adjvex);
             p=p->nextarc;
         }
         printf("\n");
	}
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    int i=0,j,one,two;
    int a[100]={0};         //��¼�Ƿ����ظ�����δ���ֹ��Ľ��

    while(V[i].key!=-1)
    {
        a[V[i].key]++;
        if(a[V[i].key]>1)
            return ERROR;
        i++;
        if(i>MAX_VERTEX_NUM)
            return ERROR;
    }
    i=0;

    do {
        G.vertices[i].data=V[i];
        G.vertices[i].firstarc=NULL;
    } while (V[i++].key!=-1);
    G.vexnum=i-1;
    i=0;
    while (VR[i][0]!=-1)
    {
        if(a[VR[i][0]]!=1||a[VR[i][1]]!=1)
            return ERROR;
        ArcNode *p;
        for(j=0;j<G.vexnum;j++)
            if (VR[i][0]==G.vertices[j].data.key)
            {
                one=j; break;
            }
        for(j=0;j<G.vexnum;j++)
            if (VR[i][1]==G.vertices[j].data.key)
            {
                two=j; break;
            }
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=two;p->nextarc=G.vertices[one].firstarc;G.vertices[one].firstarc=p;
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=one;p->nextarc=G.vertices[two].firstarc;G.vertices[two].firstarc=p;
        i++;
    }
    G.arcnum=i;
    return OK;
}

status DestroyGraph(ALGraph &G)
/*��������ͼG*/
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        free(G.vertices[i].firstarc);
        G.vertices[i].firstarc=NULL;
    }
    G.vexnum=0;
    G.arcnum=0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==u)
            return i;
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    int i;
    if(hasDuplicate(G,value.key)==0)
        return ERROR;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==u)
        {
            G.vertices[i].data=value;
            return OK;
        }
    }
    return ERROR;
}

int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int loc=LocateVex(G,u);
    if(loc==-1)
        return -1;
    if(G.vertices[loc].firstarc==NULL)
        return -1;
    return G.vertices[loc].firstarc->adjvex;
    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����v��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    int loc=LocateVex(G,v);
    if(loc==-1)
        return -1;
    int loc1=LocateVex(G,w);
    if(loc1==-1)
        return -1;

    ArcNode* temp=G.vertices[loc].firstarc;
    while(loc1!=temp->adjvex)
        temp=temp->nextarc;
    if(!temp||!temp->nextarc)
        return -1;
    return temp->nextarc->adjvex;
}

status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    if(hasDuplicate(G,v.key)==0)
        return ERROR;
    if(MAX_VERTEX_NUM==G.vexnum)
        return ERROR;
    G.vertices[G.vexnum].data=v;
    G.vertices[G.vexnum].firstarc=NULL;
    G.vexnum++;
    return OK;
}

int ArcDetect(ALGraph G,KeyType v,KeyType w)
{                       //v��wΪ����ֵ���ǹؼ���
    ArcNode *det;
    det=G.vertices[v].firstarc;
    while(det)
    {
        if(det->adjvex==w)
            return OK;
        det=det->nextarc;
    }
    return ERROR;
}

int DeleteArcNode(ALGraph &G,KeyType v,KeyType w)
{                          //v��wΪ����ֵ���ǹؼ���
    ArcNode *p,*q;
    p=G.vertices[v].firstarc;
    if(p->adjvex==w)
    {
        G.vertices[v].firstarc=p->nextarc;
        free(p);
        p=NULL;
        return OK;
    }
    q=p;p=p->nextarc;
    while(p)
    {
        if(p->adjvex==w)
        {
            q->nextarc=p->nextarc;
            free(p);
            p=NULL;
            return OK;
        }
        q=p;p=p->nextarc;
    }
    return ERROR;
}

status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    int loc=LocateVex(G,v);
    if(loc==-1)
        return ERROR;
    if(G.vexnum<=1)
        return ERROR;
    int i;

    for(i=0;i<G.vexnum;i++)       //ɾ��������ػ�
        DeleteArc(G,v,G.vertices[i].data.key);

    ArcNode *p;
    for(i=0;i<G.vexnum;i++)           //������ָ����ǰ��
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            if(p->adjvex>loc)
                p->adjvex--;
            p=p->nextarc;
        }
    }

    for(i=loc;i<G.vexnum-1;i++)         //����㲹��ȱ��
        G.vertices[i]=G.vertices[i+1];
    G.vexnum--;
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int loc1=LocateVex(G,v);
    int loc2=LocateVex(G,w);
    if(loc1==-1||loc2==-1)
        return ERROR;
    ArcNode *p,*q;
    if(ArcDetect(G,loc1,loc2))
        return ERROR;

    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=loc2;
    p->nextarc=G.vertices[loc1].firstarc;
    G.vertices[loc1].firstarc=p;
    q=(ArcNode*)malloc(sizeof(ArcNode));
    q->adjvex=loc1;
    q->nextarc=G.vertices[loc2].firstarc;
    G.vertices[loc2].firstarc=q;
    G.arcnum++;
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int loc1=LocateVex(G,v);
    int loc2=LocateVex(G,w);
    if(loc1==-1||loc2==-1)
        return ERROR;

    if(!ArcDetect(G,loc1,loc2))
        return ERROR;

    if(DeleteArcNode(G,loc1,loc2)&&DeleteArcNode(G,loc2,loc1))
        return OK;
    return ERROR;
}

int visited[MAX_VERTEX_NUM];

void DFS(ALGraph G,int i,void (*visit)(VertexType))
{
    visited[i]=1;
    visit(G.vertices[i].data);
    int j;
    for(j=FirstAdjVex(G,G.vertices[i].data.key);j>=0;j=NextAdjVex(G,G.vertices[i].data.key,G.vertices[j].data.key))
        if(!visited[j])
            DFS(G,j,visit);
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int i;
    for(i=0;i<G.vexnum;i++)
        visited[i]=0;
    for(i=0;i<G.vexnum;i++)
        if(!visited[i])
            DFS(G,i,visit);
    return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int visited[MAX_VERTEX_NUM];
    int i,j;
    for(i=0;i<G.vexnum;i++)
        visited[i]=0;
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i])
            visit(G.vertices[i].data);
        visited[i]=1;
        for(j=FirstAdjVex(G,G.vertices[i].data.key);j>=0;j=NextAdjVex(G,G.vertices[i].data.key,G.vertices[j].data.key))
            if(!visited[j])
            {
                visit(G.vertices[j].data);
                visited[j]=1;
            }
    }
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    FILE *fp1;
    fp1=fopen(FileName,"w+");
    int i,j;
    int loc1,loc2;
    for(i=0;i<G.vexnum;i++)
        fprintf(fp1,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
    fprintf(fp1,"-1 nil ");
    int a[MAX_VERTEX_NUM]={0};
    for(i=0;i<G.vexnum;i++)
        a[G.vertices[i].data.key]=1;
    for(i=0;i<MAX_VERTEX_NUM-1;i++)
        if(a[i])
            for(j=i+1;j<MAX_VERTEX_NUM;j++)
                if(a[j])
                {
                    loc1=LocateVex(G,i);
                    loc2=LocateVex(G,j);
                    if(ArcDetect(G,loc1,loc2))
                        fprintf(fp1,"%d %d ",i,j);
                }

    fprintf(fp1,"-1 -1");
    fclose(fp1);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    FILE *fp2;
    if((fp2=fopen(FileName,"r"))==NULL)
        return ERROR;
    VertexType V[21];
    KeyType VR[100][2];
    int i=0;
    do {
        fscanf(fp2,"%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        fscanf(fp2,"%d%d",&VR[i][0],&VR[i][1]);
    } while(VR[i++][0]!=-1);
    if (CreateGraph(G,V,VR)==ERROR)
    {
        printf("�������ݴ��޷�����");
        return ERROR;
    }
    fclose(fp2);
    return OK;
}

status CreateGraph1(ALGraph &G)
{
    VertexType V[21];
    KeyType VR[100][2];
    int i=0;
    do {
        scanf("%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        scanf("%d%d",&VR[i][0],&VR[i][1]);
    } while(VR[i++][0]!=-1);
    if (CreateGraph(G,V,VR)==ERROR)
    {
        printf("�������ݴ��޷�����");
        return ERROR;
    }
    return OK;
}

status GraghsAdd(GraghsLink &Graghs,char ListName[])
{
    GraghsLink p =Graghs;
    int i=0;

    while (p->next)
        p=p->next;
    GraghsLink temp;
    temp=(GraghsLink)malloc(sizeof(GraghNode));
    do {
        temp->name[i]=ListName[i];
    } while (ListName[i++]);
    temp->next=NULL;
    printf("����ͼ���ݼ���\n");
    printf("�Ƽ����Լ���5 ���Ա� 8 ���� 7 ������ 6 ����ͼ -1 nil 5 6 5 7 6 7 7 8 -1 -1\n");
    if(!CreateGraph1(temp->G))
        return ERROR;
    p->next=temp;
    return OK;
}

status GraghsRemove(GraghsLink &Graghs,char ListName[])
{
    if(Graghs==NULL)
        return INFEASIBLE;
    GraghsLink p=Graghs->next,q=Graghs;
    int j,flag;          //ѭ������
    char ch;

    while(p)
    {
        j=0;
        flag=1;
        while(ch=ListName[j])                        //�ж����Ա����Ƿ����Ҫ��
        {
            if(p->name[j]!=ch)
                flag=0;
            j++;
        }
        if(flag==1)
        {
            DestroyGraph(p->G);
            q->next=p->next;
            free(p);
            return OK;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
    if(p==NULL)
        return ERROR;
}

GraghsLink GraghsLocate(GraghsLink Graghs,char ListName[])
{
    if(Graghs==NULL)
        return NULL;
    GraghsLink p=Graghs->next;
    int j,flag;
    char ch;

    while(p)
    {
        j=0;
        flag=1;
        while(ch=ListName[j])
        {
            if(p->name[j]!=ch)
                flag=0;
            j++;
        }
        if(flag==1)
            return p;

        p=p->next;
    }
    if(p==NULL)
        return NULL;
}

int GraghsLength(GraghsLink Graghs)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(Graghs==NULL)
        return INFEASIBLE;
    GraghsLink p=Graghs;
    int i=0;     //ѭ����������
    while(p)
    {
        p=p->next;
        i++;
    }
    return i-1;
}

status GraghsTraverse(GraghsLink Graghs)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(Graghs==NULL)
        return INFEASIBLE;
    GraghsLink p=Graghs->next;
    if(p==NULL)
        return OK;
    while(p)
    {
        printf("%s ",p->name);
        p=p->next;
    }
    return OK;
}
