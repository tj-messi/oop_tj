/*大数据 2351114 朱俊泽*/
#include <stdio.h>

int main()
{
	
/*
WIN32;__linux__   用于判断操作系统
_WIN64            用于判断x86和x64模式
_MSC_VER          用于判断VS编译器
__GNUC__          用于判断gcc编译器
*/

   /* 三个条件编译的相互位置可互换（例：目前#if满足是输出VS2022，允许先换为Linux）*/
#if _MSC_VER                     
    printf("VS2022\n");
#elif (__GNUC__) && (WIN32)        
    printf("Dev\n");
#elif __linux__                  
    printf("Linux\n");
#endif

    return 0;
}
