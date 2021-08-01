#include <stdlib.h>
#include <stdio.h>

//시스템 함수 사용하기
//시스템 함수는 프로그램 안에서 새로운 프로그램을 실행하는 가장 간단한 방법이다.
//그러나 시스템 함수는 명령을 실행하기 위해 쉘까지 동작시키므로 비효율적이다.
//시스템 함수로 명령을 실행하면 본 쉘로 실행되고 -c 옵션이 지정된다.
int main(void){
  int a;
  a = system("ps -ef | grep han > han.txt");
  printf("Return Value : %d\n", a);

  return 0;
}
