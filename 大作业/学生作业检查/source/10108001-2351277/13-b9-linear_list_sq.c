#if (__GNUC__==8)//Linux
#include <unistd.h>		//exit����
#endif
#if(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
