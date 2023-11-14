#include <stdio.h>
#include <dlfcn.h>

void seperate();
void together();

int main()
{
    // seperate();
    together();
}

void together()
{
    void *mahmutHandle = dlopen("./mahmut.so", RTLD_NOW);
    void *kemalHandle = dlopen("./kemal.so", RTLD_NOW);

    void (*mahmut)() = dlsym(mahmutHandle, "_EntryPoint");
    void (*kemal)() = dlsym(kemalHandle, "_EntryPoint");

    mahmut();
    kemal();

    dlclose(mahmutHandle);
    dlclose(kemalHandle);
}

void seperate()
{
    void *mahmutHandle = dlopen("./mahmut.so", RTLD_LAZY);
    void (*mahmut)() = dlsym(mahmutHandle, "_EntryPoint");
    mahmut();
    dlclose(mahmutHandle);

    void *kemalHandle = dlopen("./kemal.so", RTLD_LAZY);
    void (*kemal)() = dlsym(kemalHandle, "_EntryPoint");
    kemal();
    dlclose(kemalHandle);
}