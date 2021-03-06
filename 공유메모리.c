//ipcrm -m shmid (제거)

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SHM_SIZE 512

void signalHandler(int signum);
void myfunc(void);

key_t mykey = 0;
int shmid = 0;
int *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    mykey = ftok("myshmkey", 2);
    shmid = shmget(mykey, MAX_SHM_SIZE, IPC_CREAT | 0600);
    shmaddr = (int*)shmat(shmid, NULL, 0);

    signal(SIGINT, signalHandler);

    signal(SIGUSR1, signalHandler);
while (1) {
        puts("Wait ...");
        pause();
    }

    return 0;
}

void signalHandler(int signum) {
    struct shmid_ds buf;

    if (signum == SIGINT) {
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    } else if (signum == SIGUSR1) {
        myfunc();
    }
}
void myfunc(void) {
    struct shmid_ds buf;
    int data = 0;

    memcpy(&data, shmaddr, sizeof(int));
    printf("Receive: %d\n", data);

    data += 1;
    memcpy(shmaddr, &data, sizeof(int));
    printf("Send: %d\n", data);

    shmctl(shmid, IPC_STAT, &buf);

    kill(buf.shm_lpid, SIGUSR1);//마지막으로 shmop 동작을 한 프로세스의 ID다. 여기선 클라이언트의 ID

}
/*
클라이언트 부분

    #include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SHM_SIZE 512

void signalHandler(int signum);
void myfunc(void);

key_t mykey = 0;
int shmid = 0;
int *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    struct shmid_ds buf;
    int data = 0;

    mykey = ftok("myshmkey", 2);
    shmid = shmget(mykey, MAX_SHM_SIZE, IPC_CREAT);
    shmaddr = (int*)shmat(shmid, NULL, 0);
signal(SIGUSR1, signalHandler);
signal(SIGINT, signalHandler);
    while (1) {
        printf("<< ");
        scanf("%d", &data);

        fflush(stdout);
        fflush(stdin);

        memcpy(shmaddr, &data, sizeof(int));
        shmctl(shmid, IPC_STAT, &buf);
        printf("%d\n", buf.shm_cpid);
        kill(buf.shm_cpid, SIGUSR1);//공유메모리를 생성한 프로세스의 id 즉, 서버에게 시그널을 보낸다.
    
        pause();
    }

    return 0;
}

void signalHandler(int signum) {
    int data = 0;

    if (signum == SIGUSR1) {
        memcpy(&data, shmaddr, sizeof(int));
        printf(">> %d\n", data);
    }
       if (signum == SIGINT) {
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    }
}

*/

