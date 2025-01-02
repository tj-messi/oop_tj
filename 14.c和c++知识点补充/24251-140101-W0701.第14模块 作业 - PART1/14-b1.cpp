/*朱俊泽 2351114 大数据*/
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
	while(1)
	{
		char id;
		char state[5];//"on或者off"
		short now = 0;//一开始全部是关闭 
		cout << "初始状态："<<endl;
		for (int i = 0; i < 10; i++)
			cout << setiosflags(ios::left)  << setfill(' ') << setw(4) << char('A' + i);
		cout<<endl;
		for (int i = 0; i < 10; i++)
			cout << setiosflags(ios::left)  << setfill(' ') << setw(4) << ((now & (1 << i)) ? "ON" : "OFF");
		cout<<endl<<endl;
		while(1)
		{
			cout << "请以(\"A On /J Off\"形式输入，输入\"Q on/off\"退出)" << endl;
			cin>>id;
			cin>>state;
			//转大写 
			if(id>='a'&&id<='z')
					id+='A'-'a';
			for(int i=0;i<3;i++)
			{
				if(state[i]>='a'&&state[i]<='z')
					state[i]+='A'-'a';
			}
			if(id=='Q')
				return 0;
			if(!(id>='A'&&id<='J'))
				continue;
			if(state[0]=='O'&&state[1]=='F'&&state[2]=='F') 
			{
				now = (now & (short(0xFDFF) >> (short)fabs('J' - id)));
				cout<<"当前状态：";
				cout<<setiosflags(ios::left);
				cout << "0x" << setfill('0') << setw(4) << hex << now<< endl;
				cout<<resetiosflags(ios::left);
				for (int i = 0; i < 10; i++)
					cout << setiosflags(ios::left)  << setfill(' ') << setw(4) << char('A' + i);
				cout<<endl;
				for (int i = 0; i < 10; i++)
					cout << setiosflags(ios::left)  << setfill(' ') << setw(4) << ((now & (1 << i)) ? "ON" : "OFF");
				cout<<endl<<endl;
			}
			else if(state[0]=='O'&&state[1]=='N')
			{
				now = (now| (0x1 << (id - 'A')));
				cout<<"当前状态：";
				cout<<resetiosflags(ios::left);
				cout << "0x" << setfill('0') << setw(4) << hex << now << endl;
				cout<<resetiosflags(ios::left);
				for (int i = 0; i < 10; i++)
					cout << setiosflags(ios::left)  << setfill(' ') << setw(4) << char('A' + i);
				cout<<endl;
				for (int i = 0; i < 10; i++)
					cout << setiosflags(ios::left)  << setfill(' ') << setw(4) << ((now & (1 << i)) ? "ON" : "OFF");
				cout<<endl<<endl;
			}
			else
				continue;
		}
	}
	return 0;
} 
