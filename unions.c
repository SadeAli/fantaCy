#include <stdio.h>

union MyUnion
{
    unsigned char rgba[4];
    unsigned short int r : 1, g : 1, b : 1, a : 1;
    int hex;
};

int main()
{
    union MyUnion myUnion;
    myUnion.hex = 0x12345678;
    myUnion.r = 0x12;
    printf("%x %x %x %x\n", myUnion.r, myUnion.g, myUnion.b, myUnion.a);
}