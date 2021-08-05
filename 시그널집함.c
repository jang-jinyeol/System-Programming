#include <signal.h>
#include <stdio.h>

/*
sigset_t 구조체 멤버로 유닉스에선 __sigbits[0] 이나 리눅스에선 __val[0]이다.
아래 코드에선 SIGINT(2), SIGQUIT(3)을 추가 했으므로 시그널 비트값이 0x06임을 알 수 있다.
2진수로 표현하면 0000 0110으로 SIGINT는 2번 SIGQUIT는 3번 비트가 이에 대응하고 있다.
시그널 집합을 사용할 때는 sigemptyset 함수를 호출해 시그널 집합을 모두 비우거나,
sigfillset 함수를 호출해 시그널 집합을 모두 1로 초기화해 사용해야 한다.
*/

int main(void) {
    sigset_t st;

    sigemptyset(&st);

    sigaddset(&st, SIGINT);
    sigaddset(&st, SIGQUIT);

    if (sigismember(&st, SIGINT))
        printf("SIGINT is setting.\n");

    printf("** Bit Pattern: %x\n",st.__val[0]);

    return 0;
}
