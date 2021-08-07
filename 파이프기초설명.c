#include <stdio.h>

//파이프 생성
//command: 쉘 명령, mode: "r" 또는 "w"
FILE *popen(const char *command, const char* mode);
/*
popen 함수는 자식 프로세스와 파이프를 만들고 mode의 값에 따라 표준 입출력을 연결한다.
popen 함수는 내부적으로 fork 함수를 실행해 자식 프로세스를 만들고 command에서 지정한 명령을
exec 함수로 실행해 자식 프로세스가 수행하도록 한다. 자식 프로세스가 실행하는 exec 함수는 다음과
같은 형태가 된다.

execl("/usr/bin/sh", "sh", "-c", command, (char*)0);

popen 함수의 리턴값은 파일 포인터다.
파일 입출력 함수에서 이 파일 포인터를 사용하면 파이프를 읽거나 쓸 수 있다.
poen 함수는 파이프 생성에 실패하면 널 포인터를 리턴한다.
*/

//파이프 닫기

int pclose(FILE *stream); //stream: popen 함수에서 리턴한 파일 포인터

/*
pclose 함수의 리턴값은 자식 프로세스의 종료 상태(exit status)다.
파이프를 닫는데 실패하면 -1을 리턴한다.
*/
