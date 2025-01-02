/*朱俊泽 2351114 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
//根据需要可加入其它头文件


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

void printlist(const struct Player* buffer)
{
    printf("%20s%s\n", "玩家昵称:", buffer->name);
    printf("%20s%hu\n", "生命值:", buffer->health);
    printf("%20s%hu\n", "力量值:", buffer->strength);
    printf("%20s%hu\n", "体质值:", buffer->constitution);
    printf("%20s%hu\n", "灵巧值:", buffer->dexterity);
    printf("%20s%u\n", "金钱值:", buffer->money);
    printf("%20s%u\n", "名声值:", buffer->fame);
    printf("%20s%u\n", "魅力值:", buffer->charm);
    printf("%20s%lu\n", "游戏累计时间(us)值:", buffer->total_play_time);
    printf("%20s%d\n", "移动速度值:", buffer->move_speed);
    printf("%20s%d\n", "攻击速度值:", buffer->attack_speed);
    printf("%20s%d\n", "攻击范围值:", buffer->attack_range);
    printf("%20s%hu\n", "攻击力值:", buffer->attack_power);
    printf("%20s%hu\n", "防御力值:", buffer->defense);
    printf("%20s%d\n", "敏捷度值:", buffer->agility);
    printf("%20s%d\n", "智力值:", buffer->intelligence);
    printf("%20s%d\n", "经验值:", buffer->experience);
    printf("%20s%d\n", "等级值:", buffer->level);
    printf("%20s%hu\n", "魔法值:", buffer->mana);
    printf("%20s%d\n", "消耗魔法值:", buffer->mana_cost);
    printf("%20s%d\n", "魔法伤害力值:", buffer->magic_damage);
    printf("%20s%d\n", "命中率值:", buffer->accuracy);
    printf("%20s%d\n", "魔法防御力值:", buffer->magic_defense);
    printf("%20s%d\n", "暴击率值:", buffer->critical_rate);
    printf("%20s%d\n", "耐力值:", buffer->stamina);
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
    fp = fopen("game.dat","rb");

	if (fp == NULL)
	{
    	fprintf(stderr, "game.dat打开失败\n");
    	return 0;
	}
	
	struct Player readout;
	fread(&readout,64,1,fp);
    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
    */
	
	printlist(&readout);
	
	fclose(fp);
	return 0;

}

void printmodify(const struct Player* buffer)
{
	printf("-------------------------------------\n");
	printf("  游戏存档文件修改工具\n");
	printf("-------------------------------------\n");
	printf("  a.%-12s(%s)\n", "玩家昵称", buffer->name);
    printf("  b.%-12s(%hu)\n", "生命", buffer->health);
    printf("  c.%-12s(%hu)\n", "力量", buffer->strength);
    printf("  d.%-12s(%hu)\n", "体质", buffer->constitution);
    printf("  e.%-12s(%hu)\n", "灵巧", buffer->dexterity);
    printf("  f.%-12s(%u)\n", "金钱", buffer->money);
    printf("  g.%-12s(%u)\n", "名声", buffer->fame);
    printf("  h.%-12s(%u)\n", "魅力", buffer->charm);
    printf("  i.%-12s(%lu)\n", "游戏累计时间", buffer->total_play_time);
    printf("  j.%-12s(%d)\n", "移动速度", buffer->move_speed);
    printf("  k.%-12s(%d)\n", "攻击速度", buffer->attack_speed);
    printf("  l.%-12s(%d)\n", "攻击范围", buffer->attack_range);
    printf("  m.%-12s(%hu)\n", "攻击力", buffer->attack_power);
    printf("  n.%-12s(%hu)\n", "防御力", buffer->defense);
    printf("  o.%-12s(%d)\n", "敏捷度", buffer->agility);
    printf("  p.%-12s(%d)\n", "智力", buffer->intelligence);
    printf("  q.%-12s(%d)\n", "经验", buffer->experience);
    printf("  r.%-12s(%d)\n", "等级", buffer->level);
    printf("  s.%-12s(%hu)\n", "魔法", buffer->mana);
    printf("  t.%-12s(%d)\n", "消耗魔法", buffer->mana_cost);
    printf("  u.%-12s(%d)\n", "魔法伤害力", buffer->magic_damage);
    printf("  v.%-12s(%d)\n", "命中率", buffer->accuracy);
    printf("  w.%-12s(%d)\n", "魔法防御力", buffer->magic_defense);
    printf("  x.%-12s(%d)\n", "暴击率", buffer->critical_rate);
    printf("  y.%-12s(%d)\n", "耐力", buffer->stamina);
    printf("-------------------------------------\n");
    printf(" 0.放弃修改\n");
	printf(" 1.存盘退出\n");
	printf("-------------------------------------\n");
	printf("请选择[a..y, 0..1] ");
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
	const uint64_t bound[]={-1,10000,10000,8192,1024,100000000,1000000,1000000,10000000000000000,100,100,100,2000,2000,100,100,100,100,10000,100,100,100,100,100,100}; 
	
    FILE *fp;

    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat","rb+");

	if (fp == NULL)
	{
    	fprintf(stderr, "game.dat打开失败\n");
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
				//待补充部分 
				int idx = op - 'a';
				switch(idx)
				{
					case 0:
            {
                // 修改玩家昵称
                printf("玩家昵称，当前值=%s，请输入 ：", tempdata.name);
                char newname[16];
                scanf("%s", newname);
                strncpy(tempdata.name, newname, 15);
                tempdata.name[15] = '\0';  // 确保字符串以'\0'结尾
                break;
            }
            case 1:
            {
                // 修改生命值
                while(1)
                {
                    printf("生命，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.health, bound[idx]);
                    int newhealth;
                    scanf("%d", &newhealth);
                    if(newhealth > bound[idx] || newhealth < 0)
                    {
                        printf("非法的生命值：%d\n", newhealth);
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
                // 修改力量值
                while(1)
                {
                    printf("力量，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.strength, bound[idx]);
                    int newstrength;
                    scanf("%d", &newstrength);
                    if(newstrength > bound[idx] || newstrength < 0)
                    {
                        printf("非法的力量值：%d\n", newstrength);
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
                // 修改体质
                while(1)
                {
                    printf("体质，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.constitution, bound[idx]);
                    int newconstitution;
                    scanf("%d", &newconstitution);
                    if(newconstitution > bound[idx] || newconstitution < 0)
                    {
                        printf("非法的体质值：%d\n", newconstitution);
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
                // 修改灵巧
                while(1)
                {
                    printf("灵巧，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.dexterity, bound[idx]);
                    int newdexterity;
                    scanf("%d", &newdexterity);
                    if(newdexterity > bound[idx] || newdexterity < 0)
                    {
                        printf("非法的灵巧值：%d\n", newdexterity);
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
                // 修改金钱
                while(1)
                {
                    printf("金钱，当前值=%u，范围[0..%lu]，请输入 ：", tempdata.money, bound[idx]);
                    int newmoney;
                    scanf("%d", &newmoney);
                    if(newmoney > bound[idx] || newmoney < 0)
                    {
                        printf("非法的金钱值：%d\n", newmoney);
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
                // 修改名声
                while(1)
                {
                    printf("名声，当前值=%u，范围[0..%lu]，请输入 ：", tempdata.fame, bound[idx]);
                    int newfame;
                    scanf("%d", &newfame);
                    if(newfame > bound[idx] || newfame < 0)
                    {
                        printf("非法的名声值：%d\n", newfame);
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
                // 修改魅力
                while(1)
                {
                    printf("魅力，当前值=%u，范围[0..%lu]，请输入 ：", tempdata.charm, bound[idx]);
                    int newcharm;
                    scanf("%d", &newcharm);
                    if(newcharm > bound[idx] || newcharm < 0)
                    {
                        printf("非法的魅力值：%d\n", newcharm);
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
                // 修改游戏累计时间
                while(1)
                {
                    printf("游戏累计时间，当前值=%lu，范围[0..%lu]，请输入 ：", tempdata.total_play_time, bound[idx]);
                    long long newtime;
                    scanf("%lld", &newtime);
                    if(newtime > bound[idx] || newtime < 0)
                    {
                        printf("非法的游戏累计时间：%lld\n", newtime);
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
                // 修改移动速度
                while(1)
                {
                    printf("移动速度，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.move_speed, bound[idx]);
                    int newmove_speed;
                    scanf("%d", &newmove_speed);
                    if(newmove_speed > bound[idx] || newmove_speed < 0)
                    {
                        printf("非法的移动速度值：%d\n", newmove_speed);
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
                // 修改攻击速度
                while(1)
                {
                    printf("攻击速度，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.attack_speed, bound[idx]);
                    int newattack_speed;
                    scanf("%d", &newattack_speed);
                    if(newattack_speed > bound[idx] || newattack_speed < 0)
                    {
                        printf("非法的攻击速度值：%d\n", newattack_speed);
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
                // 修改攻击范围
                while(1)
                {
                    printf("攻击范围，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.attack_range, bound[idx]);
                    int newattack_range;
                    scanf("%d", &newattack_range);
                    if(newattack_range > bound[idx] || newattack_range < 0)
                    {
                        printf("非法的攻击范围值：%d\n", newattack_range);
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
                // 修改攻击力
                while(1)
                {
                    printf("攻击力，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.attack_power, bound[idx]);
                    int newattack_power;
                    scanf("%d", &newattack_power);
                    if(newattack_power > bound[idx] || newattack_power < 0)
                    {
                        printf("非法的攻击力值：%d\n", newattack_power);
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
                // 修改防御力
                while(1)
                {
                    printf("防御力，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.defense, bound[idx]);
                    int newdefense;
                    scanf("%d", &newdefense);
                    if(newdefense > bound[idx] || newdefense < 0)
                    {
                        printf("非法的防御力值：%d\n", newdefense);
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
                // 修改敏捷度
                while(1)
                {
                    printf("敏捷度，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.agility, bound[idx]);
                    int newagility;
                    scanf("%d", &newagility);
                    if(newagility > bound[idx] || newagility < 0)
                    {
                        printf("非法的敏捷度值：%d\n", newagility);
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
                // 修改智力
                while(1)
                {
                    printf("智力，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.intelligence, bound[idx]);
                    int newintelligence;
                    scanf("%d", &newintelligence);
                    if(newintelligence > bound[idx] || newintelligence < 0)
                    {
                        printf("非法的智力值：%d\n", newintelligence);
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
                // 修改经验
                while(1)
                {
                    printf("经验，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.experience, bound[idx]);
                    int newexperience;
                    scanf("%d", &newexperience);
                    if(newexperience > bound[idx] || newexperience < 0)
                    {
                        printf("非法的经验值：%d\n", newexperience);
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
                // 修改等级
                while(1)
                {
                    printf("等级，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.level, bound[idx]);
                    int newlevel;
                    scanf("%d", &newlevel);
                    if(newlevel > bound[idx] || newlevel < 0)
                    {
                        printf("非法的等级值：%d\n", newlevel);
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
                // 修改魔法值
                while(1)
                {
                    printf("魔法值，当前值=%hu，范围[0..%lu]，请输入 ：", tempdata.mana, bound[idx]);
                    int newmana;
                    scanf("%d", &newmana);
                    if(newmana > bound[idx] || newmana < 0)
                    {
                        printf("非法的魔法值：%d\n", newmana);
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
                // 修改消耗魔法值
                while(1)
                {
                    printf("消耗魔法值，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.mana_cost, bound[idx]);
                    int newmana_cost;
                    scanf("%d", &newmana_cost);
                    if(newmana_cost > bound[idx] || newmana_cost < 0)
                    {
                        printf("非法的消耗魔法值：%d\n", newmana_cost);
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
                // 修改魔法伤害力
                while(1)
                {
                    printf("魔法伤害力，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.magic_damage, bound[idx]);
                    int newmagic_damage;
                    scanf("%d", &newmagic_damage);
                    if(newmagic_damage > bound[idx] || newmagic_damage < 0)
                    {
                        printf("非法的魔法伤害力值：%d\n", newmagic_damage);
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
                // 修改命中率
                while(1)
                {
                    printf("命中率，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.accuracy, bound[idx]);
                    int newaccuracy;
                    scanf("%d", &newaccuracy);
                    if(newaccuracy > bound[idx] || newaccuracy < 0)
                    {
                        printf("非法的命中率值：%d\n", newaccuracy);
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
                // 修改魔法防御力
                while(1)
                {
                    printf("魔法防御力，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.magic_defense, bound[idx]);
                    int newmagic_defense;
                    scanf("%d", &newmagic_defense);
                    if(newmagic_defense > bound[idx] || newmagic_defense < 0)
                    {
                        printf("非法的魔法防御力值：%d\n", newmagic_defense);
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
                // 修改暴击率
                while(1)
                {
                    printf("暴击率，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.critical_rate, bound[idx]);
                    int newcritical_rate;
                    scanf("%d", &newcritical_rate);
                    if(newcritical_rate > bound[idx] || newcritical_rate < 0)
                    {
                        printf("非法的暴击率值：%d\n", newcritical_rate);
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
                // 修改耐力
                while(1)
                {
                    printf("耐力，当前值=%d，范围[0..%lu]，请输入 ：", tempdata.stamina, bound[idx]);
                    int newstamina;
                    scanf("%d", &newstamina);
                    if(newstamina > bound[idx] || newstamina < 0)
                    {
                        printf("非法的耐力值：%d\n", newstamina);
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
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
