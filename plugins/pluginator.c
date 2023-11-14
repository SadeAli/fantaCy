#include "pmc.h"
#include "cengin.h"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include <dlfcn.h>

#define MAX_FILENAME_LEN 512
#define MAX_FILE_COUNT 512
#define MAX_COMMAND_LENGHT 512

#define HAS_PREFIX(a, b) (strncmp(a, b, sizeof(b) - 1) == 0)
#define CUT_PREFIX(a, b) (a + sizeof(b) - 1)

typedef char Command[MAX_COMMAND_LENGHT];

void getFileList(char (**fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN], unsigned int *fileCount, const char *path);
void loadPlugins();
void getUserCommand(Command command);
int processCommand(char *command);
void compile(const char *cFile);

char pluginPath[MAX_FILENAME_LEN] = {"plugins/"};
char pluginBinPath[MAX_FILENAME_LEN] = {"plugins/compiledPlugins/"};

Command command;
int pluginator()
{
    printf("\n< pluginator >\n\n");
    
    // load plugins if there are any
    printf("loading plugins\n");
    loadPlugins();

    // get user command and process it
    for (;;)
    {
        getUserCommand(command);
        int result = processCommand(command);
        // if result is not success, return result to parent to handle it
        if ((result != SUCCESS) && (result != FAILURE))
        {
            return result;
        }
    }
}

void loadPlugins()
{
    // get files inside plugin path
    char(*fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN];
    unsigned int fileCount;
    getFileList(&fileList, &fileCount, pluginPath);

    if (fileCount <= 2)
    {
        printf("! no plugins found\n");

        printf("\nif you want to set a new plugin path,\n"
               "\ttype: set pluginPath \"path\"\n");

        printf("\nthen reload plugins with: reload plugins\n");
    }
    else
    {
        printf("processing plugins...\n");

        for (int i = 2; i < fileCount; ++i)
        {
            char *fileExtension = strchr((*fileList)[i], '.');
            if (fileExtension == NULL)
            {
                printf("passing: \"%s\"\n", (*fileList)[i]);
                continue;
            }
            // find c files and compile them
            if (strncmp(fileExtension, ".c", 2) == 0)
            {
                printf("source file found. Compiling: %s\n", (*fileList)[i]);
                compile((*fileList)[i]);
            }
        }
    }
}

void compile(const char *cFile)
{
    // set output name
    char outputFile[MAX_FILENAME_LEN];
    strcpy(outputFile, cFile);
    // set output extension
    const unsigned int filenameLen = strlen(cFile);
    strncpy(outputFile + filenameLen - 1, "so", sizeof("so"));

    // open config file
    FILE *fp;
    fp = fopen("plugins/config.inator", "r");
    if (fp == NULL)
    {
        printf("error opening file\n");
        exit(1);
    }

    sprintf(command, "gcc -fPIC --shared -o %s%s %s%s ", pluginBinPath, outputFile, pluginPath, cFile);
    // buffer stores lines from the config file
    char buffer[512];
    // goto start of file
    fseek(fp, 0, SEEK_SET);
    // read file line by line
    // fgets returns NULL if eof
    while (fgets(buffer, sizeof(buffer), fp))
    {
        // remove '\n' from config line which is read by fgets
        buffer[strlen(buffer)] = '\0';

        char token[MAX_FILENAME_LEN + sizeof("[.compileFlags]")];
        sprintf(token, "[%s.compileFlags]", cFile);

        // set token
        char *compilerFlags;
        // if line has token remove token get link flags
        if (strncmp(buffer, token, strlen(cFile)) == 0)
        {
            compilerFlags = buffer + strlen(token) - 1;
            printf("%s\n", compilerFlags);
            strcat(command, compilerFlags);
            printf("%s\n", command);
        }
    }

    // send command to operating system
    system(command);

    // close file
    fclose(fp);
}

void getUserCommand(Command command)
{
    fgets(command, sizeof(Command), stdin);
    command[strlen(command) - 1] = '\0';
}

int processCommand(char *command)
{
    if (strncmp(command, "linux ", 6) == 0)
    {
        system(command + 6);
        return SUCCESS;
    }

    if HAS_PREFIX (command, "set pluginPath ")
    {
        strcpy(pluginPath, CUT_PREFIX(command, "set pluginPath "));
        printf("plugin path set to: %s\n", pluginPath);
        return SUCCESS;
    }

    if (strcmp(command, "reload") == 0)
    {
        loadPlugins();
        return SUCCESS;
    }

    if (strcmp(command, "exit") == 0)
    {
        return EXIT;
    }

    if (strcmp(command, "recompile") == 0)
    {
        return RECOMPILE;
    }

    if HAS_PREFIX (command, "enter ")
    {
        // get so path
        char *pluginName = CUT_PREFIX(command, "enter ");
        char pluginBin[MAX_FILENAME_LEN];
        sprintf(pluginBin, "%s%s.so", pluginBinPath, pluginName);

        // open plugin
        void *handle = dlopen(pluginBin, RTLD_LAZY);
        if (handle == NULL)
        {
            printf("failed to load %s\n", pluginName);
            return FAILURE;
        }

        // get entry
        void (*entryFunction)() = dlsym(handle, ENTRY_NAME);
        if (!entryFunction)
        {
            printf("error while loading entryFunction(): %s", dlerror());
            dlclose(handle);
            return FAILURE;
        }

        // call entry
        entryFunction();
        // close plugin
        dlclose(handle);
        return SUCCESS;
    }

    printf("\n! unknown command: %s\n\n", command);
    return FAILURE;
}

void getFileList(char (**fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN], unsigned int *fileCount, const char *path)
{
    // if path is null, set it to current directory
    if (path == NULL)
    {
        path = ".";
    }

    // static variables can be usable after function returns
    static char files[MAX_FILE_COUNT][MAX_FILENAME_LEN];
    unsigned int numberOfFiles = 0;

    // open directory
    DIR *d;
    struct dirent *dir;
    d = opendir(path);

    // if directory is null, return
    if (d == NULL)
    {
        printf("couldn't find file: %s\n", path);
        return;
    }

    // read directory
    while ((dir = readdir(d)) != NULL)
    {
        // get file name
        strcpy(files[numberOfFiles], dir->d_name);
        ++numberOfFiles;
    }
    closedir(d);

    // return file list and file count
    *fileList = &files;
    *fileCount = numberOfFiles;

    return;
}