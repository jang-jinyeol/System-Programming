#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
    
    key_t key;
    int shmid, i;
    char *shmaddr, *shmaddr2;


    shmid = shmget(IPC_PRIVATE, 20, IPC_CREAT|0644);
    
    if(shmid == -1){
        perror("shmget");
        exit(1);
    }

    switch(fork()){

        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            shmaddr =(char *)shmat(shmid,(char*)NULL,0);//shmat 함수는 공유메모리 연결 수행을 성공하면 연결된 공유메모리의 시작 주소를 리턴한다.
                //3번째 인자 shmflg는 플래그로 0이면 공유 메모리에 대해 읽기와 쓰기가 가능하고, SHM_RDONLY면 읽기만 가능하다.
            printf("Child Process ======\n");
            for(i=0;i<10;i++)
                shmaddr[i] ='a'+i;
            shmdt(shmaddr); 
            exit(0);
    
    default:
        wait(0);
        shmaddr2 = (char *)shmat(shmid,(char*)NULL,0);
        printf("Parent Process ======\n");
        for (i=0; i<10; i++)
        printf("%c", shmaddr2[i]);
        printf("\n");
        sleep(5);       //sleep 함수를 사용한 이유는 ipcs 명령으로 공유 메모리의 상태를 확인하기 위함
        shmdt(shmaddr2);
        shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
        break;

    }
    return 0;

}
