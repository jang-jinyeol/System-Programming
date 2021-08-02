/*
부모 프로세스가 자식 프로세스보다 먼저 종료되면 init 프로세스가 자식 프로세스의 새로운 부모 프로세스가 된다

종료되는 프로세스가 발생할 때 커널은 이 프로세스가 누구의 부모 프로세스인지 확인한 후, 커널이 자식 프로세스의 부모 프로세스 ID를 1(init 프로세스)로 바꿔 준다.

아래 코드를 확인해 보면 부모가 먼저 종료된 후 자식의 getppid()가 1로 바뀐것을 볼 수 있다.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main() {
     
    pid_t childPid;
    int i;
     
    childPid = fork();
     
    if(childPid > 0) {  // 부모 프로세스
        printf("부모 PID : %ld, pid : %d\n",(long)getpid(), childPid);
        sleep(2);
        printf("부모 종료\n");
        exit(0);
    }
    else if(childPid == 0){  // 자식 코드
        printf("자식 시작\n");
         
        for(i=0;i<10;i++) {
            printf("자식 PID : %ld 부모 PID : %ld\n",(long)getpid(), (long)getppid());
            sleep(1);
        }
         
        printf("자식 종료\n");
        exit(0);
    }
    else {  // fork 실패
        perror("fork Fail! \n");
        return -1;
    }
     
    return 0;
}
