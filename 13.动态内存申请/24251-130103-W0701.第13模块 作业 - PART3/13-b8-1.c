/*������ 2351114 �쿡��*/
#include <stdio.h>

int main()
{
	
/*
WIN32;__linux__   �����жϲ���ϵͳ
_WIN64            �����ж�x86��x64ģʽ
_MSC_VER          �����ж�VS������
__GNUC__          �����ж�gcc������
*/

   /* ��������������໥λ�ÿɻ���������Ŀǰ#if���������VS2022�������Ȼ�ΪLinux��*/
#if _MSC_VER                     
    printf("VS2022\n");
#elif (__GNUC__) && (WIN32)        
    printf("Dev\n");
#elif __linux__                  
    printf("Linux\n");
#endif

    return 0;
}
