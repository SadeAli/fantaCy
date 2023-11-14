#include <stdlib.h>
#include <stdio.h>

#include <string.h>

int main()
{
    // open config file
    FILE *fp;
    fp = fopen("projectConfig.txt", "r");
    if (fp == NULL)
    {
        printf("error opening file\n");
        exit(1);
    }

    char filename[512] = "harmless";

    // create buffer
    char buffer[2000];
    // goto start of file
    fseek(fp, 0, SEEK_SET);
    // read file line by line
    // fgets returns NULL if eof
    while (fgets(buffer, sizeof(buffer), fp))
    {
        // remove '\n'
        buffer[strlen(buffer) - 1] = '\0';

        // set token
        char token[512];
        sprintf(token, "[%s.compileFlags]", filename);

        // if line has token remove token and use parameters after the token
        if (strncmp(buffer, token, strlen(filename)) == 0)
        {
            sprintf(buffer, "%s\n", buffer + strlen(token));
        }
    }

    // close file
    fclose(fp);
}