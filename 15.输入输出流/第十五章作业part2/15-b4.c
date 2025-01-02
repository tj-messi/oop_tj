/*2351114 朱俊泽 大数据*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Hexcout(FILE* out, const unsigned char* buffer, int size, int offset) {
    fprintf(out, "%08x  ", offset);

    for (int i = 0; i < size; ++i) {
        if (i > 0 && i % 8 == 0) {
            fprintf(out, "- ");
        }
        fprintf(out, "%02x ", buffer[i]);
    }

    if (size < 16) {
        for (int i = size; i < 16; ++i) {
            if (i > 0 && i % 8 == 0) {
                fprintf(out, "  ");
            }
            fprintf(out, "   ");
        }
    }

    fprintf(out, "    ");

    for (int i = 0; i < size; ++i) {
        unsigned char ch = buffer[i];
        if (ch >= 33 && ch <= 126) {
            fputc(ch, out);
        } else {
            fputc('.', out);
        }
    }

    fputc('\n', out);
}

void dealfile(const char* filename, FILE* outputStream) {
    unsigned char dataBuffer[16];
    int currentOffset = 0;
    FILE* inputFile = fopen(filename, "rb");
 
    if (!inputFile) {
        fprintf(stderr, "输入文件%s打开失败！\n", filename);
        return;
    }

    while (1) {
        size_t bytesRead = fread(dataBuffer, 1, sizeof(dataBuffer), inputFile);
 
        if (bytesRead == 0) {
            break;
        }
 
        Hexcout(outputStream, dataBuffer, bytesRead, currentOffset);
 
        currentOffset += bytesRead;
    }

    fclose(inputFile);
}

void usage() {
    printf("Usage : 15-b4 --infile 原始文件 [ --outfile hex格式文件 ]\n");
    printf("        15-b4 --infile a.docx\n");
    printf("        15-b4 --infile a.docx --outfile a.hex\n");
}

int main(int argc, char* argv[]) {
    const char* input_file_name = NULL;
    const char* output_file_name = NULL;
    
    if (argc <= 2) {
        usage();
        return 0;
    } 
    
    if (strcmp(argv[1], "--infile") == 0) {
        input_file_name = argv[2];
    } else {
        usage();
        return 0;
    }
    
    if (argc == 5) {
        if (strcmp(argv[3], "--outfile") == 0) {
            output_file_name = argv[4];
        } else {
            usage();
            return 0;
        }
    } else if (argc == 4) {
        usage();
        return 0;
    }
    
    FILE* in = fopen(input_file_name, "rb");
    if (!in) {
        fprintf(stderr, "输入文件%s打开失败！\n", input_file_name);
        return 0;
    } 

    if (output_file_name) {
        FILE* out = fopen(output_file_name, "w");
        if (!out) {
            fprintf(stderr, "输出文件%s打开失败！\n", output_file_name);
            fclose(in);
            return 0;
        }
        dealfile(input_file_name, out);
        fclose(out);
    } else {
        dealfile(input_file_name, stdout);
    }

    fclose(in);
    return 0;
}
