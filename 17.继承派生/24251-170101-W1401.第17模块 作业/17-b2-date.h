/* 2351114 �쿡�� ������ */
#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* Date������� */ 
class Date {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 
	int year;
	int month;
	int day;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
     // ���캯��
    Date();
    Date(int y, int m, int d); // ʹ��ָ�����ڳ�ʼ��
    Date(int days);            // ʹ����������1900-01-01���㣩��ʼ��

    // ��������
    void set(int y, int m, int d);
    void set(int y, int m);
    void set(int y);

    // ���ڻ�ȡ
    void get(int& y, int& m, int& d);

    // ������ʾ
    void show();

    // �ж�����
    bool isleapyear(int y);

    // ��ȡĳ��ĳ�µ�����
    int getDinM(int y, int m);

    // ��������Ƿ�Ϸ�
    bool isrightDate(int y, int m, int d);

    // ����ת��
    operator int(); // ������ת��Ϊ��������1900-01-01���㣩

    // ǰ�úͺ��� ++ �� --
    Date& operator++();    // ǰ�� ++
    Date operator++(int);  // ���� ++
    Date& operator--();    // ǰ�� --
    Date operator--(int);  // ���� --

    // �������
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);
	/* ���������Ԫ����������б�Ҫ�� */
     // �Ƚ������
    friend bool operator==(const Date& d1, const Date& d2);
    friend bool operator!=(const Date& d1, const Date& d2);
    friend bool operator<(Date& d1, Date& d2);
    friend bool operator<=(Date& d1, Date& d2);
    friend bool operator>(Date& d1, Date& d2);
    friend bool operator>=(Date& d1, Date& d2);

    // ���������
    friend Date operator+(const Date& d1, const int d2);
    friend Date operator+(const int d1,const  Date& d2);
    friend Date operator-(const Date& d1, const int d2);
    friend int operator-(const Date& d1,const Date& d2);
};
