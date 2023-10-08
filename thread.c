#include <threads.h>
#include <stdio.h>

int realMain();

// craete a thread and remove main thread
int main()
{
    thrd_t thread;
    thrd_create(&thread, realMain, NULL);
    printf("another thread launched\n");
    printf("main thread exit\n");
    return 0;
}

// real main thread
int realMain()
{
    int isRunning = 1;
    while (isRunning)
    {
        printf("input 0 to exit\n");
        scanf("%d", &isRunning);
    }
    return 1;
}