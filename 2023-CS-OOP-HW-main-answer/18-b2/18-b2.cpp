/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

/* �Ӵ˴�������滻��֮�䣬����������Ķ��弰ʵ��
	1����������ȫ�ֱ���������const��#define��
	2���������������ϵͳͷ�ļ�
*/
// �Զ����strcpy����
void myStrcpy(char* dest, const char* src) 
{
	if (dest == NULL || src == NULL) 
		return; // ����ָ��
	// ����src��dest��ֱ������null�ַ�
	while (*src != '\0') 
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0'; // ��Ŀ���ַ�����ĩβ���null�ַ�
}

const int MAXBUF = 128;
class integral {
protected:
	double low, high;
	int    num;
	char   name[MAXBUF];
public:
	virtual double value()
	{
		return 0;
	}
	friend istream& operator >>(istream& in, integral& inter);
};
istream& operator >>(istream& in, integral& inter)
{
	while (1)
	{
		cout << "������" << inter.name << "�����ޡ����޼����仮������" << endl;
		in >> inter.low >> inter.high >> inter.num;
		if (in.good() && inter.low <= inter.high && inter.num > 0)
			break;
		cout << "���������������������" << endl;
		in.clear();
		in.ignore(65536, '\n');
	}
	return in;
}

class integral_sin : public integral {
protected:

public:
	integral_sin();
	virtual double value();
};
integral_sin::integral_sin()
{
	myStrcpy(name, "sinxdx");
}
double integral_sin::value()
{
	double result = 0;
	double wid = (high - low) / num;
	for (int i = 1; i <= num; i++)
		result += sin(low + i * wid) * wid;
	cout << name << "[" << low << "~" << high << "/n=" << num << "] : " << result << endl;
	return result;
}

class integral_cos : public integral {
protected:

public:
	integral_cos();
	virtual double value();
};
integral_cos::integral_cos()
{
	myStrcpy(name, "cosxdx");
}
double integral_cos::value()
{
	double result = 0;
	double wid = (high - low) / num;
	for (int i = 1; i <= num; i++)
		result += cos(low + i * wid) * wid;
	cout << name << "[" << low << "~" << high << "/n=" << num << "] : " << result << endl;
	return result;
}

class integral_exp : public integral {
protected:

public:
	integral_exp();
	virtual double value();
};
integral_exp::integral_exp()
{
	myStrcpy(name, "e^xdx");
}
double integral_exp::value()
{
	double result = 0;
	double wid = (high - low) / num;
	for (int i = 1; i <= num; i++)
		result += exp(low + i * wid) * wid;
	cout << name << "[" << low << "~" << high << "/n=" << num << "] : " << result << endl;
	return result;
}
/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����fun_integral��׼����˼��һ�£�integralӦ��ζ���
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//���������ޡ�������
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //����sinxdx��ֵ
	fun_integral(s2); //����cosxdx��ֵ
	fun_integral(s3); //����expxdx��ֵ

	return 0;
}

//ע�����μ���ȡ��ֵ�����Ϊ����double��ʽ

