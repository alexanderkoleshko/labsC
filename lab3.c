#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    int N = 4, indexMaxI = 0, indexMaxJ = 0;
    int mas[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mas[i][j] = rand() % 100;
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", mas[i][j]);
        }
    
        printf("\n");
    }
    int max = mas[0][0];
    for (int i = 0 ; i < N ; i++)
    {
        for (int j = 0 ; j < N ; j++)
        {
            if (mas[i][j] > max)
            {
                max = mas[i][j];
                indexMaxI = i;
                indexMaxJ = j;
            }
        }
    }
    int M = N - 1;
    int newMas[M][M];
    for (int i = 0; i < M; i++)
    {
       for (int j = indexMaxJ; j < M; j++)
       {
           newMas[i][j] = mas[i][j + 1];
       }
    }
    for (int i = indexMaxI; i < M; i++)
    {
        for (int j = 0; i < M; j++)
        {
        newMas[i][j] = mas[i + 1][j];
        }
    }
    printf ("Origin array:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d\t", newMas[i][j]);
        }
    
        printf("\n");
    }
    printf ("Mirror image symmetry about a horizontal axis:\n");
    int x;
    for(int i = 0, x = 1; i < M; i++, x++)
    {
        for(int j = 0; j < M; j++)
        {
            printf("%6d", newMas[M - x][j]);
        }
        printf("\n");
    }
    printf("mirror image symmetry about a vertical axis:\n");
    for (int i = 0; i < M; i++, x++)
    {
        for (int j = 0, x = 1; j < M; j++, x++)
        {
            printf("%6d", newMas[i][M - x]);
        }
        printf("\n");
    }
    return 0;
}
