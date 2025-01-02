/* 2150792 计科 牛禄阳 */
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
using namespace std;
struct student {
	int no;
	char* name;
	char* school;
};
const int bufferSize = 256; // 一个足够大的缓冲区大小
void checkNull(void* ptr, const char* errormsg)
{
	if (ptr == NULL)
	{
#ifdef __cplusplus
		cout << errormsg << " 退出进程." << endl;
#else
		printf("%s 退出进程.\n", errormsg);
#endif
		exit(-1);
	}
}
int main()
{
	ifstream in;
	ofstream out;
	in.open("stulist.txt", ios::in);
	out.open("result.txt", ios::out);
	if (!in.is_open())
	{
		cout << "打开stulist.txt文件失败" << endl;
		return -1;
	}
	if (!out.is_open())
	{
		cout << "打开result.txt文件失败" << endl;
		in.close();//关闭输入文件
		return -1;
	}
	int recruit_num = 0, application_num = 0;
	in >> recruit_num >> application_num;
	student* total_infor = new(nothrow) student[application_num];
	checkNull(total_infor, "new分配空间失败");
	/*======读入所有成员信息======*/
	for (int i = 0; i < application_num; i++)
	{
		int temp_no;
		char temp_name[bufferSize], temp_school[bufferSize];
		in >> temp_no >> temp_name >> temp_school;
		total_infor[i].name = new(nothrow) char[strlen(temp_name) + 1];
		checkNull(total_infor[i].name, "new分配空间失败");
		total_infor[i].school = new(nothrow)char[strlen(temp_school) + 1];
		checkNull(total_infor[i].school, "new分配空间失败");
		total_infor[i].no = temp_no;
		for (int k = 0;; k++)
		{
			(total_infor[i].name)[k] = temp_name[k];
			if (temp_name[k] == '\0')
				break;
		}
		for (int k = 0;; k++)
		{
			(total_infor[i].school)[k] = temp_school[k];
			if (temp_school[k] == '\0')
				break;
		}
	}

	/*======O(n*n)时间随机生成随机数======*/
	srand((unsigned int)(time(0)));
	int* randomnumlist = new (nothrow)int[recruit_num];
	checkNull(randomnumlist, "new分配空间失败");
	for (int i = 0; i < recruit_num;)
	{
		int j = 0;
		int randomNum = rand() % application_num;//生成[0, application_num-1]的随机数
		for (j = 0; j < i; j++)
		{
			if (randomNum == randomnumlist[j])
				break;
		}//判断这个数字之前有没有生成过
		if (j == i)
			randomnumlist[i++] = randomNum;
	}
	for (int i = 0; i < recruit_num; i++)
		out << total_infor[randomnumlist[i]].no << " " << total_infor[randomnumlist[i]].name << " " << total_infor[randomnumlist[i]].school << endl;

	/*======程序结束，遍历释放new空间======*/
	for (int i = 0; i < application_num; i++)
	{
		delete[]total_infor[i].school;
		delete[]total_infor[i].name;
	}
	delete[]total_infor;
	in.close();
	out.close();
	return 0;
}
/*
首先，因为姓名和毕业学校的长度均不固定且个体间差异可能较大，所以这两项需要二次按需申请
报名号位数统一，直接设置为int就可以
如果申请连续空间，一个学生至少有一个int和两个指针是连续的，也就是有12字节，假设报名一万名学生
耗费了120000B = 0.114MB 的内存空间，如果有一百万名学生，需要11.4MB的连续空间
至于二次申请的空间，显然不需要连续，因为可以通过指针访问。

如果申请链式空间，一个学生结构体中有一个int和三个指针，相当于每次都要额外使用一个指针的空间指向
链表中下一个节点，也就是下一个学生的位置。相比较数组形式其会浪费一定的内存，但也在可接受范围内。

再考虑问题需要随机抽取N位学生，显然需要随机生成N个1-M内不重复的随机数。这些数字代表这个学生在数组/链表中的位置。
所以这个问题生成随机数的方式和结合与采取的存储方式有紧密关联
首先，需要考虑随机数的生成，有两种算法，一种是洗牌算法，复杂度为O(m)；另一种是O(n*n);
可以根据实际问题的大小选择使用哪种，本人选择用n*n实现。
在已经生成完成随机数的基础上，如果使用数组方式，只需要根据下标索引取数

如果使用链表方式，最快的方法是对生成的随机数按递增排序这个需要O(NlogN)，然后再从头遍历链表，通过O(M)时间得到需要确定的学生。
链表方式无论是从内存还是从时间上都劣于数组方式。
但链表的好处是增删节点比较方便，因此可以随机生成一个数字，然后把这个数字对应位置的链表节点取出后再删除此节点
下次生成随机数的范围减小1，这个算法对应每个随机数都要遍历一次链表，所以是O(m*n)。

因此，可以看到，无论m和n的大小如何，用数组方式实现总有时间复杂度更低的算法。

数组方式需要考虑的问题是内存中是否有那么大的空间，但根据上述的推导，哪怕一百万名学生占用的连续空间
也只有11.4MB。显然通过动态申请，可以在堆中获得连续空间，所以本题用数组解决更优秀。
*/
