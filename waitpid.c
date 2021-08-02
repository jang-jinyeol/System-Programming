#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
wait 함수는 자식 프로세스가 여러 개일 경우 아무 자식 프로세스나 종료하면 리턴한다.
wiatpid 함수는 특정 pid의 자식 프로세스가 종료하기를 기다린다.
*/

int main(void) {
    int status;
    pid_t pid;

    if ((pid = fork()) < 0) { /* fork failed */
        perror("fork");
        exit(1);
    }

    if (pid == 0) {   /* child process */
        printf("--> Child process\n");
        sleep(3);
        exit(3);
    }

    printf("--> Parent process\n");
//WNOHANG 옵션은 기다리는 PID가 종료되지 않아서 즉시 종료 상태를 회수 할 수 없는 상황에서 호출자는 차단되지 않고 반환값으로 0을 받음
  //&status는 종료 상태값을 저장할 주소이다.
  //pid는 종료를 기다리는 PID
    while (waitpid(pid, &status, WNOHANG) == 0) {
        printf("Parent still wait...\n");
        sleep(1);
    }
//종료 상태값을 출력
  
  /*
  저번에 작성했던 방법으로도 출력 가능하다.
         if(WIFEXITED(status)) //정상적으로 종료가 되었으면 if문이 실행된다.
                printf("Child send : %d \n", WEXITSTATUS(status)); //리턴 값으로 3을 반환
                                */
  //자식 프로세스가 전달한 값은 부모 프로세스에 왼쪽으로 한 바이트 이동해 전달된다.
  //따라서 제대로 출력하려면 오른쪽으로 8비트 이동시켜야 한다.
    printf("Child Exit Status : %d\n", status>>8);

    return 0;
}
