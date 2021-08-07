#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdlib.h>

/*

sigprocmask(2)
sighold, sigrelse 함수와 기능이 유사하지만 시그널 집합을 사용해 한 번에 여러 시그널을 블록할 수 있다.
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);

how: 시그널을 블록할 것인지, 해제할 것인지 여부
set: 블록하거나 해제할 시그널 집합의 주소
oset: NULL 또는 이전 설정값을 저장할 시그널 집합의 주소

how에 올 수 있는 값은 다음과 같다.

SIG_BLOCK : set에 지정한 시그널 집합을 시그널 마스크에 추가한다.
SIG_UNBLOCK : set에 지정한 시그널 집합을 시그널 마스크에서 제거한다.
SIG_SETMASK : set에 지정한 시그널 집합으로 현재 시그널 마스크를 대체한다.

두 번째 인자인 set은 블록하거나 해제할 시그널 집합을 가리키고, 세 번째 인자인 oset은 NULL이 아니면 이전 설정값이 저장된다.
*/


int main(void) {

   sigset_t set;

   sigemptyset(&set);
   sigaddset(&set, SIGINT);
   sigaddset(&set, SIGQUIT);
   sigprocmask(SIG_BLOCK,&set, (sigset_t *)NULL);

   printf("Blocking Signals: SIGINT, SIGQUIT\n");

   printf("Send SIGQUIT\n");

   kill(getpid(), SIGQUIT);//첫번째 인자 시그널을 받을 pid, 두 번째 인자 pid로 지정한 프로세스에 보내려는 시그널

    printf("Unblocking Signals\n"); //SIGQUIT 시그널을 보내도 block 되고 SIG_UNBLOCK 이후 코어 덤프를 생성하며 종료된다.

    sigprocmask(SIG_UNBLOCK, &set, (sigset_t*)NULL);



    return 0;
}


