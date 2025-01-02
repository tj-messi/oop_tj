#include <stdio.h>
#include <math.h>

double definite_integration(double (*func)(double), double low, double high, int n) {
    double delta = (high - low) / n;
