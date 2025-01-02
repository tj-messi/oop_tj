/* 2353597 ��ѩ� �ư� */
#include <iostream>
#include <fstream>

using namespace std;

enum Format { WINDOWS, LINUX, UNRECOGNIZED };

Format checkFormat(const char* inputFile) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "�ļ���ʧ��" << endl;
        return UNRECOGNIZED;
    }

    char ch;
    bool hasCRLF = false;
    bool hasLF = false;

    while (inFile.get(ch)) {
        if (ch == '\r') {
            if (inFile.get(ch) && ch == '\n') {
                hasCRLF = true;
            }
            else {
                return UNRECOGNIZED;
            }
        }
        else if (ch == '\n') {
            hasLF = true;
        }
    }

    if (hasCRLF && !hasLF) {
        return WINDOWS;
    }
    else if (!hasCRLF && hasLF) {
        return LINUX;
    }
    else {
        return UNRECOGNIZED;
    }
}

void convertToLinux(const char* inputFile, const char* outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    char ch;
    while (inFile.get(ch)) {
        if (ch == '\r') {
            if (inFile.get(ch) && ch == '\n') {
                outFile.put('\n');
            }
        }
        else {
            outFile.put(ch);
        }
    }
}

void convertToWindows(const char* inputFile, const char* outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    char ch;
    while (inFile.get(ch)) {
        if (ch == '\n') {
            outFile.put('\r');
            outFile.put('\n');
        }
        else {
            outFile.put(ch);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: 15-b3 --check a.txt" << endl;
        cerr << "       15-b3 --convert wtol a.txt b.txt" << endl;
        cerr << "       15-b3 --convert ltow c.txt d.txt" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "--check" && argc == 3) {
        Format format = checkFormat(argv[2]);
        switch (format) {
            case WINDOWS:
                cout << "Windows ��ʽ" << endl;
                break;
            case LINUX:
                cout << "Linux ��ʽ" << endl;
                break;
            default:
                cout << "�ļ���ʽ�޷�ʶ��" << endl;
                break;
        }
    }
    else if (command == "--convert" && argc == 5) {
        string conversion = argv[2];
        const char* inputFile = argv[3];
        const char* outputFile = argv[4];

        Format format = checkFormat(inputFile);

        if (conversion == "wtol" && format == WINDOWS) {
            convertToLinux(inputFile, outputFile);
        }
        else if (conversion == "ltow" && format == LINUX) {
            convertToWindows(inputFile, outputFile);
        }
        else {
            cout << "�ļ���ʽ�޷�ʶ��" << endl;
        }
    }
    else {
        cerr << "Usage: 15-b3 --check a.txt" << endl;
        cerr << "       15-b3 --convert wtol a.txt b.txt" << endl;
        cerr << "       15-b3 --convert ltow c.txt d.txt" << endl;
        return 1;
    }

    return 0;
}