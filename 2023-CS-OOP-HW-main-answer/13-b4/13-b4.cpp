/* 2150792 �ƿ� ţ»�� */
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
const int bufferSize = 256; // һ���㹻��Ļ�������С
void checkNull(void* ptr, const char* errormsg)
{
	if (ptr == NULL)
	{
#ifdef __cplusplus
		cout << errormsg << " �˳�����." << endl;
#else
		printf("%s �˳�����.\n", errormsg);
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
		cout << "��stulist.txt�ļ�ʧ��" << endl;
		return -1;
	}
	if (!out.is_open())
	{
		cout << "��result.txt�ļ�ʧ��" << endl;
		in.close();//�ر������ļ�
		return -1;
	}
	int recruit_num = 0, application_num = 0;
	in >> recruit_num >> application_num;
	student* total_infor = new(nothrow) student[application_num];
	checkNull(total_infor, "new����ռ�ʧ��");
	/*======�������г�Ա��Ϣ======*/
	for (int i = 0; i < application_num; i++)
	{
		int temp_no;
		char temp_name[bufferSize], temp_school[bufferSize];
		in >> temp_no >> temp_name >> temp_school;
		total_infor[i].name = new(nothrow) char[strlen(temp_name) + 1];
		checkNull(total_infor[i].name, "new����ռ�ʧ��");
		total_infor[i].school = new(nothrow)char[strlen(temp_school) + 1];
		checkNull(total_infor[i].school, "new����ռ�ʧ��");
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

	/*======O(n*n)ʱ��������������======*/
	srand((unsigned int)(time(0)));
	int* randomnumlist = new (nothrow)int[recruit_num];
	checkNull(randomnumlist, "new����ռ�ʧ��");
	for (int i = 0; i < recruit_num;)
	{
		int j = 0;
		int randomNum = rand() % application_num;//����[0, application_num-1]�������
		for (j = 0; j < i; j++)
		{
			if (randomNum == randomnumlist[j])
				break;
		}//�ж��������֮ǰ��û�����ɹ�
		if (j == i)
			randomnumlist[i++] = randomNum;
	}
	for (int i = 0; i < recruit_num; i++)
		out << total_infor[randomnumlist[i]].no << " " << total_infor[randomnumlist[i]].name << " " << total_infor[randomnumlist[i]].school << endl;

	/*======��������������ͷ�new�ռ�======*/
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
���ȣ���Ϊ�����ͱ�ҵѧУ�ĳ��Ⱦ����̶��Ҹ���������ܽϴ�������������Ҫ���ΰ�������
������λ��ͳһ��ֱ������Ϊint�Ϳ���
������������ռ䣬һ��ѧ��������һ��int������ָ���������ģ�Ҳ������12�ֽڣ����豨��һ����ѧ��
�ķ���120000B = 0.114MB ���ڴ�ռ䣬�����һ������ѧ������Ҫ11.4MB�������ռ�
���ڶ�������Ŀռ䣬��Ȼ����Ҫ��������Ϊ����ͨ��ָ����ʡ�

���������ʽ�ռ䣬һ��ѧ���ṹ������һ��int������ָ�룬�൱��ÿ�ζ�Ҫ����ʹ��һ��ָ��Ŀռ�ָ��
��������һ���ڵ㣬Ҳ������һ��ѧ����λ�á���Ƚ�������ʽ����˷�һ�����ڴ棬��Ҳ�ڿɽ��ܷ�Χ�ڡ�

�ٿ���������Ҫ�����ȡNλѧ������Ȼ��Ҫ�������N��1-M�ڲ��ظ������������Щ���ִ������ѧ��������/�����е�λ�á�
���������������������ķ�ʽ�ͽ�����ȡ�Ĵ洢��ʽ�н��ܹ���
���ȣ���Ҫ��������������ɣ��������㷨��һ����ϴ���㷨�����Ӷ�ΪO(m)����һ����O(n*n);
���Ը���ʵ������Ĵ�Сѡ��ʹ�����֣�����ѡ����n*nʵ�֡�
���Ѿ��������������Ļ����ϣ����ʹ�����鷽ʽ��ֻ��Ҫ�����±�����ȡ��

���ʹ������ʽ�����ķ����Ƕ����ɵ���������������������ҪO(NlogN)��Ȼ���ٴ�ͷ��������ͨ��O(M)ʱ��õ���Ҫȷ����ѧ����
����ʽ�����Ǵ��ڴ滹�Ǵ�ʱ���϶��������鷽ʽ��
������ĺô�����ɾ�ڵ�ȽϷ��㣬��˿����������һ�����֣�Ȼ���������ֶ�Ӧλ�õ�����ڵ�ȡ������ɾ���˽ڵ�
�´�����������ķ�Χ��С1������㷨��Ӧÿ���������Ҫ����һ������������O(m*n)��

��ˣ����Կ���������m��n�Ĵ�С��Σ������鷽ʽʵ������ʱ�临�Ӷȸ��͵��㷨��

���鷽ʽ��Ҫ���ǵ��������ڴ����Ƿ�����ô��Ŀռ䣬�������������Ƶ�������һ������ѧ��ռ�õ������ռ�
Ҳֻ��11.4MB����Ȼͨ����̬���룬�����ڶ��л�������ռ䣬���Ա����������������㡣
*/
