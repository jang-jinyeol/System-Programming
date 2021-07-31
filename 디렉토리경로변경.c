#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_PATH_LEN 1024


int main(int argc, char const *argv[]) {

    char cwd[MAX_PATH_LEN + 1] = { '\0', }; //NULL로 초기화

    if (getcwd(cwd, MAX_PATH_LEN) == NULL) { //getcwd는 오류가 발생하면 NULL을 리턴한다. 성공하면 주소를 리턴 char* tmp=getcwd(NULL,BUFSIZ)
        perror("getcwd() error!");
        exit(-1);
    }

    printf("Current work directory: %s\n", cwd); //현재 디렉토리 경로 출력
        
        if (chdir("..") == -1) { //이동할 경로 성공하면 0 실패하면 -1 리턴
        perror("chdir() error!");
        exit(-1);
    }
        puts("Move to ..");

    if (getcwd(cwd, MAX_PATH_LEN) == NULL) { //현재 경로 버퍼에 저장
        perror("getcwd() error!");
        exit(-1);
}

    printf("Current work directory: %s\n", cwd); //현재 경로 출력
    return 0;

    }   
