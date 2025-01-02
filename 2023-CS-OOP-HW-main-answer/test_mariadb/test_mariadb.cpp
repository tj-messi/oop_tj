/* --
    ׼��������
        1�����ز���װmariadb��Windows�汾
            mariadb-10.6.5-winx64.msi
            mariadb-10.6.5-win32.msi
        2����װʱѡ�񲻰�װMariaDB Server��ֻҪDevelopment Components��Thrid party tools
            ��װ��ɺ󣬶�Ӧͷ�ļ��Ϳ��ļ�����Ŀ¼��
                x64�汾��
                    C:\Program Files\MariaDB 10.6\include\mysql
                    C:\Program Files\MariaDB 10.6\lib
                x86�汾��
                    C:\Program Files (x86)\MariaDB 10.6\include\mysql
                    C:\Program Files (x86)\MariaDB 10.6\lib
        3��������������Ŀ
            ����Ŀ - �Ҽ� - ���� - VC++Ŀ¼ - ����Ŀ¼
                ����C:\Program Files (x86)\MariaDB 10.6\include\mysql
            ����Ŀ - �Ҽ� - ���� - VC++Ŀ¼ - ��Ŀ¼
                ����C:\Program Files (x86)\MariaDB 10.6\lib
            ����Ŀ - ��Դ�ļ� - ��� - ������
                ����C:\Program Files (x86)\MariaDB 10.6\lib\libmariadb.lib
            ��C:\Program Files (x86)\MariaDB 10.6\lib\libmariadb.dll��Ӧ���Ƶ�����ĿԴ����Ŀ¼/exeͬĿ¼��
        4������Ӧ����ͨ��
        5����demo��Ȩ
            delete from mysql.user where user="demo_23241";
            grant select on demo.student to demo_23241@'%' identified by 'demo_23241*oop';
        
*/
#include <iostream>     // cin,cout��
#include <iomanip>      // setw��
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql����
using namespace std;

const char* dbserver = "10.80.42.244";
const char* dbuser = "demo_23241";
const char* dbpasswd = "demo_23241*oop";
const char* dbname = "demo";

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int main(int argc, char* argv[])
{
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;

    /* ��ʼ�� mysql ������ʧ�ܷ���NULL */
    if ((mysql = mysql_init(NULL)) == NULL) {
        cout << "mysql_init failed" << endl;
        return -1;
    }

    /* �������ݿ⣬ʧ�ܷ���NULL
        1��mysqldû����
        2��û��ָ�����Ƶ����ݿ���� */
    if (mysql_real_connect(mysql, dbserver, dbuser, dbpasswd, dbname, 0, NULL, 0) == NULL) {
        cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* �����ַ���������������ַ����� */
    mysql_set_character_set(mysql, "gbk");

    /* -----------------------------
          ���е�һ�β�ѯ - Begin
       -----------------------------*/
    /* ��ѯ���
            select * from student
        ���壺��ʾ��ѯstudent������м�¼��ÿ����¼��ԭʼ˳����ʾ�����ֶ�
        ����ֵ���ɹ�����0�����ɹ���0
        ���ɹ��ĳ��������ԣ�
            1����ѯ�ַ��������﷨����
            2����ѯ�����ڵ����ݱ� */
    if (mysql_query(mysql, "select * from student")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* ����ѯ����洢���������ִ����򷵻�NULL
        ע�⣺��ѯ���ΪNULL�����᷵��NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* ��ӡ��ǰ��ѯ���ļ�¼������ */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* ѭ����ȡ�������������ļ�¼
        1��demo���ݿ��student��ṹ���������£�
            student��Ļ����ṹ���£���5���ֶ�
            +-------+------------+------+-----+---------+-------+
            | Field | Type       | Null | Key | Default | Extra |
            +-------+------------+------+-----+---------+-------+
            | sno   | char(9)    | NO   |     | NULL    |       |
            | sname | char(8)    | NO   |     | NULL    |       |
            | ssex  | char(2)    | NO   |     | ��      |       |
            | sage  | tinyint(2) | YES  |     | NULL    |       |
            | sdept | char(2)    | YES  |     | NULL    |       |
            +-------+------------+------+-----+---------+-------+
            student����������£�
            +-----------+-------+------+------+-------+
            | sno       | sname | ssex | sage | sdept |
            +-----------+-------+------+------+-------+
            | 200215121 | ����  | ��   |   20 | CS    |
            | 200215122 | ����  | Ů   |   19 | CS    |
            | 200215123 | ����  | Ů   |   18 | MA    |
            | 200215125 | ����  | ��   |   19 | IS    |
            +-----------+-------+------+------+-------+
        2��mysql_fetch_row(result)���ص�row��һ��char��ָ�����飬Ԫ�ظ���Ϊ��ѯ������ֶ���+1�������У�row[0]~row[4]�����ݣ�row[5]ΪNULL
        3��row������˳����select���ص���˳����ͬ��������
            row[0] <=> sno
            row[1] <=> sname
            row[2] <=> ssex
            row[3] <=> sage
            row[4] <=> sdept
            row[5] <=> NULL
        4���������ݿ�����ʲô���ͣ�C�ж��������ַ��������д�������б�Ҫ����Ҫ�Լ�����ת��
        5�������Լ�����Ҫ��֯�����ʽ������ӱ߿��ߵ� */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //��������
        cout << "ѧ�ţ�" << setw(12) << row[0];    //���12λ�������
        cout << "������" << setw(8) << row[1];     //    8
        cout << "�Ա�" << setw(4) << row[2];     //    4
        cout << "���䣺" << setw(4) << row[3];     //    4��Ŀǰ���ַ�����ʽ��Ҳ������atoi(row[3])���int�͵�����
        cout << "ϵ����" << setw(4) << row[4];     //    4
        cout << endl;
    }
    cout << endl;

    /* �ͷ�result������ᶪʧ�ڴ� */
    mysql_free_result(result);

    /* -----------------------------
          ���е�һ�β�ѯ - End
       -----------------------------*/

    /* -----------------------------
          ���еڶ��β�ѯ - Begin
       -----------------------------*/
    /* ��ѯ���
           select ssex, sage, sname from student where ssex = "Ů"
       ���壺��ʾ��ѯstudent����Ա�Ϊ"Ů"�����м�¼��ÿ����¼Ҫ�Ա����䡢���������ֶ������˳������
       ����ֵ���ɹ�����0�����ɹ���0
       ���ɹ��ĳ��������ԣ�
           1����ѯ�ַ��������﷨����
           2����ѯ�����ڵ����ݱ� */
    if (mysql_query(mysql, "select ssex, sage, sname from student where ssex = \"Ů\"")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* ����ѯ����洢���������ִ����򷵻�NULL
        ע�⣺��ѯ���ΪNULL�����᷵��NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* ��ӡ��ǰ��ѯ���ļ�¼������ */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* ѭ����ȡ�������������ļ�¼
        2��row������˳����select���ص���˳����ͬ��������
            row[0] <=> ssex
            row[1] <=> sage
            row[2] <=> sname
            row[3] <=> NULL */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //��������
        cout << "�Ա�" << setw(4) << row[0];     //���4λ�������
        cout << "���䣺" << setw(4) << row[1];     //    4
        cout << "������" << setw(8) << row[2];     //    8
        cout << endl;
    }
    cout << endl;

    /* �ͷ�result������ᶪʧ�ڴ� */
    mysql_free_result(result);
    /* -----------------------------
          ���еڶ��β�ѯ - End
       -----------------------------*/

    /* -----------------------------
          ���е����β�ѯ - Begin
       -----------------------------*/
     /* ��ѯ���
              select ssex, sage, sname, sdept from student where ssex = "Ů"  and sdept = "CS"
        ���壺��ʾ��ѯstudent����Ա�Ϊ"Ů"����ϵ��Ϊ"CS"�����м�¼��ÿ����¼Ҫ�Ա����䡢������ϵ���ĸ��ֶ������˳������
          ����ֵ���ɹ�����0�����ɹ���0
          ���ɹ��ĳ��������ԣ�
              1����ѯ�ַ��������﷨����
              2����ѯ�����ڵ����ݱ� */
    if (mysql_query(mysql, "select ssex, sage, sname, sdept from student where ssex = \"Ů\" and sdept = \"CS\"")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* ����ѯ����洢���������ִ����򷵻�NULL
        ע�⣺��ѯ���ΪNULL�����᷵��NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* ��ӡ��ǰ��ѯ���ļ�¼������ */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* ѭ����ȡ�������������ļ�¼
        2��row������˳����select���ص���˳����ͬ��������
            row[0] <=> ssex
            row[1] <=> sage
            row[2] <=> sname
            row[3] <=> sdept
            row[4] <=> NULL      */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //��������
        cout << "�Ա�" << setw(4) << row[0];     //���4λ�������
        cout << "���䣺" << setw(4) << row[1];     //    4
        cout << "������" << setw(8) << row[2];     //    8
        cout << "ϵ����" << setw(4) << row[3];     //    4
        cout << endl;
    }
    cout << endl;

    /* �ͷ�result������ᶪʧ�ڴ� */
    mysql_free_result(result);
    /* -----------------------------
          ���е����β�ѯ - End
       -----------------------------*/

    /* -----------------------------
          ���е��Ĵβ�ѯ - begin
       -----------------------------*/
   /* ��ѯ���
            select * from student where ssex = "��"  or sdept = "CS"
      ���壺��ʾ��ѯstudent����Ա�Ϊ"��"��ϵ��Ϊ"CS"�����м�¼��ÿ����¼��ԭʼ˳����ʾ�����ֶ�
        ����ֵ���ɹ�����0�����ɹ���0
        ���ɹ��ĳ��������ԣ�
            1����ѯ�ַ��������﷨����
            2����ѯ�����ڵ����ݱ� */
    if (mysql_query(mysql, "select * from student where ssex = \"��\" or sdept = \"CS\"")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* ����ѯ����洢���������ִ����򷵻�NULL
        ע�⣺��ѯ���ΪNULL�����᷵��NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* ��ӡ��ǰ��ѯ���ļ�¼������ */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* ѭ����ȡ�������������ļ�¼
            row[0] <=> sno
            row[1] <=> sname
            row[2] <=> ssex
            row[3] <=> sage
            row[4] <=> sdept
            row[5] <=> NULL     */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //��������
        cout << "ѧ�ţ�" << setw(12) << row[0];    //���12λ�������
        cout << "������" << setw(8) << row[1];     //    8
        cout << "�Ա�" << setw(4) << row[2];     //    4
        cout << "���䣺" << setw(4) << row[3];     //    4��Ŀǰ���ַ�����ʽ��Ҳ������atoi(row[3])���int�͵�����
        cout << "ϵ����" << setw(4) << row[4];     //    4
        cout << endl;
    }
    cout << endl;

    /* �ͷ�result������ᶪʧ�ڴ� */
    mysql_free_result(result);
    /* -----------------------------
          ���е��Ĵβ�ѯ - End
       -----------------------------*/

    /* �ر��������� */
    mysql_close(mysql);

    return 0;
}
