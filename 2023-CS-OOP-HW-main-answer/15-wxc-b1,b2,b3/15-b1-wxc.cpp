/* 2353597 ��ѩ� �ư� */
#include <iostream>
#include <fstream>
#include <iomanip>
#include<cstring>
using namespace std;
void printHexLine(ostream& out, const unsigned char* buffer, int size, int offset) {
    
    out << setw(8) << setfill('0') << hex << offset << "  ";

    // ��ӡ16������
    for (int i = 0; i < size; ++i) {
        if (i > 0 && i % 8 == 0) {
            out << "- ";
        }
        out << setw(2) << setfill('0') << hex << static_cast<int>(buffer[i]) << " ";
    }

    // ���ո�
    if (size < 16) {
        for (int i = size; i < 16; ++i) {
            if (i > 0 && i % 8 == 0) {
                out << "  ";
            }
            out << "   ";
        }
    }

    out << "    ";

    // ��ӡʵ������
    for (int i = 0; i < size; ++i) {
        unsigned char ch = buffer[i];
        if (ch >= 33 && ch <= 126) {
            out << ch;
        }
        else {
            out << '.';
        }
    }

    out << endl;
}

void processFile(const char* inputFile, ostream& out) {
    ifstream file(inputFile, ios::binary);
    if (!file) {
        cerr << "Error: Cannot open file " << inputFile << endl;
        return;
    }

    unsigned char buffer[16];
    int offset = 0;

    while (file.read(reinterpret_cast<char*>(buffer), sizeof(buffer)) || file.gcount()) {
        int bytesRead = int(file.gcount());
        printHexLine(out, buffer, bytesRead, offset);
        offset += bytesRead;
    }
}

int main(int argc, char* argv[]) {
    const char* inputFile = nullptr;
    const char* outputFile = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--infile") ==0&& i + 1 < argc) {
            inputFile = argv[++i];
        }
        else if (strcmp(argv[i], "--outfile")==0 && i + 1 < argc) {
            outputFile = argv[++i];
        }
    }

    if (!inputFile) {
        cerr << "Usage : 15-b1 --infile ԭʼ�ļ� [ --outfile hex��ʽ�ļ� ]" << endl;
        cerr << "        15-b1 --infile a.docx" << endl;
        cerr << "        15-b1 --infile a.docx --outfile a.hex" << endl;
        return 1;
    }

    if (outputFile) {
        ofstream outFile(outputFile);
        if (!outFile) {
            cerr << "Error: Cannot open output file " << outputFile << endl;
            return 1;
        }
        processFile(inputFile, outFile);
    }
    else {
        processFile(inputFile, cout);
    }

    return 0;
}