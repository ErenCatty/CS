#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include"def.h"
#include "string.h"
#include <time.h>

/////////////////////////初始化操作//////////////////////////////
status InitCNF(CNF &S);

status InitResultList(ResList &L);

status InitDivideList(DivideList &DL);

status InitMOMList(MOMList &ML,int litnum);
///////////////////////CNF操作函数///////////////////////////////
status ShowCNF(CNF S);

status LoadCNF(CNF &S, char FileName[]);
//////////////////////////////////MOM链表操作/////////////////////////
MOMList LocateMOMNode(MOMList ML,int lit);

status MOMListAssign(MOMList &ML,CNF S);

status LiteraltoMOM(MOMList &ML,int lit) ;

status LiteraloffMOM(MOMList &ML,int lit) ;

status MOMListTraverse(MOMList ML);
///////////////////////////////////////结果链表操作函数//////////////////////
status InsertResNode(ResList &L,int lit);

int RecallResList(ResList &L);

status ResListTraverse(ResList L);
////////////////////////DivideList操作函数/////////////////////
status PushDivideNode(DivideList &L,int lit);

int PopDivideList(DivideList &L);

status DivideListTraverse(DivideList L);
///////////////////////////////CNF子句文字操作函数////////////////////////
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
/////////////////////////////分裂策略函数/////////////////////////////////
int SimpleDivideStrategy(ResList L,CNF S);

int MOMDivideStrategy(ResList L,CNF S,MOMList ML);
/////////////////////////////////回溯操作函数///////////////////////
status MOMBacktracking(CNF &S,ResList &L,MOMList &ML,int lit);

int BacktrackingbyLoop(CNF &S,ResList &L,MOMList &ML,DivideList &DL) ;

status Backtracking(CNF &S,ResList &L,int lit);

status RecallCNF(CNF &S,int lit);
///////////////////////DPLL求解部分//////////////////////////
status DPLLbyLoop(CNF &S,ResList &L,MOMList &ML,DivideList &DL);

status MOMDPLL(CNF &S,ResList &L,MOMList &ML) ;

status DPLL(CNF &S,ResList &L)   ;
/////////////////////////////////排序算法///////////////////////////////////
void BubbleSortR(ResList &List);

void BubbleSortM(MOMList &List);
//////////////////////////////////////结果输出函数//////////////////////////
status ResultPrint(ResList L,int satisfy);

int ResWrite(int satisfy,double time,ResList L,char filename[]);
/////////////////////////////////////数独部分函数/////////////
status LoadSudoku4(int sudoku4[][4], char FileName[]);

status PrintSudodu4(int sudoku4[][4]);

status Sudoku4toCNF(int sudoku4[][4],char FileName[]);

status LoadSudoku6(int sudoku6[][6], char FileName[]);

status PrintSudodu6(int sudoku6[][6]);

status Sudoku6toCNF(int sudoku6[][6],char FileName[]);

status PuzzleResult(ResList L,int kind);

#endif // FUNC_H_INCLUDED
