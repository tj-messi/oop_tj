/* 2150792 �ƿ� ţ»�� */
#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.14159;

class Shape {
protected:
	// ������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
public:
	virtual void ShapeName() = 0; // �˾䲻׼��
	virtual double area() = 0;      // �˾䲻׼��
};
//�˴����������Ķ��弰ʵ��(��Ա������������ʵ����ʽ)
class Circle : public Shape {
protected:
	double r;
public:
	Circle(double _r);
	virtual void ShapeName();
	virtual double area();
};
Circle::Circle(double _r)
{
	r = _r;
}
void Circle::ShapeName()
{
	cout << "Circle" << endl;
}
double Circle::area()
{
	if (r <= 0)
		return 0.0;
	else
		return PI * r * r;
}

class Square : public Shape {
protected:
	double a;
public:
	Square(double _a);
	virtual void ShapeName();
	virtual double area();
};
Square::Square(double _a)
{
	a = _a;
}
void Square::ShapeName()
{
	cout << "Square" << endl;
}
double Square::area()
{
	if (a <= 0) 
		return 0.0;
	else 
		return a * a;
}

class Rectangle : public Shape {
protected:
	double a, b;  // ������
public:
	Rectangle(double _a, double _b);
	virtual void ShapeName();
	virtual double area();
};
Rectangle::Rectangle(double _a, double _b)
{
	a = _a;
	b = _b;
}
void Rectangle::ShapeName()
{
	cout << "Rectangle" << endl;
}
double Rectangle::area()
{
	if (a <= 0 || b <= 0) 
		return 0.0;
	else 
		return a * b;
}

class Triangle : public Shape {
protected:
	double a, b, c; // ����
public:
	Triangle(double _a, double _b, double _c);
	virtual void ShapeName();
	virtual double area();
};
Triangle::Triangle(double _a, double _b, double _c)
{
	a = _a;
	b = _b;
	c = _c;
}
void Triangle::ShapeName()
{
	cout << "Triangle" << endl;
}
double Triangle::area()
{
	if (a <= 0 || b <= 0 || c <= 0) 
		return 0.0;
	if (a + b <= c || a + c <= b || b + c <= a)
		return 0.0; // ����������������
	double s = (a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c)); // �ú��׹�ʽ�������߼��㳤��
}

class Trapezoid : public Shape {

public:
	double up_bottom, low_bottom, high;
	Trapezoid(double a, double b, double c);
	virtual void ShapeName();
	virtual double area();
};
void Trapezoid::ShapeName()
{
	cout << "Trapezoid" << endl;
}
Trapezoid::Trapezoid(double a, double b, double c)
{
	up_bottom = a;
	low_bottom = b;
	high = c;
}
double Trapezoid::area()
{
	if (up_bottom <= 0 || low_bottom <= 0 || high <= 0) 
		return 0.0;
	else 
		return (up_bottom + low_bottom) * high / 2;
}
/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //�뾶5.2�����<=0�����Ϊ0��
        Square    s1(5.2);           //�߳�5.2�����<=0�����Ϊ0��
        Rectangle r1(5.2, 3.7);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, 4.4, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, 5);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���ʽ�ο�demo��
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε��������ʽ�ο�demo��
            cout << endl;
        }
    }

    if (1) {
        Circle    c1(-1);           //�뾶5.2�����<=0�����Ϊ0��
        Square    s1(-1);           //�߳�5.2�����<=0�����Ϊ0��
        Rectangle r1(5.2, -1);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, -1, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, -1);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        cout << "============" << endl;
        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���ʽ�ο�demo��
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε��������ʽ�ο�demo��
            cout << endl;
        }
    }

    return 0;
}

