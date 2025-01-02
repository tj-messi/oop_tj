/* 2353597 王雪宸 计拔 */
#include <iostream>
#include <fstream>

using namespace std;

enum Format { WINDOWS, LINUX, UNRECOGNIZED };

Format checkFormat(const char* inputFile) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "文件打开失败" << endl;
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
                cout << "Windows 格式" << endl;
                break;
            case LINUX:
                cout << "Linux 格式" << endl;
                break;
            default:
                cout << "文件格式无法识别" << endl;
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
            cout << "文件格式无法识别" << endl;
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