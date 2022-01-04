#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;             //״̬����ֵ

typedef struct LitNode{         //���ֽ�����Ͷ���
    int litseq;                 //����λ���������
    status flag;                //����״̬
    LitNode *next;    //��һ�����ֽ��ָ��
} LitNode,*LitLink;

typedef struct ClaNode{         //�Ӿ������Ͷ���
    int data;                   //������Ϣ
    status flag;                //�Ӿ�״̬
    int flagchange;             //���ڼ�¼�Ӿ�״̬���ĸ������޸�
    int lnum;                   //ͳ���Ӿ���������Ŀ
    LitNode *firstlit;          //ָ���һ������
    ClaNode *next;           //ָ����һ���Ӿ�
} ClaNode,*ClaLink;             //CNFͷ����Լ����ָ��

typedef struct {               //CNFͷ�������Ͷ���
    ClaLink CNFhead;           //ͷ���ָ������firstlit���ڴ�����ո�ֵ���
    int clanum,litnum;          //�Ӿ�����������
} CNF;

typedef struct ResNode{        //����洢����
    int data;
    ResNode *next;
}ResNode,*ResList;

typedef struct MOMNode{        //MOM��������
    int lit;
    status flag;
    double data;
    MOMNode *next;
}MOMNode,*MOMList;

typedef struct DivideNode{        //���Ѳ��Դ洢����ջ
    int data;
    DivideNode *next;
}DivideNode,*DivideList;
#endif // DEF_H_INCLUDED
