#include <stdio.h>
#include <sys/wait.h>

#include <signal.h>
#include <string.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

static void sigcldHandler(int sig){
    // 핸들러 구현
    // 자식프로세스가 죽었을 때의 printf 코드를 넣어볼것
    printf("Signal Handler ChildProcess dead\n");
    psignal(sig,"Received Signal\n");
}

int main()
{
    printf("메인 함수입니다.\n");
    
    pid_t sysPid, guiPid, inputPid, webPid;
    int status, savedErrno;

    int sigCnt;
    sigset_t blockMask, emptyMask;
    /*
        여기서 SIGCHLD 시그널 등록
        signal(SIGCHLD,sigcldHandler); // 자식 프로세그 시그널 생성
    */ 
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_handler = sigcldHandler;
    sigaction(SIGCHLD,&sa,NULL);

    printf("sys server 생성\n");
    sysPid = create_system_server();
    printf("gui 생성\n");
    guiPid = create_gui();
    printf("input 생성\n");
    inputPid = create_input();
    printf("web server 생성\n");
    webPid = create_web_server();

    waitpid(sysPid,&status,0);
    waitpid(guiPid,&status,0);
    waitpid(inputPid,&status,0);
    waitpid(webPid,&status,0);
    return 0;
}
