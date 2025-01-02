/*2351114 朱俊泽 大数据*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */

using namespace std;
//cdhs对应5436
/* 允许定义常变量/宏定义，但不允许定义全局变量 */
//T代表10 
const char number[] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };
#if (__linux__)             //Linux
const char color[4] = { 'H','D','C','S' };
#else					    //Win
const char color[4] = { '\3','\4','\5','\6' };
//cdhs对应5436
//cdhs对应5436
/* 可以添加自己需要的函数 */
#endif

/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char *prompt, const bool landlord, const unsigned long long player)
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
				cout << color[i % 4] << number[i / 4] << " ";
			else if (i == 52)
				cout << "BJ ";
			else if (i == 53)
				cout << "RJ ";
		}
	}
	if (landlord == true)
	{
		cout << "(地主)";
	} 
	
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
int deal(unsigned long long *player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	srand((unsigned int)(time(0)));
	
	int cnt = 0;//代表发了多少牌，/3就是已经发的轮数
	
	unsigned long long card = 0;//0表示还没被分配
	
	for(int i=1;i<=17;i++)
	{
		for(int j=1;j<=3;j++)
		{
			cnt++;
			int index = rand() % 54 ; //(0)-(53)
			if(((unsigned long long)1<<index)&card)//已经分配了 
			{
				j--;
			}
			else//没有分配 
			{
				card = (card | ((unsigned long long)1<<index)); 
				player[j%3]=(player[j%3] | ((unsigned long long)1<<index));
			}
			
			
		}
		//暂时都不是地主 
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 0, player[1]);
		print("丙的牌：", 0, player[2]);
	}
	
	int res;
	
	while (1)
	{
		cout << endl<< "请选择一个地主[0-2]：" << endl;
		cin >> res;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if ((res < 0) || (res > 2)  )
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		break;
	}
	
	for(int i=0;i<54;i++)
	{
		if (card & ((unsigned long long)1 << i))
			continue;
		else
		{
			player[res]=(player[res] | (unsigned long long)1 << i);
			card=card | ((unsigned long long)1 << i);
		} 
	}
	
	return res; //此处修改为选定的地主(0-2)
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
