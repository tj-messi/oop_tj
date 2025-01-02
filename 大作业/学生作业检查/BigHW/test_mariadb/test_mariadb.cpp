/* --
    1、将附件给出的 include_mariadb_x86.rar 文件解压到 BigHW目录下
        目录结构：BigHW -> include_mariadb_x86 -> mysql -> mysql.h等文件
    2、将附件给出的 lib_mariadb_x86.rar 文件解压到 BigHW目录下
        目录结构：BigHW -> lib_mariadb_x86 -> libmariadb.lib等文件
    3、在BigHW中建立test_mariadb项目，将test_mariadb.cpp放入项目文件中并添加到项目中，再把../lib_mariadb_x86/libmariadb.lib也添加到项目中（mysql.h不需要）
    4、应该可以编译并正确运行
    5、注意事项
        a) 考虑到网络安全因素，必须在校园网环境内，校外需要先VPN登录
        b) 附件给出的lib是x86模式，因此必须保证项目是x86模式
        c) 如果离开集成环境，在cmd下运行，则需要将../lib_mariadb_x86/libmariadb.dll放入exe文件所在目录
*/
#include <iostream>     // cin,cout等
#include <iomanip>      // setw等
#include "../include_mariadb_x86/mysql/mysql.h"      // mysql特有
using namespace std;

const char* dbserver = "10.80.42.230";
const char* dbuser = "demo_24251";
const char* dbpasswd = "demo_24251*oop";
const char* dbname = "demo";

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int main(int argc, char* argv[])
{
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;

    /* 初始化 mysql 变量，失败返回NULL */
    if ((mysql = mysql_init(NULL)) == NULL) {
        cout << "mysql_init failed" << endl;
        return -1;
    }

    /* 连接数据库，失败返回NULL
        1、mysqld没运行
        2、没有指定名称的数据库存在 */
    if (mysql_real_connect(mysql, dbserver, dbuser, dbpasswd, dbname, 0, NULL, 0) == NULL) {
        cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* 设置字符集，否则读出的字符乱码 */
    mysql_set_character_set(mysql, "gbk");

    /* -----------------------------
          进行第一次查询 - Begin
       -----------------------------*/
    /* 查询命令：
            select * from student
        含义：表示查询student表的所有记录，每条记录按原始顺序显示所有字段
        返回值：成功返回0，不成功非0
        不成功的常见可能性：
            1、查询字符串存在语法错误
            2、查询不存在的数据表 */
    if (mysql_query(mysql, "select * from student")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
        注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* 打印当前查询到的记录的数量 */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* 循环读取所有满足条件的记录
        1、demo数据库的student表结构及数据如下：
            student表的基本结构如下，共5个字段
            +-------+------------+------+-----+---------+-------+
            | Field | Type       | Null | Key | Default | Extra |
            +-------+------------+------+-----+---------+-------+
            | sno   | char(9)    | NO   |     | NULL    |       |
            | sname | char(8)    | NO   |     | NULL    |       |
            | ssex  | char(2)    | NO   |     | 男      |       |
            | sage  | tinyint(2) | YES  |     | NULL    |       |
            | sdept | char(2)    | YES  |     | NULL    |       |
            +-------+------------+------+-----+---------+-------+
            student表的数据如下：
            +-----------+-------+------+------+-------+
            | sno       | sname | ssex | sage | sdept |
            +-----------+-------+------+------+-------+
            | 200215121 | 李勇  | 男   |   20 | CS    |
            | 200215122 | 刘晨  | 女   |   19 | CS    |
            | 200215123 | 王敏  | 女   |   18 | MA    |
            | 200215125 | 张立  | 男   |   19 | IS    |
            +-----------+-------+------+------+-------+
        2、mysql_fetch_row(result)返回的row是一个char型指针数组，元素个数为查询结果的字段数+1，本例中，row[0]~row[4]有内容，row[5]为NULL
        3、row的排列顺序与select返回的列顺序相同，本例：
            row[0] <=> sno
            row[1] <=> sname
            row[2] <=> ssex
            row[3] <=> sage
            row[4] <=> sdept
            row[5] <=> NULL
        4、不论数据库中是什么类型，C中都当作是字符串来进行处理，如果有必要，需要自己进行转换
        5、根据自己的需要组织输出格式，比如加边框线等 */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //输出左对齐
        cout << "学号：" << setw(12) << row[0];    //宽度12位，左对齐
        cout << "姓名：" << setw(8) << row[1];     //    8
        cout << "性别：" << setw(4) << row[2];     //    4
        cout << "年龄：" << setw(4) << row[3];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
        cout << "系部：" << setw(4) << row[4];     //    4
        cout << endl;
    }
    cout << endl;

    /* 释放result，否则会丢失内存 */
    mysql_free_result(result);

    /* -----------------------------
          进行第一次查询 - End
       -----------------------------*/

    /* -----------------------------
          进行第二次查询 - Begin
       -----------------------------*/
    /* 查询命令：
           select ssex, sage, sname from student where ssex = "女"
       含义：表示查询student表的性别为"女"的所有记录，每条记录要性别、年龄、姓名三个字段且桉此顺序排序
       返回值：成功返回0，不成功非0
       不成功的常见可能性：
           1、查询字符串存在语法错误
           2、查询不存在的数据表 */
    if (mysql_query(mysql, "select ssex, sage, sname from student where ssex = \"女\"")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
        注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* 打印当前查询到的记录的数量 */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* 循环读取所有满足条件的记录
        2、row的排列顺序与select返回的列顺序相同，本例：
            row[0] <=> ssex
            row[1] <=> sage
            row[2] <=> sname
            row[3] <=> NULL */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //输出左对齐
        cout << "性别：" << setw(4) << row[0];     //宽度4位，左对齐
        cout << "年龄：" << setw(4) << row[1];     //    4
        cout << "姓名：" << setw(8) << row[2];     //    8
        cout << endl;
    }
    cout << endl;

    /* 释放result，否则会丢失内存 */
    mysql_free_result(result);
    /* -----------------------------
          进行第二次查询 - End
       -----------------------------*/

    /* -----------------------------
          进行第三次查询 - Begin
       -----------------------------*/
     /* 查询命令：
              select ssex, sage, sname, sdept from student where ssex = "女"  and sdept = "CS"
        含义：表示查询student表的性别为"女"并且系部为"CS"的所有记录，每条记录要性别、年龄、姓名、系部四个字段且桉此顺序排序
          返回值：成功返回0，不成功非0
          不成功的常见可能性：
              1、查询字符串存在语法错误
              2、查询不存在的数据表 */
    if (mysql_query(mysql, "select ssex, sage, sname, sdept from student where ssex = \"女\" and sdept = \"CS\"")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
        注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* 打印当前查询到的记录的数量 */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* 循环读取所有满足条件的记录
        2、row的排列顺序与select返回的列顺序相同，本例：
            row[0] <=> ssex
            row[1] <=> sage
            row[2] <=> sname
            row[3] <=> sdept
            row[4] <=> NULL      */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //输出左对齐
        cout << "性别：" << setw(4) << row[0];     //宽度4位，左对齐
        cout << "年龄：" << setw(4) << row[1];     //    4
        cout << "姓名：" << setw(8) << row[2];     //    8
        cout << "系部：" << setw(4) << row[3];     //    4
        cout << endl;
    }
    cout << endl;

    /* 释放result，否则会丢失内存 */
    mysql_free_result(result);
    /* -----------------------------
          进行第三次查询 - End
       -----------------------------*/

    /* -----------------------------
          进行第四次查询 - begin
       -----------------------------*/
   /* 查询命令：
            select * from student where ssex = "男"  or sdept = "CS"
      含义：表示查询student表的性别为"男"或系部为"CS"的所有记录，每条记录按原始顺序显示所有字段
        返回值：成功返回0，不成功非0
        不成功的常见可能性：
            1、查询字符串存在语法错误
            2、查询不存在的数据表 */
    if (mysql_query(mysql, "select * from student where ssex = \"男\" or sdept = \"CS\"")) {
        cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
        注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* 打印当前查询到的记录的数量 */
    cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* 循环读取所有满足条件的记录
            row[0] <=> sno
            row[1] <=> sname
            row[2] <=> ssex
            row[3] <=> sage
            row[4] <=> sdept
            row[5] <=> NULL     */
    while ((row = mysql_fetch_row(result)) != NULL) {
        cout << setiosflags(ios::left);           //输出左对齐
        cout << "学号：" << setw(12) << row[0];    //宽度12位，左对齐
        cout << "姓名：" << setw(8) << row[1];     //    8
        cout << "性别：" << setw(4) << row[2];     //    4
        cout << "年龄：" << setw(4) << row[3];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
        cout << "系部：" << setw(4) << row[4];     //    4
        cout << endl;
    }
    cout << endl;

    /* 释放result，否则会丢失内存 */
    mysql_free_result(result);
    /* -----------------------------
          进行第四次查询 - End
       -----------------------------*/

    /* 关闭整个连接 */
    mysql_close(mysql);

    return 0;
}
