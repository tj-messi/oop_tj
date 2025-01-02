/*朱俊泽 2351114 大数据*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
#include<climits>
using namespace std;
struct ping {
	const char* name;
	const char* description;			  
	const int num;             
	const int raw_value;           
	const int low;                 
	const int top;  
	int value;
};

const int ping_num = 3;
const char* const infor[4] = { "参数","附加参数","范围","默认值" };
const int tab_len = 7;//空格的长度 
ping menu[ping_num] = 
{
	//名，参数个数，默认值，下限，上限 
	{"-l","大小",1,64,32,64000},
	{"-n","数量",1,4,1,1024},
	{"-t","",0,0,0,1}
};
void make_tab(int len=tab_len)
{
	for(int i=1;i<=tab_len;i++)
		cout<<" ";
}

void make_line(int len)
{
	for(int i=1;i<=len;i++)
		cout<<"=";
}

int str_to_int(const char* const str, int start, int end, bool& flag) //将下标[start end)的字符串转化为int
{
	int temp = 0;
	int minus_flag = 1;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //取strlen(str)和end中较小的那个 
	if (start == real_end)
	{
		flag = false;
		return INT_MIN;
	}
	for (int i = start; i < real_end; i++)
	{
		if (i == start && str[i] == '-')
		{
			minus_flag = -1;
			continue;
		}
		temp *= 10;
		if (str[i] >= '0' && str[i] <= '9') //是数字继续
			temp += (str[i] - '0');
		else
		{
			flag = false;
			return INT_MIN;
		}
	}
	return minus_flag * temp;
}

int check_ip(const char* ip_str)
{
	string temp_str = ip_str;
	int end_index[5] = { -1,0,0,0,int(strlen(ip_str)) };		  // 数组的首元素-1不改变
	int j = 1;
	//遍历ip地址，找到'.'所在的下标
	for (int i = 0; i < int(strlen(ip_str)); i++)
	{
		if (ip_str[i] == '.')
		{
			if (j >= 4)                      // '.'的个数大于4错误
				return 0;
			else
				end_index[j++] = i;
		}
	}
	if (j < 4)								// '.'的个数小于3也错误
		return 0;
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		bool flag = true;
		temp = str_to_int(ip_str, end_index[i] + 1, end_index[i + 1], flag);
		string check_zero = temp_str.substr(end_index[i] + 1, end_index[i + 1] - end_index[i] - 1); // 截取相应的str子串
		if ((check_zero != to_string(temp) || temp < 0 || temp>255))			// 分别检测四个'.'之间的四个数字，不允许有前导0
			return 0;
	}
	return 1;
}

void usage(ping menu[ping_num])
{
	//最上一栏 
	cout<<"Usage: 14-b4-demo.exe ";
	for(int i=0;i<ping_num;i++)
	{
		cout<<"["<<menu[i].name<<" "<<menu[i].description<<"] ";
	}
	cout<<"IP地址"<<endl;
	
	//计算列表最长距离
	int max_len[4] = {0,0,0,0};
	{
		//参数表 
		int temp=strlen(infor[0]);
		for(int i=0;i<ping_num;i++)
		{
			temp=max(temp,(int)strlen(menu[i].name));
		}
		temp++;//空格
		max_len[0]=temp;
		
		//附加参数表 
		temp=strlen(infor[1]);
		for(int i=0;i<ping_num;i++)
		{
			int len=0;
			int temp_num=menu[i].num;
			while(temp_num)
			{
				len++;
				temp_num/=10;
			}
			temp=max(temp,len);
		}
		temp++;
		max_len[1]=temp;
		
		//范围表
		temp=strlen(infor[2]);
		for(int i=0;i<ping_num;i++)
		{
			int len=0;
			int temp_num=menu[i].top;
			while(temp_num)
			{
				len++;
				temp_num/=10;
			}
			temp_num=menu[i].low;
			while(temp_num)
			{
				len++;
				temp_num/=10;
			}
			temp=max(temp,len+4);
		}
		temp++;
		max_len[2]=temp;
		
		//默认值表
		 temp=strlen(infor[3]);
		for(int i=0;i<ping_num;i++)
		{
			int len=0;
			int temp_num=menu[i].raw_value;
			while(temp_num)
			{
				len++;
				temp_num/=10;
			}
			temp=max(temp,len);
		}
		temp++;
		max_len[3]=temp;
	}
	
	{
		make_tab();
		make_line(max_len[3]+max_len[2]+max_len[1]+max_len[0]+1);
		cout<<endl;
		make_tab(tab_len+1);
		for(int i=0;i<4;i++)
		{
			cout<< setiosflags(ios::left)<<setw(max_len[i])<<setfill(' ')<<infor[i];
		}
		cout<<endl;
		make_tab();
		make_line(max_len[3]+max_len[2]+max_len[1]+max_len[0]+1);
		cout<<endl;
	}
	
	{
		for(int i=0;i<ping_num;i++)
		{
			make_tab(tab_len+1);
			cout<< setiosflags(ios::left)<<setw(max_len[0])<<setfill(' ')<<menu[i].name;
			cout<< setiosflags(ios::left)<<setw(max_len[1])<<setfill(' ')<<menu[i].num;
			char temp[256];
			sprintf(temp,"%s%d%s%d%s","[",menu[i].low,"..",menu[i].top,"]");
			cout<< setiosflags(ios::left)<<setw(max_len[2])<<setfill(' ')<<temp;
			cout<< setiosflags(ios::left)<<setw(max_len[3])<<setfill(' ')<<menu[i].raw_value<<endl;			 
		} 
	}
	
	make_tab();
	make_line(max_len[3]+max_len[2]+max_len[1]+max_len[0]+1);
	cout<<endl<<endl;
} 

int main(int argc, char* argv[])
{
	if (argc < 2)//缺少参数 
	{
		usage(menu);
		return 0;
	}
	if (check_ip(argv[argc - 1]) == 0)
	{
		cout << "IP地址错误" << endl;
		return 0;
	}
	for(int i=0;i<ping_num;i++)
	{
		menu[i].value = menu[i].raw_value;
	}
	for(int i=1;i<argc-1;i++)
	{
		int id = 0, value = 0;
		if (argv[i][0] != '-')
		{
			cout << "参数" << argv[i] << "不是以-开头的合法参数" << endl;
			return 0;
		}
		int j=0;
		for (j = 0; j < ping_num; j++)
		{
			if (strcmp(argv[i], menu[j].name) == 0)
			{
				id = j;//用于定位当前参数在para_menu中的位置
				break;
			}
		}
		if (j == ping_num)
		{
			cout << "参数" << argv[i] << "不存在" << endl;
			return 0;
		}
		if (menu[id].num==0)            // 当前参数的附加参数个数为0，则不需要再次判断
		{
			menu[id].value = 1;            // 有参数为1，无参数为0，当然这是根据"-t"进行的特判
			continue;
		}
		if (argv[i + 1][0] == '-' || (i + 1 == argc - 1))
		{
			cout << "参数" << argv[i] << "没有后续参数" << endl;
			return 0;
		}
		bool checkend=false;
		value = str_to_int(argv[i + 1], 0, strlen(argv[i + 1]),checkend);
		if (value<menu[id].low || value>menu[id].top)
			menu[id].value = menu[id].raw_value;
		else
			menu[id].value = value;
		++i; //下一位参数已经被判断，现在跳过
	} 
	cout << "参数检查通过" << endl;
	for (int i = 0; i < ping_num; i++)
		cout <<menu[i].name << " 参数：" << menu[i].value << endl;
	cout << "IP地址：" << argv[argc - 1] << endl;

	return 0;
}
