#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>


int main(int argc, char const * argv[]){

    DIR * dirp; //DIR은 열린 디렉토리에 관한 정보를 담고 있는 구조체로 <dirent.h> 파일에 정의되어 있다.
    struct stat fileInfo;//파일 정보를 담을 구조체
    struct dirent * dirInfo; //struct dirent는 디렉토리에 있는 항목의 정보를 담은 구조체

    if(argc != 2){
        printf("Usagae: %s [pathname]\n", argv[0]);
        exit(-1);
    }

    if(stat(argv[1],&fileInfo)==-1){
        perror("stat() error!");
        exit(-1);
    }

    if(!S_ISDIR(fileInfo.st_mode)){ //디렉토리 파일이 아닐경우
        fprintf(stderr,"%s is not directory!\n", argv[1]);
        exit(-1);
    }

    dirp = opendir(argv[1]);//opendir함수는 수행을 성공하면 디렉토리를 가리키는 DIR 포인터를 리턴한다.
    //readdir 함수는 인자로 지정한 DIR 포인터가 가리키는 디렉토리의 내용을 한 번에 하나씩 읽어온다.
    while((dirInfo = readdir(dirp)) != NULL){ //디렉토리에 있는 항목의 정보를 담은 struct dirent* dirInfo(구조체 변수)

        printf("inode No.: %lld, Name: %s\n",dirInfo->d_ino,dirInfo->d_name);
    }

    closedir(dirp);
    

}
