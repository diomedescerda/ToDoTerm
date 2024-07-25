#include <string.h>
#include "modules.h"

int found = -1;

void addTodo(const char* name, int priority) {
    tasks[taskCount].index = taskCount + 1;
    strncpy(tasks[taskCount].name, name, 256);
    tasks[taskCount].name[256] = '\0';

    if (priority == 'H'){
        tasks[taskCount].color = RED;
    } else if (priority == 'M') {
        tasks[taskCount].color = YELLOW;
    } else if (priority == 'L') {
        tasks[taskCount].color = GREEN;
    }
    tasks[taskCount].is_done = 0;

    taskCount++;
}

void removeTodo(int index) {
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
    } 
}

void markDone(int id) {
    found = -1;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == id) {
            tasks[i].is_done = 1;
            break;
        }
    }
}

void markUndone(int id) {
    found = -1;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == id) {
            tasks[i].is_done = 0;
            break;
        }
    }
    strcpy(msg, "It has been marked undone");
}
