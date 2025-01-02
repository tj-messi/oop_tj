/* 2150792 ţ»�� �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "13-b9-linear_list_sq.h"

#define INSERT_NUM		115		//��ʼ������е�Ԫ������

#ifdef ELEMTYPE_IS_DOUBLE
    #define MAX_NUM_PER_LINE 	5		//ÿ����������Ԫ�ظ���
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    #define MAX_NUM_PER_LINE 	5		//ÿ����������Ԫ�ظ���
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    #define MAX_NUM_PER_LINE 	1		//ÿ����������Ԫ�ظ���
#else	//ȱʡ����int����
    #define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���
#endif

int line_count = 0;   //��ӡ����ʱ�ļ�����

/* ���ڱȽ�����ֵ�Ƿ���ȵľ��庯������LocateElem�еĺ���ָ�붨����ͬ������ʱ����
   int LocateElem(sqlist L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)) */
Status MyCompare(ElemType e1, ElemType e2)
{
#ifdef ELEMTYPE_IS_DOUBLE
    if (fabs(e1-e2)<1e-6)
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    if (strcmp(e1, e2)==0)
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    if (e1.num==e2.num)
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    if (e1->num==e2->num)
#else	//ȱʡ����int����
    if (e1==e2)
#endif
    	return TRUE;
    else
    	return FALSE;
}

/* ���ڷ���ĳ��Ԫ�ص�ֵ�ľ��庯������ListTraverse�еĺ���ָ�붨����ͬ������ʱ����
   Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
Status MyVisit(ElemType e)
{
#ifdef ELEMTYPE_IS_DOUBLE
    printf("%5.1f->", e);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    printf("%s->", e);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    printf("%d-%s-%c-%f-%s->", e.num, e.name, e.sex, e.score, e.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    printf("%d-%s-%c-%f-%s->", e->num, e->name, e->sex, e->score, e->addr);
#else	//ȱʡ����int����
    printf("%3d->", e);
#endif

    /* ÿ���MAX_NUM_PER_LINE������ӡһ������ */
    if ((++line_count)%MAX_NUM_PER_LINE == 0)
    	printf("\n");

    return OK;
}

int main()
{
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
    /* ����������������ҪԤ������ */
    ElemType e[]={{1001, "����", 'M', 76.5, "�Ϻ���������"},
		  {1002, "����", 'F', 87, "�Ϻ���������"},
		  {1003, "����", 'M', 80, "�㽭ʡ������"},
		  {1004, "����", 'M', 54, "�㽭ʡ������"},
		  {1005, "ţ��", 'F', 85, "����ʡ�Ͼ���"},
		  {1006, "���", 'M', 60, "����ʡ������"}};
    ElemType e_delete2[] = { {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"} };
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    /* ����������������ҪԤ������ */
    ET       e[]={{1001, "����", 'M', 76.5, "�Ϻ���������"},
		  {1002, "����", 'F', 87, "�Ϻ���������"},
		  {1003, "����", 'M', 80, "�㽭ʡ������"},
		  {1004, "����", 'M', 54, "�㽭ʡ������"},
		  {1005, "ţ��", 'F', 85, "����ʡ�Ͼ���"},
		  {1006, "���", 'M', 60, "����ʡ������"}};
    ET       e_delete2[] = { {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"},
      {1001, "����", 'M', 76.5, "�Ϻ���������"} };
#endif
    sqlist   L;
    ElemType e1, e2;
    int      i;
/* ======��ʼ��˳���====== */
    InitList(&L);

    printf("�ձ�=%s\n", (ListEmpty(L)==TRUE)?"TRUE":"FALSE");
    printf("��=%d\n\n", ListLength(L));

#ifdef ELEMTYPE_IS_DOUBLE
    printf("����%d��Ԫ�أ�\n", INSERT_NUM);
    for (i=INSERT_NUM*2; i>0; i-=2)
	ListInsert(&L, 1, (ElemType)i);	//i�����ͣ��ϸ���˵��Ҫת��Ϊdouble
#elif defined (ELEMTYPE_IS_CHAR_ARRAY)
    printf("����%d��Ԫ�أ�\n", INSERT_NUM);
    for (i=INSERT_NUM*2; i>0; i-=2) {
	sprintf(e1, "test%03d", i);
	ListInsert(&L, 1, e1);
	}
#elif defined (ELEMTYPE_IS_CHAR_P)
    printf("����%d��Ԫ�أ�\n", INSERT_NUM);
    e1 = (ElemType)malloc(80*sizeof(char));	//e1ʵ����ָ�룬������������Ӧ�Ŀռ�
    e2 = (ElemType)malloc(80*sizeof(char));	//e2ʵ����ָ�룬������������Ӧ�Ŀռ�
    for (i=INSERT_NUM*2; i>0; i-=2) {
	sprintf(e1, "test%03d", i);
	ListInsert(&L, 1, e1);
	}
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    printf("����6��Ԫ�أ�\n");
    for (i=0; i<6; i++)
	ListInsert(&L, ListLength(L)+1, *(e+i));
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    printf("����6��Ԫ�أ�\n");
    e1 = (ElemType)malloc(sizeof(ET));
    e2 = (ElemType)malloc(sizeof(ET));

    printf("����6��Ԫ�أ�\n");
    for (i=0; i<6; i++)
	ListInsert(&L, ListLength(L)+1, (e+i));
#else	//ȱʡ����int����
    printf("����%d��Ԫ�أ�\n", INSERT_NUM);
    for (i=INSERT_NUM*2; i>0; i-=2)
	ListInsert(&L, 1, i);
#endif

    ListTraverse(L, MyVisit);//�˴�����MyVisit������

    printf("�ձ�=%s\n", (ListEmpty(L)==TRUE)?"TRUE":"FALSE");
    printf("��=%d\n\n", ListLength(L));

    /*======����Priorelem��Nextelem======*/
    /* �ֱ�ȡ��1������Լ�С�ڵ�1����������4������µĵ�Ԫ��ֵ��ǰ��ֵ�����ֵ
     ����ټ�һ����������ֵ */
    printf("\n����Priorelem��Nextelem\n");
    for (i = 0; i < 5; i++) {
        int pos;
        switch (i) {
            case 0:
                pos = 1;
                break;
            case 1:
                pos = ListLength(L);
                break;
            case 2:
                pos = -1;
                break;
            case 3:
                pos = ListLength(L) + 1;
                break;
            case 4:
                printf("������ҪȡԪ�ص�λ��[1..%d]��", ListLength(L));
                scanf("%d", &pos);
                break;
}

        /* ȡ��1��Ԫ���Լ�ǰ������� */
        if (GetElem(L, pos, &e1) == OK) {
#ifdef ELEMTYPE_IS_DOUBLE
            printf("��%d��Ԫ��=%5.lf\n", pos, e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
            printf("��%d��Ԫ��=%s\n", pos, e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
            printf("��%d��Ԫ��=\"%d.%s.%c.%f.%s\"\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
            printf("��%d��Ԫ��=\"%d.%s.%c.%f.%s\"\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
            printf("��%d��Ԫ��=%d\n", pos, e1);
#endif

            /* ֻ��ȡ����ĳ��Ԫ�أ�����ȡǰ���ͺ�� */
            if (PriorElem(L, e1, &e2, MyCompare) == OK)
#ifdef ELEMTYPE_IS_DOUBLE
                printf("��%d��Ԫ��(%5.1f)��ǰ��=%5.1f\n", pos, e1, e2);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
                printf("��%d��Ԫ��(%s)��ǰ��=%s\n", pos, e1, e2);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
                printf("��%d��Ԫ��\"%d.%s.%c.%f.%s\"��ǰ��=\"%d.%s.%c.%f.%s\"\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr, e2.num, e2.name, e2.sex, e2.score, e2.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
                printf("��%d��Ԫ��\"%d.%s.%c.%f.%s\"��ǰ��=\"%d.%s.%c.%f.%s\"\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr, e2->num, e2->name, e2->sex, e2->score, e2->addr);
#else	//ȱʡ����int����
                printf("��%d��Ԫ��(%d)��ǰ��=%d\n", pos, e1, e2);
#endif
            else
#ifdef ELEMTYPE_IS_DOUBLE
                printf("�޷�ȡ�õ�%d��Ԫ��(%5.1f)��ǰ��\n", pos, e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
                printf("�޷�ȡ�õ�%d��Ԫ��(%s)��ǰ��\n", pos, e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
                printf("�޷�ȡ�õ�%d��Ԫ��\"%d.%s.%c.%f.%s\"��ǰ��\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
                printf("�޷�ȡ�õ�%d��Ԫ��\"%d.%s.%c.%f.%s\"��ǰ��\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
                printf("�޷�ȡ�õ�%d��Ԫ��(%d)��ǰ��\n", pos, e1);
#endif

            if (NextElem(L, e1, &e2, MyCompare) == OK)
#ifdef ELEMTYPE_IS_DOUBLE
                printf("��%d��Ԫ��(%5.1f)�ĺ��=%5.1f\n", pos, e1, e2);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
                printf("��%d��Ԫ��(%s)�ĺ��=%s\n", pos, e1, e2);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
                printf("��%d��Ԫ��\"%d.%s.%c.%f.%s\"�ĺ��=\"%d.%s.%c.%f.%s\"\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr, e2.num, e2.name, e2.sex, e2.score, e2.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
                printf("��%d��Ԫ��\"%d.%s.%c.%f.%s\"�ĺ��=\"%d.%s.%c.%f.%s\"\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr, e2->num, e2->name, e2->sex, e2->score, e2->addr);
#else	//ȱʡ����int����
                printf("��%d��Ԫ��(%d)�ĺ��=%d\n", pos, e1, e2);
#endif
            else
#ifdef ELEMTYPE_IS_DOUBLE
                printf("�޷�ȡ�õ�%d��Ԫ��(%5.1f)�ĺ��\n", pos, e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
                printf("�޷�ȡ�õ�%d��Ԫ��(%s)�ĺ��\n", pos, e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
                printf("�޷�ȡ�õ�%d��Ԫ��\"%d.%s.%c.%f.%s\"�ĺ��\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
                printf("�޷�ȡ�õ�%d��Ԫ��\"%d.%s.%c.%f.%s\"�ĺ��\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
                printf("�޷�ȡ�õ�%d��Ԫ��(%d)�ĺ��\n", pos, e1);
#endif
        }
        else
            printf("�޷�ȡ�õ�%d��Ԫ��\n\n", pos);
        } // end of for

/* ======����ListInsert1����====== */
    printf("\n����ListInsert1������ʼ\n");
#ifdef ELEMTYPE_IS_DOUBLE
    printf("\n������Ҫ����Ԫ�ص�ֵ��\n");
    scanf("%lf", &e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    printf("\n������Ҫ����Ԫ�ص�ֵ��\n");
    scanf("%s", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    printf("\n������Ҫ����Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
    scanf("%d %s %c %f %s", &e1.num, e1.name, &e1.sex, &e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    printf("\n������Ҫ����Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
    scanf("%d %s %c %f %s", &e1->num, e1->name, &e1->sex, &e1->score, e1->addr);
#else	//ȱʡ����int����
    printf("\n������Ҫ����Ԫ�ص�ֵ��\n");
    scanf("%d", &e1);
#endif

#ifdef ELEMTYPE_IS_DOUBLE
    printf("\n������Ҫ����Ԫ�غ�һ��Ԫ�ص�ֵ��\n");
    scanf("%lf", &e2);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    printf("\n������Ҫ����Ԫ�غ�һ��Ԫ�ص�ֵ��\n");
    scanf("%s", e2);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    printf("\n������Ҫ����Ԫ�غ�һ��Ԫ�ص�ֵ��(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
    scanf("%d %s %c %f %s", &e2.num, e2.name, &e2.sex, &e2.score, e2.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    printf("\n������Ҫ����Ԫ�غ�һ��Ԫ�ص�ֵ��(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
    scanf("%d %s %c %f %s", &e2->num, e2->name, &e2->sex, &e2->score, e2->addr);
#else	//ȱʡ����int����
    printf("\n������Ҫ����Ԫ�غ�һ��Ԫ�ص�ֵ��\n");
    scanf("%d", &e2);
#endif

    if (ListInsert1(&L, e2, e1, MyCompare) == OK) {
#ifdef ELEMTYPE_IS_DOUBLE
        printf("����Ԫ��=%5.1f�ɹ�\n", e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
        printf("����Ԫ��=%s�ɹ�\n", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        printf("����Ԫ��=\"%d.%s.%c.%f.%s\"�ɹ�\n", e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
        printf("����Ԫ��=\"%d.%s.%c.%f.%s\"�ɹ�\n", e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
        printf("����Ԫ��=%d�ɹ�\n", e1);
#endif
        printf("�±�Ϊ��\n");
        ListTraverse(L, MyVisit);
    }
    else
#ifdef ELEMTYPE_IS_DOUBLE
        printf("����Ԫ��=%5.1fʧ��\n", e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
        printf("����Ԫ��=%sʧ��\n", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        printf("����Ԫ��=\"%d.%s.%c.%f.%s\"ʧ��\n", e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
        printf("����Ԫ��=\"%d.%s.%c.%f.%s\"ʧ��\n", e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
    	printf("����Ԫ��%dʧ��\n", e1);
#endif
    printf("\n����ListInsert1��������\n");

/* ======����ListDelete1����====== */
    printf("\n����ListDelete1������ʼ\n");

#ifdef ELEMTYPE_IS_DOUBLE
    printf("\n������Ҫɾ��Ԫ�ص�ֵ��\n");
    scanf("%lf", &e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    printf("\n������Ҫɾ��Ԫ�ص�ֵ��\n");
    scanf("%s", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    printf("\n������Ҫɾ��Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
    scanf("%d %s %c %f %s", &e1.num, e1.name, &e1.sex, &e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    printf("\n������Ҫɾ��Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
    scanf("%d %s %c %f %s", &e1->num, e1->name, &e1->sex, &e1->score, e1->addr);
#else	//ȱʡ����int����
    printf("\n������Ҫɾ��Ԫ�ص�ֵ��\n");
    scanf("%d", &e1);
#endif

    if (ListDelete1(&L, e1, MyCompare) == OK) {
#ifdef ELEMTYPE_IS_DOUBLE
        printf("ɾ��Ԫ��=%5.1f�ɹ�\n", e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
        printf("ɾ��Ԫ��=%s�ɹ�\n", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"�ɹ�\n", e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"�ɹ�\n", e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
        printf("ɾ��Ԫ��=%d�ɹ�\n", e1);
#endif
        printf("�±�Ϊ��\n");
        ListTraverse(L, MyVisit);
    }
    else
#ifdef ELEMTYPE_IS_DOUBLE
        printf("ɾ��Ԫ��=%5.1fʧ��\n", e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
        printf("ɾ��Ԫ��=%sʧ��\n", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"ʧ��\n", e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"ʧ��\n", e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
        printf("ɾ��Ԫ��=%dʧ��\n", e1);
#endif
    printf("\n����ListDelete1��������\n");

    printf("\n�Ȳ���6����ͬԪ�����ڲ���ListDelete2\n");
    while (1)
    {
        if (getchar() == '\n')
            break;
    }
#ifdef ELEMTYPE_IS_DOUBLE
    for (i = 0; i < 6; i++)
        ListInsert(&L, 1, 2.0);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY)
    for (i = 0; i < 6; i++) {
        sprintf(e1, "test%03d", 2);
        ListInsert(&L, 1, e1);
    }
#elif defined (ELEMTYPE_IS_CHAR_P)
    e1 = (ElemType)malloc(80 * sizeof(char));	//e1ʵ����ָ�룬������������Ӧ�Ŀռ�
    e2 = (ElemType)malloc(80 * sizeof(char));	//e2ʵ����ָ�룬������������Ӧ�Ŀռ�
    for (i = 0; i < 6; i++) {
        sprintf(e1, "test%03d", 2);
        ListInsert(&L, 1, e1);
    }
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    for (i = 0; i < 6; i++)
        ListInsert(&L, ListLength(L) + 1, *(e_delete2 + i));
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    e1 = (ElemType)malloc(sizeof(ET));
    e2 = (ElemType)malloc(sizeof(ET));

    for (i = 0; i < 6; i++)
        ListInsert(&L, ListLength(L) + 1, (e_delete2 + i));
#else	//ȱʡ����int����
    for (i = 0; i < 6; i++)
        ListInsert(&L, 1, 2);
#endif

    printf("�����ı�Ϊ��\n");
    ListTraverse(L, MyVisit);
    printf("�ձ�=%s\n", (ListEmpty(L) == TRUE) ? "TRUE" : "FALSE");
    printf("��=%d\n", ListLength(L));

#ifdef ELEMTYPE_IS_DOUBLE
    e1 = 2.0;
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    strcpy(e1, "test002");
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    e1.num = 1001, e1.sex = 'M', e1.score = 76.5;
    strcpy(e1.addr, "�Ϻ���������");
    strcpy(e1.name, "����");
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    e1->num = 1001, e1->sex = 'M', e1->score = 76.5;
    strcpy(e1->addr, "�Ϻ���������");
    strcpy(e1->name, "����");
#else	//ȱʡ����int����
    e1 = 2;
#endif

    printf("\n���س���ɾ�����кͲ���������ͬ����������\n");
    while (1)
    {
        if (getchar() == '\n')
            break;
    }
    if (ListDelete2(&L, e1, MyCompare) == OK) {
#ifdef ELEMTYPE_IS_DOUBLE
        printf("ɾ��Ԫ��=%5.1f�ɹ�\n", e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
        printf("ɾ��Ԫ��=%s�ɹ�\n", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"�ɹ�\n", e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"�ɹ�\n", e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
        printf("ɾ��Ԫ��=%d�ɹ�\n", e1);
#endif
        printf("ִ��ListDelete2�������±�Ϊ��\n");
        ListTraverse(L, MyVisit);
        printf("�ձ�=%s\n", (ListEmpty(L) == TRUE) ? "TRUE" : "FALSE");
        printf("��=%d\n", ListLength(L));
    }
    else
#ifdef ELEMTYPE_IS_DOUBLE
        printf("ɾ��Ԫ��=%5.1fʧ��\n", e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
        printf("ɾ��Ԫ��=%sʧ��\n", e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"ʧ��\n", e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
        printf("ɾ��Ԫ��=\"%d.%s.%c.%f.%s\"ʧ��\n", e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//ȱʡ����int����
        printf("ɾ��Ԫ��=%dʧ��\n", e1);
#endif
    printf("\n����ListDelete2����\n");

    printf("\n����ClearList1������ʼ�����س�������\n");
    while (1)
    {
        if (getchar() == '\n')
            break;
    }
    printf("\n��ձ�\n");
    ClearList1(&L);
    printf("�ձ�=%s\n", (ListEmpty(L)==TRUE)?"TRUE":"FALSE");
    printf("��=%d\n", ListLength(L));
    printf("������С=%d\n", L.listsize);

    printf("\n����ClearList1��������\n");


    DestroyList(&L);

    return 0;
}
