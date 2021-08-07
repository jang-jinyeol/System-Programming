#include <stdio.h>
#include <stdlib.h>



int main(void){

    FILE* fp;

    int a;

    fp = popen("wc -l", "w"); //"w" 모드를 사용해 쓰기 전용 파이프를 생성하고 자식 프로세스는 wc -l 명령을 수행하도록 한다.
    //wc -l은 입력되는 데이터의 행 수를 출력하는 명령이다.

    if (fp == NULL){
        fprintf(stderr, "popen failed\n");
        exit(1);
    } 

    for (a=0;a<100;a++)
    fprintf(fp, "test line\n");

    pclose(fp);

    return 0;



}
