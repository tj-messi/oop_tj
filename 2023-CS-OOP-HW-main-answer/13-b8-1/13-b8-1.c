#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int p[10];
    for (int i = 0; i < 10; ++i)
        p[i] = i;
    p[10] = 1;
    p[11] = 2;
    p[12] = 3;
    p[13] = 4;
    p[14] = 5;
    //p[15] = 6;
    p[16] = 7;
    printf("addr:%p\n", p);
    for (int i = -4; i < 17; i++)
        printf("%p:%02x\n", (p + i), p[i]);
    return 0;
}
