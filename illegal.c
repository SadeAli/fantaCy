#include <stdio.h>
#include <stdlib.h>

int *laugh();

int main()
{
    printf("%d\n", *laugh());
}

int *laugh()
{
    int lol = 7;
    int *p = &lol;
    return p;
}