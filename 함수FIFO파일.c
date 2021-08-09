#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
FIFO 파일은 서버에선 O_WRONLY 클라이언트에선 O_RDONLY로 설정한다.
*/
int main(void){
    int pd, n;
    char msg[] = "Hello, FIFO";
    printf("Server ======\n");

    if(mkfifo("./HAN-FIFO", 0666) == -1){
        perror("mkfifo");
        exit(1);
    }

    if((pd = open("./HAN-FIFO", O_WRONLY)) == -1){
        perror("open");
        exit(1);
    }

    printf("To Client : %s\n", msg);
    n = write(pd, msg, strlen(msg)+1);
    if(n == -1){
        perror("write");
        exit(1);
    }
    close(pd);
}
/*
client 부분

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){

int pd, n;
char inmsg[80];

    if((pd = open("./HAN-FIFO", O_RDONLY)) == -1){
        perror("open");
        exit(1);
    }

    printf("Client ======\n");
    write(1, "From Server :",13);

    while((n=read(pd, inmsg, 80)) > 0){
        write(1, inmsg, n);
    }

    if(n==-1){
        perror("read");
        exit(1);
    }

    write(1, "\n",1);
    close(pd);

    return 0;
}

*/
