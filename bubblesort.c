#include <stdio.h>
#include <string.h>
 
#define STR_LEN     100
 
typedef const char *string;
 
void Swap(string *ps1, string *ps2);
void sort(string arr[], int len, int (*comp)(string, string));
int (*how_to_sort(const char sort_type[]))(string, string);
 
int NameAscending(string, string);
int LengthAscending(string, string);
 
int main(void)
{
    int i;
    char sort_type[STR_LEN];
 
    string arr[] = {
        "hello",
        "world",
        "my",
        "name",
        "is"
    };
    const int count = sizeof(arr)/sizeof(string);
    int (*comp)(string, string) = 0;
 
    printf("Enter sort way: ");
    scanf("%s", sort_type);
 
    // 함수 포인터를 입력받은 인자로 결정해야 하는 상황
    comp = how_to_sort(sort_type);
 
    if (comp==0)
    {
        fprintf(stderr, "Cannot find function %s\n", sort_type);
        return -1;
    }
 
    printf("Before sort: \n");
    for (i=0; i<count; ++i)
        printf("%d: %s\n", i, arr[i]);
 
    sort(arr, count, comp);
    printf("After sort: \n");
    for (i=0; i<count; ++i)
        printf("%d: %s\n", i, arr[i]);
 
    return 0;
}
 
void Swap(string *ps1, string *ps2)
{
    string tmp = *ps1;
    *ps1 = *ps2;
    *ps2 = tmp;
}
void sort(string arr[], int len, int (*comp)(string, string))
{
    int i, j;
    for (i=0; i<len-1; ++i)
        for (j=0; j<len-i-1; ++j)
            if (comp(arr[j], arr[j+1])>0)
                Swap(&arr[j], &arr[j+1]);
}
int (*how_to_sort(const char sort_type[]))(string, string)
{
    // 인자로 const char sort_type[]을 받고
    // int (*)(string, string)을 반환합니다.
 
    if (strcmp(sort_type, "NameAscending")==0)
        return NameAscending;
    else if (strcmp(sort_type, "LengthAscending")==0)
        return LengthAscending;
    else
        return 0;
}
 
int NameAscending(string str1, string str2)
{
    return strcmp(str1, str2);
}
int LengthAscending(string str1, string str2)
{
    return (int)(strlen(str1) - strlen(str2));
}
