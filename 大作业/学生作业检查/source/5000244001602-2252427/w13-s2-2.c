#include <stdio.h>
#include <string.h>

void rotateString(const char* src, char* dest, int n, int m) {
    m = m % n;  // ·ÀÖ¹ m ³¬¹ý×Ö·û´®³¤¶È
