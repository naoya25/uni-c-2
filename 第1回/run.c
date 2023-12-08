#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 6
#define N 3

double P[N + 1][N + 1];
double A[N + 1];

void input_vector2(double *b, char c, int n, FILE *fin, FILE *fout);
void gauss2(double a[N + 1][N + 1], double b[N + 1]);
void least_square(double *x, double *y, FILE *fout);

int main(void)
{
    FILE *fin, *fout;
    double x[M];
    double y[M];

    if ((fin = fopen("input_func.dat", "r")) == NULL)
    {
        printf("ファイルが見つかりません: input_func.dat \n");
        exit(1);
    }
    if ((fout = fopen("output_func.dat", "w")) == NULL)
    {
        printf("ファイルが作成できません： output_func.dat\n");
        exit(1);
    }

    input_vector2(x, 'x', M, fin, fout);
    input_vector2(y, 'y', M, fin, fout);
    least_square(x, y, fout);
    fclose(fin);
    fclose(fout);
    printf("計算終了\n");

    return 0;
}

void least_square(double *x, double *y, FILE *fout)
{
    int i, j, k;

    for (i = 0; i <= N; i++)
    {
        A[i] = 0.0;
        for (j = 0; j <= M - 1; j++)
        {
            A[i] += y[j] * pow(x[j], (double)(i));
        }
    }
    for (i = 0; i <= N; i++)
    {
        for (j = 0; j <= i; j++)
        {
            P[i][j] = 0.0;
            for (k = 0; k <= M - 1; k++)
            {
                P[i][j] += pow(x[k], (double)(i + j));
                P[j][i] = P[i][j];
            }
        }
    }

    gauss2(P, A);

    fprintf(fout, "最小2乗近似式はy=\n");
    for (i = N; i >= 0; i--)
    {
        fprintf(fout, "+ %5.2f x^%d", A[i], i);
    }
    fprintf(fout, "\n");
}

void input_vector2(double *b, char c, int n, FILE *fin, FILE *fout)
{
    int i;
    fprintf(fout, "ベクトル%cは次の通りです\n", c);
    for (i = 0; i < n; i++)
    {
        fscanf(fin, "%lf", &b[i]);
        fprintf(fout, "%5.2f\t", b[i]);
    }
    fprintf(fout, "\n");
}

void gauss2(double a[N + 1][N + 1], double b[N + 1])
{
    int i, j, k, ip;
    double alpha, tmp;
    double amax, eps = pow(2.0, -50.0);
    for (k = 0; k <= N + 1 - 2; k++)
    {

        amax = fabs(a[k][k]);
        ip = k;
        for (i = k + 1; i <= N + 1 - 1; i++)
        {
            if (fabs(a[i][k]) > amax)
            {
                amax = fabs(a[i][k]);
                ip = i;
            }
        }

        if (amax < eps)
            printf("行列が正則ではない!\n");

        if (ip != k)
        {
            for (j = k; j <= N + 1 - 1; j++)
            {
                // a[k][j]とa[ip][j]の交換
                tmp = a[k][j];
                a[k][j] = a[ip][j];
                a[ip][j] = tmp;
            }
            tmp = b[k];
            b[k] = b[ip];
            b[ip] = tmp;
        }

        for (i = k + 1; i <= N + 1 - 1; i++)
        {
            alpha = -a[i][k] / a[k][k];
            for (j = k + 1; j <= N + 1 - 1; j++)
            {
                a[i][j] += alpha * a[k][j];
            }
            b[i] += alpha * b[k];
        }
    }

    b[N + 1 - 1] = b[N + 1 - 1] / a[N + 1 - 1][N + 1 - 1];
    for (k = N + 1 - 2; k >= 0; k--)
    {
        tmp = b[k];
        for (j = k + 1; j <= N + 1 - 1; j++)
        {
            tmp -= a[k][j] * b[j];
        }
        b[k] = tmp / a[k][k];
    }
}
