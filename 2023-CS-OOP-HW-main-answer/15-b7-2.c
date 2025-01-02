/* 2353597 ��ѩ� �ư� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


//������Ҫ�ɼ�������ͷ�ļ�


//�˴�Ϊʾ���������޸Ľṹ�����ƣ������޸Ľṹ���еĳ�Ա���ݣ�Ҫ��sizeof������64
#pragma pack(1)
struct PlayerData {
    char nickname[16];  // 1-16: ��ҵ��ǳƣ����15���ַ�
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
#pragma pack()

/* �˴�����������������������
   1�����������ĺ����������������µ� FILE* �����д�/��/д/�رյȲ���
   2����������ͬ��������main����
*/
void handleError(FILE* gfile) {
    if (gfile == NULL) {
        fprintf(stderr, "game.dat��ʧ��\n");
        exit(1);
    }
}

void validateAndSetValue(uint16_t* value, uint16_t min, uint16_t max, const char* name) {
    while (1) {
        uint16_t newValue;
        scanf("%hu", &newValue);
        if (newValue >= min && newValue <= max) {
            *value = newValue;
            break;
        }
        else {
            printf("�Ƿ���%s��%hu�����������룺", name, newValue);
            while (getchar() != '\n');
        }
    }
}

void validateAndSetValue32(uint32_t* value, uint32_t min, uint32_t max, const char* name) {
    while (1) {
        uint32_t newValue;
        scanf("%u", &newValue);
        if (newValue >= min && newValue <= max) {
            *value = newValue;
            break;
        }
        else {
            printf("�Ƿ���%s��%u�����������룺", name, newValue);
            while (getchar() != '\n');
        }
    }
}

void validateAndSetValue64(uint64_t* value, uint64_t min, uint64_t max, const char* name) {
    while (1) {
        uint64_t newValue;
        scanf("%llu", &newValue);
        if (newValue >= min && newValue <= max) {
            *value = newValue;
            break;
        }
        else {
            printf("�Ƿ���%s��%llu�����������룺", name, newValue);
            while (getchar() != '\n');
        }
    }
}

void validateAndSetValue8(uint8_t* value, uint8_t min, uint8_t max, const char* name) {
    while (1) {
        int newValue;
        scanf("%d", &newValue);
        if (newValue >= min && newValue <= max) {
            *value = (uint8_t)newValue;
            break;
        }
        else {
            printf("�Ƿ���%s��%d�����������룺", name, newValue);
            while (getchar() != '\n');
        }
    }
}

void printMenu(const struct PlayerData* buffer) {
    printf("%-20s%s\n", "����ǳ�:", buffer->nickname);
    printf("%-20s%hu\n", "����ֵ:", buffer->health);
    printf("%-20s%hu\n", "����ֵ:", buffer->strength);
    printf("%-20s%hu\n", "����ֵ:", buffer->constitution);
    printf("%-20s%hu\n", "����ֵ:", buffer->dexterity);
    printf("%-20s%u\n", "��Ǯֵ:", buffer->money);
    printf("%-20s%u\n", "����ֵ:", buffer->fame);
    printf("%-20s%u\n", "����ֵ:", buffer->charm);
    printf("%-20s%llu\n", "��Ϸ�ۼ�ʱ��(us)ֵ:", buffer->total_play_time);
    printf("%-20s%d\n", "�ƶ��ٶ�ֵ:", buffer->move_speed);
    printf("%-20s%d\n", "�����ٶ�ֵ:", buffer->attack_speed);
    printf("%-20s%d\n", "������Χֵ:", buffer->attack_range);
    printf("%-20s%hu\n", "������ֵ:", buffer->attack_power);
    printf("%-20s%hu\n", "������ֵ:", buffer->defense);
    printf("%-20s%d\n", "���ݶ�ֵ:", buffer->agility);
    printf("%-20s%d\n", "����ֵ:", buffer->intelligence);
    printf("%-20s%d\n", "����ֵ:", buffer->experience);
    printf("%-20s%d\n", "�ȼ�ֵ:", buffer->level);
    printf("%-20s%hu\n", "ħ��ֵ:", buffer->mana);
    printf("%-20s%d\n", "����ħ��ֵ:", buffer->mana_cost);
    printf("%-20s%d\n", "ħ���˺���ֵ:", buffer->magic_damage);
    printf("%-20s%d\n", "������ֵ:", buffer->accuracy);
    printf("%-20s%d\n", "ħ��������ֵ:", buffer->magic_defense);
    printf("%-20s%d\n", "������ֵ:", buffer->critical_rate);
    printf("%-20s%d\n", "����ֵ:", buffer->stamina);
}

void printMenu_modify(const struct PlayerData* buffer) {
    printf("a.%-18s(%s)\n", "����ǳ�", buffer->nickname);
    printf("b.%-18s(%hu)\n", "����ֵ", buffer->health);
    printf("c.%-18s(%hu)\n", "����ֵ", buffer->strength);
    printf("d.%-18s(%hu)\n", "����ֵ", buffer->constitution);
    printf("e.%-18s(%hu)\n", "����ֵ", buffer->dexterity);
    printf("f.%-18s(%u)\n", "��Ǯֵ", buffer->money);
    printf("g.%-18s(%u)\n", "����ֵ", buffer->fame);
    printf("h.%-18s(%u)\n", "����ֵ", buffer->charm);
    printf("i.%-18s(%llu)\n", "��Ϸ�ۼ�ʱ��(us)ֵ", buffer->total_play_time);
    printf("j.%-18s(%d)\n", "�ƶ��ٶ�ֵ", buffer->move_speed);
    printf("k.%-18s(%d)\n", "�����ٶ�ֵ", buffer->attack_speed);
    printf("l.%-18s(%d)\n", "������Χֵ", buffer->attack_range);
    printf("m.%-18s(%hu)\n", "������ֵ", buffer->attack_power);
    printf("n.%-18s(%hu)\n", "������ֵ", buffer->defense);
    printf("o.%-18s(%d)\n", "���ݶ�ֵ", buffer->agility);
    printf("p.%-18s(%d)\n", "����ֵ", buffer->intelligence);
    printf("q.%-18s(%d)\n", "����ֵ", buffer->experience);
    printf("r.%-18s(%d)\n", "�ȼ�ֵ", buffer->level);
    printf("s.%-18s(%hu)\n", "ħ��ֵ", buffer->mana);
    printf("t.%-18s(%d)\n", "����ħ��ֵ", buffer->mana_cost);
    printf("u.%-18s(%d)\n", "ħ���˺���ֵ", buffer->magic_damage);
    printf("v.%-18s(%d)\n", "������ֵ", buffer->accuracy);
    printf("w.%-18s(%d)\n", "ħ��������ֵ", buffer->magic_defense);
    printf("x.%-18s(%d)\n", "������ֵ", buffer->critical_rate);
    printf("y.%-18s(%d)\n", "����ֵ", buffer->stamina);
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
    fp = fopen("game.dat", "rb");

    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 fread(***, 1, sizeof(demo), fp);
    */
    handleError(fp);

    struct PlayerData buffer;
    fread(&buffer, sizeof(struct PlayerData), 1, fp);

    if (ferror(fp)) {
        fprintf(stderr, "game.dat��ʧ��\n");
        fclose(fp);
        return 1;
    }

    printMenu(&buffer);

    fclose(fp);
    return 0;

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
    /* ��������ֻ������һ�� FILE* */
    FILE *fp;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ�д��ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������fopen�⣬�����������ط��������ٳ���fopen/freopen  */
    fp = fopen("game.dat", "rb+");

    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 fread(***, 1, sizeof(demo), fp);
             ֻ������һ����д��64�ֽڵķ�����***������д��game.dat�У����������ơ��ṹ����������ָ����
                 fwrite(***, 1, sizeof(demo), fp);
    */
    handleError(fp);

    struct PlayerData buffer;
    fread(&buffer, sizeof(struct PlayerData), 1, fp);

    if (ferror(fp)) {
        fprintf(stderr, "game.datд��ʧ��\n");
        fclose(fp);
        return 1;
    }

    int modified = 0;

    do {
        printf("-------------------------------------\n");
        printf("  ��Ϸ�浵�ļ��޸Ĺ���\n");
        printf("-------------------------------------\n");
        printMenu_modify(&buffer);
        printf("-------------------------------------\n");
        printf(" 0.�����޸�\n");
        printf(" 1.�����˳�\n");
        printf("-------------------------------------\n");
        printf("��ѡ��[a..y, 0..1] ");
        char input;
        scanf(" %c", &input);

        if (input == '0') {
            break;
        }
        else if (input == '1') {
            fseek(fp, 0, SEEK_SET);
            fwrite(&buffer, sizeof(struct PlayerData), 1, fp);
            if (ferror(fp)) {
                fprintf(stderr, "Error: Could not write data.\n");
                fclose(fp);
                return 1;
            }
            break;
        }
        else if (input >= 'a' && input <= 'y') {
            int choice = input - 'a'; // Map 'a' to 0, 'b' to 1, ..., 'y' to 24

            switch (choice) {
                case 0: {
                    printf("����ǳƣ���ǰֵ=%s�������� ��", buffer.nickname);
                    char newNickname[16];
                    scanf("%s", newNickname);
                    strncpy(buffer.nickname, newNickname, 15);
                    buffer.nickname[15] = '\0';
                    break;
                }
                case 1: {
                    printf("����ֵ����ǰֵ=%hu�� ������ ��", buffer.health);
                    validateAndSetValue(&buffer.health, 0, 10000, "����ֵ");
                    break;
                }
                case 2: {
                    printf("����ֵ����ǰֵ=%hu�� ������ ��", buffer.strength);
                    validateAndSetValue(&buffer.strength, 0, 10000, "����ֵ");
                    break;
                }
                case 3: {
                    printf("����ֵ����ǰֵ=%hu�� ������ ��", buffer.constitution);
                    validateAndSetValue(&buffer.constitution, 0, 8192, "����ֵ");
                    break;
                }
                case 4: {
                    printf("����ֵ����ǰֵ=%hu�� ������ ��", buffer.dexterity);
                    validateAndSetValue(&buffer.dexterity, 0, 1024, "����ֵ");
                    break;
                }
                case 5: {
                    printf("��Ǯֵ����ǰֵ=%u�� ������ ��", buffer.money);
                    validateAndSetValue32(&buffer.money, 0, 100000000, "��Ǯֵ");
                    break;
                }
                case 6: {
                    printf("����ֵ����ǰֵ=%u�� ������ ��", buffer.fame);
                    validateAndSetValue32(&buffer.fame, 0, 1000000, "����ֵ");
                    break;
                }
                case 7: {
                    printf("����ֵ����ǰֵ=%u�� ������ ��", buffer.charm);
                    validateAndSetValue32(&buffer.charm, 0, 1000000, "����ֵ");
                    break;
                }
                case 8: {
                    printf("��Ϸ�ۼ�ʱ��(us)ֵ����ǰֵ=%llu�� ������ ��", buffer.total_play_time);
                    validateAndSetValue64(&buffer.total_play_time, 0, 10000000000000000, "��Ϸ�ۼ�ʱ��");
                    break;
                }
                case 9: {
                    printf("�ƶ��ٶ�ֵ����ǰֵ=%d�� ������ ��", buffer.move_speed);
                    validateAndSetValue8(&buffer.move_speed, 0, 100, "�ƶ��ٶ�");
                    break;
                }
                case 10: {
                    printf("�����ٶ�ֵ����ǰֵ=%d�� ������ ��", buffer.attack_speed);
                    validateAndSetValue8(&buffer.attack_speed, 0, 100, "�����ٶ�");
                    break;
                }
                case 11: {
                    printf("������Χֵ����ǰֵ=%d�� ������ ��", buffer.attack_range);
                    validateAndSetValue8(&buffer.attack_range, 0, 100, "������Χ");
                    break;
                }
                case 12: {
                    printf("������ֵ����ǰֵ=%hu�� ������ ��", buffer.attack_power);
                    validateAndSetValue(&buffer.attack_power, 0, 2000, "������");
                    break;
                }
                case 13: {
                    printf("������ֵ����ǰֵ=%hu�� ������ ��", buffer.defense);
                    validateAndSetValue(&buffer.defense, 0, 2000, "������");
                    break;
                }
                case 14: {
                    printf("���ݶ�ֵ����ǰֵ=%d�� ������ ��", buffer.agility);
                    validateAndSetValue8(&buffer.agility, 0, 100, "���ݶ�");
                    break;
                }
                case 15: {
                    printf("����ֵ����ǰֵ=%d�� ������ ��", buffer.intelligence);
                    validateAndSetValue8(&buffer.intelligence, 0, 100, "����");
                    break;
                }
                case 16: {
                    printf("����ֵ����ǰֵ=%d�� ������ ��", buffer.experience);
                    validateAndSetValue8(&buffer.experience, 0, 100, "����");
                    break;
                }
                case 17: {
                    printf("�ȼ�ֵ����ǰֵ=%d�� ������ ��", buffer.level);
                    validateAndSetValue8(&buffer.level, 0, 100, "�ȼ�");
                    break;
                }
                case 18: {
                    printf("ħ��ֵ����ǰֵ=%hu�� ������ ��", buffer.mana);
                    validateAndSetValue(&buffer.mana, 0, 10000, "ħ��ֵ");
                    break;
                }
                case 19: {
                    printf("����ħ��ֵ����ǰֵ=%d�� ������ ��", buffer.mana_cost);
                    validateAndSetValue8(&buffer.mana_cost, 0, 100, "����ħ��ֵ");
                    break;
                }
                case 20: {
                    printf("ħ���˺���ֵ����ǰֵ=%d�� ������ ��", buffer.magic_damage);
                    validateAndSetValue8(&buffer.magic_damage, 0, 100, "ħ���˺���");
                    break;
                }
                case 21: {
                    printf("������ֵ����ǰֵ=%d�� ������ ��", buffer.accuracy);
                    validateAndSetValue8(&buffer.accuracy, 0, 100, "������");
                    break;
                }
                case 22: {
                    printf("ħ��������ֵ����ǰֵ=%d�� ������ ��", buffer.magic_defense);
                    validateAndSetValue8(&buffer.magic_defense, 0, 100, "ħ��������");
                    break;
                }
                case 23: {
                    printf("������ֵ����ǰֵ=%d�� ������ ��", buffer.critical_rate);
                    validateAndSetValue8(&buffer.critical_rate, 0, 100, "������");
                    break;
                }
                case 24: {
                    printf("����ֵ����ǰֵ=%d�� ������ ��", buffer.stamina);
                    validateAndSetValue8(&buffer.stamina, 0, 100, "����");
                    break;
                }
                default:
                    printf("��Ч��ѡ��\n");
                    break;
            }
            modified = 1;
        }
        else {
            printf("Invalid input. Please try again.\n");
        }
    } while (1);

    fclose(fp);
    return 0;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main�������������������������ļ���д
***************************************************************************/
int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s --read | --modify\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--read") == 0) {
        return read();
    }
    else if (strcmp(argv[1], "--modify") == 0) {
        return modify();
    }
    else {
        fprintf(stderr, "Invalid option. Use --read or --modify.\n");
        return 1;
    }
    return 0;
}