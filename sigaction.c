#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/*
struct sigaction{
    int sa_flags; //sa_flags는 시그널 전달 방법을 수정할 플래그를 지정함)
    union{
        void (*sa_handler)();
        void (*sa_sigaction)(int, siginfo_t *,void *);
    }_funcptr;
    sigset_t sa_mask; //f
}

union에 있는건 아닌 것 같다 union안에 있었다면 struct sigaction act
act._funcptr.sa_handler = handler 이런식으로 코드를 짜야했을 것이다.
*/

//handler 함수
void handler(int signo){
    
    psignal(signo, "Received Signal");
    sleep(5);
    printf("In Signal Handler, After Sleep\n");

}

int main(void){

    struct sigaction act;
    sigemptyset(&act.sa_mask);//sa_mask는 sigset_t의 구조체 변수로 시그널 집합 처리를 위해 사용함

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT); //시그널 핸들러가 동작하는 중에 SIGQUIT 시그널을 블록하기 위해 sa_mask에 SIGQUIT 시그널을 설정한다.
    act.sa_flags = 0; //sa_flags에는 아무 플래그도 지정하지 않는다.(sa_flags는 시그널 전달 방법을 수정할 플래그를 지정함)
    act.sa_handler = handler; //핸들러 지정
    if(sigaction(SIGINT,&act,(struct sigaction *)NULL)<0){ //sigaction(int sig, const struct sigaction *restrict act,struct sigaction *restrict oact);
    //sig: 처리할 시그널, act: 시그널을 처리할 방법을 지정한 구조체 주소,oact 기존에 시그널을 처리하던 방법을 저장할 구조체 주소
    //sigaction은 수행을 성공하면 0을 실패하면 -1이 리턴된다.
        perror("sigaction");
        exit(1);
    }

fprintf(stderr,"Input SIGINT: ");
pause();
fprintf(stderr,"After Signal Handler\n");


return 0;
}
/*
Ctrl + c 를 입력해 SIGINT 시그널을 보내면 즉시 시그널 핸들러인 handler 함수가 호출된다.
5초동안 sleep 상태가 되고 그 사이 Ctrl + |(역슬래쉬) 시그널을 보내면 블록되어 기다리고 있다가 handler 함수의 동작이 끝난 후 처리된다.
코어 덤프를 생성하고 종료했음을 알 수 있다.
*/
