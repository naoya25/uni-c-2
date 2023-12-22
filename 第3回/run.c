#include <stdio.h>
#include <math.h>

double func1(double x)
{
    return 2 / (x * x);
}

double func2(double x)
{
    return 4 / (1 + x * x);
}

double trapezoidal(double a, double b, int n, double (*f)(double))
{
    double h = (b - a) / n;
    double T = ((*f)(a) + (*f)(b)) / 2.0;

    for (int i = 1; i < n; i++)
    {
        T += (*f)(a + i * h);
    }

    T *= h;
    return T;
}

double simpson(double a, double b, int n, double (*f)(double))
{
    double h = (b - a) / (2 * n);
    double S = (*f)(a) + (*f)(b);

    for (int i = 1; i < n; i++)
    {
        S += 4 * (*f)(a + (2 * i - 1) * h) + 2 * (*f)(a + 2 * i * h);
    }
    S += 4 * (*f)(a + (2 * n - 1) * h);
    S *= h / 3;
    return S;
}

int main()
{
    int nums[] = {10, 100, 1000, 10000};
    for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++)
    {
        int n = nums[i];

        double tr_result1 = trapezoidal(1, 2, n, func1);
        double tr_result2 = trapezoidal(0, 1, n, func2);
        double si_result1 = simpson(1, 2, n, func1);
        double si_result2 = simpson(0, 1, n, func2);

        printf("分割数: %d\n", n);

        printf("台形公式\n");
        printf("func1[1,2]: %20.15f\n", tr_result1);
        printf("func2[0,1]: %20.15f\n", tr_result2);

        printf("シンプソン公式\n");
        printf("func1[1,2]: %20.15f\n", si_result1);
        printf("func2[0,1]: %20.15f\n", si_result2);

        printf("台形公式とシンプソン公式の誤差\n");
        printf("func1: %20.15f\n", tr_result1 - si_result1);
        printf("func2: %20.15f\n", tr_result2 - si_result2);

        printf("実際の積分値との誤差\n");
        printf("台形公式\n");
        printf("func1: %20.15f\n", 1 - tr_result1);
        printf("func2: %20.15f\n", M_PI - tr_result2);
        printf("シンプソン公式\n");
        printf("func1: %20.15f\n", 1 - si_result1);
        printf("func2: %20.15f\n", M_PI - si_result2);
    }

    return 0;
}
