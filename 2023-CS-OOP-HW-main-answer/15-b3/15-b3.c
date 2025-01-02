/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char* const procname)
{
	printf("Usage : %s --infile 原始文件 [ --outfile hex格式文件 ]\n", procname);
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
			if (infile_name != NULL) // 多次输入--infile
			{
				usage(argv[0]);
				return 0;
			}
			infile_name = argv[i + 1];
		}
		else if (strcmp(argv[i], "--outfile") == 0)
		{
			if (outfile_name != NULL) // 多次输入--outfile
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

	if ((fin = fopen(infile_name, "rb")) == NULL)  // 打开输入文件是否成功
	{
		printf("输入文件%s打开失败!", infile_name);
		return 0;
	}

	if (outfile_name != NULL) // outfile_name可以为NULL，但为NULL就不能fopen
	{
		if ((fout = fopen(outfile_name, "w")) == NULL) // 打开输出文件是否成功
		{
			printf("输出文件%s打开失败!", outfile_name);
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
	--i; // 多读入了EOF

	clearerr(fin);
	line = i / 16;
	col = i % 16;
	rewind(fin); //指针回到文件开头

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