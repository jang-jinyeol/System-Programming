#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> // for open
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

/*
read(2) 함수 기능
파일을 읽는 함수입니다.

함수 원형
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t nbytes);
매개변수
int fd

읽을 파일의 파일 디스크립터

 

void *buf

읽어들인 데이터를 저장할 버퍼(배열)

 

size_t nbytes

읽어들일 데이터의 최대 길이 (buf의 길이보다 길어선 안됨)

반환값
읽어들인 데이터의 길이
무조건 nbytes 가 리턴되는 것은 아님. 중간에 파일의 끝을 만난다면 거기까지만 읽기 때문
*/
//-------------------------------------------------------------//
/*
write(2) 함수 기능
파일에 write 하는 시스템 함수입니다.

함수 원형
#include <unistd.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t nbytes);
매개변수
fd

대상 파일 디스크립터

 

buf

쓰고자 하는 데이터가 담긴 버퍼

 

nbytes

쓰고자 하는 데이터의 길이 ( buf의 길이보다 길어선 안됨 )

반환값
성공 시 실제로 쓰여진 데이터의 길이 리턴

에러 시 -1 리턴 후 errno 설정

 

-1 이 아니더라도 자신이 쓰고자 한 데이터의 길이 nbytes 보다 적게 쓰여졌다면 에러라고 볼 수 있습니다.
*/

int main() {
    char buf[BUFFER_SIZE];
    int length;

    // 0번 파일(표준 입력) 에서 입력을 받아옴
    length = read(0, buf, BUFFER_SIZE);
    
    // 1번 파일(표준 출력)으로 출력함
    if (write(1, buf, length) != length) {
        fprintf(stderr, "write error\n");
        exit(1);
    }
	exit(0);
}
