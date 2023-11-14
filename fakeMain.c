#include "plugins/pmc.h"

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdbool.h>

#define REALMAIN_NAME "pluginator"

int (*realMain)(void) = NULL;
void *handle = NULL;

void load();
void compile();

bool isCompiled = 0;

int main()
{
    int running = 1;
    load();
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
            load();
            break;
        default:
            break;
        }
    }
}

void load()
{
    handle = dlopen("plugins/compiledPlugins/" REALMAIN_NAME ".so", RTLD_LAZY);
    if (handle == NULL)
    {
        if (isCompiled)
        {
            printf("failed to load " REALMAIN_NAME "\n");
            exit(1);
        }
        else
        {
            compile();
        }
    }

    realMain = dlsym(handle, REALMAIN_NAME);
    if (!realMain)
    {
        printf("error while loading "REALMAIN_NAME"(): %s", dlerror());
        dlclose(handle);
        exit(1);
    }

    printf(REALMAIN_NAME " loaded\n\n");
}

void compile()
{
    isCompiled = 0;
    printf("\n\ncompiling pluginator...\n");
    const int result = system("cc -fPIC --shared -o plugins/compiledPlugins/" REALMAIN_NAME ".so plugins/" REALMAIN_NAME ".c");
    if (result == 0)
    {
        load();
        isCompiled = 1;
    }
    else
    {
        printf("failed to compile " REALMAIN_NAME "\n");
        exit(1);
    }
}