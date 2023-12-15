#include <stdio.h>
#include <stdlib.h>

void input_vector3(double *b, int m, int n, FILE *fin);
double lagrange(double *x, double *y, int m, int n, double xi);

int main(void)
{
    FILE *fin, *fout;
    double xi;

    int N;
    printf("データの個数を入力してください→");
    scanf("%d", &N);

    double *x = (double *)malloc(N * sizeof(double));
    double *y = (double *)malloc(N * sizeof(double));

    if (x == NULL || y == NULL)
    {
        printf("メモリの確保に失敗しました\n");
        exit(1);
    }

    if ((fin = fopen("input_lag.dat", "r")) == NULL)
    {
        printf("ファイルが見つかりません: input_lag.dat \n");
        exit(1);
    }

    if ((fout = fopen("output_lag.dat", "w")) == NULL)
    {
        printf("ファイルが作成できません: output_lag.dat \n");
        exit(1);
    }

    input_vector3(x, 0, N - 1, fin);
    input_vector3(y, 0, N - 1, fin);

    printf("補間点を入力してください →");
    scanf("%lf", &xi);
    printf("補間の結果は、P(%f) = %f \n", xi, lagrange(x, y, 0, N - 1, xi));

    double delta = 0.01;
    for (xi = x[0]; xi < x[N - 1] + delta; xi += delta)
    {
        fprintf(fout, "%f \t %f\n", xi, lagrange(x, y, 0, N - 1, xi));
    }

    free(x);
    free(y);

    if (fin != NULL)
    {
        fclose(fin);
    }

    if (fout != NULL)
    {
        fclose(fout);
    }

    return 0;
}

double lagrange(double *x, double *y, int m, int n, double xi)
{
    int i, k;
    double pn = 0.0, li;

    for (i = m; i <= n; i++)
    {
        li = 1.0;

        for (k = m; k <= n; k++)
        {
            if (k != i)
                li *= (xi - x[k]) / (x[i] - x[k]);
        }
        pn += li * y[i];
    }
    return pn;
}

void input_vector3(double *b, int m, int n, FILE *fin)
{
    int i;
    for (i = m; i <= n; i++)
    {
        fscanf(fin, "%lf", &b[i]);
    }
}
