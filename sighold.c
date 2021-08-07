#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include <sys/types.h>
// #include <stdlib.h>


/*
sighold 함수는 인자로 받은 시그널을 프로세스의 시그널 마스크에 추가한다.
시그널 마스크에 추가된 시그널은 블록되어 해당 시그널을 받지 않는다.
sigrelse 함수는 프로세스의 시그널 마스크에서 시그널을 해제한다.
*/
void handler(int signo){

char* s;

s = strsignal(signo); //string.h 시그널 정보 출력 함수 원형은 char *strsignal(int sig);
// printf("Received Signal : %s\n", s);
psignal(signo, s);
}

int main(void) {

    if (sigset(SIGINT, handler) == SIG_ERR){
        perror("sigset");
        exit(1);
    }
    
    sighold(SIGINT);

    pause();

    return 0;
}


