#include <stdio.h>
#include <stdlib.h>
#include "../include/modules.h"

void serialize_tasks(const char *filename) {
  FILE *file = fopen(filename, "w");
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
    FILE *file = fopen(filename, "r");
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
