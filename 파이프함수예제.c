#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
read(), write() 함수 개념을 완벽히 숙지하지 못하면 이해하기 힘든 코드다.
자식 프로세스와 부모 프로세스 중 무엇이 먼저 실행될지는 모른다.
child process 에선 fd[1] 즉, 쓰기를 닫고 parent process 에선 fd[0] 읽기를 닫는다.
부모 프로세스에서 "Test Message\n"를 쓰고 자식 프로세스에서 fd[0]으로 받아 buf에 저장 후 출력한다.

부모 프로세스에선 waitpid 함수로 자식 프로세스를 회수한다.
*/
int main(void) {
    int fd[2];
    pid_t pid;
    char buf[257];
    int len, status;

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
            write(1, "Child Process:", 15);
            len = read(fd[0], buf, 256);
            write(1, buf, len);
            close(fd[0]);
            break;
        default :
            close(fd[0]);
            buf[0] = '\0';
            write(fd[1], "Test Message\n", 14);
            close(fd[1]);
            waitpid(pid, &status, 0);
            break;
    }

    return 0;
}
