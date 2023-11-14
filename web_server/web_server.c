#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_web_server()
{
    pid_t systemPid;
    printf("여기서 Web Server 프로세스를 생성합니다.\n");
    switch(systemPid = fork()){
        case -1:
            perror("웹서버 fork 실패\n");
            break;
        case 0:
            printf("나 system server 프로세스!\n");
            if(execl("/usr/local/bin/filebrowser","filebrowser","-p","8282",NULL)){
                printf("execfailed\n");
            }            
            break;
        default:
            break;
    }
    return 0;
}
