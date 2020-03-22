#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int x;

int getOperator()
{
    while (true)
    {
        printf("Введите значение х: ");
        scanf("%d", &x);
        if ( x == 1 || x == 2 || x == 3 || x == 4 || x == 5 || x == 6 || x == 7 || x == 8 || x == 9 || x == 0 )
        {
            return x;
        }
        else
        {
            printf("Что-то пошло не так, введи заново!");
        }
    }
}

int factorial(int count)
{
    int fct = 1;
    for (int i = 1; i <= count; i++)
    {
        fct = fct * i;
    }
    return fct;
}

int solve(double radians, int n)
{
    long double d, e, a, b, c, result = 0;
    for (int y = 1; y < 100; y++)
    {
        d = (2 * y) - 1;
        e = y - 1;
        a = pow(-1, e);
        b = pow(radians, d);
        c = factorial(d);
        result += (a * b) / (long double)c;
        if (result - sin(radians) < e)
        {
            printf("S(x) - %Lf\n", result);
            return y;
        }
    }
    return 0;
}

int main()
{
    getOperator();
    printf("%d", solve(x, 0));
    return 0;
}
