#include <stdio.h>

// void *(*(*func)[5])();
// ??? WTH ???
void hello()
{
}

typedef int (*arr_t)[3][2];

int main()
{
    int mat[2][3] = {{5, 1, 2}, {4, 7, 8}};
    int i, j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%d ", (*((arr_t)&mat))[i][j]);
        }
        printf("\n");
    }
}