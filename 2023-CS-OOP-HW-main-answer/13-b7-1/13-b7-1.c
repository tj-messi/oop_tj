/* 2150792 牛禄阳 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc/free用
/*
WIN32;__linux__   用于判断操作系统
_WIN64            用于判断x86和x64模式
_MSC_VER          用于判断VS编译器
__GNUC__          用于判断gcc编译器
*/
int main()
{
    /* 三个条件编译的相互位置可互换（例：目前#if满足是输出VS2022，允许先换为Linux）*/

#if _MSC_VER                       //MSVC编译器,VS所使用,但无法判断是哪个版本的VS
    printf("VS2022\n");
#elif (__GNUC__) && (WIN32)        //windows操作系统且GCC编译器,目前安装的Dev所使用
    printf("Dev\n");
#elif __linux__                    //Linux操作系统,不需要编译器限制
    printf("Linux\n");
#endif

    return 0;
}
