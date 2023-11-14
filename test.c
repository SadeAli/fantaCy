#include <stdio.h>
#include <string.h>

int main()
{
    char command[512];
    fprintf(stdin, "hello\n");

    fscanf(stdout, "%s", command);

    fprintf(stdout, "%s\n", command);
}