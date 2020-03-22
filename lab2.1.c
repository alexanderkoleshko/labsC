#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int r;
float k;

int getOperatorR()
{
    while (true)
    {
        printf("Введите радиус шара: ");
        scanf("%d", &r);
        if ( r == 1 || r == 2 || r == 3 || r == 4 || r == 5 || r == 6 || r == 7 || r == 8 || r == 9 || r == 0 )
        {
            return r;
        }
        else
        {
            printf("Что-то пошло не так, введи заново!");
        }
    }
}

int getOperatorK()
{
    while (true)
    {
        printf("Введите расстояние от центра шара до сечения: ");
        scanf("%f", &k);
        if ( k == 1 || k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9 || k == 0 )
        {
            return k;
        }
        else
        {
            printf("Что-то пошло не так, введи заново!");
        }
    }
}

int main() {
    int menu, pi = 3.14;
    float S, V, L, a;
    getOperatorR();
    do {
        printf("1. Вывод площади поверхности шара.\n2. Вывод объема шара.\n3. Вывод длины ребра вписанного правильного тетраэдра.\n4. Вывод площади сечения, проведенного на расстоянии k от центра шара.\n5. Информация о версии и авторе программы.\n0. Выход из программы.\n");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                S = 4 * pi * pow(r, 2);
                printf("%f", S);
                printf("%s", "\n");
                break;
            case 2:
                V = 4 / 3 * pi * pow(r, 3);
                printf("%f", V);
                printf("%s", "\n");
                break;
            case 3:
                a = 4 * r / sqrt(6);
                printf("%f", a);
                printf("%s", "\n");
                break;
            case 4:
                getOperatorK();
                L = sqrt(pow(r, 2) - pow(k, 2));
                printf("%f", L);
                printf("%s", "\n");
                break;
            case 5:
                printf("VERSION - 1.0\nAUTHOR - Alexander Koleshko");
                printf("%s", "\n");
                break;
        }
    } while (menu !=0);
    
    return 0;
}
