/*2150792 计科 牛禄阳*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */

using namespace std;

/* 允许定义常变量/宏定义，但不允许定义全局变量 */
//cdhs对应5436 
const char Puke_number[13] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };
#if (__linux__)             //Linux
const char Puke_color[4] = { 'H','D','C','S' };
#else					    //Win
const char Puke_color[4] = { '\3','\4','\5','\6' };
#endif
//cdhs对应5436 
//cdhs对应5436 

/* 可以添加自己需要的函数 */
int get_input_int(int low, int high, int& elem_int, int base)
{
	cout << endl << "请选择一个地主[0-2]：" << endl;
	while (1)
	{
		cin >> elem_int;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << endl << "请选择一个地主[0-2]：" << endl;
			continue;
		}
		if (((elem_int < low) || (elem_int > high) || (elem_int % base != 0)) && (cin.good() == 1))
		{
			cout << endl << "请选择一个地主[0-2]：" << endl;
			continue;
		}
		if (elem_int >= low && elem_int <= high && elem_int % base == 0)
			break;
	}
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* 只允许定义不超过三个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	static int num_times = 1, cnt = 0;
	if (cnt++ % 3 == 0 && num_times <= 17)
		cout << dec << "第" << num_times++ << "轮结束：" << endl;


	cout << prompt;
	for (int i = 0; i < 54; i++)
	{
		if (player & ((unsigned long long) 1 << i))      // 当前位置有牌
		{
			if (i <= 51)
				cout << Puke_color[i % 4] << Puke_number[i / 4] << " ";
			else if (i == 52)
				cout << "BJ ";
			else if (i == 53)
				cout << "RJ ";
		}
	}
	if (landlord == true)
		cout << "(地主)";
	cout << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：发牌（含键盘输入地主）
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */

	srand((unsigned int)(time(0)));								 // 使用当前时间作为随机种子
	static long long Puke=0x003FFFFFFFFFFFFF;					 // 低位赋值为54位1
	int landlord = 0;
	for (int i = 0; i < 17; i++)								 // 共发牌17轮
	{
		for (int j = 0; j < 3; j++)								 // 一次为三个人发牌
		{
			int index = rand() % 54;                             // 生成0-53范围内的随机数
			if (Puke & ((long long) 1 << index))                 // 当前位置没有被分配
			{
				Puke = (Puke & ((long long)(0xFFDFFFFFFFFFFFFF) >> (53 - index)));// 将Puke已经发牌的位置0
				player[j]= (player[j] | ((unsigned long long) 1 << index));	      // 将player被发牌的位置1	
			}
			else                                                 // 当前位置已被分配 
				--j;
		}
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 0, player[1]);
		print("丙的牌：", 0, player[2]);
		//cout << "0x" << setfill('0') << setw(16) << hex << Puke << endl;//输出开关数值
		//cout << "0x" << setfill('0') << setw(16) << hex << player[0] << endl;//输出开关数值
		//cout << "0x" << setfill('0') << setw(16) << hex << player[1] << endl;//输出开关数值
		//cout << "0x" << setfill('0') << setw(16) << hex << player[2] << endl;//输出开关数值
	}
	get_input_int(0, 2, landlord, 1);
	for (int i = 0; i < 54; i++)								// 遍历剩余的扑克牌堆，将剩余的牌全发给地主
	{
		if (Puke & ((long long)1 << i))                         // 当前位置没有被分配
		{
			Puke = (Puke & ((long long)(0xFFDFFFFFFFFFFFFF) >> (53 - i)));         // 将Puke已经发牌的位置0
			player[landlord] = (player[landlord] | ((unsigned long long) 1 << i)); // 将landlord被发牌的位置1	
		}
	}
	return landlord;											 // 此处修改为选定的地主(0-2)
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", (landlord == 0), player[0]);
	print("乙的牌：", (landlord == 1), player[1]);
	print("丙的牌：", (landlord == 2), player[2]);

	return 0;
}
