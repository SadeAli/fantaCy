#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 5, y = 5;
    int(*arr)[x][y] = calloc(25, sizeof(int));

    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            (*arr)[i][j] = (5 * i + 1) * (j + 1);
        }
    }

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%3d ", (*arr)[i][j]);
        }
        putc('\n', stdout);
    }

    free(arr);
}