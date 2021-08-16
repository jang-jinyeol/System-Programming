#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main( )
{
 int fd1, fd2, fd3;
 int size;
 fd1 = open("hello.txt", O_RDONLY);   // 읽기 전용으로 파일 오픈
 char * a = (char *)malloc(100);          // 100Byte 만큼 메모리 할당
 memset(a, 0, 100);                         // 0으로 초기화
 
 fd2 = open("world.txt", O_RDONLY);   // 읽기 전용으로 파일 오픈
 char * b = (char *)malloc(100);          // wrold.txt파일 크기 + 1 만큼 메모리 할당
 memset(b, 0, 100);                         // 0으로 초기화
 
read(fd1, a, 6);    // fd1의 파일 크기만큼 파일내용을 a에 저장
read(fd2, b, 6);    // fd2의 파일 크기만큼 파일내용을 b에 저장

    fd3 = open("Add.txt", O_RDWR | O_CREAT | O_APPEND );
  // 읽기/쓰기, 존재하지 않을경우 생성하기, 덧붙이기 옵션사용.
 
   size = strlen(a) + strlen(b);  // a크기 + b크기를 저장
   write(fd3, a, strlen(a));        // Add.txt에 hello라는 내용 덧붙이기
   write(fd3, b, strlen(b));       // Add.txt에 world라는 내용 덧붙이기
   
   char * ab = (char *)malloc(size + 1);    // a크기 + b크기 + 1 만큼 메모리 할당
 
   fd3 = open("Add.txt", O_RDONLY);  
   // 위에서 Add.txt 파일이 존재하지않는경우 생성되며,  설정한 읽기/쓰기는 적용안되므로
 
   read(fd3, ab, size + 1);    // fd3의 파일내용을 size + 1 크기만큼 읽음(저장)
 
   printf("*******  hello.txt & world.txt print!   *******\n");
   printf("%s%s\n",a, b);      // a의내용(hello.txt)과 b의내용(world.txt)을 같이 출력
 
  printf("*******          Add.txt print!         *******\n");
  printf("%s\n", ab);         // ab의 내용을 출력(Add.txt);
 
  close(fd1);      // hello.txt 파일 닫기.
  close(fd2);      // world.txt 파일 닫기.
  close(fd3);      // 생성한 Add.txt 파일 닫기.
 
  free(a);          // a 메모리 반환.
  free(b);          // b 메모리 반환.
  free(ab);         // ab 메모리 반환.
 
  return 0;
}
