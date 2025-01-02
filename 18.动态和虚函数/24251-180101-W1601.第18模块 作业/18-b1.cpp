/*2351114 �쿡�� ������*/ 
#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.14159;

class Shape {
protected:
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
public:
    virtual void ShapeName() = 0; //�˾䲻׼��
    virtual double area() = 0;    // ���麯�����������
    virtual ~Shape() {}          // ����������
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
};

// Բ����
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r > 0 ? r : 0) {}
    void ShapeName() override;
    double area() override;
};

void Circle::ShapeName(){
       cout << "Circle" << endl;
}
double Circle::area(){
    return radius > 0 ? PI * radius * radius : 0;
}

// ��������
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s > 0 ? s : 0) {}
    void ShapeName() override;
    double area() override;
};
void Square::ShapeName() {
    cout << "Square" << endl;
}
double Square::area()  {
    return side > 0 ? side * side : 0;
}


// ������
class Rectangle : public Shape {
private:
    double length, width;
public:
    Rectangle(double l, double w) : length(l > 0 ? l : 0), width(w > 0 ? w : 0) {}
    void ShapeName() override;
    double area() override;
};
void Rectangle::ShapeName()  {
    cout << "Rectangle" << endl;
}
double Rectangle::area(){
    return (length > 0 && width > 0) ? length * width : 0;
}

// ������
class Trapezoid : public Shape {
private:
    double topBase, bottomBase, height;
public:
    Trapezoid(double t, double b, double h)
        : topBase(t > 0 ? t : 0), bottomBase(b > 0 ? b : 0), height(h > 0 ? h : 0) {
    }
    void ShapeName() override;
    double area() override;
};
void Trapezoid::ShapeName()  {
    cout << "Trapezoid" << endl;
}
double Trapezoid::area()  {
    return (topBase > 0 && bottomBase > 0 && height > 0) ?
        0.5 * (topBase + bottomBase) * height : 0;
}

// ��������
class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double side1, double side2, double side3)
        : a(side1 > 0 ? side1 : 0), b(side2 > 0 ? side2 : 0), c(side3 > 0 ? side3 : 0) {
    }
    void ShapeName() override;
    double area() override;
};

void Triangle::ShapeName()  {
    cout << "Triangle" << endl;
}
double Triangle::area()  {
    if (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a) {
        double s = (a + b + c) / 2; // ���ܳ�
        return sqrt(s * (s - a) * (s - b) * (s - c)); // ���׹�ʽ
    }
    return 0;
}

//�˴����������Ķ��弰ʵ��(��Ա������������ʵ����ʽ)

/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������������main�����Ĵ��¿�ܣ��������΢����ı��ֵ
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //�뾶�����<=0�����Ϊ0��
        Square    s1(5.2);           //�߳������<=0�����Ϊ0��
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
        Circle    c1(-1);           //�뾶�����<=0�����Ϊ0��
        Square    s1(-1);           //�߳������<=0�����Ϊ0��
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

