/*�쿡�� 2351114 ������*/
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
const char* const infor[4] = { "����","���Ӳ���","��Χ","Ĭ��ֵ" };
const int tab_len = 7;//�ո�ĳ��� 
ping menu[ping_num] = 
{
	//��������������Ĭ��ֵ�����ޣ����� 
	{"-l","��С",1,64,32,64000},
	{"-n","����",1,4,1,1024},
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

int str_to_int(const char* const str, int start, int end, bool& flag) //���±�[start end)���ַ���ת��Ϊint
{
	int temp = 0;
	int minus_flag = 1;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //ȡstrlen(str)��end�н�С���Ǹ� 
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
		if (str[i] >= '0' && str[i] <= '9') //�����ּ���
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
	int end_index[5] = { -1,0,0,0,int(strlen(ip_str)) };		  // �������Ԫ��-1���ı�
	int j = 1;
	//����ip��ַ���ҵ�'.'���ڵ��±�
	for (int i = 0; i < int(strlen(ip_str)); i++)
	{
		if (ip_str[i] == '.')
		{
			if (j >= 4)                      // '.'�ĸ�������4����
				return 0;
			else
				end_index[j++] = i;
		}
	}
	if (j < 4)								// '.'�ĸ���С��3Ҳ����
		return 0;
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		bool flag = true;
		temp = str_to_int(ip_str, end_index[i] + 1, end_index[i + 1], flag);
		string check_zero = temp_str.substr(end_index[i] + 1, end_index[i + 1] - end_index[i] - 1); // ��ȡ��Ӧ��str�Ӵ�
		if ((check_zero != to_string(temp) || temp < 0 || temp>255))			// �ֱ����ĸ�'.'֮����ĸ����֣���������ǰ��0
			return 0;
	}
	return 1;
}

void usage(ping menu[ping_num])
{
	//����һ�� 
	cout<<"Usage: 14-b4-demo.exe ";
	for(int i=0;i<ping_num;i++)
	{
		cout<<"["<<menu[i].name<<" "<<menu[i].description<<"] ";
	}
	cout<<"IP��ַ"<<endl;
	
	//�����б������
	int max_len[4] = {0,0,0,0};
	{
		//������ 
		int temp=strlen(infor[0]);
		for(int i=0;i<ping_num;i++)
		{
			temp=max(temp,(int)strlen(menu[i].name));
		}
		temp++;//�ո�
		max_len[0]=temp;
		
		//���Ӳ����� 
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
		
		//��Χ��
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
		
		//Ĭ��ֵ��
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
	if (argc < 2)//ȱ�ٲ��� 
	{
		usage(menu);
		return 0;
	}
	if (check_ip(argv[argc - 1]) == 0)
	{
		cout << "IP��ַ����" << endl;
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
			cout << "����" << argv[i] << "������-��ͷ�ĺϷ�����" << endl;
			return 0;
		}
		int j=0;
		for (j = 0; j < ping_num; j++)
		{
			if (strcmp(argv[i], menu[j].name) == 0)
			{
				id = j;//���ڶ�λ��ǰ������para_menu�е�λ��
				break;
			}
		}
		if (j == ping_num)
		{
			cout << "����" << argv[i] << "������" << endl;
			return 0;
		}
		if (menu[id].num==0)            // ��ǰ�����ĸ��Ӳ�������Ϊ0������Ҫ�ٴ��ж�
		{
			menu[id].value = 1;            // �в���Ϊ1���޲���Ϊ0����Ȼ���Ǹ���"-t"���е�����
			continue;
		}
		if (argv[i + 1][0] == '-' || (i + 1 == argc - 1))
		{
			cout << "����" << argv[i] << "û�к�������" << endl;
			return 0;
		}
		bool checkend=false;
		value = str_to_int(argv[i + 1], 0, strlen(argv[i + 1]),checkend);
		if (value<menu[id].low || value>menu[id].top)
			menu[id].value = menu[id].raw_value;
		else
			menu[id].value = value;
		++i; //��һλ�����Ѿ����жϣ���������
	} 
	cout << "�������ͨ��" << endl;
	for (int i = 0; i < ping_num; i++)
		cout <<menu[i].name << " ������" << menu[i].value << endl;
	cout << "IP��ַ��" << argv[argc - 1] << endl;

	return 0;
}
