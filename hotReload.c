#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dlfcn.h>

#define MAX_FILENAME_LEN 512
#define MAX_FILE_COUNT 1000
#define MAX_COMMAND_LENGHT 512

typedef void (*module_func)(void);

void getFileList(char (**fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN], unsigned int *fileCount);

int main()
{
    char(*fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN];
    unsigned int fileCount;
    getFileList(&fileList, &fileCount);

    int i;
    for (i = 0; i < fileCount; ++i)
    {
        printf("%s\n", (*fileList)[i]);
    }

reload:
    if (system("gcc --shared -o harmless.so harmless.c"))
    {
        printf("compilation failed\n");
        return -1;
    }

    void *handle = dlopen("./harmless.so", RTLD_LAZY);
    if (handle == NULL)
    {
        printf("failed to load module\n");
    }
    
    module_func fn = dlsym(handle, "harmless");

    if (!fn)
    {
        printf("line %s error: %s\n", __LINE__, dlerror());
        dlclose(handle);
        return 1;
    }

    fn();
    dlclose(handle);

    char command[MAX_COMMAND_LENGHT];
    printf("Do you want to reload? (y/n): ");
    scanf("%s", command);

    if (strcmp(command, "y") == 0)
    {
        goto reload;
    }

    return 0;
}

void getFileList(char (**fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN], unsigned int *fileCount)
{
    static char files[MAX_FILE_COUNT][MAX_FILENAME_LEN] = {0};
    unsigned int _fileCount = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    while ((dir = readdir(d)) != NULL)
    {
        // get file name
        strcpy(files[_fileCount], dir->d_name);
        ++_fileCount;
    }
    closedir(d);

    *fileList = &files;
    *fileCount = _fileCount;
}