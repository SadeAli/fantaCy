#include "pmc.h"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include <dlfcn.h>

#define MAX_FILENAME_LEN 512
#define MAX_FILE_COUNT 1000
#define MAX_COMMAND_LENGHT 512

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
    printf("getting list of files\n");
    char(*fileList)[MAX_FILE_COUNT][MAX_FILENAME_LEN];
    unsigned int fileCount;
    getFileList(&fileList, &fileCount, pluginPath);
    printf("list of files generated\n");

    if (fileCount == 0)
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
    const char *dlExtension = "so";

    char outputFile[MAX_FILENAME_LEN];
    strcpy(outputFile, cFile);

    const unsigned int filenameLen = strlen(cFile);
    strncpy(outputFile + filenameLen - 1, dlExtension, 3);

    sprintf(command, "gcc -fPIC --shared -o %s%s %s%s", pluginBinPath, outputFile, pluginPath, cFile);

    // send command to operating system
    system(command);
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

    if (strncmp(command, "set pluginPath ", 15) == 0)
    {
        strcpy(pluginPath, command + 15);
        printf("plugin path set to: %s\n", pluginPath);
        return SUCCESS;
    }

    if (strcmp(command, "reload plugins") == 0)
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