#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include"def.h"
#include "string.h"
#include <time.h>

/////////////////////////��ʼ������//////////////////////////////
status InitCNF(CNF &S);

status InitResultList(ResList &L);

status InitDivideList(DivideList &DL);

status InitMOMList(MOMList &ML,int litnum);
///////////////////////CNF��������///////////////////////////////
status ShowCNF(CNF S);

status LoadCNF(CNF &S, char FileName[]);
//////////////////////////////////MOM�������/////////////////////////
MOMList LocateMOMNode(MOMList ML,int lit);

status MOMListAssign(MOMList &ML,CNF S);

status LiteraltoMOM(MOMList &ML,int lit) ;

status LiteraloffMOM(MOMList &ML,int lit) ;

status MOMListTraverse(MOMList ML);
///////////////////////////////////////��������������//////////////////////
status InsertResNode(ResList &L,int lit);

int RecallResList(ResList &L);

status ResListTraverse(ResList L);
////////////////////////DivideList��������/////////////////////
status PushDivideNode(DivideList &L,int lit);

int PopDivideList(DivideList &L);

status DivideListTraverse(DivideList L);
///////////////////////////////CNF�Ӿ����ֲ�������////////////////////////
ClaLink LocateClause(CNF S,int cla);

status IsUnitClause(ClaLink C) ;

int LocateUnitClause(CNF S);

status DestroyClause(CNF &S,int cla,int lit);

status ExistNonClause(CNF S) ;

status AddClausetoLast(CNF &S,int lit);

status RemoveLastClause(CNF &S);

int FindFirstLiteral(ClaLink L);

status ExistClause(CNF S);

status ClearLiteral(CNF &S,int lit);
/////////////////////////////���Ѳ��Ժ���/////////////////////////////////
int SimpleDivideStrategy(ResList L,CNF S);

int MOMDivideStrategy(ResList L,CNF S,MOMList ML);
/////////////////////////////////���ݲ�������///////////////////////
status MOMBacktracking(CNF &S,ResList &L,MOMList &ML,int lit);

int BacktrackingbyLoop(CNF &S,ResList &L,MOMList &ML,DivideList &DL) ;

status Backtracking(CNF &S,ResList &L,int lit);

status RecallCNF(CNF &S,int lit);
///////////////////////DPLL��ⲿ��//////////////////////////
status DPLLbyLoop(CNF &S,ResList &L,MOMList &ML,DivideList &DL);

status MOMDPLL(CNF &S,ResList &L,MOMList &ML) ;

status DPLL(CNF &S,ResList &L)   ;
/////////////////////////////////�����㷨///////////////////////////////////
void BubbleSortR(ResList &List);

void BubbleSortM(MOMList &List);
//////////////////////////////////////����������//////////////////////////
status ResultPrint(ResList L,int satisfy);

int ResWrite(int satisfy,double time,ResList L,char filename[]);
/////////////////////////////////////�������ֺ���/////////////
status LoadSudoku4(int sudoku4[][4], char FileName[]);

status PrintSudodu4(int sudoku4[][4]);

status Sudoku4toCNF(int sudoku4[][4],char FileName[]);

status LoadSudoku6(int sudoku6[][6], char FileName[]);

status PrintSudodu6(int sudoku6[][6]);

status Sudoku6toCNF(int sudoku6[][6],char FileName[]);

status PuzzleResult(ResList L,int kind);

#endif // FUNC_H_INCLUDED
