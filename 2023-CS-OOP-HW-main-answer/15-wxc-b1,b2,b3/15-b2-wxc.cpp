/* 2353597 王雪宸 计拔 */
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;


unsigned char hexToByte(const char* hex) {
    unsigned char byte = 0;
    for (int i = 0; i < 2; ++i) {
        byte <<= 4;
        if (isdigit(hex[i])) {
            byte |= hex[i] - '0';
        }
        else {
            byte |= tolower(hex[i]) - 'a' + 10;
        }
    }
    return byte;
}

void convertHexToBinary(const char* inputFile, const char* outputFile) {
    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Error: Cannot open file " << inputFile << endl;
        return;
    }

    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return;
    }

    char line[100];
    while (inFile.getline(line, sizeof(line))) {
        int length = strlen(line);
        if (length < 10) continue; 

        int hexEnd = 58; // 后面正常显示内容不转换
        for (int i = 10; i < hexEnd && i < length;) {
            if (line[i] == ' ' || line[i] == '-') {
                ++i;
                continue;
            }
            if (isxdigit(line[i]) && isxdigit(line[i + 1])) {
                unsigned char byte = hexToByte(&line[i]);
                outFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                i += 2;
            }
            else {
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    const char* inputFile = nullptr;
    const char* outputFile = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--infile") == 0 && i + 1 < argc) {
            inputFile = argv[++i];
        }
        else if (strcmp(argv[i], "--outfile") == 0 && i + 1 < argc) {
            outputFile = argv[++i];
        }
    }

    if (!inputFile || !outputFile) {
        cerr << "Usage: 15-b2 --infile b.hex --outfile a.txt" << endl;
        cerr << "       15-b2 --outfile a.txt --infile b.hex" << endl;
        return 1;
    }

    convertHexToBinary(inputFile, outputFile);

    return 0;
}