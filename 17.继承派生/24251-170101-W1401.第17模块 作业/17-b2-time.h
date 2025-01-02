/* 2351114 �쿡�� ������ */

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* Time������� */ 
class Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 
	int hour;   // Сʱ
	int minute; // ����
	int second; // ��

public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
    // ���캯��
    Time();                             // Ĭ�Ϲ��캯������ʼ��Ϊ 00:00:00
    Time(int h, int m, int s);          // ʹ��Сʱ�����ӡ����ʼ��
    Time(int seconds);                  // ʹ����������ʼ��

    // ʱ������
    void set(int h, int m, int s);      // ����Сʱ�����ӡ���
    void set(int h, int m);             // ����Сʱ������
    void set(int h);                    // ����Сʱ
    void set();                         // ���ʱ�䣬����Ϊ 00:00:00

    // ʱ���ȡ
    void get(int& h, int& m, int& s);   // ��ȡСʱ�����ӡ���

    // ��ʾʱ��
    void show();                        // �� hh:mm:ss ��ʽ��ʾʱ��

    // ���ʱ���Ƿ�Ϸ�
    bool isrightTime(int h, int m, int s);

    // ����ת��
    operator int();                     // ��ʱ��ת��Ϊ���������� 00:00:00 ��ʼ���㣩

    // ǰ�úͺ��� ++ �� --
    Time& operator++();                 // ǰ�� ++
    Time operator++(int);               // ���� ++
    Time& operator--();                 // ǰ�� --
    Time operator--(int);               // ���� --

	/* ���������Ԫ����������б�Ҫ�� */
    // ���������
    friend Time operator+(const Time& t1,const int seconds);
    friend Time operator+(const int seconds,const Time& t2);
    friend Time operator-(const Time& t1,const int seconds);
    friend int operator-(const Time& t1,const Time& t2);

    // �Ƚ������
    friend bool operator==(const Time& t1, const Time& t2);
    friend bool operator!=(const Time& t1, const Time& t2);
    friend bool operator<(Time& t1, Time& t2);
    friend bool operator<=(Time& t1, Time& t2);
    friend bool operator>(Time& t1, Time& t2);
    friend bool operator>=(Time& t1, Time& t2);

    // �������
    friend ostream& operator<<(ostream& out, const Time& t);
    friend istream& operator>>(istream& in, Time& t);
};
