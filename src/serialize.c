#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/modules.h"

void serialize_tasks(const char *filename) {
    char filePath[256];

    if (filename[0] == '~') {
        const char *homeDir = getenv("HOME");
        if (homeDir == NULL) {
            perror("Failed to get home directory");
            return;
        }
        snprintf(filePath, sizeof(filePath), "%s%s", homeDir, filename + 1);
    } else {
        strncpy(filePath, filename, sizeof(filePath));
    }

    char dirPath[256];
    strncpy(dirPath, filePath, sizeof(dirPath));
    char *lastSlash = strrchr(dirPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0'; 

        struct stat st = {0};
        if (stat(dirPath, &st) == -1) {
            if (mkdir(dirPath, 0700) == -1) {
                perror("Failed to create directory");
                return;
            }
        }
    }

    FILE *file = fopen(filePath, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < taskCount; ++i) {
        fprintf(file, "%d %d %s %d %d %d\n", tasks[i].index, tasks[i].ogIndex, tasks[i].name, tasks[i].priority, tasks[i].time, tasks[i].isDone);
    }

    fclose(file);
}

Task* deserialize_tasks(const char *filename, size_t *size) {
    char filePath[256];
    if (filename[0] == '~') {
        const char *homeDir = getenv("HOME");
        if (homeDir == NULL) {
            perror("Failed to get home directory");
            return NULL;
        }
        snprintf(filePath, sizeof(filePath), "%s%s", homeDir, filename + 1);
    } else {
        strncpy(filePath, filename, sizeof(filePath));
    }

    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Failed to open file for reading");
        return NULL;
    }

    Task *tasks = NULL;
    Task task;
    *size = 0;

    while (fscanf(file, "%d %d %255s %d %d %d\n", &task.index, &task.ogIndex, task.name, &task.priority, &task.time, &task.isDone) == 6) {
        tasks = realloc(tasks, (*size + 1) * sizeof(Task));
        if (!tasks) {
            perror("Failed to allocate memory");
            fclose(file);
            return NULL;
        }
        tasks[*size] = task;
        (*size)++;
    }

    fclose(file);
    return tasks;
}
