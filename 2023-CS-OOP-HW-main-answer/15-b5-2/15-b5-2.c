/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char* const procname)
{
	printf("Usage : %s --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���\n", procname);
	printf("        %s --check a.txt\n", procname);
	printf("        %s --convert wtol a.win.txt a.linux.txt\n", procname);
	printf("        %s --convert ltow a.linux.txt a.win.txt\n", procname);
	return 0;
}

int check_file(const char* file_name)
{
	unsigned char pre, now;
	int first = 1, Linux_file = 1, Windows_file = 1;
	FILE* fin = NULL;
	fin = fopen(file_name, "rb");
	if (fin == NULL)
	{
		return 0; // �޷���
	}
	while (!feof(fin))
	{
		now = fgetc(fin);
		if (feof(fin))
			break;
		if (first == 1)
		{
			pre = now;
			first = 0;
			continue;
		}
		if (pre == '\x0D' && now == '\x0A')
			Linux_file = 0;
		if (pre != '\x0D' && now == '\x0A')
			Windows_file = 0;
		pre = now;
	}
	fclose(fin);
	if (Linux_file == 1 && Windows_file == 0)
		return 1;
	else if (Linux_file == 0 && Windows_file == 1)
		return 2;
	else
		return 3;
}

int convert_file(const char* file_name1, const char* file_name2, const char* convert_cmd)
{

	FILE* fin = NULL, * fout = NULL;
	fin = fopen(file_name1, "rb");
	if (fin == NULL)
		return 0; //�ļ��޷���
	int option = strcmp(convert_cmd, "wtol") == 0 ? 1 : 2; // wtolΪ1��ltowΪ2
	if (option == 1 && check_file(file_name1) != 2) // Windows�޷�ʶ��
	{
		fclose(fin);
		return 1; // �ļ���ʽ�޷�ʶ��
	}
	if (option == 2 && check_file(file_name1) != 1) //Linux�޷�ʶ��
	{
		fclose(fin);
		return 1; // �ļ���ʽ�޷�ʶ��
	}
	fout = fopen(file_name2, "wb");
	if (fout == NULL)
	{
		fclose(fin);
		return 0; //�ļ��޷���
	}

	unsigned char pre, now;
	int first = 1;
	int cnt = 0;
	while (!feof(fin))
	{
		now = fgetc(fin);
		if (feof(fin))
			break;
		if (first == 1)
		{
			pre = now;
			fputc(now, fout);
			first = 0;
			continue;
		}
		if (option == 1)      // Windows
		{
			if (pre == '\x0D' && now == '\x0A')
			{
				fseek(fout, -1, SEEK_CUR);
				++cnt;
			}
		}
		else if (option == 2) // Linux
		{
			if (now == '\x0A') //����\x0Aǰ���\x0D
			{
				fputc('\x0D', fout);
				++cnt;
			}
		}
		pre = now;
		fputc(now, fout);
	}

	if (option == 1)
		printf("ת����ɣ�ȥ��%d��0x0D\n", cnt);
	else if (option == 2)
		printf("ת����ɣ�����%d��0x0D\n", cnt);

	fclose(fin);
	fclose(fout);
	return 2;

}

int main(int argc, char** argv)
{
	/* ����main���������ж� */
	if (!(argc == 3 || argc == 5)) // ���������Ȳ���3���ֲ���5��
	{
		usage(argv[0]);
		return 0;
	}
	if (argc == 3 && strcmp(argv[1], "--check"))   // ������3����������"--check"
	{
		usage(argv[0]);
		return 0;
	}
	if (argc == 5 && (strcmp(argv[1], "--convert")
		|| (strcmp(argv[2], "wtol") && strcmp(argv[2], "ltow")))) // ������5��������"--convert",����"wtol"��"ltow"
	{
		usage(argv[0]);
		return 0;
	}
	char* file_name1 = NULL, * file_name2 = NULL, * convert_cmd = NULL;
	if (argc == 3)
		file_name1 = argv[2];
	else if (argc == 5)
	{
		convert_cmd = argv[2];
		file_name1 = argv[3];
		file_name2 = argv[4];
	}
	if (argc == 3)
	{
		int temp = check_file(file_name1);
		if (temp == 0)
			printf("�ļ���ʧ��\n");
		else if (temp == 1)
			printf("Linux��ʽ\n");
		else if (temp == 2)
			printf("Windows��ʽ\n");
		else
			printf("�ļ���ʽ�޷�ʶ��\n");
	}
	if (argc == 5)
	{
		int temp = convert_file(file_name1, file_name2, convert_cmd);
		if (temp == 0)
			printf("�ļ���ʧ��\n");
		else if (temp == 1)
			printf("�ļ���ʽ�޷�ʶ��\n");
	}
	return 0;
}
