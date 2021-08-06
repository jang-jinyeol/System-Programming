#define _CRT_SECURE_NO_WARNINGS    // strcpy 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <string.h>    // strcpy 함수가 선언된 헤더 파일

void *allocMemory()    // void 포인터를 반환하는 allocMemory 함수 정의
{
    void *ptr = malloc(100);    // 100바이트만큼 동적 메모리 할당

    return ptr;    // void 포인터 반환
    //return malloc(100) 한번에 가능
}

int main()
{
    char *s1 = (char*)allocMemory();       // void 포인터를 char 포인터에 넣어서 문자열처럼 사용, gcc에선 가능하나 비주얼스튜디오에선 (char*)형변환 해주어야 함
    strcpy(s1, "Hello, world!");    // s1에 Hello, world! 복사
    printf("%s\n", s1);             // Hello, world!
    free(s1);                       // 동적 메모리 해제
    
    int *numPtr1 =(int*) allocMemory();   // void 포인터를 int 포인터에 넣어서 정수 배열처럼 사용, gcc에선 가능하나 비주얼스튜디오에선 (int*)형변환 해주어야 함
    numPtr1[0] = 10;                // 첫 번째 요소에 10 저장
    numPtr1[1] = 20;                // 두 번째 요소에 20 저장
    printf("%d %d\n", numPtr1[0], numPtr1[1]); // 10 20
    free(numPtr1);                  // 동적 메모리 해제
    
    return 0;
}
