#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define LISTS_INIT_SIZE 10
typedef int ElemType;
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;

typedef struct{
struct{
    char name[30];
    LinkList L;
    }elem[LISTS_INIT_SIZE];
    int length;                   //��Ϊ�Ѿ�ȷ��elem[10]�����Գ����Ѿ�ȷ��Ϊ10.
    int listsize;
}LISTS;

#endif // FUNC_H_INCLUDED
