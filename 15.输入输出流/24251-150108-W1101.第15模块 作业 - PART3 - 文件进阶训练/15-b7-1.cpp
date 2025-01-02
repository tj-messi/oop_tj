/*�쿡�� 2351114 ������*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <limits>
#include <iomanip>
using namespace std;

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

void printlist(const Player& buffer)
{
    cout << setw(20) << "����ǳ�:" << buffer.name << endl;
    cout << setw(20) << "����ֵ:" << buffer.health << endl;
    cout << setw(20) << "����ֵ:" << buffer.strength << endl;
    cout << setw(20) << "����ֵ:" << buffer.constitution << endl;
    cout << setw(20) << "����ֵ:" << buffer.dexterity << endl;
    cout << setw(20) << "��Ǯֵ:" << buffer.money << endl;
    cout << setw(20) << "����ֵ:" << buffer.fame << endl;
    cout << setw(20) << "����ֵ:" << buffer.charm << endl;
    cout << setw(20) << "��Ϸ�ۼ�ʱ��(us)ֵ:" << buffer.total_play_time << endl;
    cout << setw(20) << "�ƶ��ٶ�ֵ:" << (int)buffer.move_speed << endl;
    cout << setw(20) << "�����ٶ�ֵ:" << (int)buffer.attack_speed << endl;
    cout << setw(20) << "������Χֵ:" << (int)buffer.attack_range << endl;
    cout << setw(20) << "������ֵ:" << buffer.attack_power << endl;
    cout << setw(20) << "������ֵ:" << buffer.defense << endl;
    cout << setw(20) << "���ݶ�ֵ:" << (int)buffer.agility << endl;
    cout << setw(20) << "����ֵ:" << (int)buffer.intelligence << endl;
    cout << setw(20) << "����ֵ:" << (int)buffer.experience << endl;
    cout << setw(20) << "�ȼ�ֵ:" << (int)buffer.level << endl;
    cout << setw(20) << "ħ��ֵ:" << buffer.mana << endl;
    cout << setw(20) << "����ħ��ֵ:" << (int)buffer.mana_cost << endl;
    cout << setw(20) << "ħ���˺���ֵ:" << (int)buffer.magic_damage << endl;
    cout << setw(20) << "������ֵ:" << (int)buffer.accuracy << endl;
    cout << setw(20) << "ħ��������ֵ:" << (int)buffer.magic_defense << endl;
    cout << setw(20) << "������ֵ:" << (int)buffer.critical_rate << endl;
    cout << setw(20) << "����ֵ:" << (int)buffer.stamina << endl;
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
    fstream fs("game.dat", ios::in | ios::binary);
    
    if (!fs.is_open()) {
        cerr << "game.dat��ʧ��" << endl;
        return 0;
    }
    
    Player readout;
    fs.read(reinterpret_cast<char*>(&readout), sizeof(Player));
    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 fread(***, 1, sizeof(demo), fp);
    */
    
    printlist(readout);
    fs.close();
    return 0;
}

void printmodify(const Player& buffer)
{
    cout << "-------------------------------------" << endl;
    cout << "  ��Ϸ�浵�ļ��޸Ĺ���" << endl;
    cout << "-------------------------------------" << endl;
    cout << "  a." << setw(12) << left << "����ǳ�" << "(" << buffer.name << ")" << endl;
    cout << "  b." << setw(12) << left << "����" << "(" << buffer.health << ")" << endl;
    cout << "  c." << setw(12) << left << "����" << "(" << buffer.strength << ")" << endl;
    cout << "  d." << setw(12) << left << "����" << "(" << buffer.constitution << ")" << endl;
    cout << "  e." << setw(12) << left << "����" << "(" << buffer.dexterity << ")" << endl;
    cout << "  f." << setw(12) << left << "��Ǯ" << "(" << buffer.money << ")" << endl;
    cout << "  g." << setw(12) << left << "����" << "(" << buffer.fame << ")" << endl;
    cout << "  h." << setw(12) << left << "����" << "(" << buffer.charm << ")" << endl;
    cout << "  i." << setw(12) << left << "��Ϸ�ۼ�ʱ��" << "(" << buffer.total_play_time << ")" << endl;
    cout << "  j." << setw(12) << left << "�ƶ��ٶ�" << "(" << (int)buffer.move_speed << ")" << endl;
    cout << "  k." << setw(12) << left << "�����ٶ�" << "(" << (int)buffer.attack_speed << ")" << endl;
    cout << "  l." << setw(12) << left << "������Χ" << "(" << (int)buffer.attack_range << ")" << endl;
    cout << "  m." << setw(12) << left << "������" << "(" << buffer.attack_power << ")" << endl;
    cout << "  n." << setw(12) << left << "������" << "(" << buffer.defense << ")" << endl;
    cout << "  o." << setw(12) << left << "���ݶ�" << "(" << (int)buffer.agility << ")" << endl;
    cout << "  p." << setw(12) << left << "����" << "(" << (int)buffer.intelligence << ")" << endl;
    cout << "  q." << setw(12) << left << "����" << "(" << (int)buffer.experience << ")" << endl;
    cout << "  r." << setw(12) << left << "�ȼ�" << "(" << (int)buffer.level << ")" << endl;
    cout << "  s." << setw(12) << left << "ħ��" << "(" << buffer.mana << ")" << endl;
    cout << "  t." << setw(12) << left << "����ħ��" << "(" << (int)buffer.mana_cost << ")" << endl;
    cout << "  u." << setw(12) << left << "ħ���˺���" << "(" << (int)buffer.magic_damage << ")" << endl;
    cout << "  v." << setw(12) << left << "������" << "(" << (int)buffer.accuracy << ")" << endl;
    cout << "  w." << setw(12) << left << "ħ��������" << "(" << (int)buffer.magic_defense << ")" << endl;
    cout << "  x." << setw(12) << left << "������" << "(" << (int)buffer.critical_rate << ")" << endl;
    cout << "  y." << setw(12) << left << "����" << "(" << (int)buffer.stamina << ")" << endl;
    cout << "-------------------------------------" << endl;
    cout << " 0.�����޸�" << endl;
    cout << " 1.�����˳�" << endl;
    cout << "-------------------------------------" << endl;
    cout << "��ѡ��[a..y, 0..1] ";

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
    const long long int bound[]={-1,10000,10000,8192,1024,100000000,1000000,1000000,10000000000000000,100,100,100,2000,2000,100,100,100,100,10000,100,100,100,100,100,100};

    fstream fs("game.dat", ios::in | ios::out | ios::binary);

    if (!fs.is_open()) {
        cerr << "game.dat��ʧ��" << endl;
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
        // �޸�����ǳ�
        cout << "����ǳƣ���ǰֵ=" << tempdata.name << "�������� ��";
        string newname;
        cin >> newname;
        strncpy(tempdata.name, newname.c_str(), 15);
        tempdata.name[15] = '\0';  // ȷ���ַ�����'\0'��β
        break;
    }
    case 1: {
        // �޸�����ֵ
        while (true) {
            cout << "��������ǰֵ=" << tempdata.health << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newhealth;
            cin >> newhealth;
            if (newhealth > bound[idx] || newhealth < 0) {
                cout << "�Ƿ�������ֵ��" << newhealth << endl;
                continue;
            }
            tempdata.health = (uint16_t)newhealth;
            break;
        }
        break;
    }
    case 2: {
        // �޸�����ֵ
        while (true) {
            cout << "��������ǰֵ=" << tempdata.strength << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newstrength;
            cin >> newstrength;
            if (newstrength > bound[idx] || newstrength < 0) {
                cout << "�Ƿ�������ֵ��" << newstrength << endl;
                continue;
            }
            tempdata.strength = (uint16_t)newstrength;
            break;
        }
        break;
    }
    case 3: {
        // �޸�����
        while (true) {
            cout << "���ʣ���ǰֵ=" << tempdata.constitution << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newconstitution;
            cin >> newconstitution;
            if (newconstitution > bound[idx] || newconstitution < 0) {
                cout << "�Ƿ�������ֵ��" << newconstitution << endl;
                continue;
            }
            tempdata.constitution = (uint16_t)newconstitution;
            break;
        }
        break;
    }
    case 4: {
        // �޸�����
        while (true) {
            cout << "���ɣ���ǰֵ=" << tempdata.dexterity << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newdexterity;
            cin >> newdexterity;
            if (newdexterity > bound[idx] || newdexterity < 0) {
                cout << "�Ƿ�������ֵ��" << newdexterity << endl;
                continue;
            }
            tempdata.dexterity = (uint16_t)newdexterity;
            break;
        }
        break;
    }
    case 5: {
        // �޸Ľ�Ǯ
        while (true) {
            cout << "��Ǯ����ǰֵ=" << tempdata.money << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newmoney;
            cin >> newmoney;
            if (newmoney > bound[idx] || newmoney < 0) {
                cout << "�Ƿ��Ľ�Ǯֵ��" << newmoney << endl;
                continue;
            }
            tempdata.money = (uint32_t)newmoney;
            break;
        }
        break;
    }
    case 6: {
        // �޸�����
        while (true) {
            cout << "��������ǰֵ=" << tempdata.fame << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newfame;
            cin >> newfame;
            if (newfame > bound[idx] || newfame < 0) {
                cout << "�Ƿ�������ֵ��" << newfame << endl;
                continue;
            }
            tempdata.fame = (uint32_t)newfame;
            break;
        }
        break;
    }
    case 7: {
        // �޸�����
        while (true) {
            cout << "��������ǰֵ=" << tempdata.charm << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newcharm;
            cin >> newcharm;
            if (newcharm > bound[idx] || newcharm < 0) {
                cout << "�Ƿ�������ֵ��" << newcharm << endl;
                continue;
            }
            tempdata.charm = (uint32_t)newcharm;
            break;
        }
        break;
    }
    case 8: {
        // �޸���Ϸ�ۼ�ʱ��
        while (true) {
            cout << "��Ϸ�ۼ�ʱ�䣬��ǰֵ=" << tempdata.total_play_time << "����Χ[0.." << bound[idx] << "]�������� ��";
            long long newtime;
            cin >> newtime;
            if (newtime > bound[idx] || newtime < 0) {
                cout << "�Ƿ�����Ϸ�ۼ�ʱ�䣺" << newtime << endl;
                continue;
            }
            tempdata.total_play_time = (uint64_t)newtime;
            break;
        }
        break;
    }
    case 9: {
        // �޸��ƶ��ٶ�
        while (true) {
            cout << "�ƶ��ٶȣ���ǰֵ=" << (int)tempdata.move_speed << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newmove_speed;
            cin >> newmove_speed;
            if (newmove_speed > bound[idx] || newmove_speed < 0) {
                cout << "�Ƿ����ƶ��ٶ�ֵ��" << newmove_speed << endl;
                continue;
            }
            tempdata.move_speed = (uint8_t)newmove_speed;
            break;
        }
        break;
    }
    case 10: {
        // �޸Ĺ����ٶ�
        while (true) {
            cout << "�����ٶȣ���ǰֵ=" << (int)tempdata.attack_speed << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newattack_speed;
            cin >> newattack_speed;
            if (newattack_speed > bound[idx] || newattack_speed < 0) {
                cout << "�Ƿ��Ĺ����ٶ�ֵ��" << newattack_speed << endl;
                continue;
            }
            tempdata.attack_speed = (uint8_t)newattack_speed;
            break;
        }
        break;
    }
    case 11: {
        // �޸Ĺ�����Χ
        while (true) {
            cout << "������Χ����ǰֵ=" << (int)tempdata.attack_range << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newattack_range;
            cin >> newattack_range;
            if (newattack_range > bound[idx] || newattack_range < 0) {
                cout << "�Ƿ��Ĺ�����Χֵ��" << newattack_range << endl;
                continue;
            }
            tempdata.attack_range = (uint8_t)newattack_range;
            break;
        }
        break;
    }
    case 12: {
        // �޸Ĺ�����
        while (true) {
            cout << "����������ǰֵ=" << tempdata.attack_power << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newattack_power;
            cin >> newattack_power;
            if (newattack_power > bound[idx] || newattack_power < 0) {
                cout << "�Ƿ��Ĺ�����ֵ��" << newattack_power << endl;
                continue;
            }
            tempdata.attack_power = (uint16_t)newattack_power;
            break;
        }
        break;
    }
    case 13: {
        // �޸ķ�����
        while (true) {
            cout << "����������ǰֵ=" << tempdata.defense << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newdefense;
            cin >> newdefense;
            if (newdefense > bound[idx] || newdefense < 0) {
                cout << "�Ƿ��ķ�����ֵ��" << newdefense << endl;
                continue;
            }
            tempdata.defense = (uint16_t)newdefense;
            break;
        }
        break;
    }
    case 14: {
        // �޸����ݶ�
        while (true) {
            cout << "���ݶȣ���ǰֵ=" << (int)tempdata.agility << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newagility;
            cin >> newagility;
            if (newagility > bound[idx] || newagility < 0) {
                cout << "�Ƿ������ݶ�ֵ��" << newagility << endl;
                continue;
            }
            tempdata.agility = (uint8_t)newagility;
            break;
        }
        break;
    }
    case 15: {
        // �޸�����
        while (true) {
            cout << "��������ǰֵ=" << (int)tempdata.intelligence << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newintelligence;
            cin >> newintelligence;
            if (newintelligence > bound[idx] || newintelligence < 0) {
                cout << "�Ƿ�������ֵ��" << newintelligence << endl;
                continue;
            }
            tempdata.intelligence = (uint8_t)newintelligence;
            break;
        }
        break;
    }
    case 16: {
        // �޸ľ���
        while (true) {
            cout << "���飬��ǰֵ=" << (int)tempdata.experience << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newexperience;
            cin >> newexperience;
            if (newexperience > bound[idx] || newexperience < 0) {
                cout << "�Ƿ��ľ���ֵ��" << newexperience << endl;
                continue;
            }
            tempdata.experience = (uint8_t)newexperience;
            break;
        }
        break;
    }
    case 17: {
        // �޸ĵȼ�
        while (true) {
            cout << "�ȼ�����ǰֵ=" << (int)tempdata.level << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newlevel;
            cin >> newlevel;
            if (newlevel > bound[idx] || newlevel < 0) {
                cout << "�Ƿ��ĵȼ�ֵ��" << newlevel << endl;
                continue;
            }
            tempdata.level = (uint8_t)newlevel;
            break;
        }
        break;
    }
    case 18: {
        // �޸�ħ��ֵ
        while (true) {
            cout << "ħ��ֵ����ǰֵ=" << tempdata.mana << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newmana;
            cin >> newmana;
            if (newmana > bound[idx] || newmana < 0) {
                cout << "�Ƿ���ħ��ֵ��" << newmana << endl;
                continue;
            }
            tempdata.mana = (uint16_t)newmana;
            break;
        }
        break;
    }
    case 19: {
        // �޸�����ħ��ֵ
        while (true) {
            cout << "����ħ��ֵ����ǰֵ=" << (int)tempdata.mana_cost << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newmana_cost;
            cin >> newmana_cost;
            if (newmana_cost > bound[idx] || newmana_cost < 0) {
                cout << "�Ƿ�������ħ��ֵ��" << newmana_cost << endl;
                continue;
            }
            tempdata.mana_cost = (uint8_t)newmana_cost;
            break;
        }
        break;
    }
    case 20: {
        // �޸�ħ���˺���
        while (true) {
            cout << "ħ���˺�������ǰֵ=" << (int)tempdata.magic_damage << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newmagic_damage;
            cin >> newmagic_damage;
            if (newmagic_damage > bound[idx] || newmagic_damage < 0) {
                cout << "�Ƿ���ħ���˺���ֵ��" << newmagic_damage << endl;
                continue;
            }
            tempdata.magic_damage = (uint8_t)newmagic_damage;
            break;
        }
        break;
    }
    case 21: {
        // �޸�������
        while (true) {
            cout << "�����ʣ���ǰֵ=" << (int)tempdata.accuracy << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newaccuracy;
            cin >> newaccuracy;
            if (newaccuracy > bound[idx] || newaccuracy < 0) {
                cout << "�Ƿ���������ֵ��" << newaccuracy << endl;
                continue;
            }
            tempdata.accuracy = (uint8_t)newaccuracy;
            break;
        }
        break;
    }
    case 22: {
        // �޸�ħ��������
        while (true) {
            cout << "ħ������������ǰֵ=" << (int)tempdata.magic_defense << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newmagic_defense;
            cin >> newmagic_defense;
            if (newmagic_defense > bound[idx] || newmagic_defense < 0) {
                cout << "�Ƿ���ħ��������ֵ��" << newmagic_defense << endl;
                continue;
            }
            tempdata.magic_defense = (uint8_t)newmagic_defense;
            break;
        }
        break;
    }
    case 23: {
        // �޸ı�����
        while (true) {
            cout << "�����ʣ���ǰֵ=" << (int)tempdata.critical_rate << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newcritical_rate;
            cin >> newcritical_rate;
            if (newcritical_rate > bound[idx] || newcritical_rate < 0) {
                cout << "�Ƿ��ı�����ֵ��" << newcritical_rate << endl;
                continue;
            }
            tempdata.critical_rate = (uint8_t)newcritical_rate;
            break;
        }
        break;
    }
    case 24: {
        // �޸�����
        while (true) {
            cout << "��������ǰֵ=" << (int)tempdata.stamina << "����Χ[0.." << bound[idx] << "]�������� ��";
            int newstamina;
            cin >> newstamina;
            if (newstamina > bound[idx] || newstamina < 0) {
                cout << "�Ƿ�������ֵ��" << newstamina << endl;
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main�������������������������ļ���д
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

