#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;             //状态返回值

typedef struct LitNode{         //文字结点类型定义
    int litseq;                 //顶点位置文字序号
    status flag;                //文字状态
    LitNode *next;    //下一个文字结点指针
} LitNode,*LitLink;

typedef struct ClaNode{         //子句结点类型定义
    int data;                   //顶点信息
    status flag;                //子句状态
    int flagchange;             //用于记录子句状态被哪个文字修改
    int lnum;                   //统计子句中文字数目
    LitNode *firstlit;          //指向第一个文字
    ClaNode *next;           //指向下一个子句
} ClaNode,*ClaLink;             //CNF头结点以及结点指针

typedef struct {               //CNF头结点的类型定义
    ClaLink CNFhead;           //头结点指针且其firstlit用于存放最终赋值结果
    int clanum,litnum;          //子句数、文字数
} CNF;

typedef struct ResNode{        //结果存储链表
    int data;
    ResNode *next;
}ResNode,*ResList;

typedef struct MOMNode{        //MOM计算链表
    int lit;
    status flag;
    double data;
    MOMNode *next;
}MOMNode,*MOMList;

typedef struct DivideNode{        //分裂策略存储链表栈
    int data;
    DivideNode *next;
}DivideNode,*DivideList;
#endif // DEF_H_INCLUDED
