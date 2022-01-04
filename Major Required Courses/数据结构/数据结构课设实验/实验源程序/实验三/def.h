#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LISTS_INIT_SIZE 10

typedef int status;
typedef int KeyType;

typedef struct {
     KeyType  key;
     char others[20];
} TElemType; //������������Ͷ���

typedef struct BiTNode{    //����������Ķ���
      TElemType data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct{
struct{
    char name[30];
    BiTree T;
    }elem[LISTS_INIT_SIZE];
    int length;                   //��Ϊ�Ѿ�ȷ��elem[10]�����Գ����Ѿ�ȷ��Ϊ10.
    int listsize;
}LISTS;


#endif // DEF_H_INCLUDED
