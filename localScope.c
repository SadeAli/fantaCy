#include <stdio.h>

void asd()
{
    extern int a;
    printf("a: %d\n", a);
}

int main()
{
    extern int a;
    printf("a: %d\n", a);

    {
        int a = 5;
        printf("a: %d\n", a);
    }

    printf("a: %d\n", a);

    asd();
}