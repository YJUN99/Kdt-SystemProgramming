#include <stdio.h>
#include <sys/prctl.h>

#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

/* Threads header */
#include <assert.h>
#include <pthread.h>


#define MILLISEC_PER_SECOND 1000
#define NANOSEC_PER_USEC    1000
#define USEC_PER_MILLISEC   1000

static int toy_timer = 0;


int posix_sleep_ms(unsigned int timeout_ms)
{
    struct timespec sleep_time;

    sleep_time.tv_sec = timeout_ms / MILLISEC_PER_SECOND;
    sleep_time.tv_nsec = (timeout_ms % MILLISEC_PER_SECOND) * (NANOSEC_PER_USEC * USEC_PER_MILLISEC);

    return nanosleep(&sleep_time, NULL);
}

void timer_handler(int signo){
    toy_timer++;
    //printf("timer 만료\n");
}


void *watchdog_thread(void *arg){
    printf("watch dog thread\n");
    while(1){
        posix_sleep_ms(1000);
    }
}

void *disk_service_thread(void *arg){
    printf("diskservice thread\n");
    while(1){
        posix_sleep_ms(1000);
    }
}
void *monitor_thread(void *arg){
    printf("monitor thread\n");
    while(1){
        posix_sleep_ms(1000);
    }
}
void *camera_service_thread(void *arg){
    printf("camera thread\n");
    while(1){
        posix_sleep_ms(1000);
    }
}

int system_server()
{

    struct itimerspec ts;
    struct sigaction  sa;
    struct sigevent   sev;
    timer_t *tidlist;
    tidlist = malloc(sizeof(timer_t));

    printf("나 system_server 프로세스!\n");
    // 5 sec timer create

    
    sa.sa_flags = 0;
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGALRM,&sa,NULL) < 0){
        perror("Timer SA\n");
        exit(1);
    }

    sev.sigev_notify = SIGEV_SIGNAL; // 이벤트 통지로 시그널을 발생
    sev.sigev_signo = SIGALRM;
    sev.sigev_value.sival_int = 0;

    if (timer_create(CLOCK_REALTIME, &sev, tidlist) < 0) {
        perror("timer_create error");
        exit(1);
    }

    ts.it_value.tv_sec = 5;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = 5;
    ts.it_interval.tv_nsec = 0;


    if(timer_settime(*tidlist,0,&ts,NULL) < 0){
        perror("timer set Error\n");
        exit(1);
    }

    // thread 구현
    pthread_t th_watchDog, th_diskService, th_monitor, th_camera;
    int th_res_code;
    
    if((th_res_code = pthread_create(&th_watchDog , NULL , watchdog_thread, NULL)) == -1)
        perror("input.c th_command\n");
    if((th_res_code = pthread_create(&th_diskService , NULL , disk_service_thread, NULL)) == -1)
        perror("input.c th_sensor\n");
    if((th_res_code = pthread_create(&th_monitor , NULL , monitor_thread, NULL)) == -1)
        perror("input.c th_command\n");
    if((th_res_code = pthread_create(&th_camera , NULL , camera_service_thread, NULL)) == -1)
        perror("input.c th_sensor\n");


    while (1) {
        sleep(1);
    }

    pthread_detach(th_watchDog);
    pthread_detach(th_diskService);
    pthread_detach(th_monitor);
    pthread_detach(th_camera);

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
