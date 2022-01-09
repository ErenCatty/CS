#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

pid_t  pid1,pid2;
int isEnd = 0;
int pf1 = 0;
int pf2 = 0;

/*kill the subprocess*/
void killProcess()
{
    kill(pid1,SIGUSR1);
    kill(pid2,SIGUSR2);
}

void pid1Killed()
{
    printf("child process 1 is killed by parent\n");
    exit(0);
}

void pid2Killed()
{
    printf("child process 2 is killed by parent\n");
    exit(0);
}

int main()
{
    int quitPid;
    int pipefd[2]; 
    pipe(pipefd);//create pipe
    char inPipe[120],outPipe[120];//character string

    while((pid1=fork())==-1);
    while((pid2=fork())==-1);

    if(pid1==0)
    {
        signal(SIGINT,SIG_IGN);
        signal(SIGUSR1,pid1Killed);
        int x=1;
        //lock the input section
        while(1)
        {
            lockf(pipefd[1],1,0);
            sprintf(outPipe,"I send you %d time\n ",x++);
            write(pipefd[1],outPipe,50);
            sleep(1);                     //sleep for one second
            //unlock the input section
            lockf(pipefd[1],0,0);
        }
    }
    else if(pid2==0)
    {
        signal(SIGINT,SIG_IGN);
        signal(SIGUSR2,pid2Killed);
        while(1)
        {
            lockf(pipefd[0],1,0);//lock the read section
            if((read(pipefd[0],inPipe,50))!=0)printf("%s",inPipe);
            lockf(pipefd[0],1,0);
        }
    }
    else
    {
        //main process
        signal(SIGINT,killProcess);
        waitpid(pid1,&quitPid,0);
        waitpid(pid2,&quitPid,0);
        close(pipefd[1]);
        close(pipefd[0]);
        printf("parent process is killed!\n");
        exit(0);
    }
}
