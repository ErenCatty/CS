#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include"def.h"
#include "string.h"


int hasDuplicate(ALGraph G,KeyType u);

void visit(VertexType v);

void ShowGragh(ALGraph G);

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);

status DestroyGraph(ALGraph &G);

int LocateVex(ALGraph G,KeyType u);

status PutVex(ALGraph &G,KeyType u,VertexType value);

int FirstAdjVex(ALGraph G,KeyType u);

int NextAdjVex(ALGraph G,KeyType v,KeyType w);

status InsertVex(ALGraph &G,VertexType v);

int ArcDetect(ALGraph G,KeyType v,KeyType w);

int DeleteArcNode(ALGraph &G,KeyType v,KeyType w);

status DeleteArc(ALGraph &G,KeyType v,KeyType w);

status DeleteVex(ALGraph &G,KeyType v);

status InsertArc(ALGraph &G,KeyType v,KeyType w);

status DeleteArc(ALGraph &G,KeyType v,KeyType w);

void DFS(ALGraph G,int i,void (*visit)(VertexType));

status DFSTraverse(ALGraph &G,void (*visit)(VertexType));

status BFSTraverse(ALGraph &G,void (*visit)(VertexType));

status SaveGraph(ALGraph G, char FileName[]);

status LoadGraph(ALGraph &G, char FileName[]);

int GraghsLength(GraghsLink Graghs);

status GraghsAdd(GraghsLink &Graghs,char ListName[]);

status GraghsTraverse(GraghsLink Graghs);

status GraghsRemove(GraghsLink &Graghs,char ListName[]);

GraghsLink GraghsLocate(GraghsLink Graghs,char ListName[]);

#endif // FUNC_H_INCLUDED
