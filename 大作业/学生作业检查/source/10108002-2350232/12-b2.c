#include <stdio.h>
#include <math.h>

double definite_integration(double (*func)(double), double low, double high, int n) {
    double width = (high - low) / n;
