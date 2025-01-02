
    virtual double area() = 0;    // 纯虚函数，计算面积
    virtual ~Shape() {}          // 虚析构函数
    //根据需要加入相应的成员，也可以为空
};

// 圆形类
class Circle : public Shape {
private:
    double radius;
public: