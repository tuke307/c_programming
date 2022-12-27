#include <math.h>

const double h = 10e-8;

double f(double x) {
    return pow(x - 3, 2);
}

double df(double x) {
    return 2*(x - 3);
}

double df_approx(double x) {
    return (f(x + h) - f(x)) / h;
}