#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
exec 함수군은 인자로 받은 다른 프로그램을 자신을 호출한 프로세스의 메모리에 덮어쓴다.
exec함수군을 호출한 프로세스 자체가 바뀌므로 호출이 성공하면 리턴값이 없다.
*/

int main(void) {
    char *argv[3];

    printf("Before exec function\n");
    
    argv[0] = "ls";
    argv[1] = "-a";
    argv[2] = NULL; //execv의 두번째 인자 argv는 포인터 배열이고 마지막에는 NULL 문자를 저장해야 한다.
    if (execv("/bin/ls", argv) == -1) {//첫번째 인자 path에 지정한 경로명의 파일을 실행한다.
        perror("execv");
        exit(1);
    }

    printf("After exec function\n");

    return 0;
}
