#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include"def.h"
#include "string.h"

int hasDuplicates(TElemType* definition);

status CreateBiTree(BiTree &T,TElemType definition[]);

status ClearBiTree(BiTree &T);

int BiTreeDepth(BiTree T);

BiTNode* LocateNode(BiTree T,KeyType e);

status Assign(BiTree& T, KeyType e, TElemType value);

BiTNode* GetSibling(BiTree T,KeyType e);

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);

BiTNode* GetParent(BiTree T,KeyType e);

status DeleteNode(BiTree &T,KeyType e);

status PreOrderTraverse(BiTree T,void (*visit)(BiTree));

status InOrderTraverse(BiTree T,void (*visit)(BiTree));

status PostOrderTraverse(BiTree T,void (*visit)(BiTree));

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));

status PreOrderSave(BiTree T, FILE* fp);

int PreOrderLoad(BiTree f, FILE* fp, int flag) ;

status SaveBiTree(BiTree T, char FileName[]);

status LoadBiTree(BiTree& T, char FileName[]);

void visit(BiTree T);

status AddList(LISTS &Lists,char ListName[]);

status RemoveList(LISTS &Lists,char ListName[]);

int LocateList(LISTS Lists,char ListName[]);


#endif // FUNC_H_INCLUDED
