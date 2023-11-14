#include <stdio.h>
#include <sys/prctl.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int system_server()
{
    printf("나 system_server 프로세스!\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

int create_system_server()
{
    pid_t systemPid;
    const char *name = "system_server";
    printf("여기서 시스템 프로세스를 생성합니다.\n");
    switch (systemPid = fork())
    {
    case -1:
        // system_server fork Error
        perror("Sys fork Error");
        break;
    case 0:
        // child Process
        // Process 식별을 위한 프로세스의 이름 변경
        if(prctl(PR_SET_NAME, (unsigned long)name) < 0){ // 프로세스의 이름 변경 실패
            perror("sys server 이름변경 실패\n");
            exit(1);
        }
        system_server();
        break;
    default:
        break;
    }
    return 0;
}
