#include "MySem.h"
#include "MyShm.h"
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


void signalHandler(int signum);

int shmid = 0;

int *shmaddr = NULL;

int semidServ = 0;
int semidClnt = 0;

int main(int argc, char const *argv[]){

    int req = 0;
    int res = 0;

    union semun semunBuf;
    shmid = creatShm(MY_SHM_KEY);
    shmaddr = shmat(shmid, NULL, 0);
    semidServ = creatSem(MY_SEM_SERV_KEY);
    semunBuf.val = 0;
    semctl(semidServ, 0, SETVAL, semunBuf);//SETVAL은 세모포어(struct sem)?의 semval 값을 semunBuf.val(4번째 인자 추가됨)로 설정한다.

    semidClnt = creatSem(MY_SEM_CLNT_KEY);
    semunBuf.val = 1;
    semctl(semidClnt, 0, SETVAL, semunBuf);
    signal(SIGINT, signalHandler); 


    while(1) {
        puts("Wait ...");

        lockSem(semidServ);
        memcpy(&req, shmaddr, sizeof(int));
        res = req + 1;
        memcpy(shmaddr, &res, sizeof(int));
        unlockSem(semidClnt);

        printf("Request: %d\n", req);
        printf("Response: %d\n", res);
        fflush(stdout);
    }

    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        closeSem(semidClnt);
        closeSem(semidServ);

        shmdt(shmaddr);
        closeShm(shmid);

        exit(0);
    }
} 
