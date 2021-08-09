#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

/*
메시지큐 생성과 비슷하다.
*/
int main(void){
    
    key_t key;
    int shmid;

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, IPC_CREAT|0644);
    
    if(shmid == -1){
        perror("shmget");
        exit(1);
    }

    return 0;


}
