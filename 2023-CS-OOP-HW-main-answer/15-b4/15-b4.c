/* 2150792 �ƿ� ţ»�� */
/* 1850772 ����Դ 2151187 Ԭ֮�� 2152202 �ݾ��� 2152988 ������ 2153731 ����ŵ 2252210 ��Ľ�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char* const procname)
{
	printf("Usage : %s --infile hex��ʽ�ļ� --outfile bin��ʽ�ļ�\n", procname);
	printf("        %s --infile a.hex --outfile a.bin\n", procname);
	return 0;
}

int main(int argc, char* argv[])
{

	FILE* fin = NULL, * fout = stdout;
	char* infile_name = NULL, * outfile_name = NULL;
	if (argc != 5)
	{
		usage(argv[0]);
		return 0;
	}
	int i = 1;
	while (1)
	{
		if (i + 1 >= argc || i > 3)
			break;
		if (strcmp(argv[i], "--infile") == 0)
		{
			if (infile_name != NULL) // �������--infile
			{
				usage(argv[0]);
				return 0;
			}
			infile_name = argv[i + 1];
		}
		else if (strcmp(argv[i], "--outfile") == 0)
		{
			if (outfile_name != NULL) // �������--outfile
			{
				usage(argv[0]);
				return 0;
			}
			outfile_name = argv[i + 1];
		}
		else
		{
			usage(argv[0]);
			return 0;
		}
		i = i + 2;
	}

	if (infile_name == NULL || outfile_name == NULL) // ���infile_name��outfile_name
	{
		usage(argv[0]);
		return 0;
	}

	if ((fin = fopen(infile_name, "rb")) == NULL) // �����ļ��Ƿ�ɹ�
	{
		printf("�����ļ�%s��ʧ��!", infile_name);
		return 0;
	}

	if ((fout = fopen(outfile_name, "wb")) == NULL) // ��������ļ��Ƿ�ɹ�����wb����demo����һ��
	{
		printf("����ļ�%s��ʧ��!", outfile_name);
		return 0;
	}

	int offset = 0;
	char file_str[20];   
	while (1)
	{
		fscanf(fin, "%x", &offset); // �����ƫ����
		if (feof(fin))
			break;
		fgetc(fin);
		fgetc(fin); // �������ո�
		int end_flag = 0, end_file = 0;
		for (int i = 0; i < 16; i++)
		{
			unsigned char  num[2] = { 0,0 };
			num[0] = fgetc(fin);
			num[1] = fgetc(fin);
			fgetc(fin);                            // ��ȥ���ݼ�Ŀո�
			if (num[0] == ' ' || num[1] == ' ')   
			{
				end_flag = 1;
				break;
			}
			for (int j = 0; j < 2; j++)
			{
				if (num[j] >= '0' && num[j] <= '9')
					num[j] -= '0';                 // �ַ�������ת��Ϊ����
				else
					num[j] = num[j] - 'a' + 10;    // ʮ��������ĸת��Ϊ����
			}
			fputc(16 * num[0] + num[1], fout);     // �����ַ�ת��Ϊ����
			if (i == 7)							   // �����м����'- '
			{
				num[0] = fgetc(fin);
				num[1] = fgetc(fin);
			}
		}
		fscanf(fin, "%s", file_str);               // ��ȡ�ո��Ҳ��ַ���fscanf�����ǰ���ո�
#if    (__linux__)                                 // ���з�ʮ����д�������ƶ���Linux��Ϊ0A��Windows��ΪOD OA         
		end_file = fgetc(fin);
#else                   
		end_file = fgetc(fin);
		end_file = fgetc(fin);
#endif
		if (end_file == EOF || end_flag)
			break;
	}

	fclose(fin);
	fclose(fout);

	return 0;

}
