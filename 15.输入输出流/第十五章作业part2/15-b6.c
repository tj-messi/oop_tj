/*2351114 朱俊泽 大数据*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkformat(const char* input_file_name)
{
    FILE *in = fopen(input_file_name, "rb");
    if (!in)
    {
        // printf("输入文件%s打开失败！\n", input_file_name);
        return 3;
    }

    int rn = 0;
    int n = 0;
    int nowch;
    while ((nowch = fgetc(in)) != EOF)
    {
        if (nowch == '\r')
        {
            nowch = fgetc(in);
            if (nowch == '\n')
                rn = 1;
            else
            {
                fclose(in);
                return 3;
            }
        }
        else if (nowch == '\n')
        {
            n = 1;
        }
    }

    fclose(in);

    if (rn && n)
        return 3;
    else if (rn)
        return 1;
    else if (n)
        return 2;
    else
        return 3;
}

void convert(int op, const char* input_file_name, const char* output_file_name)
{
    FILE *in = fopen(input_file_name, "rb");
    if (!in)
    {
        // printf("输入文件%s打开失败！\n", input_file_name);
        return;
    }

    FILE *out = fopen(output_file_name, "wb");
    if (!out)
    {
        fclose(in);
        // printf("输出文件%s打开失败！\n", output_file_name);
        return;
    }

    int nowch;
    int cnt = 0;
    if (op == 1) // 转linux
    {
        while ((nowch = fgetc(in)) != EOF)
        {
            if (nowch == '\r')
            {
                nowch = fgetc(in);
                if (nowch == '\n')
                {
                    fputc('\n', out);
                    cnt++;
                }
            }
            else
            {
                fputc(nowch, out);
            }
        }
        printf("转换完成，去除%d个0x0D\n", cnt);
    }
    if (op == 2) // 转windows
    {
        while ((nowch = fgetc(in)) != EOF)
        {
            if (nowch == '\n')
            {
                fputc('\r', out);
                fputc('\n', out);
                cnt++;
            }
            else
            {
                fputc(nowch, out);
            }
        }
        printf("转换完成，加入%d个0x0D\n", cnt);
    }

    fclose(in);
    fclose(out);
}

void usage()
{
    printf("Usage : 15-b6 --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名\n");
    printf("        15-b6 --check a.txt\n");
    printf("        15-b6 --convert wtol a.win.txt a.linux.txt\n");
    printf("        15-b6 --convert ltow a.linux.txt a.win.txt\n");
}

int main(int argc, char* argv[])
{
    const char* input_file_name = NULL;
    const char* output_file_name = NULL;

    if (argc == 3)
    {
        if (strcmp(argv[1], "--check") == 0)
        {
            input_file_name = argv[2];
            int op = checkformat(input_file_name);
            // 输出格式结果
            switch (op)
            {
            case 1:
                printf("Windows格式\n");
                break;
            case 2:
                printf("Linux格式\n");
                break;
            case 3:
                printf("文件格式无法识别\n");
                break;
            default:
                printf("文件格式无法识别\n");
                break;
            }
        }
        else
        {
            usage();
            return 0;
        }
    }
    else if (argc == 5)
    {
        input_file_name = argv[3];
        output_file_name = argv[4];
        if (strcmp(argv[1], "--convert") == 0)
        {
            if (strcmp(argv[2], "wtol") == 0) // 转linux
            {
                if (checkformat(input_file_name) != 1)
                {
                    printf("文件格式无法识别\n");
                    return 0;
                }
                convert(1, input_file_name, output_file_name);
            }
            else if (strcmp(argv[2], "ltow") == 0) // 转windows
            {
                if (checkformat(input_file_name) != 2)
                {
                    printf("文件格式无法识别\n");
                    return 0;
                }
                convert(2, input_file_name, output_file_name);
            }
            else
            {
                usage();
                return 0;
            }
        }
        else
        {
            usage();
            return 0;
        }
    }
    else
    {
        usage();
        return 0;
    }

    return 0;
}
