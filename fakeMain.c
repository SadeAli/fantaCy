#include "plugins/pmc.h"

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int (*realMain)(void) = NULL;
void *handle = NULL;

void compile();

int main()
{
    int running = 1;
    compile();
    while (running)
    {
        int result = realMain();
        switch (result)
        {
        case EXIT:
            running = 0;
            dlclose(handle);
            break;
        case RECOMPILE:
            dlclose(handle);
            compile();
            break;
        default:
            break;
        }
    }
}

void compile()
{
    printf("\n\ncompiling pluginator...\n");
    system("gcc -fPIC --shared -o plugins/compiledPlugins/pluginator.so plugins_a/pluginator.c");
    // load pluginator function from pluginator.so
    handle = dlopen("plugins/compiledPlugins/pluginator.so", RTLD_LAZY);
    if (handle == NULL)
    {
        printf("failed to load pluginator\n");
        exit(1);
    }
    realMain = dlsym(handle, "pluginator");
    if (!realMain)
    {
        printf("error while loading realMain(): %s", dlerror());
        dlclose(handle);
        exit(1);
    }
    printf("pluginator loaded\n\n");
}