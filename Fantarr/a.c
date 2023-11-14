#include <stdio.h>
#include <stdlib.h>

void setArr(int (*arr)[1][1], int row, int col);
void printArr(int (*arr)[1][1], int row, int col);

int main()
{
    int x = 3, y = 2;
    int(*arr)[y][x] = calloc(x * y, sizeof(int));

    setArr(arr, y, x);
    printArr(arr, y, x);
    printf("\n");
    printArr(arr, x, y);
    printf("\n");
    printArr(arr, 1, 6);
    printf("\n");
    printArr(arr, 6, 1);

    free(arr);
}

void setArr(int (*arr)[1][1], int row, int col)
{
    int(*tempArr)[row][col] = arr;

    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            (*tempArr)[i][j] = (col * i + 1) * (j + 1);
        }
        printf("\n");
    }
}

void printArr(int (*arr)[1][1], int row, int col)
{
    int(*tempArr)[row][col] = arr;

    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%3d ", (*tempArr)[i][j]);
        }
        putc('\n', stdout);
    }
}