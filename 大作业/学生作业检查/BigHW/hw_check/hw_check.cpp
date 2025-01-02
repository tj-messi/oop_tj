/*2351114 大数据 朱俊泽*/
#include "hw_check.h"
using namespace std;



// Helper function to check if the file exists
bool fileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

// Check if a file is a valid PDF
Check checkPDF(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return FILE_NOT_FOUND;

    char buffer[8];
    file.read(buffer, 8);
    std::string header(buffer, 8);

    if (header.substr(0, 7) == "%PDF-1." && isdigit(header[7])) {
        return CORRECT;
    }
    return NOT_PDF;
}

// Check if a file is UTF-8 encoded
bool isUTF8(const std::string & file_path)
    {
        ifstream fin(file_path, std::ios::binary);
        unsigned char temp_ch;
        bool ascii = true;
        fin.clear();
        fin.seekg(0, ios::beg);
        while (1)
        {
            temp_ch = fin.get();
            if (fin.eof())
                break;
            if ((temp_ch & 0x80) == 0)          // 1字节
                ;
            else if ((temp_ch & 0xe0) == 0xc0)  // 2字节，110xxxxx
            {
                temp_ch = fin.get();
                if (fin.eof())
                    return 0;
                if ((temp_ch & 0xc0) != 0x80)
                    return 0;
                ascii = false;
            }
            else if ((temp_ch & 0xf0) == 0xe0)  // 3字节，1110xxxx
            {
                for (int i = 0; i < 2; i++)
                {
                    temp_ch = fin.get();
                    if (fin.eof())
                        return 0;
                    if ((temp_ch & 0xc0) != 0x80)
                        return 0;
                }
                ascii = false;
            }
            else if ((temp_ch & 0xf8) == 0xf0)  //4字节，11110xxx
            {
                for (int i = 0; i < 3; i++)
                {
                    temp_ch = fin.get();
                    if (fin.eof())
                        return 0;
                    if ((temp_ch & 0xc0) != 0x80)
                        return 0;
                }
                ascii = false;
            }
            else
                return 0;
        }
        if (ascii)
            return 0;
        else
            return 1;
    }

bool checkvs(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary); // 以二进制方式打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filePath << std::endl;
        return false;
    }

    std::vector<int> invalidPositions; // 用于存储 \r 未紧跟 \n 的位置
    char prevChar = 0, currentChar;
    int position = 0;

    while (file.get(currentChar)) {
        if (prevChar == '\r' && currentChar != '\n') {
            invalidPositions.push_back(position - 1); // 记录 \r 的位置
        }
        prevChar = currentChar;
        position++;
    }

    file.close();

    if (!invalidPositions.empty()) {
        //std::cout << "发现 " << invalidPositions.size() << " 处 \\r 未紧跟 \\n，位置分别是: ";
        return true;
        for (int pos : invalidPositions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }
    else {
       // std::cout << "文件格式正确，没有 \\r 未紧跟 \\n 的问题！" << std::endl;
        return false;
    }
}

// Main function to check file format
Check checkfilebase(const std::string& path) {
    if (!fileExists(path)) {
        return FILE_NOT_FOUND;
    }

    std::string extension = path.substr(path.find_last_of('.'));
    if (extension == ".pdf") {
        return checkPDF(path);
    } 
    else if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".c") {
        if (isUTF8(path)) {
            return INVALID_ENCODING;
        } else {
            if (checkvs(path))
            {
                return NOT_VS;
            }
            return CORRECT;
        }
    } else {
        return CORRECT; // For other file types, always return CORRECT
    }
}

bool isMatch(const string& part, const string& target) {
    return part == target;
}

Check checkfilefirst(const string& firstline, const MYSQL_ROW& row, const string& stuNo, const string& stuName) {

    string validParts;
    if (firstline.substr(0, 2) == "//") {// "//"形式
        validParts = firstline.substr(2);
    }
    else if(firstline.substr(0, 2)=="/*"&& firstline.substr(firstline.size()-2, 2)=="*/")// /**/ 形式
    {
        validParts = firstline.substr(2, firstline.length() - 4);
    }
    else if (firstline.substr(0, 2) == "/*" && firstline.substr(firstline.size() - 2, 2) != "*/" && firstline.find("*/")!=-1)
    {
        //首行/* */格式有问题
        return FIRSTLINE_MULTIERROR;
    }
    else if (firstline.substr(0, 2) == "/*" && firstline.find("*/") == -1)
    {
        //首行/* */格式有问题
        return FIRSTLINE_MULTIERROR;
    }
    else
    {
        //首行不是注释行
        return FIRSTLINE_NOT_DEFINE;
    }

    // 分割字符串时，不使用数组存储结果
    stringstream ss(validParts);
    string part1, part2, part3;

    // 手动拆分前三个部分
    if (!(ss >> part1) || !(ss >> part2) || !(ss >> part3)) {
        return FIRSTLINE_NOT_3_ITEMS;
    }

    // 检查是否有多余部分
    string extra;
    if (ss >> extra) {
        return FIRSTLINE_NOT_3_ITEMS;
    }

    // 验证每部分是否匹配
    bool flag = true; // 用于标识是否所有项都匹配
    string stuCls = row[6];
    string stuCls1 = row[5];
    string stuCls2 = "";
    if (stuCls.find("|") != -1)//存在转专业
    {
        stuCls2 = stuCls.substr(stuCls.find("|")+1);
        stuCls = stuCls.substr(0, stuCls.find("|") );
    }

    if (!isMatch(part1, stuNo) && !isMatch(part2, stuNo) && !isMatch(part3, stuNo)) {
        if (flag) {
            cout << "首行";
            flag = false;
        }
        cout << "学号不匹配";
    }

    if ( !isMatch(part1, stuName)&& !isMatch(part2, stuName) && !isMatch(part3, stuName)) {
        if (flag) {
            cout << "首行";
            flag = false;
        }
        cout << "姓名不匹配";
    }

    if (!isMatch(part1, stuCls) &&  !isMatch(part3, stuCls)&& !isMatch(part2, stuCls)&&!isMatch(part1, stuCls2) && !isMatch(part3, stuCls2) && !isMatch(part2, stuCls2) && !isMatch(part1, stuCls1) && !isMatch(part3, stuCls1) && !isMatch(part2, stuCls1)) {
        if (flag) {
            cout << "首行";
            flag = false;
        }
        cout << "班级不匹配";
    }

    // 判断最终结果
    if (flag) {
        return CORRECT;
    }
    else {
        return FIRSTLINE_ERROR;
    }
}

Check checkfilesecond(const string& secondline, const string& own_stu_no)
{
    string validParts;
    if (secondline.substr(0, 2) == "//") {// "//"形式
        validParts = secondline.substr(2);
    }
    else if (secondline.substr(0, 2) == "/*" && secondline.substr(secondline.size() - 2, 2) == "*/")// /**/ 形式
    {
        validParts = secondline.substr(2, secondline.length() - 4);
    }
    else //否则注释有问题
    {
        return SECONDLINE_NOT_DEFINE;
    }

   
    stringstream sscnt(validParts);
    string nowcnt;
    int cntcnt = 0;
    while (sscnt >> nowcnt)
    {
        cntcnt++;
    }


    int cnt = 0;//记录读到的段数
    stringstream ss(validParts);
    string now;
    while (ss >> now)
    { 
        if (cnt % 2 == 0)//重新要读学号了
        {
            
            if (now.size() != 7 && cntcnt - cnt != 1)
            {
                cout << "第" << cnt / 2 + 1 << "位同学的学号[" << now << "]不是7位，后续内容忽略" << endl;
                return STU_NO_ERROR;
            }
            if (now == own_stu_no)
            {
                cout << "第[" << cnt / 2 + 1 << "]项写了自己，后续内容忽略" << endl;
                return WRITE_SELF;
            }
        }
        else
        {
            
        }
        cnt++;
    }
    if (cntcnt % 2 != 0)
    {
        cout << "第[" << cnt / 2  << "]个学生后面的信息不全(只读到一项)，后续内容忽略" << endl;
        return NOT_DOUBLE;
    }
    return CORRECT;
}

void Crosscheck(Cross cross)
{
    for (int i = 0; i < (int)cross.stu_list.size(); i++)
    {
        string validParts;
        if (cross.stu_list[i].secondline.substr(0, 2) == "//") {// "//"形式
            validParts = cross.stu_list[i].secondline.substr(2);
        }
        else if (cross.stu_list[i].secondline.substr(0, 2) == "/*" && cross.stu_list[i].secondline.substr(cross.stu_list[i].secondline.size() - 2, 2) == "*/")// /**/ 形式
        {
            validParts = cross.stu_list[i].secondline.substr(2, cross.stu_list[i].secondline.length() - 4);
        }
        else //否则注释有问题
        {
            continue;
        }

        int cnt = 0;//记录读到的段数
        stringstream ss(validParts);
        string now;
        string now_no, now_name;
        while (ss >> now)
        {
            if (cnt % 2 == 0)//重新要读学号了
            {

                if (now.size() != 7)
                {
                    break;
                    //cout << "第" << cnt / 2 + 1 << "位同学的学号[" << now << "]不是7位，后续内容忽略" << endl;
                }
                else if (now == cross.stu_list[i].no)
                {
                    //cout << "第[" << cnt / 2 + 1 << "]项写了自己，后续内容忽略" << endl;
                    break;
                }
                else
                {
                    now_no = now;
                }
            }
            else
            {
                now_name = now;
                cross.stu_list[i].valid_stu.push_back({ now_no,now_name });
            }
            cnt++;
        }
    }
    for (int i = 0; i < (int)cross.stu_list.size(); i++)
    {
        cout << resetiosflags(ios::right) << setiosflags(ios::left)<<setw(3)<< i+1 << ": " << cross.stu_list[i].cno <<"-" << cross.stu_list[i].no << "-" << cross.stu_list[i].name << endl;
        if (isUTF8(cross.source_root + cross.stu_list[i].cno + '-' + cross.stu_list[i].no + '/' + cross.filename))
        {
            continue;
        }
        string no1 = cross.stu_list[i].no;
        string name1 = cross.stu_list[i].name;
        for (int j = 0; j < (int)cross.stu_list[i].valid_stu.size(); j++)
        {
            cout << "\t" << cross.stu_list[i].valid_stu[j].no << " " << cross.stu_list[i].valid_stu[j].name<<"\t";
            //检查对方对自己的情况
            string no2 = cross.stu_list[i].valid_stu[j].no;
            string name2 = cross.stu_list[i].valid_stu[j].name;
            bool vis = false;
            {
                //优先检查名字，学号是否写对了
                //你没写对他的名字or学号
                bool flag = false;
                for (int k = 0; k < (int)cross.stu_list.size(); k++)
                {
                    if (cross.stu_list[k].no == no2)
                    {
                        flag = true;        
                        if (cross.stu_list[k].name != name2)
                        {
                            vis = true;
                            cout << "对方姓名不正确" << endl;
                        }

                    }
                }
                if (!flag && !vis) // 没找到对应学号
                {
                    vis = true;
                    cout << "对方学号不存在" << endl;
                }
                else //找到了对应的人，你写对了他
                {
                    for (int k = 0; k < (int)cross.stu_list.size(); k++)
                    {
                        bool flag = false;
                        if (cross.stu_list[k].no == no2)
                        {
                            for (int o = 0; o < (int)cross.stu_list[k].valid_stu.size(); o++)
                            {
                                if (cross.stu_list[k].valid_stu[o].no == no1)
                                {
                                    flag = true;
                                    if (cross.stu_list[k].valid_stu[o].name != name1 && !vis)
                                    {
                                        vis = true;
                                        cout << "没写对你名字" << endl;
                                    }
                                }
                            }
                            if (!flag && !vis)
                            {
                                vis = true;
                                cout << "抛弃了你" << endl;
                            }

                        }
                    }
                }
            }
            if (!vis)
                cout << endl;
        }
    }
}