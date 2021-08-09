#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//메시지 큐 생성 및 메시지 전송하기

struct mymsgbuf {

    long mtype; //메시지 유형으로, 양수를 지정한다.
    char mtext[80]; //msgsnd 함수의 msgsz로 지정한 크기의 버퍼로, 메시지 내용이 저장된다.
};

int main(void){
    key_t key;
    int msgid;
    struct mymsgbuf mesg;

    key = ftok("keyfile", 1);
    //메시지 큐 식별자 생성
    msgid = msgget(key, IPC_CREAT|0644); //메시지 큐를 구별하는 키, 메시지 큐의 속성을 설정하는 플래그

    if (msgid == -1){
        perror("msgget");
        exit(1);
    }

    mesg.mtype = 1;

    strcpy(mesg.mtext, "Message Q Test");

    if(msgsnd(msgid,(void*)&mesg,80,IPC_NOWAIT) == -1){
        perror("msgsnd");
        exit(1);
    }
return 0;
}

/*
수신 부분
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct mymsgbuf {

    long mtype; //메시지 유형으로, 양수를 지정한다.
    char mtext[80]; //msgsnd 함수의 msgsz로 지정한 크기의 버퍼로, 메시지 내용이 저장된다.
};

int main(void){
    key_t key;
    int msgid, len;
    struct mymsgbuf inmsg;

    key = ftok("keyfile", 1);
    //메시지 큐 식별자 생성
    if((msgid = msgget(key, 0))<0){ //메시지 큐를 구별하는 키, 메시지 큐의 속성을 설정하는 플래그
       perror("msgget");
        exit(1);
    }

 len = msgrcv(msgid,&inmsg,80,0,0); //실패시 -1 성공시 읽어온 메시지의 바이트 수를 리턴한다.
 printf("Received Msg = %s, Len=%d\n",inmsg.mtext, len);
return 0;
}
*/
