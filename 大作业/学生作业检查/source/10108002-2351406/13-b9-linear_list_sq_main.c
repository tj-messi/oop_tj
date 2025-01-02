#include "13-b9-linear_list_sq.h"

// 比较函数，用于判断两个元素是否相等
Status compare(ElemType e1, ElemType e2) {
    return (e1 == e2) ? 0 : -1; // 如果相等返回0，不相等返回-1
