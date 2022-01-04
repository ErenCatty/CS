#include"func.h"

int main()
{
    int op=1;
    char filename[20];        //cnf�ļ����洢
    char sudokuname[20]="sudoku2.txt";      //�����ļ����洢
    char sudokucnf[20]="sudoku2.cnf";
    CNF S;                     //����cnf
    DivideList DL;             //���ѽ������ջ
    ResList RL;             //�������
    MOMList ML;                //MOM����
    int sudoku4[4][4];      //��¼�Ľ�����
    int sudoku6[6][6];      //��¼��������
    int sudokind=0;           //��¼ѡ����������
    int satisfy;               //DPLL�Ƿ�����ɹ�
    clock_t start_t, end_t;
    double total_t;

    while(op){
        system("cls");	printf("\n\n");
        printf("             SAT���ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("            1.��ʼ���洢�ṹ\n");
        printf("            2.��ȡ�Ľ����������cnf�ļ�\n");
        printf("            3.��ȡ�������������cnf�ļ�\n");
        printf("            4.��ȡcnf�ļ�\n");
        printf("            5.DPLL����\n");
        printf("            6.�Ż���DPLL����\n");
        printf("            7.���res�ļ�\n");
        printf("            8.���������\n");
        printf("            0.�˳�ϵͳ\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~8]:");
        scanf("%d",&op);
        switch(op){
        case 1:
            if(InitCNF(S)&&InitResultList(RL)&&InitDivideList(DL))
                printf("��ʼ���ɹ�\n");
            else
                printf("��ʼ��ʧ��\n");
            getchar();getchar();
            break;
        case 2:
            sudokind=4;
            printf("�����������ļ���\n");
            scanf("%s",sudokuname);
            LoadSudoku4(sudoku4,sudokuname);
            PrintSudodu4(sudoku4);
            Sudoku4toCNF(sudoku4,sudokuname);
            getchar();getchar();
            break;
        case 3:
            sudokind=6;
            printf("�����������ļ���\n");
            scanf("%s",sudokuname);
            LoadSudoku6(sudoku6,sudokuname);
            PrintSudodu6(sudoku6);
            Sudoku6toCNF(sudoku6,sudokuname);
            getchar();getchar();
            break;
        case 4:
            printf("�������ļ���\n");
            scanf("%s",filename);
            LoadCNF(S,filename);
            InitMOMList(ML,S.litnum);
            MOMListAssign(ML,S);
            BubbleSortM(ML);
            printf("�����ɹ�\n");
            getchar();getchar();
            break;
        case 5:
            start_t = clock();
            satisfy=DPLL(S,RL);
            end_t = clock();
            if(satisfy)
            {
                printf("����ɹ�\n");
                ResultPrint(RL,satisfy);
            }
            else
                printf("����ʧ��\n");

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
                printf("����ɹ�\n");
                ResultPrint(RL,satisfy);
            }
            else
                printf("����ʧ��\n");

            total_t = ((double)(end_t - start_t))/ CLOCKS_PER_SEC*1000;
            printf("%f ms",total_t);

            getchar();getchar();
            break;
        case 7:
            if(ResWrite(satisfy,total_t,RL,filename)==OK)
                printf("���д��ɹ�\n");
            else printf("���д��ʧ��\n");
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
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}       //end of main()

