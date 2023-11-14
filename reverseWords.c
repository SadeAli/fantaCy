#include <stdio.h>
#include <stdarg.h>

int sumNNumbers(int n, ...)
{
    va_list list;
    int total;

    total = 0;

    va_start(list, n);

    for (int i = 0; i < 4; i++)
    {
        total = total + va_arg(list, int);
    }

    va_end(list);
    return total;
}

void reverseOrder(char *str, const int currentOffset)
{
    char c = *str;
    if (!c)
        return;

    if (c == ' ')
    {
        for (int i = 0; i < currentOffset / 2; i++)
        {
            char tmp = *(str - i);
            *(str - i) = *(str - currentOffset + i);
            *(str - currentOffset + i) = tmp;
        }

        reverseOrder(str + 1, 0);
        return;
    }

    reverseOrder(str + 1, currentOffset + 1);

    return;
}

int main()
{
    char kelime[] = "yapisal ve matematik";
    reverseOrder(kelime, 0);
    printf("%s\n", kelime);

    // printf("%d\n", sumAllnNumbers(3, 2, 37, 2));
}