//독립적인 프로세스 간 공유 메모리 사용 예제
//서버
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/shm.h>
#include <string.h>


void handler(int dummy){
    ;
}

int main(void){
    key_t key;
    int shmid;
    void *shmaddr;
    char buf[1024];
    sigset_t mask;

    key = ftok("shmfile",1);
    shmid = shmget(key, 1024, IPC_CREAT|0666);
    
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigset(SIGUSR1, handler);
    
    printf("Listener wait for Talker\n");
    sigsuspend(&mask); //SIGUSR1 시그널을 받을 때까지 기다린다.

    printf("Listnet Start ======\n");
    shmaddr = shmat(shmid, NULL,0);
    strcpy(buf, (char*)shmaddr);

    strcpy((char*)shmaddr, "Have a nice day\n");
    sleep(3); //talker가 ipcs를 실행할 시간을 위해서 sleep
    shmdt(shmaddr);
    
}


//독립적인 프로세스 간 공유 메모리 사용 예제
//클라이언트
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char **argv){
    key_t key;
    int shmid;
    void* shmaddr;
    char buf[1024];

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, 0); //키값으로 listener가 만든 공유 메모리의 식별자를 읽어온다.

    shmaddr = shmat(shmid, NULL,0); //공유 메모리와 연결 shmat 함수는 수행을 성공시 연결된 공유 메모리의 시작 주소를 리턴한다.
    strcpy((char*)shmaddr, "Hello, I'm talker\n");//해당 메모리에 인사말을 복사

    kill(atoi(argv[1]), SIGUSR1); //명령행 인자로 받은 listener의 PID를 지정하고 SIGUSR1 시그널을 보낸다.
    sleep(2);//sleep 함수를 수행해 잠시 기다렸다가 공유 메모리에서 listener가 보낸 응답을 읽어 출력한다.
    strcpy(buf, (char*)shmaddr);

    printf("Listener said : %s\n", buf);
    system("ipcs -m");
    shmdt(shmaddr);
    shmctl(shmid,IPC_RMID,NULL);//공유메모리 식별자,수행할 제어 기능, 제어 기능에 사용되는 공유 메모리 구조체의 주소

    return 0;
}
