#include "func.h"

status LoadSudoku4(int sudoku4[][4], char FileName[])
{
    FILE *fp;
    if((fp=fopen(FileName,"r"))==NULL)
        return ERROR;

    int i,j;                           //ѭ������

    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            fscanf(fp,"%d",&sudoku4[i][j]);
    fclose(fp);
    return OK;
}

status PrintSudodu4(int sudoku4[][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            printf("% d",sudoku4[i][j]);
        printf("\n");
    }
    return OK;
}

status Sudoku4toCNF(int sudoku4[][4],char FileName[])
{
    int i,j,k,m;

    while(FileName[i]!='\0') i++;
	FileName[i-3]='c';    //ֻ�ı��ļ�����չ��
	FileName[i-2]='n';
	FileName[i-1]='f';
    FILE *fp;
    if((fp=fopen(FileName,"w+"))==NULL)
        return ERROR;
    fprintf(fp,"p cnf ");
    int litcount=0,clacount=0;
    int lit;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(sudoku4[i][j]==1||sudoku4[i][j]==0)       //���Ӿ伯
                clacount++;
    litcount+=4*4;
    clacount+=32;                     //Լ��һ���������Ӿ�
    clacount+=64;                     //Լ�������������Ӿ�
    litcount+=144;                    //Լ����������������
    clacount+=444;                      //Լ�������������Ӿ�
    fprintf(fp,"%d %d\n",litcount,clacount);
    for(i=0;i<4;i++)                  //���Ӿ�����
        for(j=0;j<4;j++)
        {
            if(sudoku4[i][j]==1)
                fprintf(fp,"%d 0\n",(i)*4+j+1);
            else if(sudoku4[i][j]==0)
                fprintf(fp,"%d 0\n",-(i)*4-j-1);
        }

    for(i=1;i<=4;i++)                  //Լ��һ�Ӿ�����
    {
        for(k=1;k<=2;k++)
        {
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",(i-1)*4+j);
            fprintf(fp,"0\n");
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",-(i-1)*4-j);
            fprintf(fp,"0\n");
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",(j-1)*4+i);
            fprintf(fp,"0\n");
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",-(j-1)*4-i);
            fprintf(fp,"0\n");
        }
    }

    for(i=1;i<=4;i++)                       //Լ�����Ӿ�����
        for(k=1;k<=4;k++)
        {
            for(j=1;j<=4;j++)
                if(j!=k)
                    fprintf(fp,"%d ",(i-1)*4+j);
            fprintf(fp,"0\n");
            for(j=1;j<=4;j++)
                if(j!=k)
                    fprintf(fp,"%d ",-(i-1)*4-j);
            fprintf(fp,"0\n");
            for(j=1;j<=4;j++)
                if(j!=k)
                    fprintf(fp,"%d ",(j-1)*4+i);
            fprintf(fp,"0\n");
            for(j=1;j<=4;j++)
                if(j!=k)
                    fprintf(fp,"%d ",-(j-1)*4-i);
            fprintf(fp,"0\n");
        }
    lit=16;
    for(i=1;i<=4;i++)                 //��һ
        for(j=i+1;j<=4;j++)           //�ж�
        {
            for(m=1;m<=4;m++)         //��m
            {
                lit++;                //��������Ϊ1�ı�Ԫ��11211
                fprintf(fp,"%d %d 0\n",(i-1)*4+m,-lit);
                fprintf(fp,"%d %d 0\n",(j-1)*4+m,-lit);
                fprintf(fp,"%d %d %d 0\n",-((i-1)*4+m),-((j-1)*4+m),lit);
                lit++;                //��������Ϊ0�ı�Ԫ��11210
                fprintf(fp,"%d %d 0\n",-((i-1)*4+m),-lit);
                fprintf(fp,"%d %d 0\n",-((j-1)*4+m),-lit);
                fprintf(fp,"%d %d %d 0\n",(i-1)*4+m,(j-1)*4+m,lit);
                lit++;                //�����Ԫ��1121
                fprintf(fp,"%d %d 0\n",-(lit-2),lit);
                fprintf(fp,"%d %d 0\n",-(lit-1),lit);
                fprintf(fp,"%d %d %d 0\n",lit-2,lit-1,-lit);
            }
            for(k=0;k<4;k++)
            {
                fprintf(fp,"%d ",-(lit-3*k));

            }
            fprintf(fp,"0\n");
        }
    for(i=1;i<=4;i++)                 //��һ
        for(j=i+1;j<=4;j++)           //�ж�
        {
            for(m=1;m<=4;m++)         //��m
            {
                lit++;                //��������Ϊ1�ı�Ԫ��21211
                fprintf(fp,"%d %d 0\n",(m-1)*4+i,-lit);
                fprintf(fp,"%d %d 0\n",(m-1)*4+j,-lit);
                fprintf(fp,"%d %d %d 0\n",-((m-1)*4+i),-((m-1)*4+j),lit);
                lit++;                //��������Ϊ0�ı�Ԫ��21210
                fprintf(fp,"%d %d 0\n",-((m-1)*4+i),-lit);
                fprintf(fp,"%d %d 0\n",-((m-1)*4+j),-lit);
                fprintf(fp,"%d %d %d 0\n",(m-1)*4+i,(m-1)*4+j,lit);
                lit++;                //�����Ԫ��2121
                fprintf(fp,"%d %d 0\n",-(lit-2),lit);
                fprintf(fp,"%d %d 0\n",-(lit-1),lit);
                fprintf(fp,"%d %d %d 0\n",lit-2,lit-1,-lit);
            }
            for(k=0;k<4;k++)
            {
                fprintf(fp,"%d ",-(lit-3*k));

            }
            fprintf(fp,"0\n");
        }


    fclose(fp);
    return OK;
}

status LoadSudoku6(int sudoku6[][6], char FileName[])
//�����ļ�FileName���Ӿ��Լ��������ݣ������ڽ�����
{
    FILE *fp;
    if((fp=fopen(FileName,"r"))==NULL)
        return ERROR;

    int i,j;                           //ѭ������

    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            fscanf(fp,"%d",&sudoku6[i][j]);
    fclose(fp);
    return OK;
}

status PrintSudodu6(int sudoku6[][6])
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
            printf("% d",sudoku6[i][j]);
        printf("\n");
    }
    return OK;
}

status Sudoku6toCNF(int sudoku6[][6],char FileName[])
{
    int i,j,k,m;
    while(FileName[i]!='\0') i++;
	FileName[i-3]='c';    //ֻ�ı��ļ�����չ��
	FileName[i-2]='n';
	FileName[i-1]='f';
    FILE *fp;
    if((fp=fopen(FileName,"w+"))==NULL)
        return ERROR;
    fprintf(fp,"p cnf ");
    int litcount=0,clacount=0;
    int lit;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            if(sudoku6[i][j]==1||sudoku6[i][j]==0)       //���Ӿ伯
                clacount++;
    litcount+=6*6;
    clacount+=96;                     //Լ��һ���������Ӿ�
    clacount+=360;                     //Լ�������������Ӿ�
    litcount+=540;                    //Լ����������������
    clacount+=1650;                      //Լ�������������Ӿ�
    fprintf(fp,"%d %d\n",litcount,clacount);
    for(i=0;i<6;i++)                  //���Ӿ�����
        for(j=0;j<6;j++)
        {
            if(sudoku6[i][j]==1)
                fprintf(fp,"%d 0\n",(i)*6+j+1);
            else if(sudoku6[i][j]==0)
                fprintf(fp,"%d 0\n",-(i)*6-j-1);
        }

    for(i=1;i<=6;i++)                  //Լ��һ���Ӿ�����
    {
        for(k=1;k<=4;k++)
        {
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",(i-1)*6+j);
            fprintf(fp,"0\n");
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",-(i-1)*6-j);
            fprintf(fp,"0\n");
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",(j-1)*6+i);
            fprintf(fp,"0\n");
            for(j=k;j<=(k+2);j++)
                fprintf(fp,"%d ",-(j-1)*6-i);
            fprintf(fp,"0\n");
        }
    }

    for(i=1;i<=6;i++)                  //Լ�����Ӿ�����
        for(m=1;m<=6;m++)
            for(k=m+1;k<=6;k++)
            {
                for(j=1;j<=6;j++)
                    if(j!=k&&j!=m)
                        fprintf(fp,"%d ",(i-1)*6+j);
                fprintf(fp,"0\n");
                for(j=1;j<=6;j++)
                    if(j!=k&&j!=m)
                        fprintf(fp,"%d ",-(i-1)*6-j);
                fprintf(fp,"0\n");
                for(j=1;j<=6;j++)
                    if(j!=k&&j!=m)
                        fprintf(fp,"%d ",(j-1)*6+i);
                fprintf(fp,"0\n");
                for(j=1;j<=6;j++)
                    if(j!=k&&j!=m)
                        fprintf(fp,"%d ",-(j-1)*6-i);
                fprintf(fp,"0\n");
            }
    lit=6*6;
    for(i=1;i<=6;i++)                 //��һ
        for(j=i+1;j<=6;j++)           //�ж�
        {
            for(m=1;m<=6;m++)         //��m
            {
                lit++;                //��������Ϊ1�ı�Ԫ��11211
                fprintf(fp,"%d %d 0\n",(i-1)*6+m,-lit);
                fprintf(fp,"%d %d 0\n",(j-1)*6+m,-lit);
                fprintf(fp,"%d %d %d 0\n",-((i-1)*6+m),-((j-1)*6+m),lit);
                lit++;                //��������Ϊ0�ı�Ԫ��11210
                fprintf(fp,"%d %d 0\n",-((i-1)*6+m),-lit);
                fprintf(fp,"%d %d 0\n",-((j-1)*6+m),-lit);
                fprintf(fp,"%d %d %d 0\n",(i-1)*6+m,(j-1)*6+m,lit);
                lit++;                //�����Ԫ��1121
                fprintf(fp,"%d %d 0\n",-(lit-2),lit);
                fprintf(fp,"%d %d 0\n",-(lit-1),lit);
                fprintf(fp,"%d %d %d 0\n",lit-2,lit-1,-lit);
            }
            for(k=0;k<6;k++)
            {
                fprintf(fp,"%d ",-(lit-3*k));

            }
            fprintf(fp,"0\n");
        }
    for(i=1;i<=6;i++)                 //��һ
        for(j=i+1;j<=6;j++)           //�ж�
        {
            for(m=1;m<=6;m++)         //��m
            {
                lit++;                //��������Ϊ1�ı�Ԫ��21211
                fprintf(fp,"%d %d 0\n",(m-1)*6+i,-lit);
                fprintf(fp,"%d %d 0\n",(m-1)*6+j,-lit);
                fprintf(fp,"%d %d %d 0\n",-((m-1)*6+i),-((m-1)*6+j),lit);
                lit++;                //��������Ϊ0�ı�Ԫ��21210
                fprintf(fp,"%d %d 0\n",-((m-1)*6+i),-lit);
                fprintf(fp,"%d %d 0\n",-((m-1)*6+j),-lit);
                fprintf(fp,"%d %d %d 0\n",(m-1)*6+i,(m-1)*6+j,lit);
                lit++;                //�����Ԫ��2121
                fprintf(fp,"%d %d 0\n",-(lit-2),lit);
                fprintf(fp,"%d %d 0\n",-(lit-1),lit);
                fprintf(fp,"%d %d %d 0\n",lit-2,lit-1,-lit);
            }
            for(k=0;k<6;k++)
            {
                fprintf(fp,"%d ",-(lit-3*k));

            }
            fprintf(fp,"0\n");
        }

    fclose(fp);
    return OK;
}

status PuzzleResult(ResList L,int kind)
{
    printf("\n");
    if(L==NULL)
        return INFEASIBLE;
    ResList p=L->next;
    if(p==NULL)
        return OK;
    int i,j;
    if(kind==4)
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(p->data>0)
                    printf("1 ");
                else if(p->data<0)
                    printf("0 ");
                p=p->next;
            }
            printf("\n");
        }
    }
    if(kind==6)
    {
        for(i=0;i<6;i++)
        {
            for(j=0;j<6;j++)
            {
                if(p->data>0)
                    printf("1 ");
                else if(p->data<0)
                    printf("0 ");
                p=p->next;
            }
            printf("\n");
        }
    }
    return OK;
}
