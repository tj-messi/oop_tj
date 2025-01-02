/*2351114 �쿡�� ������*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkformat(const char* input_file_name)
{
    FILE *in = fopen(input_file_name, "rb");
    if (!in)
    {
        // printf("�����ļ�%s��ʧ�ܣ�\n", input_file_name);
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
        // printf("�����ļ�%s��ʧ�ܣ�\n", input_file_name);
        return;
    }

    FILE *out = fopen(output_file_name, "wb");
    if (!out)
    {
        fclose(in);
        // printf("����ļ�%s��ʧ�ܣ�\n", output_file_name);
        return;
    }

    int nowch;
    int cnt = 0;
    if (op == 1) // תlinux
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
        printf("ת����ɣ�ȥ��%d��0x0D\n", cnt);
    }
    if (op == 2) // תwindows
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
        printf("ת����ɣ�����%d��0x0D\n", cnt);
    }

    fclose(in);
    fclose(out);
}

void usage()
{
    printf("Usage : 15-b6 --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���\n");
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
            // �����ʽ���
            switch (op)
            {
            case 1:
                printf("Windows��ʽ\n");
                break;
            case 2:
                printf("Linux��ʽ\n");
                break;
            case 3:
                printf("�ļ���ʽ�޷�ʶ��\n");
                break;
            default:
                printf("�ļ���ʽ�޷�ʶ��\n");
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
            if (strcmp(argv[2], "wtol") == 0) // תlinux
            {
                if (checkformat(input_file_name) != 1)
                {
                    printf("�ļ���ʽ�޷�ʶ��\n");
                    return 0;
                }
                convert(1, input_file_name, output_file_name);
            }
            else if (strcmp(argv[2], "ltow") == 0) // תwindows
            {
                if (checkformat(input_file_name) != 2)
                {
                    printf("�ļ���ʽ�޷�ʶ��\n");
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
