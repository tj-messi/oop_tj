#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <cstring>
using namespace std;
int main()
{
    int p[10] = { 0,1,2,3,4,5,6,7,8 };
    p[10] = 10;    //此句越界
    p[11] = 11;    //此句越界
    p[14] = 14;    //此句越界
    p[15] = 15;    //此句越界
    cout << "addr:" << hex << (void*)(p) << endl;
    for (int i = -4; i < 16; i++)
        cout << hex << (void*)(p + i) << ":" << int(p[i]) << endl;
    return 0;
}
