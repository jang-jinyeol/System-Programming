/*
고아와 반대로 자식 프로세스가 부모 프로세스 보다 먼저 종료되는 경우가 있다.

혹은 자식 프로세스가 모든 자원을 반납했어도 부모 프로세스가 종료 상태 정보를 얻어가지 않는 경우도 있다.

이럴경우 좀비 프로세스가 발생한다. 부모 프로세스가 wait관련 함수를 호출해야 사라진다.(동기화)

ps aux | grep Z 명령어를 사용하여 좀비 프로세스를 확인한다.(STAT에 Z로 표시됨)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
 
int main() {
     
    pid_t childPid;
     
    childPid = fork();
     
    if(childPid > 0) {  // 부모 프로세스
        printf("부모 PID : %ld, pid : %d\n",(long)getpid(), childPid);
        sleep(30);
        printf("부모 종료\n");
        exit(0);
    }
    else if(childPid == 0){  // 자식 코드
        printf("자식 시작 PID : %ld\n", (long)getpid());
        sleep(1);
        printf("자식 종료\n");
        exit(0);
    }
    else {  // fork 실패
        perror("fork Fail! \n");
        return -1;
    }
     
    return 0;
}
