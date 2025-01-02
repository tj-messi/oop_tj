/*2351114 �쿡�� ������*/
#include <iostream>
#include <cmath>
using namespace std;
#define N 128

/* �Ӵ˴�������滻��֮�䣬����������Ķ��弰ʵ��
	1����������ȫ�ֱ���������const��#define��
	2���������������ϵͳͷ�ļ�
*/ 


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

// ������� integral
class integral {
protected:
    double lower; // ��������
    double upper; // ��������
    int n;        // �������������
    char name[N];//��������
public:
    integral() : lower(0), upper(0), n(0) {}
    virtual ~integral() {}
    virtual double value() = 0; // ���麯�����������ֵ

    // ����������������������������޺ͻ�����
    friend istream& operator>>(istream& in, integral& obj) {
        while (1)
        {
            cout << "������" << obj.name << "�����ޡ����޼����仮������" << endl;
            in >> obj.lower >> obj.upper >> obj.n;
            if (in.good() && obj.lower <= obj.upper && obj.n > 0)
                break;
            cout << "���������������������" << endl;
            in.clear();
            in.ignore(65536, '\n');
        }
        return in;
    }
};

// ���� sin(x) �Ķ�����
class integral_sin : public integral {
public:
    integral_sin()
    {
        myStrcpy(name, "sinxdx");
    }
    double value() override {
        double step = (upper - lower) / n; // ÿ��С����Ŀ��
        double sum = 0;
        for (int i = 1; i <= n; ++i) {
            double x = lower + i * step; // ȡ�����Ҷ˵�
            sum += sin(x) * step;       // �������
        }
        cout << name << "[" << lower << "~" << upper << "/n=" << n << "] : " << sum << endl;
        return sum;
    }
};

// ���� cos(x) �Ķ�����
class integral_cos : public integral {
public:
    integral_cos()
    {
        myStrcpy(name, "cosxdx");
    }
    double value() override {
        double step = (upper - lower) / n; // ÿ��С����Ŀ��
        double sum = 0;
        for (int i = 1; i <= n; ++i) {
            double x = lower + i * step; // ȡ�����Ҷ˵�
            sum += cos(x) * step;       // �������
        }
        cout << name << "[" << lower << "~" << upper << "/n=" << n << "] : " << sum << endl;
        return sum;
    }
};

// ���� exp(x) �Ķ�����
class integral_exp : public integral {
public:
    integral_exp()
    {
        myStrcpy(name, "e^xdx");
    }
    double value() override {
        double step = (upper - lower) / n; // ÿ��С����Ŀ��
        double sum = 0;
        for (int i = 1; i <= n; ++i) {
            double x = lower + i * step; // ȡ�����Ҷ˵�
            sum += exp(x) * step;       // �������
        }
        cout << name << "[" << lower << "~" << upper << "/n=" << n << "] : " << sum << endl;
        return sum;
    }
};

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

