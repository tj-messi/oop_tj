/* 2351114 �쿡�� ������ */
#include "17-b2-date.h"
#include "17-b2-time.h"

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* DateTime��Ļ���Ҫ��
	1�����������κ����ݳ�Ա
	2�������ٶ����Ա���� 
*/

class DateTime:public Date, public Time {
protected:
	/* �������ٶ����κ����ݳ�Ա */ 

public:
	/* �������ٶ����κ����ݳ�Ա��������Ҫ�ĳ�Ա��������Ԫ���������� */
    // Ĭ�Ϲ��캯��
    DateTime();

    // ʹ�����ں�ʱ���ʼ��
    DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0);

    // ʹ����������ʼ��
    DateTime(long long seconds);

    // ��������ʱ��
    void set(const int y = 1900, const int m = 1, const int d = 1, const int h = 0, const int min = 0, const int s = 0);
    void set(long long secconds);
    //void set();

    // ��ȡ����ʱ��
    void get(int& y, int& m, int& d, int& h, int& min, int& s);

    // ��ʾ����ʱ��
    void show();

    // ����ת��
    operator long long()const;
    operator long long();

    // ǰ�úͺ��� ++ �� --
    DateTime& operator++();
    DateTime operator++(int);
    DateTime& operator--();
    DateTime operator--(int);

	/* ���������Ԫ����������б�Ҫ�� */

     // ���������
    friend DateTime operator+(const DateTime& dt, long long seconds);
    friend DateTime operator+(long long seconds,const DateTime& dt );
    friend DateTime operator + (const DateTime& dt, int seconds);
    friend DateTime operator + (int seconds, const DateTime& dt);

#if defined(__linux) || defined(__linux__)
    friend DateTime operator + (long int seconds, const DateTime& dt);
    friend DateTime operator + (const DateTime& dt, long int seconds);
    friend DateTime operator - (const DateTime& dt, long int seconds);
#endif

    friend DateTime operator-(const DateTime& dt, long long seconds);
    friend DateTime operator - (const DateTime& dt, int seconds);
    friend long long operator-(const DateTime& dt1, const DateTime& dt2);

    // �Ƚ������
    friend bool operator==(const DateTime& dt1, const DateTime& dt2);
    friend bool operator!=(const DateTime& dt1, const DateTime& dt2);
    friend bool operator<(const DateTime& dt1, const DateTime& dt2);
    friend bool operator<=(const DateTime& dt1, const DateTime& dt2);
    friend bool operator>(const DateTime& dt1, const DateTime& dt2);
    friend bool operator>=(const DateTime& dt1, const DateTime& dt2);

    // �������
    friend ostream& operator<<(ostream& out, const DateTime& dt);
    friend istream& operator>>(istream& in, DateTime& dt);
};
