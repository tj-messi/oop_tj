/*2351114 朱俊泽 大数据*/ 
#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.14159;

class Shape {
protected:
    //根据需要加入相应的成员，也可以为空
public:
    virtual void ShapeName() = 0; //此句不准动
    virtual double area() = 0;    // 纯虚函数，计算面积
    virtual ~Shape() {}          // 虚析构函数
    //根据需要加入相应的成员，也可以为空
};

// 圆形类
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

// 正方形类
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


// 矩形类
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

// 梯形类
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

// 三角形类
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
        double s = (a + b + c) / 2; // 半周长
        return sqrt(s * (s - a) * (s - b) * (s - c)); // 海伦公式
    }
    return 0;
}

//此处给出五个类的定义及实现(成员函数采用体外实现形式)

/* -- 替换标记行 -- 本行不要做任何改动 -- 本行不要删除 -- 在本行的下面不要加入任何自己的语句，作业提交后从本行开始会被替换 -- 替换标记行 -- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：给出的是main函数的大致框架，允许进行微调或改变初值
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //半径（如果<=0，面积为0）
        Square    s1(5.2);           //边长（如果<=0，面积为0）
        Rectangle r1(5.2, 3.7);      //长、宽（如果任一<=0，面积为0）
        Trapezoid t1(2.3, 4.4, 3.8); //上底、下底、高（如果任一<=0，面积为0）
        Triangle  t2(3, 4, 5);       //三边长度（如果任一<=0或不构成三角形，面积为0）
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //分别打印不同形状图形的名称（格式参考demo）
            cout << s[i]->area() << endl; //分别打印不同形状图形的面积（格式参考demo）
            cout << endl;
        }
    }

    if (1) {
        Circle    c1(-1);           //半径（如果<=0，面积为0）
        Square    s1(-1);           //边长（如果<=0，面积为0）
        Rectangle r1(5.2, -1);      //长、宽（如果任一<=0，面积为0）
        Trapezoid t1(2.3, -1, 3.8); //上底、下底、高（如果任一<=0，面积为0）
        Triangle  t2(3, 4, -1);       //三边长度（如果任一<=0或不构成三角形，面积为0）
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        cout << "============" << endl;
        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //分别打印不同形状图形的名称（格式参考demo）
            cout << s[i]->area() << endl; //分别打印不同形状图形的面积（格式参考demo）
            cout << endl;
        }
    }

    return 0;
}

