#include <stdio.h>                        


void Print(int a) {

    printf("%d", a);
}

int main()
{

    void* test;

    test = Print;
    
    (*(void(*)(int))test)(5); //형변환 후 역참조
 
    return 0;
}
