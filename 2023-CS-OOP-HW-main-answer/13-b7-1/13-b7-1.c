/* 2150792 ţ»�� �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc/free��
/*
WIN32;__linux__   �����жϲ���ϵͳ
_WIN64            �����ж�x86��x64ģʽ
_MSC_VER          �����ж�VS������
__GNUC__          �����ж�gcc������
*/
int main()
{
    /* ��������������໥λ�ÿɻ���������Ŀǰ#if���������VS2022�������Ȼ�ΪLinux��*/

#if _MSC_VER                       //MSVC������,VS��ʹ��,���޷��ж����ĸ��汾��VS
    printf("VS2022\n");
#elif (__GNUC__) && (WIN32)        //windows����ϵͳ��GCC������,Ŀǰ��װ��Dev��ʹ��
    printf("Dev\n");
#elif __linux__                    //Linux����ϵͳ,����Ҫ����������
    printf("Linux\n");
#endif

    return 0;
}
