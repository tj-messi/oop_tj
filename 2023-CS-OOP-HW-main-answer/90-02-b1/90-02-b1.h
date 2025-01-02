/* �ƿ� 2150792 ţ»�� */
#pragma once
/* =====================90-02-b1�Ĳ˵���ʾ��Ϣ===================== */
const char* const menu_infor_90_02_b1[] = {
    "1.�����ڲ�������",
	"2.�ڲ����飬�����в������ʾһ����",
	"3.�ڲ����飬�Զ����䣬֧�ְ������������һ������",
	"4.�ڲ����飬�Զ����䣬֧�ְ�����������������Ϸ",
	"5.����cmd������",
	"6.cmd���棬�����в������ʾһ������",
	"7.cmd���棬�Զ����䣬֧�ְ������������һ������",
	"8.cmd���棬�Զ����䣬֧�ְ�����������������Ϸ",
	"0.�˳�"
};
const char total_choice_90_02_b1[] = { '1','2','3','4','5','6','7','8','0' };
/*
��һ��ʵ�ַ�����
const char* total_choice_90_02_b1 = "1234567";
���ַ����н���ѡ�񣬿���ͨ���ַ���ѡ����ʵ�ֳ�����λ����ѡ�񣬶��ҵ�ʵ�ַ�ʽ�޷�������λ����ѡ��
*/
const int  infor_num_90_02_b1 = 9;
const char* const game_oper_infor_90_02_b1[] = {
    "��Ϸ����: �� ��ʱ����ת90��; �� ��������һ��;",
    "          �� �����ƶ�; �� �����ƶ�;",
    "          space(�ո�) �������䵽��(������������е��κβ���);",
    "          A/a ��ͣ[�ٴε������]; Q/q ������Ϸ;"
};
const char* const game_exec_infor_90_02_b1[] = {
    "��һ�����������: ",
    "��Ϸ�÷�: ",
    "�����ٶ�: ",
    "����������: "
};

/* =====================90-02-b1�ĳ���������===================== */
const int  TETROMINO_ROW = 5;
const int  TETROMINO_COL = 5;                 //������ת���飬����������Ϊ5X5������
const int  TETROMINO_TYPE = 10;
const int  OFFSET_ROW = TETROMINO_ROW / 2;    //��������ʱ��ƫ����
const int  OFFSET_COL = TETROMINO_ROW / 2;
const int  OFFSET_GAMEARRAY = 2;              //��Ϊgamearray�к��и�����4������������ʵ�ʷ���ƫ����
const int  FRAME_LENGTH = 2;                  //��߿�Ŀ�ȣ���"�U"�Ŀ�ȣ�
const int  LENGTH_BASE_TITLE = 36;            //������ʾ��ʽ�£���Ϸ�ı��ⳤ��
const int  MAX_GAMEAREA_ROW = 30;
const int  MAX_GAMEAREA_COL = 25;             //�����Ϸ����Ϊ��26�У���21��,Ϊ��ȷ���߽�λ�õ���ת��������4
const int  BASE_OPER_INFOR_X = 45;            //������ʽ������ʾ��Ϣ��cmd���������Xֵ
const int  BASE_OPER_INFOR_Y = 1;             //������ʽ������ʾ��Ϣ��cmd���������Yֵ
const int  BASE_EXEC_INFOR_Y = 10;            //������ʽ��Ϸִ����Ϣ��cmd���������Yֵ
const int  LENGTH_BASE_OPER_INFOR = 70;       //������ʽ������ʾ��Ϣ��cmd����ĳ���
const int  LENGTH_BASE_GAME_INFOR = 58;       //������ʽ��Ϸִ����Ϣ��cmd����ĳ���
const int  CONSOLE_OPER_INFOR_X = 135;        //console��ʽ������ʾ��Ϣ��cmd���������Xֵ
const int  CONSOLE_GAME_INFOR_Y = 35;         //console��ʽ��Ϸ��ʾ��Ϣ��cmd���������Yֵ
/* �����ʼ״̬��������״���飬û���õ�������ֵΪ - 2���õ���û�����ָ��ǵ�����Ϊ - 1����������Ϊ����ֵ */
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

/* =====================90-02-b1�Ľṹ���ö�ٶ���===================== */
struct Tetromino {
    int row, col;                           //��¼5X5�������ĵ������������(������Ϸ�������)
    int number;                             //���ַ����ֵ
    int shape[TETROMINO_ROW][TETROMINO_COL];//ÿ�����ַ���Ϊ�������е�����
};
struct Gamearea {
    bool gameover;                          //��Ϸ�Ƿ����
    int  gamerow, gamecol;                  //ʵ����Ϸ�������������������ʼ�����޸ģ�
    int  gamey, gamex;                      //ʵ����Ϸ��������ϽǶ�Ӧ��cmd�����ڵ�x��y���ꡣ��ʼ�����޸ģ�
    int  gamesocre;                         //��Ϸ�÷�
    int  elimlinenum;                       //�Ѿ�����������
    double dropspeed;                       //����������ٶȡ�����������Ա�������������޸ģ�
    int  gamearray[MAX_GAMEAREA_ROW][MAX_GAMEAREA_COL];  //��Ϸ�������顣
    Tetromino currnetTetromino;             //��ǰ��Ϸ����ķ���
    Tetromino nextTetromino;                //��һ������
};
enum class GameAction {
    EXIT = 0,       //Q/q����Ϸ����
    ROTATE,         //�ϼ�ͷ����ת
    DROP_NORMAL,    //�¼�ͷ������ִ��һ������
    DROP_FAST,      //�ո񣬿�������
    MOVE_LEFT,      //���ͷ������
    MOVE_RIGHT,     //�Ҽ�ͷ������
    STOP,           //�ո���Ϸ��ͣ�������壬��ʵû���õ���ö�����͡�
    NONE            //��Ȼ����
};

/* =====================90-02-b1-tools�ĺ�������===================== */
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

/* =====================90-02-b1-base�ĺ�������===================== */
int fun1();
int fun2();
int fun3();
void print_erase_base_number(Gamearea gameboard, int choice);
void print_base_operation_infor(int cmdx, int cmdy);
void print_base_game_exec_infor(int cmdx, int cmdy, Gamearea gameboard);
void print_base_frame(int gamerow, int gamecol, int& cmdx, int& cmdy);
void move_tetromino_fastdrop(Gamearea& gameboard, int choice);

/* =====================90-02-b1-console�ĺ�������===================== */
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