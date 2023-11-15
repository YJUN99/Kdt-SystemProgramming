#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_gui()
{
    pid_t systemPid;
    printf("GUI를 생성합니다.");
    printf("여기서 GUI 프로세스를 생성합니다.\n");
    switch(systemPid = fork()){
        case -1:
            perror("GUI fork 실패\n");
            break;
        case 0:
            printf("나 GUI 프로세스!\n");
            if(execl("/usr/bin/google-chrome-stable", "/usr/bin/google-chrome-stable","http://localhost:8282", NULL)){
                printf("exec실패\n");
            }
            break;
        default:
            break;
    }
    
    return 0;
}
