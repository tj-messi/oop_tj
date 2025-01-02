/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char* const procname)
{
	printf("Usage : %s --infile ԭʼ�ļ� [ --outfile hex��ʽ�ļ� ]\n", procname);
	printf("        %s --infile a.docx\n", procname);
	printf("        %s --infile a.docx --outfile a.hex\n", procname);
	return 0;
}

int main(int argc, char* argv[])
{
	FILE* fin = NULL, * fout = stdout;
	char* infile_name=NULL, * outfile_name=NULL;
	if (argc <= 1 || argc > 5)
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

	if (infile_name == NULL)
	{
		usage(argv[0]);
		return 0;
	}

	if ((fin = fopen(infile_name, "rb")) == NULL)  // �������ļ��Ƿ�ɹ�
	{
		printf("�����ļ�%s��ʧ��!", infile_name);
		return 0;
	}

	if (outfile_name != NULL) // outfile_name����ΪNULL����ΪNULL�Ͳ���fopen
	{
		if ((fout = fopen(outfile_name, "w")) == NULL) // ������ļ��Ƿ�ɹ�
		{
			printf("����ļ�%s��ʧ��!", outfile_name);
			return 0;
		}
	}

	unsigned char ch[20];
	i = 0;
	int line = 0, col = 0;
	while (!feof(fin))
	{
		fgetc(fin);
		++i;
	}
	--i; // �������EOF

	clearerr(fin);
	line = i / 16;
	col = i % 16;
	rewind(fin); //ָ��ص��ļ���ͷ

	for (int k = 0; k < line; k++)
	{
		fprintf(fout, "%08x  ", 16 * k);
		for (int t = 0; t < 16; t++)
			ch[t] = fgetc(fin);
		for (int t = 0; t < 16; t++)
		{
			if (t == 8)
				fprintf(fout, "- ");
			fprintf(fout, "%02x ", (int)ch[t]);
		}
		fprintf(fout, "    ");
		for (int t = 0; t < 16; t++)
		{
			if (ch[t] >= 33 && ch[t] <= 126)
				fprintf(fout, "%c", ch[t]);
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	}
	if (col != 0)
	{
		fprintf(fout, "%08x  ", 16 * line);
		for (int t = 0; t < col; t++)
			ch[t] = fgetc(fin);
		for (int t = 0; t < col; t++)
		{
			if (t == 8)
				fprintf(fout, "- ");
			fprintf(fout, "%02x ", (int)ch[t]);
		}
		if (col <= 8)
			fprintf(fout, "%*s", 54 - 3 * col, " ");
		else
			fprintf(fout, "%*s", 54 - 3 * col - 2, " ");
		for (int t = 0; t < col; t++)
		{
			if (ch[t] >= 33 && ch[t] <= 126)
				fprintf(fout, "%c", ch[t]);
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	}

	fclose(fin);
	fclose(fout);
    return 0;
}