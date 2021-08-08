#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
책에 나온 코드는 순서에 문제가 있어서 수정하였다.(부모 자식 둘다 먼저 파이프로 write 함)
양방향 파이프는 파이프 함수를 각각 fd1[2], 와 fd2[2]를 인자로 호출한다.
부모 프로세스는 fd1가 보내는용 이므로 fd1[0]은 close하고 fd2는 receive용 이므로 fd2[1]은 close 한다.
자식 프로세스 이하 동일
*/
int main(void) {
    int fd1[2], fd2[2];
    pid_t pid;
    char buf[257];
    int len, status;

    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(1);
    }

    if (pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : /* child */
            close(fd1[1]);
            close(fd2[0]);
            strcpy(buf, "Good\n");
            write(fd2[1], buf, strlen(buf));
            write(1, "Child Process:", 15);
            len = read(fd1[0], buf, 256);
            write(1, buf, len);


            break;
        default :
            close(fd1[0]);
            close(fd2[1]);
            buf[0] = '\0';
            write(fd1[1], "Hello\n", 6);
            len = read(fd2[0], buf, 256);
            

            write(1, "Parent Process:", 15);
            write(1, buf, len);
            
      
            waitpid(pid, &status, 0);
            break;
    }

    return 0;
}
