#include <stdio.h>
#include <sys/wait.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int main()
{
    printf("메인 함수입니다.\n");
    
    pid_t sysPid, guiPid, inputPid, webPid;
    int status, savedErrno;

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
