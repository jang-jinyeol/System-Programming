#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void myError(const char* msg);
void fileType(const struct stat* fileInfo);
void fileMode(const struct stat* fileInfo);
//main에서 명령행 인자로 받는다.
int main(int argc, char const* argv[])
{
    struct stat fileInfo;
    struct passwd* userInfo;

    if (argc != 2) {
        printf("Usage: %s [pathname]\n", argv[0]);
        exit(-1);
    }

    printf("File name or path: %s\n", argv[1]);
    if (stat(argv[1], &fileInfo) == -1) {
        myError("stat() error!");
    }
    printf("File type: ");
    fileType(&fileInfo);

    printf("File permission: ");
    fileMode(&fileInfo);

    printf("File size: %ld\n", fileInfo.st_size);
//
    userInfo = getpwuid(fileInfo.st_uid);
    printf("Owner name: %s\n", userInfo->pw_name);

    return 0;
}

void myError(const char* msg)
{
    perror(msg);
    exit(-1);
}
//파일의 종류 검색 관련 매크로 함수 16진수로 st_mode와 and 연산을 한다.
void fileType(const struct stat* fileInfo) {
    if (S_ISREG(fileInfo->st_mode)) {
        printf("Regular file");
    }
    else if (S_ISDIR(fileInfo->st_mode)) {
        printf("Directory");
    }
    else if (S_ISLNK(fileInfo->st_mode)) {
        printf("Symbolic link");
    }
    else if (S_ISSOCK(fileInfo->st_mode)) {
        printf("Socket");
    }
    else if (S_ISFIFO(fileInfo->st_mode)) {
        printf("FIFO");
    }
    else if (S_ISCHR(fileInfo->st_mode)) {
        printf("Character device");
    }
    else if (S_ISBLK(fileInfo->st_mode)) {
        printf("Block device");
    }
    else if (S_TYPEISMQ(fileInfo)) {
        printf("Message queue");
    }
    else if (S_TYPEISSEM(fileInfo)) {
        printf("Semaphore");
    }
    else if (S_TYPEISSHM(fileInfo)) {
        printf("Shared memory");
    }
    puts("");
}
//파일의 접근 권한 검색 관련 상수(POSIX) 함수 8진수로 st_mode와 and 연산을 한다.
void fileMode(const struct stat* fileInfo)
{
    // User
    if (S_IRUSR & fileInfo->st_mode) { printf("r"); }
    else { printf("-"); }

    if (S_IWUSR & fileInfo->st_mode) { printf("w"); }
    else { printf("-"); }

    if (S_IXUSR & fileInfo->st_mode) { printf("x"); }
    else { printf("-"); }

    // Group
    if (S_IRGRP & fileInfo->st_mode) { printf("r"); }
    else { printf("-"); }

    if (S_IWGRP & fileInfo->st_mode) { printf("w"); }
    else { printf("-"); }

    if (S_IXGRP & fileInfo->st_mode) { printf("x"); }
    else { printf("-"); }
    // Others
    if (S_IROTH & fileInfo->st_mode) { printf("r"); }
    else { printf("-"); }

    if (S_IWOTH & fileInfo->st_mode) { printf("w"); }
    else { printf("-"); }

    if (S_IXOTH & fileInfo->st_mode) { printf("x"); }
    else { printf("-"); }

    puts("");
}

