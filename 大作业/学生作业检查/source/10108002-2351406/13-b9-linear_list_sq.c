#include "13-b9-linear_list_sq.h"

// 清空线性表并恢复到初始空间
Status ClearList1(sqlist *L) {
    if (L == NULL) return -1;
