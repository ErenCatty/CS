#include"func.h"

int main()
{
    int op=1;
    char filename[20];        //cnf文件名存储
    char sudokuname[20]="sudoku2.txt";      //数读文件名存储
    char sudokucnf[20]="sudoku2.cnf";
    CNF S;                     //储存cnf
    DivideList DL;             //分裂结点链表栈
    ResList RL;             //结果储存
    MOMList ML;                //MOM链表
    int sudoku4[4][4];      //记录四阶数独
    int sudoku6[6][6];      //记录六阶数独
    int sudokind=0;           //记录选择数独种类
    int satisfy;               //DPLL是否运算成功
    clock_t start_t, end_t;
    double total_t;

    while(op){
        system("cls");	printf("\n\n");
        printf("             SAT求解系统\n");
        printf("-------------------------------------------------\n");
        printf("            1.初始化存储结构\n");
        printf("            2.读取四阶数独并输出cnf文件\n");
        printf("            3.读取六阶数独并输出cnf文件\n");
        printf("            4.读取cnf文件\n");
        printf("            5.DPLL运算\n");
        printf("            6.优化版DPLL运算\n");
        printf("            7.输出res文件\n");
        printf("            8.输出数独答案\n");
        printf("            0.退出系统\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~8]:");
        scanf("%d",&op);
        switch(op){
        case 1:
            if(InitCNF(S)&&InitResultList(RL)&&InitDivideList(DL))
                printf("初始化成功\n");
            else
                printf("初始化失败\n");
            getchar();getchar();
            break;
        case 2:
            sudokind=4;
            printf("请输入数独文件名\n");
            scanf("%s",sudokuname);
            LoadSudoku4(sudoku4,sudokuname);
            PrintSudodu4(sudoku4);
            Sudoku4toCNF(sudoku4,sudokuname);
            getchar();getchar();
            break;
        case 3:
            sudokind=6;
            printf("请输入数独文件名\n");
            scanf("%s",sudokuname);
            LoadSudoku6(sudoku6,sudokuname);
            PrintSudodu6(sudoku6);
            Sudoku6toCNF(sudoku6,sudokuname);
            getchar();getchar();
            break;
        case 4:
            printf("请输入文件名\n");
            scanf("%s",filename);
            LoadCNF(S,filename);
            InitMOMList(ML,S.litnum);
            MOMListAssign(ML,S);
            BubbleSortM(ML);
            printf("创建成功\n");
            getchar();getchar();
            break;
        case 5:
            start_t = clock();
            satisfy=DPLL(S,RL);
            end_t = clock();
            if(satisfy)
            {
                printf("运算成功\n");
                ResultPrint(RL,satisfy);
            }
            else
                printf("运算失败\n");

            total_t = ((double)(end_t - start_t))/ CLOCKS_PER_SEC*1000;
            printf("%f ms",total_t);

            getchar();getchar();
            break;
        case 6:
            start_t = clock();
            //satisfy=DPLLbyLoop(S,RL,ML,DL);
            satisfy=MOMDPLL(S,RL,ML);
            end_t = clock();
            if(satisfy)
            {
                printf("运算成功\n");
                ResultPrint(RL,satisfy);
            }
            else
                printf("运算失败\n");

            total_t = ((double)(end_t - start_t))/ CLOCKS_PER_SEC*1000;
            printf("%f ms",total_t);

            getchar();getchar();
            break;
        case 7:
            if(ResWrite(satisfy,total_t,RL,filename)==OK)
                printf("结果写入成功\n");
            else printf("结果写入失败\n");
            getchar();getchar();
            break;
        case 8:
            PuzzleResult(RL,sudokind);
            getchar();getchar();
            break;
        case 0:
            break;
            }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}       //end of main()

