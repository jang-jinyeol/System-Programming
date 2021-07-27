#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd;
	mode_t mode;

	//mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; //0644
	fd = open("unix.txt", O_CREAT, 0644);

	if (fd == -1){
		perror("Creat"); //오류가 발생할 경우 Creat를 출력하고 종료
		exit(1);
	}

	close(fd);


}
