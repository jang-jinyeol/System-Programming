#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
ps 명령의 결과는 기본적으로 표준 출력으로 출력되고, grep 명령은 표준 입력을 통해 입력받는다.
따라서 부모 프로세스와 자식 프로세스 간의 통신이 표준 입출력 대신 파이프를 통해 이루어지도록 만들어야 한다.

자식 프로세스에서는 fd[0]의 값이 0이 아니면, 즉 표준 입력이 아니면 fd[0]의 값을 표준 입력으로 복사한 후 fd[0]을 닫는다.
이제 자식 프로세스에서는 표준 입력을 fd[0]이 가리키는 파이프에서 읽는다.

자식 프로세스가 grep 명령을 exec 함수로 호출한다. 이미 표준 입력으로 파이프의 입력 파일 기술자를 복사했으므로 표준 입력을 통해 grep 명령을 읽어들인다.

부모 프로세스도 이하 동일

*/

int main(void) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : /* child */
            close(fd[1]);
            if (fd[0] != 0) {
                dup2(fd[0], 0);
                close(fd[0]);
            }
            execlp("grep", "grep", "telnet", (char *)NULL);
            exit(1);
            break;
        default :
            close(fd[0]);
            if (fd[1] != 1) {
                dup2(fd[1], 1);
                close(fd[1]);
            }
            execlp("ps", "ps", "-ef", (char *)NULL);
            wait(NULL);
            break;
    }

    return 0;
}
