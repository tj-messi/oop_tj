/*�쿡�� 2351114 ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
//������Ҫ�ɼ�������ͷ�ļ�


//�˴�Ϊʾ���������޸Ľṹ�����ƣ������޸Ľṹ���еĳ�Ա���ݣ�Ҫ��sizeof������64
struct __attribute__((packed)) Player 
{
    char name[16];  // 1-16: ��ҵ��ǳƣ����15���ַ�
    uint16_t health;    // 17-18: ����ֵ(0-10000)
    uint16_t strength;  // 19-20: ����ֵ(0-10000)
    uint16_t constitution;  // 21-22: ����(0-8192)
    uint16_t dexterity; // 23-24: ����(0-1024)
    uint32_t money;     // 25-28: ��Ǯ����(0-100000000)
    uint32_t fame;      // 29-32: ����ֵ(0-1000000)
    uint32_t charm;     // 33-36: ����ֵ(0-1000000)
    uint64_t total_play_time; // 37-44: ��Ϸ�ۼ�ʱ��(0-10000000000000000)
    uint8_t move_speed; // 45: �ƶ��ٶ�(0-100)
    uint8_t attack_speed; // 46: �����ٶ�(0-100)
    uint8_t attack_range; // 47: ������Χ(0-100)
    uint8_t reserved;   // 48: Ԥ��ֵ���ݲ���
    uint16_t attack_power; // 49-50: ������(0-2000)
    uint16_t defense;   // 51-52: ������(0-2000)
    uint8_t agility;    // 53: ���ݶ�(0-100)
    uint8_t intelligence; // 54: ����(0-100)
    uint8_t experience; // 55: ����(0-100)
    uint8_t level;      // 56: �ȼ�(0-100)
    uint16_t mana;      // 57-58: ħ��ֵ(0-10000)
    uint8_t mana_cost;  // 59: ʹ��ħ��ʱÿ�����ĵ�ħ��ֵ(0-100)
    uint8_t magic_damage; // 60: ħ���˺���(0-100)
    uint8_t accuracy;   // 61: ������(0-100)
    uint8_t magic_defense; // 62: ħ��������(0-100)
    uint8_t critical_rate; // 63: ������(0-100)
    uint8_t stamina;    // 64: ����(0-100)
};

/* �˴�����������������������
   1�����������ĺ����������������µ� FILE* �����д�/��/д/�رյȲ���
   2����������ͬ��������main����
*/

void printlist(const struct Player* buffer)
{
    printf("%20s%s\n", "����ǳ�:", buffer->name);
    printf("%20s%hu\n", "����ֵ:", buffer->health);
    printf("%20s%hu\n", "����ֵ:", buffer->strength);
    printf("%20s%hu\n", "����ֵ:", buffer->constitution);
    printf("%20s%hu\n", "����ֵ:", buffer->dexterity);
    printf("%20s%u\n", "��Ǯֵ:", buffer->money);
    printf("%20s%u\n", "����ֵ:", buffer->fame);
    printf("%20s%u\n", "����ֵ:", buffer->charm);
    printf("%20s%lu\n", "��Ϸ�ۼ�ʱ��(us)ֵ:", buffer->total_play_time);
    printf("%20s%d\n", "�ƶ��ٶ�ֵ:", buffer->move_speed);
    printf("%20s%d\n", "�����ٶ�ֵ:", buffer->attack_speed);
    printf("%20s%d\n", "������Χֵ:", buffer->attack_range);
    printf("%20s%hu\n", "������ֵ:", buffer->attack_power);
    printf("%20s%hu\n", "������ֵ:", buffer->defense);
    printf("%20s%d\n", "���ݶ�ֵ:", buffer->agility);
    printf("%20s%d\n", "����ֵ:", buffer->intelligence);
    printf("%20s%d\n", "����ֵ:", buffer->experience);
    printf("%20s%d\n", "�ȼ�ֵ:", buffer->level);
    printf("%20s%hu\n", "ħ��ֵ:", buffer->mana);
    printf("%20s%d\n", "����ħ��ֵ:", buffer->mana_cost);
    printf("%20s%d\n", "ħ���˺���ֵ:", buffer->magic_damage);
    printf("%20s%d\n", "������ֵ:", buffer->accuracy);
    printf("%20s%d\n", "ħ��������ֵ:", buffer->magic_defense);
    printf("%20s%d\n", "������ֵ:", buffer->critical_rate);
    printf("%20s%d\n", "����ֵ:", buffer->stamina);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��fopen��һ��fread����Ϊ����������������fclose��
***************************************************************************/
int read()
{
    /* ��������ֻ������һ�� FILE* */
    FILE *fp;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ���ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������fopen�⣬�����������ط��������ٳ���fopen/freopen  */
    fp = fopen("game.dat","rb");

	if (fp == NULL)
	{
    	fprintf(stderr, "game.dat��ʧ��\n");
    	return 0;
	}
	
	struct Player readout;
	fread(&readout,64,1,fp);
    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 fread(***, 1, sizeof(demo), fp);
    */
	
	printlist(&readout);
	
	fclose(fp);
	return 0;

}

void printmodify(const struct Player* buffer)
{
	printf("-------------------------------------\n");
	printf("  ��Ϸ�浵�ļ��޸Ĺ���\n");
	printf("-------------------------------------\n");
	printf("  a.%-12s(%s)\n", "����ǳ�", buffer->name);
    printf("  b.%-12s(%hu)\n", "����", buffer->health);
    printf("  c.%-12s(%hu)\n", "����", buffer->strength);
    printf("  d.%-12s(%hu)\n", "����", buffer->constitution);
    printf("  e.%-12s(%hu)\n", "����", buffer->dexterity);
    printf("  f.%-12s(%u)\n", "��Ǯ", buffer->money);
    printf("  g.%-12s(%u)\n", "����", buffer->fame);
    printf("  h.%-12s(%u)\n", "����", buffer->charm);
    printf("  i.%-12s(%lu)\n", "��Ϸ�ۼ�ʱ��", buffer->total_play_time);
    printf("  j.%-12s(%d)\n", "�ƶ��ٶ�", buffer->move_speed);
    printf("  k.%-12s(%d)\n", "�����ٶ�", buffer->attack_speed);
    printf("  l.%-12s(%d)\n", "������Χ", buffer->attack_range);
    printf("  m.%-12s(%hu)\n", "������", buffer->attack_power);
    printf("  n.%-12s(%hu)\n", "������", buffer->defense);
    printf("  o.%-12s(%d)\n", "���ݶ�", buffer->agility);
    printf("  p.%-12s(%d)\n", "����", buffer->intelligence);
    printf("  q.%-12s(%d)\n", "����", buffer->experience);
    printf("  r.%-12s(%d)\n", "�ȼ�", buffer->level);
    printf("  s.%-12s(%hu)\n", "ħ��", buffer->mana);
    printf("  t.%-12s(%d)\n", "����ħ��", buffer->mana_cost);
    printf("  u.%-12s(%d)\n", "ħ���˺���", buffer->magic_damage);
    printf("  v.%-12s(%d)\n", "������", buffer->accuracy);
    printf("  w.%-12s(%d)\n", "ħ��������", buffer->magic_defense);
    printf("  x.%-12s(%d)\n", "������", buffer->critical_rate);
    printf("  y.%-12s(%d)\n", "����", buffer->stamina);
    printf("-------------------------------------\n");
    printf(" 0.�����޸�\n");
	printf(" 1.�����˳�\n");
	printf("-------------------------------------\n");
	printf("��ѡ��[a..y, 0..1] ");
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read��һ��write����Ϊ����������������fclose��
***************************************************************************/
int modify()
{
	const uint64_t bound[]={-1,10000,10000,8192,1024,100000000,1000000,1000000,10000000000000000,100,100,100,2000,2000,100,100,100,100,10000,100,100,100,100,100,100}; 
	
    FILE *fp;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ���ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������fopen�⣬�����������ط��������ٳ���fopen/freopen  */
    fp = fopen("game.dat","rb+");

	if (fp == NULL)
	{
    	fprintf(stderr, "game.dat��ʧ��\n");
    	return 0;
	}
	
	struct Player tempdata;
	fread(&tempdata,64,1,fp);
  	
	while(1)
	{
		printmodify(&tempdata);
		char op;
		scanf("%c",&op);
		if(!((op>='a'&&op<='y') || (op=='0') || (op == '1')))
		{
			continue;
		}
		if(op=='0')
		{
			break;
		}
		else if(op=='1')
		{
			fseek(fp, 0, SEEK_SET);
			fwrite(&tempdata, 64, 1, fp);
			break;
		}
		else
		{
			printf("\n\n");
			{
				//�����䲿�� 
				int idx = op - 'a';
				switch(idx)
				{
					case 0:
            {
                // �޸�����ǳ�
                printf("����ǳƣ���ǰֵ=%s�������� ��", tempdata.name);
                char newname[16];
                scanf("%s", newname);
                strncpy(tempdata.name, newname, 15);
                tempdata.name[15] = '\0';  // ȷ���ַ�����'\0'��β
                break;
            }
            case 1:
            {
                // �޸�����ֵ
                while(1)
                {
                    printf("��������ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.health, bound[idx]);
                    int newhealth;
                    scanf("%d", &newhealth);
                    if(newhealth > bound[idx] || newhealth < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newhealth);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewhealth = (uint16_t)newhealth;
                        tempdata.health = rnewhealth;
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                // �޸�����ֵ
                while(1)
                {
                    printf("��������ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.strength, bound[idx]);
                    int newstrength;
                    scanf("%d", &newstrength);
                    if(newstrength > bound[idx] || newstrength < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newstrength);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewstrength = (uint16_t)newstrength;
                        tempdata.strength = rnewstrength;
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                // �޸�����
                while(1)
                {
                    printf("���ʣ���ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.constitution, bound[idx]);
                    int newconstitution;
                    scanf("%d", &newconstitution);
                    if(newconstitution > bound[idx] || newconstitution < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newconstitution);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewconstitution = (uint16_t)newconstitution;
                        tempdata.constitution = rnewconstitution;
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                // �޸�����
                while(1)
                {
                    printf("���ɣ���ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.dexterity, bound[idx]);
                    int newdexterity;
                    scanf("%d", &newdexterity);
                    if(newdexterity > bound[idx] || newdexterity < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newdexterity);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewdexterity = (uint16_t)newdexterity;
                        tempdata.dexterity = rnewdexterity;
                        break;
                    }
                }
                break;
            }
            case 5:
            {
                // �޸Ľ�Ǯ
                while(1)
                {
                    printf("��Ǯ����ǰֵ=%u����Χ[0..%lu]�������� ��", tempdata.money, bound[idx]);
                    int newmoney;
                    scanf("%d", &newmoney);
                    if(newmoney > bound[idx] || newmoney < 0)
                    {
                        printf("�Ƿ��Ľ�Ǯֵ��%d\n", newmoney);
                        continue;
                    }
                    else
                    {
                        uint32_t rnewmoney = (uint32_t)newmoney;
                        tempdata.money = rnewmoney;
                        break;
                    }
                }
                break;
            }
            case 6:
            {
                // �޸�����
                while(1)
                {
                    printf("��������ǰֵ=%u����Χ[0..%lu]�������� ��", tempdata.fame, bound[idx]);
                    int newfame;
                    scanf("%d", &newfame);
                    if(newfame > bound[idx] || newfame < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newfame);
                        continue;
                    }
                    else
                    {
                        uint32_t rnewfame = (uint32_t)newfame;
                        tempdata.fame = rnewfame;
                        break;
                    }
                }
                break;
            }
            case 7:
            {
                // �޸�����
                while(1)
                {
                    printf("��������ǰֵ=%u����Χ[0..%lu]�������� ��", tempdata.charm, bound[idx]);
                    int newcharm;
                    scanf("%d", &newcharm);
                    if(newcharm > bound[idx] || newcharm < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newcharm);
                        continue;
                    }
                    else
                    {
                        uint32_t rnewcharm = (uint32_t)newcharm;
                        tempdata.charm = rnewcharm;
                        break;
                    }
                }
                break;
            }
            case 8:
            {
                // �޸���Ϸ�ۼ�ʱ��
                while(1)
                {
                    printf("��Ϸ�ۼ�ʱ�䣬��ǰֵ=%lu����Χ[0..%lu]�������� ��", tempdata.total_play_time, bound[idx]);
                    long long newtime;
                    scanf("%lld", &newtime);
                    if(newtime > bound[idx] || newtime < 0)
                    {
                        printf("�Ƿ�����Ϸ�ۼ�ʱ�䣺%lld\n", newtime);
                        continue;
                    }
                    else
                    {
                        uint64_t rnewtime = (uint64_t)newtime;
                        tempdata.total_play_time = rnewtime;
                        break;
                    }
                }
                break;
            }
            case 9:
            {
                // �޸��ƶ��ٶ�
                while(1)
                {
                    printf("�ƶ��ٶȣ���ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.move_speed, bound[idx]);
                    int newmove_speed;
                    scanf("%d", &newmove_speed);
                    if(newmove_speed > bound[idx] || newmove_speed < 0)
                    {
                        printf("�Ƿ����ƶ��ٶ�ֵ��%d\n", newmove_speed);
                        continue;
                    }
                    else
                    {
                        tempdata.move_speed = (uint8_t)newmove_speed;
                        break;
                    }
                }
                break;
            }
            case 10:
            {
                // �޸Ĺ����ٶ�
                while(1)
                {
                    printf("�����ٶȣ���ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.attack_speed, bound[idx]);
                    int newattack_speed;
                    scanf("%d", &newattack_speed);
                    if(newattack_speed > bound[idx] || newattack_speed < 0)
                    {
                        printf("�Ƿ��Ĺ����ٶ�ֵ��%d\n", newattack_speed);
                        continue;
                    }
                    else
                    {
                        tempdata.attack_speed = (uint8_t)newattack_speed;
                        break;
                    }
                }
                break;
            }
            case 11:
            {
                // �޸Ĺ�����Χ
                while(1)
                {
                    printf("������Χ����ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.attack_range, bound[idx]);
                    int newattack_range;
                    scanf("%d", &newattack_range);
                    if(newattack_range > bound[idx] || newattack_range < 0)
                    {
                        printf("�Ƿ��Ĺ�����Χֵ��%d\n", newattack_range);
                        continue;
                    }
                    else
                    {
                        tempdata.attack_range = (uint8_t)newattack_range;
                        break;
                    }
                }
                break;
            }
            case 12:
            {
                // �޸Ĺ�����
                while(1)
                {
                    printf("����������ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.attack_power, bound[idx]);
                    int newattack_power;
                    scanf("%d", &newattack_power);
                    if(newattack_power > bound[idx] || newattack_power < 0)
                    {
                        printf("�Ƿ��Ĺ�����ֵ��%d\n", newattack_power);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewattack_power = (uint16_t)newattack_power;
                        tempdata.attack_power = rnewattack_power;
                        break;
                    }
                }
                break;
            }
            case 13:
            {
                // �޸ķ�����
                while(1)
                {
                    printf("����������ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.defense, bound[idx]);
                    int newdefense;
                    scanf("%d", &newdefense);
                    if(newdefense > bound[idx] || newdefense < 0)
                    {
                        printf("�Ƿ��ķ�����ֵ��%d\n", newdefense);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewdefense = (uint16_t)newdefense;
                        tempdata.defense = rnewdefense;
                        break;
                    }
                }
                break;
            }
            case 14:
            {
                // �޸����ݶ�
                while(1)
                {
                    printf("���ݶȣ���ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.agility, bound[idx]);
                    int newagility;
                    scanf("%d", &newagility);
                    if(newagility > bound[idx] || newagility < 0)
                    {
                        printf("�Ƿ������ݶ�ֵ��%d\n", newagility);
                        continue;
                    }
                    else
                    {
                        tempdata.agility = (uint8_t)newagility;
                        break;
                    }
                }
                break;
            }
            case 15:
            {
                // �޸�����
                while(1)
                {
                    printf("��������ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.intelligence, bound[idx]);
                    int newintelligence;
                    scanf("%d", &newintelligence);
                    if(newintelligence > bound[idx] || newintelligence < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newintelligence);
                        continue;
                    }
                    else
                    {
                        tempdata.intelligence = (uint8_t)newintelligence;
                        break;
                    }
                }
                break;
            }
            case 16:
            {
                // �޸ľ���
                while(1)
                {
                    printf("���飬��ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.experience, bound[idx]);
                    int newexperience;
                    scanf("%d", &newexperience);
                    if(newexperience > bound[idx] || newexperience < 0)
                    {
                        printf("�Ƿ��ľ���ֵ��%d\n", newexperience);
                        continue;
                    }
                    else
                    {
                        tempdata.experience = (uint8_t)newexperience;
                        break;
                    }
                }
                break;
            }
            case 17:
            {
                // �޸ĵȼ�
                while(1)
                {
                    printf("�ȼ�����ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.level, bound[idx]);
                    int newlevel;
                    scanf("%d", &newlevel);
                    if(newlevel > bound[idx] || newlevel < 0)
                    {
                        printf("�Ƿ��ĵȼ�ֵ��%d\n", newlevel);
                        continue;
                    }
                    else
                    {
                        tempdata.level = (uint8_t)newlevel;
                        break;
                    }
                }
                break;
            }
            case 18:
            {
                // �޸�ħ��ֵ
                while(1)
                {
                    printf("ħ��ֵ����ǰֵ=%hu����Χ[0..%lu]�������� ��", tempdata.mana, bound[idx]);
                    int newmana;
                    scanf("%d", &newmana);
                    if(newmana > bound[idx] || newmana < 0)
                    {
                        printf("�Ƿ���ħ��ֵ��%d\n", newmana);
                        continue;
                    }
                    else
                    {
                        uint16_t rnewmana = (uint16_t)newmana;
                        tempdata.mana = rnewmana;
                        break;
                    }
                }
                break;
            }
            case 19:
            {
                // �޸�����ħ��ֵ
                while(1)
                {
                    printf("����ħ��ֵ����ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.mana_cost, bound[idx]);
                    int newmana_cost;
                    scanf("%d", &newmana_cost);
                    if(newmana_cost > bound[idx] || newmana_cost < 0)
                    {
                        printf("�Ƿ�������ħ��ֵ��%d\n", newmana_cost);
                        continue;
                    }
                    else
                    {
                        tempdata.mana_cost = (uint8_t)newmana_cost;
                        break;
                    }
                }
                break;
            }
            case 20:
            {
                // �޸�ħ���˺���
                while(1)
                {
                    printf("ħ���˺�������ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.magic_damage, bound[idx]);
                    int newmagic_damage;
                    scanf("%d", &newmagic_damage);
                    if(newmagic_damage > bound[idx] || newmagic_damage < 0)
                    {
                        printf("�Ƿ���ħ���˺���ֵ��%d\n", newmagic_damage);
                        continue;
                    }
                    else
                    {
                        tempdata.magic_damage = (uint8_t)newmagic_damage;
                        break;
                    }
                }
                break;
            }
            case 21:
            {
                // �޸�������
                while(1)
                {
                    printf("�����ʣ���ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.accuracy, bound[idx]);
                    int newaccuracy;
                    scanf("%d", &newaccuracy);
                    if(newaccuracy > bound[idx] || newaccuracy < 0)
                    {
                        printf("�Ƿ���������ֵ��%d\n", newaccuracy);
                        continue;
                    }
                    else
                    {
                        tempdata.accuracy = (uint8_t)newaccuracy;
                        break;
                    }
                }
                break;
            }
            case 22:
            {
                // �޸�ħ��������
                while(1)
                {
                    printf("ħ������������ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.magic_defense, bound[idx]);
                    int newmagic_defense;
                    scanf("%d", &newmagic_defense);
                    if(newmagic_defense > bound[idx] || newmagic_defense < 0)
                    {
                        printf("�Ƿ���ħ��������ֵ��%d\n", newmagic_defense);
                        continue;
                    }
                    else
                    {
                        tempdata.magic_defense = (uint8_t)newmagic_defense;
                        break;
                    }
                }
                break;
            }
            case 23:
            {
                // �޸ı�����
                while(1)
                {
                    printf("�����ʣ���ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.critical_rate, bound[idx]);
                    int newcritical_rate;
                    scanf("%d", &newcritical_rate);
                    if(newcritical_rate > bound[idx] || newcritical_rate < 0)
                    {
                        printf("�Ƿ��ı�����ֵ��%d\n", newcritical_rate);
                        continue;
                    }
                    else
                    {
                        tempdata.critical_rate = (uint8_t)newcritical_rate;
                        break;
                    }
                }
                break;
            }
            case 24:
            {
                // �޸�����
                while(1)
                {
                    printf("��������ǰֵ=%d����Χ[0..%lu]�������� ��", tempdata.stamina, bound[idx]);
                    int newstamina;
                    scanf("%d", &newstamina);
                    if(newstamina > bound[idx] || newstamina < 0)
                    {
                        printf("�Ƿ�������ֵ��%d\n", newstamina);
                        continue;
                    }
                    else
                    {
                        tempdata.stamina = (uint8_t)newstamina;
                        break;
                    }
                }
                break;
            }
				}
			}
		}
	}
  
	fclose(fp);
	return 0;
	
	
}

void usage(const char * name)
{
	printf("usage : %s --modify | --read\n",name );
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main�������������������������ļ���д
***************************************************************************/
int main(int argc, char **argv)
{
	//struct Player player;
	//printf("%d\n",sizeof(struct Player));
    if(argc!=2 || argc > 2)
    {
    	usage("15-b7-2.c");
	}
    else if(strcmp(argv[1],"--modify")==0)
    {
    	modify();
	} 
    else if(strcmp(argv[1],"--read")==0)
    {
    	read();
	}
	else
	{
		usage("15-b7-2.c");
	}
    
    return 0;
}
