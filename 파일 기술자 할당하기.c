#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd;

	//close(0); 0번 파일기술자를 close하면 아래에서 0이 출력된다.

	fd = open("unix.txt", O_RDWR);

	if (fd == -1){
		perror("Excl");
		exit(1);
	}

	printf("unix.txt : fd = %d\n", fd); //0~2는 기본적으로 할당되어 있으므로 3이 출력된다.

	close(fd);


}
