#include <iostream>

int main()
{
    int a[5];

    for (auto b : a)
    {
        std::cout << b << std::endl;
    }

    return 0;
}