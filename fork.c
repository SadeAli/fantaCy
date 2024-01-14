#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    __pid_t pid = fork();
    if (pid == 0)
    {
        printf("Child process\n");
    }
    else if (pid > 0)
    {
        printf("Parent process\n");
    }
    else
    {
        printf("Fork failed\n");
    }
}