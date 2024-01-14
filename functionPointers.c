#include <stdio.h>

void hello(int a);

void (*funcReturner(int a, int b))()
{
    return hello;
}

int main()
{
    hello(0);
    void (*ptr)() = hello;
    void (*ptr2)() = (*ptr);
    ptr(1, 2, 3);
    ptr2(1, 2, 3);
    funcReturner(1, 2)();
    return 0;
}

void hello(int a)
{
    printf("Hello World %d\n", a);
}