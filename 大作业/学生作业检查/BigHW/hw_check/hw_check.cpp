/*2351114 ������ �쿡��*/
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
            if ((temp_ch & 0x80) == 0)          // 1�ֽ�
                ;
            else if ((temp_ch & 0xe0) == 0xc0)  // 2�ֽڣ�110xxxxx
            {
                temp_ch = fin.get();
                if (fin.eof())
                    return 0;
                if ((temp_ch & 0xc0) != 0x80)
                    return 0;
                ascii = false;
            }
            else if ((temp_ch & 0xf0) == 0xe0)  // 3�ֽڣ�1110xxxx
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
            else if ((temp_ch & 0xf8) == 0xf0)  //4�ֽڣ�11110xxx
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
    std::ifstream file(filePath, std::ios::binary); // �Զ����Ʒ�ʽ���ļ�
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filePath << std::endl;
        return false;
    }

    std::vector<int> invalidPositions; // ���ڴ洢 \r δ���� \n ��λ��
    char prevChar = 0, currentChar;
    int position = 0;

    while (file.get(currentChar)) {
        if (prevChar == '\r' && currentChar != '\n') {
            invalidPositions.push_back(position - 1); // ��¼ \r ��λ��
        }
        prevChar = currentChar;
        position++;
    }

    file.close();

    if (!invalidPositions.empty()) {
        //std::cout << "���� " << invalidPositions.size() << " �� \\r δ���� \\n��λ�÷ֱ���: ";
        return true;
        for (int pos : invalidPositions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }
    else {
       // std::cout << "�ļ���ʽ��ȷ��û�� \\r δ���� \\n �����⣡" << std::endl;
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
    if (firstline.substr(0, 2) == "//") {// "//"��ʽ
        validParts = firstline.substr(2);
    }
    else if(firstline.substr(0, 2)=="/*"&& firstline.substr(firstline.size()-2, 2)=="*/")// /**/ ��ʽ
    {
        validParts = firstline.substr(2, firstline.length() - 4);
    }
    else if (firstline.substr(0, 2) == "/*" && firstline.substr(firstline.size() - 2, 2) != "*/" && firstline.find("*/")!=-1)
    {
        //����/* */��ʽ������
        return FIRSTLINE_MULTIERROR;
    }
    else if (firstline.substr(0, 2) == "/*" && firstline.find("*/") == -1)
    {
        //����/* */��ʽ������
        return FIRSTLINE_MULTIERROR;
    }
    else
    {
        //���в���ע����
        return FIRSTLINE_NOT_DEFINE;
    }

    // �ָ��ַ���ʱ����ʹ������洢���
    stringstream ss(validParts);
    string part1, part2, part3;

    // �ֶ����ǰ��������
    if (!(ss >> part1) || !(ss >> part2) || !(ss >> part3)) {
        return FIRSTLINE_NOT_3_ITEMS;
    }

    // ����Ƿ��ж��ಿ��
    string extra;
    if (ss >> extra) {
        return FIRSTLINE_NOT_3_ITEMS;
    }

    // ��֤ÿ�����Ƿ�ƥ��
    bool flag = true; // ���ڱ�ʶ�Ƿ������ƥ��
    string stuCls = row[6];
    string stuCls1 = row[5];
    string stuCls2 = "";
    if (stuCls.find("|") != -1)//����תרҵ
    {
        stuCls2 = stuCls.substr(stuCls.find("|")+1);
        stuCls = stuCls.substr(0, stuCls.find("|") );
    }

    if (!isMatch(part1, stuNo) && !isMatch(part2, stuNo) && !isMatch(part3, stuNo)) {
        if (flag) {
            cout << "����";
            flag = false;
        }
        cout << "ѧ�Ų�ƥ��";
    }

    if ( !isMatch(part1, stuName)&& !isMatch(part2, stuName) && !isMatch(part3, stuName)) {
        if (flag) {
            cout << "����";
            flag = false;
        }
        cout << "������ƥ��";
    }

    if (!isMatch(part1, stuCls) &&  !isMatch(part3, stuCls)&& !isMatch(part2, stuCls)&&!isMatch(part1, stuCls2) && !isMatch(part3, stuCls2) && !isMatch(part2, stuCls2) && !isMatch(part1, stuCls1) && !isMatch(part3, stuCls1) && !isMatch(part2, stuCls1)) {
        if (flag) {
            cout << "����";
            flag = false;
        }
        cout << "�༶��ƥ��";
    }

    // �ж����ս��
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
    if (secondline.substr(0, 2) == "//") {// "//"��ʽ
        validParts = secondline.substr(2);
    }
    else if (secondline.substr(0, 2) == "/*" && secondline.substr(secondline.size() - 2, 2) == "*/")// /**/ ��ʽ
    {
        validParts = secondline.substr(2, secondline.length() - 4);
    }
    else //����ע��������
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


    int cnt = 0;//��¼�����Ķ���
    stringstream ss(validParts);
    string now;
    while (ss >> now)
    { 
        if (cnt % 2 == 0)//����Ҫ��ѧ����
        {
            
            if (now.size() != 7 && cntcnt - cnt != 1)
            {
                cout << "��" << cnt / 2 + 1 << "λͬѧ��ѧ��[" << now << "]����7λ���������ݺ���" << endl;
                return STU_NO_ERROR;
            }
            if (now == own_stu_no)
            {
                cout << "��[" << cnt / 2 + 1 << "]��д���Լ����������ݺ���" << endl;
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
        cout << "��[" << cnt / 2  << "]��ѧ���������Ϣ��ȫ(ֻ����һ��)���������ݺ���" << endl;
        return NOT_DOUBLE;
    }
    return CORRECT;
}

void Crosscheck(Cross cross)
{
    for (int i = 0; i < (int)cross.stu_list.size(); i++)
    {
        string validParts;
        if (cross.stu_list[i].secondline.substr(0, 2) == "//") {// "//"��ʽ
            validParts = cross.stu_list[i].secondline.substr(2);
        }
        else if (cross.stu_list[i].secondline.substr(0, 2) == "/*" && cross.stu_list[i].secondline.substr(cross.stu_list[i].secondline.size() - 2, 2) == "*/")// /**/ ��ʽ
        {
            validParts = cross.stu_list[i].secondline.substr(2, cross.stu_list[i].secondline.length() - 4);
        }
        else //����ע��������
        {
            continue;
        }

        int cnt = 0;//��¼�����Ķ���
        stringstream ss(validParts);
        string now;
        string now_no, now_name;
        while (ss >> now)
        {
            if (cnt % 2 == 0)//����Ҫ��ѧ����
            {

                if (now.size() != 7)
                {
                    break;
                    //cout << "��" << cnt / 2 + 1 << "λͬѧ��ѧ��[" << now << "]����7λ���������ݺ���" << endl;
                }
                else if (now == cross.stu_list[i].no)
                {
                    //cout << "��[" << cnt / 2 + 1 << "]��д���Լ����������ݺ���" << endl;
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
            //���Է����Լ������
            string no2 = cross.stu_list[i].valid_stu[j].no;
            string name2 = cross.stu_list[i].valid_stu[j].name;
            bool vis = false;
            {
                //���ȼ�����֣�ѧ���Ƿ�д����
                //��ûд����������orѧ��
                bool flag = false;
                for (int k = 0; k < (int)cross.stu_list.size(); k++)
                {
                    if (cross.stu_list[k].no == no2)
                    {
                        flag = true;        
                        if (cross.stu_list[k].name != name2)
                        {
                            vis = true;
                            cout << "�Է���������ȷ" << endl;
                        }

                    }
                }
                if (!flag && !vis) // û�ҵ���Ӧѧ��
                {
                    vis = true;
                    cout << "�Է�ѧ�Ų�����" << endl;
                }
                else //�ҵ��˶�Ӧ���ˣ���д������
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
                                        cout << "ûд��������" << endl;
                                    }
                                }
                            }
                            if (!flag && !vis)
                            {
                                vis = true;
                                cout << "��������" << endl;
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