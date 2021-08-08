#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1
int main(){
        int fd[2];
        pid_t pid;
        char buf[MAX_BUF];

        if(pipe(fd) < 0){
                printf("pipe error\n");
                exit(1);
        }
        if((pid=fork())<0){
                printf("fork error\n");
                exit(1);
        }

        if(pid>0){ //parent process
                close(fd[READ]);
                strcpy(buf,"message from parent");
                write(fd[WRITE],buf,strlen(buf)+1);
        }else{  //child process
                close(fd[WRITE]);
                read(fd[READ],buf,MAX_BUF);
                printf("child got message : %s\n",buf);
        }
        exit(0);
}
