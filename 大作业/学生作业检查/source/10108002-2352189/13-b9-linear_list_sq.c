#include "13-b9-linear_list_sq.h"

Status InitList(sqlist* L) {
    L->data = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
    if (!L->data) {
