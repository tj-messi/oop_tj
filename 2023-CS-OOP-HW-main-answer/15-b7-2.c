/* 2353597 王雪宸 计拔 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


//根据需要可加入其它头文件


//此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
#pragma pack(1)
struct PlayerData {
    char nickname[16];  // 1-16: 玩家的昵称，最多15个字符
    uint16_t health;    // 17-18: 生命值(0-10000)
    uint16_t strength;  // 19-20: 力量值(0-10000)
    uint16_t constitution;  // 21-22: 体质(0-8192)
    uint16_t dexterity; // 23-24: 灵巧(0-1024)
    uint32_t money;     // 25-28: 金钱数量(0-100000000)
    uint32_t fame;      // 29-32: 名声值(0-1000000)
    uint32_t charm;     // 33-36: 魅力值(0-1000000)
    uint64_t total_play_time; // 37-44: 游戏累计时间(0-10000000000000000)
    uint8_t move_speed; // 45: 移动速度(0-100)
    uint8_t attack_speed; // 46: 攻击速度(0-100)
    uint8_t attack_range; // 47: 攻击范围(0-100)
    uint8_t reserved;   // 48: 预留值，暂不用
    uint16_t attack_power; // 49-50: 攻击力(0-2000)
    uint16_t defense;   // 51-52: 防御力(0-2000)
    uint8_t agility;    // 53: 敏捷度(0-100)
    uint8_t intelligence; // 54: 智力(0-100)
    uint8_t experience; // 55: 经验(0-100)
    uint8_t level;      // 56: 等级(0-100)
    uint16_t mana;      // 57-58: 魔法值(0-10000)
    uint8_t mana_cost;  // 59: 使用魔法时每次消耗的魔法值(0-100)
    uint8_t magic_damage; // 60: 魔法伤害力(0-100)
    uint8_t accuracy;   // 61: 命中率(0-100)
    uint8_t magic_defense; // 62: 魔法防御力(0-100)
    uint8_t critical_rate; // 63: 暴击率(0-100)
    uint8_t stamina;    // 64: 耐力(0-100)
};
#pragma pack()

/* 此处允许新增函数，数量不限
   1、所有新增的函数，均不允许定义新的 FILE* 并进行打开/读/写/关闭等操作
   2、上述限制同样适用于main函数
*/
void handleError(FILE* gfile) {
    if (gfile == NULL) {
        fprintf(stderr, "game.dat打开失败\n");
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
            printf("非法的%s：%hu，请重新输入：", name, newValue);
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
            printf("非法的%s：%u，请重新输入：", name, newValue);
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
            printf("非法的%s：%llu，请重新输入：", name, newValue);
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
            printf("非法的%s：%d，请重新输入：", name, newValue);
            while (getchar() != '\n');
        }
    }
}

void printMenu(const struct PlayerData* buffer) {
    printf("%-20s%s\n", "玩家昵称:", buffer->nickname);
    printf("%-20s%hu\n", "生命值:", buffer->health);
    printf("%-20s%hu\n", "力量值:", buffer->strength);
    printf("%-20s%hu\n", "体质值:", buffer->constitution);
    printf("%-20s%hu\n", "灵巧值:", buffer->dexterity);
    printf("%-20s%u\n", "金钱值:", buffer->money);
    printf("%-20s%u\n", "名声值:", buffer->fame);
    printf("%-20s%u\n", "魅力值:", buffer->charm);
    printf("%-20s%llu\n", "游戏累计时间(us)值:", buffer->total_play_time);
    printf("%-20s%d\n", "移动速度值:", buffer->move_speed);
    printf("%-20s%d\n", "攻击速度值:", buffer->attack_speed);
    printf("%-20s%d\n", "攻击范围值:", buffer->attack_range);
    printf("%-20s%hu\n", "攻击力值:", buffer->attack_power);
    printf("%-20s%hu\n", "防御力值:", buffer->defense);
    printf("%-20s%d\n", "敏捷度值:", buffer->agility);
    printf("%-20s%d\n", "智力值:", buffer->intelligence);
    printf("%-20s%d\n", "经验值:", buffer->experience);
    printf("%-20s%d\n", "等级值:", buffer->level);
    printf("%-20s%hu\n", "魔法值:", buffer->mana);
    printf("%-20s%d\n", "消耗魔法值:", buffer->mana_cost);
    printf("%-20s%d\n", "魔法伤害力值:", buffer->magic_damage);
    printf("%-20s%d\n", "命中率值:", buffer->accuracy);
    printf("%-20s%d\n", "魔法防御力值:", buffer->magic_defense);
    printf("%-20s%d\n", "暴击率值:", buffer->critical_rate);
    printf("%-20s%d\n", "耐力值:", buffer->stamina);
}

void printMenu_modify(const struct PlayerData* buffer) {
    printf("a.%-18s(%s)\n", "玩家昵称", buffer->nickname);
    printf("b.%-18s(%hu)\n", "生命值", buffer->health);
    printf("c.%-18s(%hu)\n", "力量值", buffer->strength);
    printf("d.%-18s(%hu)\n", "体质值", buffer->constitution);
    printf("e.%-18s(%hu)\n", "灵巧值", buffer->dexterity);
    printf("f.%-18s(%u)\n", "金钱值", buffer->money);
    printf("g.%-18s(%u)\n", "名声值", buffer->fame);
    printf("h.%-18s(%u)\n", "魅力值", buffer->charm);
    printf("i.%-18s(%llu)\n", "游戏累计时间(us)值", buffer->total_play_time);
    printf("j.%-18s(%d)\n", "移动速度值", buffer->move_speed);
    printf("k.%-18s(%d)\n", "攻击速度值", buffer->attack_speed);
    printf("l.%-18s(%d)\n", "攻击范围值", buffer->attack_range);
    printf("m.%-18s(%hu)\n", "攻击力值", buffer->attack_power);
    printf("n.%-18s(%hu)\n", "防御力值", buffer->defense);
    printf("o.%-18s(%d)\n", "敏捷度值", buffer->agility);
    printf("p.%-18s(%d)\n", "智力值", buffer->intelligence);
    printf("q.%-18s(%d)\n", "经验值", buffer->experience);
    printf("r.%-18s(%d)\n", "等级值", buffer->level);
    printf("s.%-18s(%hu)\n", "魔法值", buffer->mana);
    printf("t.%-18s(%d)\n", "消耗魔法值", buffer->mana_cost);
    printf("u.%-18s(%d)\n", "魔法伤害力值", buffer->magic_damage);
    printf("v.%-18s(%d)\n", "命中率值", buffer->accuracy);
    printf("w.%-18s(%d)\n", "魔法防御力值", buffer->magic_defense);
    printf("x.%-18s(%d)\n", "暴击率值", buffer->critical_rate);
    printf("y.%-18s(%d)\n", "耐力值", buffer->stamina);
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次fopen、一次fread（因为包含错误处理，允许多次fclose）
***************************************************************************/
int read()
{
    /* 本函数中只允许定义一个 FILE* */
    FILE *fp;

    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat", "rb");

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
    */
    handleError(fp);

    struct PlayerData buffer;
    fread(&buffer, sizeof(struct PlayerData), 1, fp);

    if (ferror(fp)) {
        fprintf(stderr, "game.dat打开失败\n");
        fclose(fp);
        return 1;
    }

    printMenu(&buffer);

    fclose(fp);
    return 0;

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read、一次write（因为包含错误处理，允许多次fclose）
***************************************************************************/
int modify()
{
    /* 本函数中只允许定义一个 FILE* */
    FILE *fp;

    /* 文件打开，具体要求为：
       1、要求以读写方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat", "rb+");

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
             只允许用一次性写入64字节的方法将***的内容写入game.dat中（缓冲区名称、结构体名称自行指定）
                 fwrite(***, 1, sizeof(demo), fp);
    */
    handleError(fp);

    struct PlayerData buffer;
    fread(&buffer, sizeof(struct PlayerData), 1, fp);

    if (ferror(fp)) {
        fprintf(stderr, "game.dat写入失败\n");
        fclose(fp);
        return 1;
    }

    int modified = 0;

    do {
        printf("-------------------------------------\n");
        printf("  游戏存档文件修改工具\n");
        printf("-------------------------------------\n");
        printMenu_modify(&buffer);
        printf("-------------------------------------\n");
        printf(" 0.放弃修改\n");
        printf(" 1.存盘退出\n");
        printf("-------------------------------------\n");
        printf("请选择[a..y, 0..1] ");
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
                    printf("玩家昵称，当前值=%s，请输入 ：", buffer.nickname);
                    char newNickname[16];
                    scanf("%s", newNickname);
                    strncpy(buffer.nickname, newNickname, 15);
                    buffer.nickname[15] = '\0';
                    break;
                }
                case 1: {
                    printf("生命值，当前值=%hu， 请输入 ：", buffer.health);
                    validateAndSetValue(&buffer.health, 0, 10000, "生命值");
                    break;
                }
                case 2: {
                    printf("力量值，当前值=%hu， 请输入 ：", buffer.strength);
                    validateAndSetValue(&buffer.strength, 0, 10000, "力量值");
                    break;
                }
                case 3: {
                    printf("体质值，当前值=%hu， 请输入 ：", buffer.constitution);
                    validateAndSetValue(&buffer.constitution, 0, 8192, "体质值");
                    break;
                }
                case 4: {
                    printf("灵巧值，当前值=%hu， 请输入 ：", buffer.dexterity);
                    validateAndSetValue(&buffer.dexterity, 0, 1024, "灵巧值");
                    break;
                }
                case 5: {
                    printf("金钱值，当前值=%u， 请输入 ：", buffer.money);
                    validateAndSetValue32(&buffer.money, 0, 100000000, "金钱值");
                    break;
                }
                case 6: {
                    printf("名声值，当前值=%u， 请输入 ：", buffer.fame);
                    validateAndSetValue32(&buffer.fame, 0, 1000000, "名声值");
                    break;
                }
                case 7: {
                    printf("魅力值，当前值=%u， 请输入 ：", buffer.charm);
                    validateAndSetValue32(&buffer.charm, 0, 1000000, "魅力值");
                    break;
                }
                case 8: {
                    printf("游戏累计时间(us)值，当前值=%llu， 请输入 ：", buffer.total_play_time);
                    validateAndSetValue64(&buffer.total_play_time, 0, 10000000000000000, "游戏累计时间");
                    break;
                }
                case 9: {
                    printf("移动速度值，当前值=%d， 请输入 ：", buffer.move_speed);
                    validateAndSetValue8(&buffer.move_speed, 0, 100, "移动速度");
                    break;
                }
                case 10: {
                    printf("攻击速度值，当前值=%d， 请输入 ：", buffer.attack_speed);
                    validateAndSetValue8(&buffer.attack_speed, 0, 100, "攻击速度");
                    break;
                }
                case 11: {
                    printf("攻击范围值，当前值=%d， 请输入 ：", buffer.attack_range);
                    validateAndSetValue8(&buffer.attack_range, 0, 100, "攻击范围");
                    break;
                }
                case 12: {
                    printf("攻击力值，当前值=%hu， 请输入 ：", buffer.attack_power);
                    validateAndSetValue(&buffer.attack_power, 0, 2000, "攻击力");
                    break;
                }
                case 13: {
                    printf("防御力值，当前值=%hu， 请输入 ：", buffer.defense);
                    validateAndSetValue(&buffer.defense, 0, 2000, "防御力");
                    break;
                }
                case 14: {
                    printf("敏捷度值，当前值=%d， 请输入 ：", buffer.agility);
                    validateAndSetValue8(&buffer.agility, 0, 100, "敏捷度");
                    break;
                }
                case 15: {
                    printf("智力值，当前值=%d， 请输入 ：", buffer.intelligence);
                    validateAndSetValue8(&buffer.intelligence, 0, 100, "智力");
                    break;
                }
                case 16: {
                    printf("经验值，当前值=%d， 请输入 ：", buffer.experience);
                    validateAndSetValue8(&buffer.experience, 0, 100, "经验");
                    break;
                }
                case 17: {
                    printf("等级值，当前值=%d， 请输入 ：", buffer.level);
                    validateAndSetValue8(&buffer.level, 0, 100, "等级");
                    break;
                }
                case 18: {
                    printf("魔法值，当前值=%hu， 请输入 ：", buffer.mana);
                    validateAndSetValue(&buffer.mana, 0, 10000, "魔法值");
                    break;
                }
                case 19: {
                    printf("消耗魔法值，当前值=%d， 请输入 ：", buffer.mana_cost);
                    validateAndSetValue8(&buffer.mana_cost, 0, 100, "消耗魔法值");
                    break;
                }
                case 20: {
                    printf("魔法伤害力值，当前值=%d， 请输入 ：", buffer.magic_damage);
                    validateAndSetValue8(&buffer.magic_damage, 0, 100, "魔法伤害力");
                    break;
                }
                case 21: {
                    printf("命中率值，当前值=%d， 请输入 ：", buffer.accuracy);
                    validateAndSetValue8(&buffer.accuracy, 0, 100, "命中率");
                    break;
                }
                case 22: {
                    printf("魔法防御力值，当前值=%d， 请输入 ：", buffer.magic_defense);
                    validateAndSetValue8(&buffer.magic_defense, 0, 100, "魔法防御力");
                    break;
                }
                case 23: {
                    printf("暴击率值，当前值=%d， 请输入 ：", buffer.critical_rate);
                    validateAndSetValue8(&buffer.critical_rate, 0, 100, "暴击率");
                    break;
                }
                case 24: {
                    printf("耐力值，当前值=%d， 请输入 ：", buffer.stamina);
                    validateAndSetValue8(&buffer.stamina, 0, 100, "耐力");
                    break;
                }
                default:
                    printf("无效的选择！\n");
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
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