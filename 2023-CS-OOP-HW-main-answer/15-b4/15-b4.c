/* 2150792 计科 牛禄阳 */
/* 1850772 张哲源 2151187 袁之典 2152202 戚峻榕 2152988 杨恺铭 2153731 胡语诺 2252210 韩慕非 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char* const procname)
{
	printf("Usage : %s --infile hex格式文件 --outfile bin格式文件\n", procname);
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

	if (infile_name == NULL || outfile_name == NULL) // 检测infile_name和outfile_name
	{
		usage(argv[0]);
		return 0;
	}

	if ((fin = fopen(infile_name, "rb")) == NULL) // 检测打开文件是否成功
	{
		printf("输入文件%s打开失败!", infile_name);
		return 0;
	}

	if ((fout = fopen(outfile_name, "wb")) == NULL) // 检测打开输出文件是否成功，是wb，和demo保持一致
	{
		printf("输出文件%s打开失败!", outfile_name);
		return 0;
	}

	int offset = 0;
	char file_str[20];   
	while (1)
	{
		fscanf(fin, "%x", &offset); // 读左侧偏移量
		if (feof(fin))
			break;
		fgetc(fin);
		fgetc(fin); // 读两个空格
		int end_flag = 0, end_file = 0;
		for (int i = 0; i < 16; i++)
		{
			unsigned char  num[2] = { 0,0 };
			num[0] = fgetc(fin);
			num[1] = fgetc(fin);
			fgetc(fin);                            // 读去数据间的空格
			if (num[0] == ' ' || num[1] == ' ')   
			{
				end_flag = 1;
				break;
			}
			for (int j = 0; j < 2; j++)
			{
				if (num[j] >= '0' && num[j] <= '9')
					num[j] -= '0';                 // 字符型数字转化为整形
				else
					num[j] = num[j] - 'a' + 10;    // 十六进制字母转化为整形
			}
			fputc(16 * num[0] + num[1], fout);     // 两个字符转化为整形
			if (i == 7)							   // 读到中间会有'- '
			{
				num[0] = fgetc(fin);
				num[1] = fgetc(fin);
			}
		}
		fscanf(fin, "%s", file_str);               // 读取空格右侧字符，fscanf会忽视前导空格
#if    (__linux__)                                 // 换行符十进制写，二进制读。Linux下为0A，Windows下为OD OA         
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
