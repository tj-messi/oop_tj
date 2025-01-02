/*朱俊泽 2351114 大数据*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <limits>
#include <iomanip>
using namespace std;

//此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
struct __attribute__((packed)) Player 
{
    char name[16];  // 1-16: 玩家的昵称，最多15个字符
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

/* 此处允许新增函数，数量不限
   1、所有新增的函数，均不允许定义新的 FILE* 并进行打开/读/写/关闭等操作
   2、上述限制同样适用于main函数
*/

void printlist(const Player& buffer)
{
    cout << setw(20) << "玩家昵称:" << buffer.name << endl;
    cout << setw(20) << "生命值:" << buffer.health << endl;
    cout << setw(20) << "力量值:" << buffer.strength << endl;
    cout << setw(20) << "体质值:" << buffer.constitution << endl;
    cout << setw(20) << "灵巧值:" << buffer.dexterity << endl;
    cout << setw(20) << "金钱值:" << buffer.money << endl;
    cout << setw(20) << "名声值:" << buffer.fame << endl;
    cout << setw(20) << "魅力值:" << buffer.charm << endl;
    cout << setw(20) << "游戏累计时间(us)值:" << buffer.total_play_time << endl;
    cout << setw(20) << "移动速度值:" << (int)buffer.move_speed << endl;
    cout << setw(20) << "攻击速度值:" << (int)buffer.attack_speed << endl;
    cout << setw(20) << "攻击范围值:" << (int)buffer.attack_range << endl;
    cout << setw(20) << "攻击力值:" << buffer.attack_power << endl;
    cout << setw(20) << "防御力值:" << buffer.defense << endl;
    cout << setw(20) << "敏捷度值:" << (int)buffer.agility << endl;
    cout << setw(20) << "智力值:" << (int)buffer.intelligence << endl;
    cout << setw(20) << "经验值:" << (int)buffer.experience << endl;
    cout << setw(20) << "等级值:" << (int)buffer.level << endl;
    cout << setw(20) << "魔法值:" << buffer.mana << endl;
    cout << setw(20) << "消耗魔法值:" << (int)buffer.mana_cost << endl;
    cout << setw(20) << "魔法伤害力值:" << (int)buffer.magic_damage << endl;
    cout << setw(20) << "命中率值:" << (int)buffer.accuracy << endl;
    cout << setw(20) << "魔法防御力值:" << (int)buffer.magic_defense << endl;
    cout << setw(20) << "暴击率值:" << (int)buffer.critical_rate << endl;
    cout << setw(20) << "耐力值:" << (int)buffer.stamina << endl;
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
    fstream fs("game.dat", ios::in | ios::binary);
    
    if (!fs.is_open()) {
        cerr << "game.dat打开失败" << endl;
        return 0;
    }
    
    Player readout;
    fs.read(reinterpret_cast<char*>(&readout), sizeof(Player));
    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
    */
    
    printlist(readout);
    fs.close();
    return 0;
}

void printmodify(const Player& buffer)
{
    cout << "-------------------------------------" << endl;
    cout << "  游戏存档文件修改工具" << endl;
    cout << "-------------------------------------" << endl;
    cout << "  a." << setw(12) << left << "玩家昵称" << "(" << buffer.name << ")" << endl;
    cout << "  b." << setw(12) << left << "生命" << "(" << buffer.health << ")" << endl;
    cout << "  c." << setw(12) << left << "力量" << "(" << buffer.strength << ")" << endl;
    cout << "  d." << setw(12) << left << "体质" << "(" << buffer.constitution << ")" << endl;
    cout << "  e." << setw(12) << left << "灵巧" << "(" << buffer.dexterity << ")" << endl;
    cout << "  f." << setw(12) << left << "金钱" << "(" << buffer.money << ")" << endl;
    cout << "  g." << setw(12) << left << "名声" << "(" << buffer.fame << ")" << endl;
    cout << "  h." << setw(12) << left << "魅力" << "(" << buffer.charm << ")" << endl;
    cout << "  i." << setw(12) << left << "游戏累计时间" << "(" << buffer.total_play_time << ")" << endl;
    cout << "  j." << setw(12) << left << "移动速度" << "(" << (int)buffer.move_speed << ")" << endl;
    cout << "  k." << setw(12) << left << "攻击速度" << "(" << (int)buffer.attack_speed << ")" << endl;
    cout << "  l." << setw(12) << left << "攻击范围" << "(" << (int)buffer.attack_range << ")" << endl;
    cout << "  m." << setw(12) << left << "攻击力" << "(" << buffer.attack_power << ")" << endl;
    cout << "  n." << setw(12) << left << "防御力" << "(" << buffer.defense << ")" << endl;
    cout << "  o." << setw(12) << left << "敏捷度" << "(" << (int)buffer.agility << ")" << endl;
    cout << "  p." << setw(12) << left << "智力" << "(" << (int)buffer.intelligence << ")" << endl;
    cout << "  q." << setw(12) << left << "经验" << "(" << (int)buffer.experience << ")" << endl;
    cout << "  r." << setw(12) << left << "等级" << "(" << (int)buffer.level << ")" << endl;
    cout << "  s." << setw(12) << left << "魔法" << "(" << buffer.mana << ")" << endl;
    cout << "  t." << setw(12) << left << "消耗魔法" << "(" << (int)buffer.mana_cost << ")" << endl;
    cout << "  u." << setw(12) << left << "魔法伤害力" << "(" << (int)buffer.magic_damage << ")" << endl;
    cout << "  v." << setw(12) << left << "命中率" << "(" << (int)buffer.accuracy << ")" << endl;
    cout << "  w." << setw(12) << left << "魔法防御力" << "(" << (int)buffer.magic_defense << ")" << endl;
    cout << "  x." << setw(12) << left << "暴击率" << "(" << (int)buffer.critical_rate << ")" << endl;
    cout << "  y." << setw(12) << left << "耐力" << "(" << (int)buffer.stamina << ")" << endl;
    cout << "-------------------------------------" << endl;
    cout << " 0.放弃修改" << endl;
    cout << " 1.存盘退出" << endl;
    cout << "-------------------------------------" << endl;
    cout << "请选择[a..y, 0..1] ";

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
    const long long int bound[]={-1,10000,10000,8192,1024,100000000,1000000,1000000,10000000000000000,100,100,100,2000,2000,100,100,100,100,10000,100,100,100,100,100,100};

    fstream fs("game.dat", ios::in | ios::out | ios::binary);

    if (!fs.is_open()) {
        cerr << "game.dat打开失败" << endl;
        return 0;
    }

    Player tempdata;
    fs.read(reinterpret_cast<char*>(&tempdata), sizeof(Player));
    
    while (true) {
        printmodify(tempdata);
        char op;
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!(op >= 'a' && op <= 'y') && op != '0' && op != '1') {
            continue;
        }
        
        if (op == '0') {
            break;
        }
        else if (op == '1') {
            fs.seekg(0, ios::beg);
            fs.write(reinterpret_cast<char*>(&tempdata), sizeof(Player));
            break;
        }
        else {
            cout << "\n\n";
            int idx = op - 'a';
            switch (idx) {
    case 0: {
        // 修改玩家昵称
        cout << "玩家昵称，当前值=" << tempdata.name << "，请输入 ：";
        string newname;
        cin >> newname;
        strncpy(tempdata.name, newname.c_str(), 15);
        tempdata.name[15] = '\0';  // 确保字符串以'\0'结尾
        break;
    }
    case 1: {
        // 修改生命值
        while (true) {
            cout << "生命，当前值=" << tempdata.health << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newhealth;
            cin >> newhealth;
            if (newhealth > bound[idx] || newhealth < 0) {
                cout << "非法的生命值：" << newhealth << endl;
                continue;
            }
            tempdata.health = (uint16_t)newhealth;
            break;
        }
        break;
    }
    case 2: {
        // 修改力量值
        while (true) {
            cout << "力量，当前值=" << tempdata.strength << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newstrength;
            cin >> newstrength;
            if (newstrength > bound[idx] || newstrength < 0) {
                cout << "非法的力量值：" << newstrength << endl;
                continue;
            }
            tempdata.strength = (uint16_t)newstrength;
            break;
        }
        break;
    }
    case 3: {
        // 修改体质
        while (true) {
            cout << "体质，当前值=" << tempdata.constitution << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newconstitution;
            cin >> newconstitution;
            if (newconstitution > bound[idx] || newconstitution < 0) {
                cout << "非法的体质值：" << newconstitution << endl;
                continue;
            }
            tempdata.constitution = (uint16_t)newconstitution;
            break;
        }
        break;
    }
    case 4: {
        // 修改灵巧
        while (true) {
            cout << "灵巧，当前值=" << tempdata.dexterity << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newdexterity;
            cin >> newdexterity;
            if (newdexterity > bound[idx] || newdexterity < 0) {
                cout << "非法的灵巧值：" << newdexterity << endl;
                continue;
            }
            tempdata.dexterity = (uint16_t)newdexterity;
            break;
        }
        break;
    }
    case 5: {
        // 修改金钱
        while (true) {
            cout << "金钱，当前值=" << tempdata.money << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newmoney;
            cin >> newmoney;
            if (newmoney > bound[idx] || newmoney < 0) {
                cout << "非法的金钱值：" << newmoney << endl;
                continue;
            }
            tempdata.money = (uint32_t)newmoney;
            break;
        }
        break;
    }
    case 6: {
        // 修改名声
        while (true) {
            cout << "名声，当前值=" << tempdata.fame << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newfame;
            cin >> newfame;
            if (newfame > bound[idx] || newfame < 0) {
                cout << "非法的名声值：" << newfame << endl;
                continue;
            }
            tempdata.fame = (uint32_t)newfame;
            break;
        }
        break;
    }
    case 7: {
        // 修改魅力
        while (true) {
            cout << "魅力，当前值=" << tempdata.charm << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newcharm;
            cin >> newcharm;
            if (newcharm > bound[idx] || newcharm < 0) {
                cout << "非法的魅力值：" << newcharm << endl;
                continue;
            }
            tempdata.charm = (uint32_t)newcharm;
            break;
        }
        break;
    }
    case 8: {
        // 修改游戏累计时间
        while (true) {
            cout << "游戏累计时间，当前值=" << tempdata.total_play_time << "，范围[0.." << bound[idx] << "]，请输入 ：";
            long long newtime;
            cin >> newtime;
            if (newtime > bound[idx] || newtime < 0) {
                cout << "非法的游戏累计时间：" << newtime << endl;
                continue;
            }
            tempdata.total_play_time = (uint64_t)newtime;
            break;
        }
        break;
    }
    case 9: {
        // 修改移动速度
        while (true) {
            cout << "移动速度，当前值=" << (int)tempdata.move_speed << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newmove_speed;
            cin >> newmove_speed;
            if (newmove_speed > bound[idx] || newmove_speed < 0) {
                cout << "非法的移动速度值：" << newmove_speed << endl;
                continue;
            }
            tempdata.move_speed = (uint8_t)newmove_speed;
            break;
        }
        break;
    }
    case 10: {
        // 修改攻击速度
        while (true) {
            cout << "攻击速度，当前值=" << (int)tempdata.attack_speed << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newattack_speed;
            cin >> newattack_speed;
            if (newattack_speed > bound[idx] || newattack_speed < 0) {
                cout << "非法的攻击速度值：" << newattack_speed << endl;
                continue;
            }
            tempdata.attack_speed = (uint8_t)newattack_speed;
            break;
        }
        break;
    }
    case 11: {
        // 修改攻击范围
        while (true) {
            cout << "攻击范围，当前值=" << (int)tempdata.attack_range << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newattack_range;
            cin >> newattack_range;
            if (newattack_range > bound[idx] || newattack_range < 0) {
                cout << "非法的攻击范围值：" << newattack_range << endl;
                continue;
            }
            tempdata.attack_range = (uint8_t)newattack_range;
            break;
        }
        break;
    }
    case 12: {
        // 修改攻击力
        while (true) {
            cout << "攻击力，当前值=" << tempdata.attack_power << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newattack_power;
            cin >> newattack_power;
            if (newattack_power > bound[idx] || newattack_power < 0) {
                cout << "非法的攻击力值：" << newattack_power << endl;
                continue;
            }
            tempdata.attack_power = (uint16_t)newattack_power;
            break;
        }
        break;
    }
    case 13: {
        // 修改防御力
        while (true) {
            cout << "防御力，当前值=" << tempdata.defense << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newdefense;
            cin >> newdefense;
            if (newdefense > bound[idx] || newdefense < 0) {
                cout << "非法的防御力值：" << newdefense << endl;
                continue;
            }
            tempdata.defense = (uint16_t)newdefense;
            break;
        }
        break;
    }
    case 14: {
        // 修改敏捷度
        while (true) {
            cout << "敏捷度，当前值=" << (int)tempdata.agility << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newagility;
            cin >> newagility;
            if (newagility > bound[idx] || newagility < 0) {
                cout << "非法的敏捷度值：" << newagility << endl;
                continue;
            }
            tempdata.agility = (uint8_t)newagility;
            break;
        }
        break;
    }
    case 15: {
        // 修改智力
        while (true) {
            cout << "智力，当前值=" << (int)tempdata.intelligence << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newintelligence;
            cin >> newintelligence;
            if (newintelligence > bound[idx] || newintelligence < 0) {
                cout << "非法的智力值：" << newintelligence << endl;
                continue;
            }
            tempdata.intelligence = (uint8_t)newintelligence;
            break;
        }
        break;
    }
    case 16: {
        // 修改经验
        while (true) {
            cout << "经验，当前值=" << (int)tempdata.experience << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newexperience;
            cin >> newexperience;
            if (newexperience > bound[idx] || newexperience < 0) {
                cout << "非法的经验值：" << newexperience << endl;
                continue;
            }
            tempdata.experience = (uint8_t)newexperience;
            break;
        }
        break;
    }
    case 17: {
        // 修改等级
        while (true) {
            cout << "等级，当前值=" << (int)tempdata.level << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newlevel;
            cin >> newlevel;
            if (newlevel > bound[idx] || newlevel < 0) {
                cout << "非法的等级值：" << newlevel << endl;
                continue;
            }
            tempdata.level = (uint8_t)newlevel;
            break;
        }
        break;
    }
    case 18: {
        // 修改魔法值
        while (true) {
            cout << "魔法值，当前值=" << tempdata.mana << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newmana;
            cin >> newmana;
            if (newmana > bound[idx] || newmana < 0) {
                cout << "非法的魔法值：" << newmana << endl;
                continue;
            }
            tempdata.mana = (uint16_t)newmana;
            break;
        }
        break;
    }
    case 19: {
        // 修改消耗魔法值
        while (true) {
            cout << "消耗魔法值，当前值=" << (int)tempdata.mana_cost << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newmana_cost;
            cin >> newmana_cost;
            if (newmana_cost > bound[idx] || newmana_cost < 0) {
                cout << "非法的消耗魔法值：" << newmana_cost << endl;
                continue;
            }
            tempdata.mana_cost = (uint8_t)newmana_cost;
            break;
        }
        break;
    }
    case 20: {
        // 修改魔法伤害力
        while (true) {
            cout << "魔法伤害力，当前值=" << (int)tempdata.magic_damage << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newmagic_damage;
            cin >> newmagic_damage;
            if (newmagic_damage > bound[idx] || newmagic_damage < 0) {
                cout << "非法的魔法伤害力值：" << newmagic_damage << endl;
                continue;
            }
            tempdata.magic_damage = (uint8_t)newmagic_damage;
            break;
        }
        break;
    }
    case 21: {
        // 修改命中率
        while (true) {
            cout << "命中率，当前值=" << (int)tempdata.accuracy << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newaccuracy;
            cin >> newaccuracy;
            if (newaccuracy > bound[idx] || newaccuracy < 0) {
                cout << "非法的命中率值：" << newaccuracy << endl;
                continue;
            }
            tempdata.accuracy = (uint8_t)newaccuracy;
            break;
        }
        break;
    }
    case 22: {
        // 修改魔法防御力
        while (true) {
            cout << "魔法防御力，当前值=" << (int)tempdata.magic_defense << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newmagic_defense;
            cin >> newmagic_defense;
            if (newmagic_defense > bound[idx] || newmagic_defense < 0) {
                cout << "非法的魔法防御力值：" << newmagic_defense << endl;
                continue;
            }
            tempdata.magic_defense = (uint8_t)newmagic_defense;
            break;
        }
        break;
    }
    case 23: {
        // 修改暴击率
        while (true) {
            cout << "暴击率，当前值=" << (int)tempdata.critical_rate << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newcritical_rate;
            cin >> newcritical_rate;
            if (newcritical_rate > bound[idx] || newcritical_rate < 0) {
                cout << "非法的暴击率值：" << newcritical_rate << endl;
                continue;
            }
            tempdata.critical_rate = (uint8_t)newcritical_rate;
            break;
        }
        break;
    }
    case 24: {
        // 修改耐力
        while (true) {
            cout << "耐力，当前值=" << (int)tempdata.stamina << "，范围[0.." << bound[idx] << "]，请输入 ：";
            int newstamina;
            cin >> newstamina;
            if (newstamina > bound[idx] || newstamina < 0) {
                cout << "非法的耐力值：" << newstamina << endl;
                continue;
            }
            tempdata.stamina = (uint8_t)newstamina;
            break;
        }
        break;
    }
}

        }
    }

    fs.close();
    return 0;
}

void usage(const char* name)
{
    cout << "usage : " << name << " --modify | --read" << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
***************************************************************************/
int main(int argc, char **argv)
{
    if (argc != 2) {
        usage("15-b7-2.cpp");
    }
    else if (strcmp(argv[1], "--modify") == 0) {
        modify();
    }
    else if (strcmp(argv[1], "--read") == 0) {
        read();
    }
    else {
        usage("15-b7-2.cpp");
    }

    return 0;
}

