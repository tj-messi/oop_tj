/* 计科 2150792 牛禄阳 */
#pragma once
/* =====================90-02-b1的菜单提示信息===================== */
const char* const menu_infor_90_02_b1[] = {
    "1.画出内部数组框架",
	"2.内部数组，仅在中部随机显示一个数",
	"3.内部数组，自动下落，支持按键操作，完成一次下落",
	"4.内部数组，自动下落，支持按键操作，完整版游戏",
	"5.画出cmd界面框架",
	"6.cmd界面，仅在中部随机显示一个数字",
	"7.cmd界面，自动下落，支持按键操作，完成一次下落",
	"8.cmd界面，自动下落，支持按键操作，完整版游戏",
	"0.退出"
};
const char total_choice_90_02_b1[] = { '1','2','3','4','5','6','7','8','0' };
/*
另一种实现方法：
const char* total_choice_90_02_b1 = "1234567";
在字符串中进行选择，可以通过字符串选择函数实现超过两位数的选择，而我的实现方式无法做到两位数的选择
*/
const int  infor_num_90_02_b1 = 9;
const char* const game_oper_infor_90_02_b1[] = {
    "游戏操作: ↑ 逆时针旋转90度; ↓ 立即下落一格;",
    "          ← 向左移动; → 向右移动;",
    "          space(空格) 快速下落到底(忽视下落过程中的任何操作);",
    "          A/a 暂停[再次点击继续]; Q/q 结束游戏;"
};
const char* const game_exec_infor_90_02_b1[] = {
    "下一个下落的数字: ",
    "游戏得分: ",
    "下落速度: ",
    "已消除行数: "
};

/* =====================90-02-b1的常变量定义===================== */
const int  TETROMINO_ROW = 5;
const int  TETROMINO_COL = 5;                 //考虑旋转方块，将方块设置为5X5的区域
const int  TETROMINO_TYPE = 10;
const int  OFFSET_ROW = TETROMINO_ROW / 2;    //遍历数组时的偏移量
const int  OFFSET_COL = TETROMINO_ROW / 2;
const int  OFFSET_GAMEARRAY = 2;              //因为gamearray行和列个增加4而产生的数组实际访问偏移量
const int  FRAME_LENGTH = 2;                  //外边框的宽度（即"║"的宽度）
const int  LENGTH_BASE_TITLE = 36;            //数组显示形式下，游戏的标题长度
const int  MAX_GAMEAREA_ROW = 30;
const int  MAX_GAMEAREA_COL = 25;             //最大游戏区域为高26行，宽21列,为了确保边界位置的旋转，各增加4
const int  BASE_OPER_INFOR_X = 45;            //数组形式操作提示信息在cmd界面的坐标X值
const int  BASE_OPER_INFOR_Y = 1;             //数组形式操作提示信息在cmd界面的坐标Y值
const int  BASE_EXEC_INFOR_Y = 10;            //数组形式游戏执行信息在cmd界面的坐标Y值
const int  LENGTH_BASE_OPER_INFOR = 70;       //数组形式操作提示信息在cmd界面的长度
const int  LENGTH_BASE_GAME_INFOR = 58;       //数组形式游戏执行信息在cmd界面的长度
const int  CONSOLE_OPER_INFOR_X = 135;        //console形式操作提示信息在cmd界面的坐标X值
const int  CONSOLE_GAME_INFOR_Y = 35;         //console形式游戏提示信息在cmd界面的坐标Y值
/* 定义初始状态的数字形状数组，没有用到的区域值为 - 2，用到但没有数字覆盖的区域为 - 1，其余区域为数字值 */
const int TETROMINONUMBER[TETROMINO_TYPE][TETROMINO_ROW][TETROMINO_COL] =
{
    {
        {-2,  0,  0,  0, -2},
        {-2,  0, -1,  0, -2},
        {-2,  0, -1,  0, -2},
        {-2,  0, -1,  0, -2},
        {-2,  0,  0,  0, -2}
    },
    {
        {-2, -1, 1, -1, -2},
        {-2, -1, 1, -1, -2},
        {-2, -1, 1, -1, -2},
        {-2, -1, 1, -1, -2},
        {-2, -1, 1, -1, -2}
    },
    {
        {-2,  2,  2,  2, -2},
        {-2, -1, -1,  2, -2},
        {-2,  2,  2,  2, -2},
        {-2,  2, -1, -1, -2},
        {-2,  2,  2,  2, -2}
    },
    {
        {-2,  3,  3,  3, -2},
        {-2, -1, -1,  3, -2},
        {-2,  3,  3,  3, -2},
        {-2, -1, -1,  3, -2},
        {-2,  3,  3,  3, -2}
    },
    {
        {-2,  4, -1,  4, -2},
        {-2,  4, -1,  4, -2},
        {-2,  4,  4,  4, -2},
        {-2, -1, -1,  4, -2},
        {-2, -1, -1,  4, -2}
    },
    {
        {-2,  5,  5,  5, -2},
        {-2,  5, -1, -1, -2},
        {-2,  5,  5,  5, -2},
        {-2, -1, -1,  5, -2},
        {-2,  5,  5,  5, -2}
    },
    {
        {-2,  6,  6,  6, -2},
        {-2,  6, -1, -1, -2},
        {-2,  6,  6,  6, -2},
        {-2,  6, -1,  6, -2},
        {-2,  6,  6,  6, -2}
    },
    {
        {-2,  7,  7,  7, -2},
        {-2, -1, -1,  7, -2},
        {-2, -1, -1,  7, -2},
        {-2, -1, -1,  7, -2},
        {-2, -1, -1,  7, -2}
    },
    {
        {-2,  8,  8,  8, -2},
        {-2,  8, -1,  8, -2},
        {-2,  8,  8,  8, -2},
        {-2,  8, -1,  8, -2},
        {-2,  8,  8,  8, -2}
    },
    {
        {-2,  9,  9,  9, -2},
        {-2,  9, -1,  9, -2},
        {-2,  9,  9,  9, -2},
        {-2, -1, -1,  9, -2},
        {-2,  9,  9,  9, -2}
    }
};

/* =====================90-02-b1的结构体和枚举定义===================== */
struct Tetromino {
    int row, col;                           //记录5X5数组中心点的行数和列数(对于游戏区域而言)
    int number;                             //数字方块的值
    int shape[TETROMINO_ROW][TETROMINO_COL];//每个数字方块为五行五列的数组
};
struct Gamearea {
    bool gameover;                          //游戏是否结束
    int  gamerow, gamecol;                  //实际游戏区域的行数、列数。初始化后不修改！
    int  gamey, gamex;                      //实际游戏区域的左上角对应的cmd界面内的x和y坐标。初始化后不修改！
    int  gamesocre;                         //游戏得分
    int  elimlinenum;                       //已经消除的行数
    double dropspeed;                       //方块的下落速度。以上三个成员在消除函数中修改！
    int  gamearray[MAX_GAMEAREA_ROW][MAX_GAMEAREA_COL];  //游戏区域数组。
    Tetromino currnetTetromino;             //当前游戏下落的方块
    Tetromino nextTetromino;                //下一个方块
};
enum class GameAction {
    EXIT = 0,       //Q/q，游戏结束
    ROTATE,         //上箭头，旋转
    DROP_NORMAL,    //下箭头，立即执行一次下落
    DROP_FAST,      //空格，快速下落
    MOVE_LEFT,      //左箭头，左移
    MOVE_RIGHT,     //右箭头，右移
    STOP,           //空格，游戏暂停。仅定义，其实没有用到此枚举类型。
    NONE            //自然下落
};

/* =====================90-02-b1-tools的函数声明===================== */
GameAction get_keyboard_in();
int execute_game_process(Gamearea& gameboard, int choice);
void process_cannot_move(Gamearea& gameboard, int choice);
void print_gamearray(Gamearea& gameboard, int choice);
void input_gamearea(int& M, int& N);
int  elim_gamearea(Gamearea& gameboard);
void inc_score_speed_elimnum(Gamearea& gameboard, int cnt_elimlinenum);
int  move_tetromino_ccw90degrees(Gamearea& gameboard, Tetromino& temp_tetromino);
int  move_tetromino_left_right(Gamearea& gameboard, int choice);
int  move_tetromino_normaldrop(Gamearea gameboard);
int  check_gameover(Gamearea gameboard);
int  check_gameaction_legality(Gamearea gameboard, Tetromino temp_tetromino);
int  get_next_num(const bool new_seed = false, const unsigned int seed = 0);
void initial_tetromino(Gamearea& gameboard, int choice);
void initial_gamearray(Gamearea& gameboard);

/* =====================90-02-b1-base的函数声明===================== */
int fun1();
int fun2();
int fun3();
void print_erase_base_number(Gamearea gameboard, int choice);
void print_base_operation_infor(int cmdx, int cmdy);
void print_base_game_exec_infor(int cmdx, int cmdy, Gamearea gameboard);
void print_base_frame(int gamerow, int gamecol, int& cmdx, int& cmdy);
void move_tetromino_fastdrop(Gamearea& gameboard, int choice);

/* =====================90-02-b1-console的函数声明===================== */
int fun4();
int fun5();
int fun6();
int fun7();
int fun8();
void print_console_oper_infor();
void print_console_game_infor(Gamearea gameboard);
void print_console_next_number_frame(Gamearea gameboard);
void print_erase_console_number(Gamearea gameboard, int choice);
void print_console_frame(int gamerow, int gamecol);