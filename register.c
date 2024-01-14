#include <stdio.h>

void a(register int b)
{
    printf("b: %d\n", b);
}

int main()
{
    goto Pb;
    a(5);
    Pb:
    printf("fake\n");
}
