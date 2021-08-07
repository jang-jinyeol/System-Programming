#include <stdio.h>
#include <stdlib.h>

/*
자식 프로세스에서는 date 명령을 수행하도록 한다.
부모 프로세스에서는 자식 프로세스가 기록한 데이터를 읽고 저장해 출력한다.
실행 결과를 보면 자식 프로세스가 실행한 date 명령의 결과를 부모 프로세스가 읽어서 출력한 것이다.
*/

int main(void){

    FILE* fp;
    char buf[256];
    
    fp = popen("date", "r");
    if (fp == NULL){
        fprintf(stderr, "aasd");
        exit(1);
    }
    
    if(fgets(buf,sizeof(buf),fp)==NULL){
        fprintf(stderr, "No data from pipe!\n");
        exit(1);
    }

    printf("line : %s\n",buf);
    pclose(fp);

    return 0;



}
