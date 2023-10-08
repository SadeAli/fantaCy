#include <stdio.h>

int main()
{
    FILE *fp = fopen("plugins/compiledPlugins/pluginator.so", "rb");
    if (fp == NULL)
    {
        printf("cannot open file\n"
               "error: %d",
               ferror(fp));
    }

    static char buffer[2048];
    while (fgets(buffer, 2047, fp))
    {
        printf("%s", buffer);
    }

    fclose(fp);

    return 0;
}