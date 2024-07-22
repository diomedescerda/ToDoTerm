#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "modules.h"

void addTodo(const char* name, const char* priority) {
    if (taskCount < 10000) {
        tasks[taskCount].index = taskCount + 1;
        strncpy(tasks[taskCount].name, name, 999);
        tasks[taskCount].name[999] = '\0';
        tasks[taskCount].color = RED;
       taskCount++;
    }
    strcpy(msg, "It has been added");
}

void removeTodo(int index) {
    int found = -1;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == index) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < taskCount - 1; i++) {
            tasks[i] = tasks[i+1];
            tasks[i].index--;
        }
        taskCount--;
        strcpy(msg, "It has been remove");
    } else {
        strcpy(msg, "Index incorrect");
    }
}

void markDone(int index) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == index) {
            tasks[i].is_done = 1;
            break;
        }
    }
    strcpy(msg, "It has been marked done");
}

void markUndone(int index) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == index) {
            tasks[i].is_done = 0;
            break;
        }
    }
    strcpy(msg, "It has been marked undone");
}
