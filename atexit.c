#include <stdlib.h>
#include <stdio.h>

/*
atexit 함수는 프로세스가 종료할 때 수행할 기능을 예약한다.
#include <stdlib.h>
int atexit(void(*func)(void));
함수의 포인터를 받는다. 인자와 리턴값이 없는 함수다.
아래의 코드를 실행해보면 함수가 예약 순서와 반대로 호출된다.
*/
void cleanup1(void) {
    printf("Cleanup 1 is called.\n");
}

void cleanup2(void) {
    printf("Cleanup 2 is called.\n");
}

int main(void) {
    atexit(cleanup1);
    atexit(cleanup2);

    exit(0);
}
