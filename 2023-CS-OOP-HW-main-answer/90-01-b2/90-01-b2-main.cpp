/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

/*Read Me
  ����ɴ���ҵʱ������ϸ������demo��ʾ�Ĳ�����֮���������Խ��иĽ����ش˽��ҵ���ҵ��demo�Ĳ�֮ͬ��
  �ڴ�˵����ϣ��������ʦ/����������ҵʱ�鿴��
  1.����С���У�demo��ӡ���ƶ��������ʱ�Ѿ���������Ҫ�����ɵ���Ž�ȥ������ֱ����ȥ�����������������
	��ǰ������ƶ��������һģһ���� ������Ϊ������ʽ����ֱ����������ƶ�����ȥ����������ʾ���ƶ��������
	�����ǰ�Ҫ�ƶ�������ƶ���ָ��λ�ã�����ӡ�µ���Ҳ����ȥ�����������ȥ����ʱ�Ѿ��Ʒ֡�Ȼ���ڵ�ǰ����
	����ʾ�У���ӡ�³��ֵ�����ȥ��������ע��������ر��жϣ��ǲ�����Ϊ�³��ֵ�������ǡ�ú�֮ǰ���ĸ���
	������Ȼ����ȥ����������£�����ȥ�����������÷֣���Ҳ��demo��һ��bug��ͬ��cmd�����ƶ�����ʱҲ��
	������bug��
  2.cmdͼ�ν���Ĳ����ƶ�����û�к�demoһ�������ĳ������ͨ�����˿���һ����״�����Ǳ���ԭ��״����Ȼ�����
	��1�����Ӱ���С�ĸĶ���
*/

int main()
{
	while (1)
	{
		char choice = 0;
		cct_cls();
		cct_setconsoleborder(120, 30, 120, 9001);//���ò˵����ڴ�С
		choice = menu(menu_infor_90_01_b2, total_choice_90_01_b2, infor_num_90_01_b2);
		if (choice == '0')
			return 0;
		cct_cls();
		int tmp = 0, score = 0;
		switch (choice)
		{
			case '1':
				fun_1(choice);
				break;
			case '2':
				fun_2(choice);
				break;
			case '3':
				fun_3(choice);
				break;
			case '4':
				fun_4(choice);
				break;
			case '5':
				fun_5(choice);
				break;
			case '6':
				fun_6(choice);
				break;
			case '7':
				fun_7(choice);
				break;
		}
	}
	return 0;
}

