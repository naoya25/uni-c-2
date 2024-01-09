#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func1(double x)
{
    return 2 / (x * x);
}
double func2(double x)
{
    return 4 / (1 + x * x);
}

double romberg(double a, double b, int N, double eps, double (*f)(double))
{
    double S, h, t[N], f0, f1;
    int j, k, m, n;
    h = b - a;
    f0 = (*f)(a);
    f1 = (*f)(b);
    t[0] = h * (f0 + f1) / 2;

    for (n = 1; n <= N; n++)
    {
        h /= 2;
        S = 0;
        for (j = 1; j <= (int)(pow(2, n) - 1); j++)
        {
            S += (*f)(a + j * h);
        }
        t[n] = h * (f0 + 2 * S + f1) / 2;
        if (fabs(t[n] - t[n - 1]) < eps)
            return t[n];
        k = n;
        for (m = 1; m <= n; m++)
        {
            k = k - 1;
            t[k] = (pow(4, m) * t[k + 1] - t[k]) / (pow(4, m) - 1);
            if (k >= 1 && fabs(t[k] - t[k - 1]) < eps)
                return t[k];
        }
    }

    return t[N];
}

int main(void)
{
    int N = 6;
    double eps = pow(10, -10);
    printf("2/(x*x)を[1,2]で積分します。最大反復回数は%dです。\n", N);
    printf("結果は%20.15f です\n", romberg(1, 2, N, eps, func1));
    printf("4/(1+x*x)を[O,1]で横分します。最大反復回数は%dです\n", N);
    printf("結果は%20.15fです\n", romberg(0, 1, N, eps, func2));
    return 0;
}
