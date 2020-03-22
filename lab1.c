#include <stdio.h>
#include <stdbool.h>

int x;

int getOperator()
{
    while (true)
    {
        printf("Введите x: ");
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

int main()
{
    int i, summ, j;
    getOperator();
    for (i = 2; i <= x; i++)
    {
        summ = 0;
        for (j = 1; j < i; j++)
        {
            if (i % j == 0)
            {
                summ += j;
            }
        }
        if (summ == i)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}
