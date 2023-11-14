#include <stdio.h>
#include <sys/prctl.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int input()
{
    printf("나 input 프로세스!\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

int create_input()
{
    pid_t systemPid;
    const char *name = "input";

    printf("여기서 input 프로세스를 생성합니다.\n");
    switch(systemPid = fork()){
        case -1:
            perror("input fork failed\n");
            break;
        case 0:
            if(prctl(PR_SET_NAME, (unsigned long) name) < 0){
                perror("input prctl failed\n");
                exit(1);
            }
            input();
            break;
        default:
            break;
    }

    return 0;
}