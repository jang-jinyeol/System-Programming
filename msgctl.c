#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
/*
IPC_RMID 옵션으로 받은 메시지를 삭제한다.
12~13 행에서 이전과 같은 키를 생성해 메시지 큐 식별자를 리턴 받는다
*/
int main(void){
    key_t key;
    int msgid;

    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT|0644);
      
      if (msgid == -1){
        perror("msgget");
        exit(1);
    }

    printf("Before IPC_RMID\n");
    system("ipcs -q");
    msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);
    printf("After IPC_RMID\n");
    system("ipcs -q");

    return 0;
}
