#include <stdio.h>

// existential crisis
const int *const *const *const *(*const (*volatile (*(*j)())[7])())();

#define STRINGIFY(x) #x

int i = 5;

void someNonsense()
{
    static int *i;
    auto int b;
    j = (const int *const *const *const *(*const (*volatile(*(*)())[7])())()) & b;
    j = (const int *const *const *const *(*const (*volatile(*(*)())[7])())())(&i + 1);
}

int main()
{
    someNonsense();

}