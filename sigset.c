#include <unistd.h>
#include <signal.h>
#include <siginfo.h>
#include <stdlib.h>
#include <stdio.h>
/*
sigset 함수가 signal 함수와 다른 점은 시그널 핸들러가 한 번 호출된 후에 기본 동작으로 재설정하지 않고
시그널 핸들러를 자동으로 재지정한다는 것이다.
ex) void(*hand)(int)
hand = signal(SIGINT, handler);
*/
void handler(int signo) {
    printf("Signal Handler Signal Number : %d\n", signo);
    psignal(signo, "Received Signal");
}

int main(void) {
    if (sigset(SIGINT, handler) == SIG_ERR) {
        perror("sigset");
        exit(1);
    }

    printf("Wait 1st Ctrl+C... : SIGINT\n");
    pause();
    printf("After 1st Signal Handler\n");
    printf("Wait 2nd Ctrl+C... : SIGINT\n");
    pause();
    printf("After 2nd Signal Handler\n");

    return 0;
}
