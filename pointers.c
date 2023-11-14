#include <stdio.h>
#include <stdlib.h>

int mSum(int **, int, int);

int main()
{
    int mat[5][5];
    int sum = mSum(mat, 5, 5);
    printf("Sum of all elements in tda: %d\n", sum);
}

int mSum(int **mat, int x, int y)
{
    int sum = 0;
    int i, j;

    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; i++)
        {
            sum += *((int *)mat + i * y + j);
        }
    }

    return sum;
}