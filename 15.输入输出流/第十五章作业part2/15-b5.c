/*2351114 �쿡�� ������*/ 
/*2353597 ��ѩ� 2351577 ��巺� 2353259 ������ 2251174 ������ 2252109 ������ 2152131 �����*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ������ʮ�������ַ�ת��Ϊһ���ֽ�
unsigned char convertHexPairToByte(const char* hexPair) {
    unsigned char result = 0;
    for (int i = 0; i < 2; ++i) {
        result <<= 4; // ����4λΪ��һ��ʮ�����������ڳ��ռ�
        char currentChar = hexPair[i];
        if (isdigit(currentChar)) {
            result |= currentChar - '0'; // �����ַ�ת��Ϊ��Ӧ����ֵ
        } else {
            result |= tolower(currentChar) - 'a' + 10; // ��ĸ�ַ�ת��Ϊ��Ӧ��ʮ������ֵ
        }
    }
    return result;
}

void hex_to_bin(const char* input_file_name, const char* output_file_name) {
    FILE *in = fopen(input_file_name, "rb");
    if (!in) {
        printf("�����ļ�%s��ʧ�ܣ�\n", input_file_name);
        return;
    }

    FILE *out = fopen(output_file_name, "wb");
    if (!out) {
        fclose(in);
        printf("����ļ�%s��ʧ�ܣ�\n", output_file_name);
        return;
    }

    char lineBuffer[100];
    while (fgets(lineBuffer, sizeof(lineBuffer), in)) {
        size_t lineLength = strlen(lineBuffer);
        if (lineLength < 10) {
            continue; // ��������
        }

        for (size_t i = 10; i < 58 && i < lineLength; i++) {
            // �����ո�Ͷ̺���
            if (lineBuffer[i] == ' ' || lineBuffer[i] == '-') {
                continue;
            }

            // ��鵱ǰλ�ü������ַ��Ƿ�Ϊʮ����������
            if (isxdigit(lineBuffer[i]) && isxdigit(lineBuffer[i + 1])) {
                unsigned char byte = convertHexPairToByte(&lineBuffer[i]);
                fwrite(&byte, sizeof(byte), 1, out);
                i++; // �ƶ�����һ��ʮ�����ƶ�
            } else {
                break; // �������ʮ�����ƶԣ���ֹͣ����ǰ��
            }
        }
    }

    fclose(in);
    fclose(out);
}

void usage() {
    printf("Usage : 15-b5 --infile b.hex --outfile a.txt\n");
    printf("        15-b5 --outfile a.txt --infile b.hex\n");
}

int main(int argc, char* argv[]) {
    const char* input_file_name = NULL;
    const char* output_file_name = NULL;

    if (argc != 5) {
        usage();
        return 0;
    }

    // ��������
    if (strcmp(argv[1], "--infile") == 0) {
        input_file_name = argv[2];
        if (strcmp(argv[3], "--outfile") == 0) {
            output_file_name = argv[4];
        } else {
            usage();
            return 0;
        }
    } else if (strcmp(argv[3], "--infile") == 0) {
        input_file_name = argv[4];
        if (strcmp(argv[1], "--outfile") == 0) {
            output_file_name = argv[2];
        } else {
            usage();
            return 0;
        }
    } else {
        usage();
        return 0;
    }

    // ���ļ���ת��
    hex_to_bin(input_file_name, output_file_name);

    return 0;
}
