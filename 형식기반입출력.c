#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)
int main(void) {
    FILE* rfp, * wfp;
    int id, s1, s2, s3, s4;
    //읽기전용 파일 포인터
    if ((rfp = fopen("text.txt", "r")) == NULL) {
        perror("fopen: text.text");
        exit(1);
    }
    //쓰기전용 파일 포인터
    if ((wfp = fopen("text2.txt", "w")) == NULL) {
        perror("fopen: test2.txt");
        exit(1); //stdlib.h 파일에 존재
    }
    //형식기반 입력을 이용하여 입력을 받고, 형식기반출력을 이용하여 평균을 구한 뒤 텍스트에 출력한다.
    fprintf(wfp, "학번       평균\n");
    while (fscanf(rfp, "%d %d %d %d %d", &id, &s1, &s2, &s3, &s4) != EOF) {
        fprintf(wfp, "%d : %d\n", id, (s1 + s2 + s3 + s4) / 4);
    }
    //닫기
    fclose(rfp);
    fclose(wfp);

    return 0;
}
