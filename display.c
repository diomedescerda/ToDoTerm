#include <ctype.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include "modules.h"

int id;

char* generateToDoString(struct passwd *pw) {
    char* result = NULL;
    size_t size = 0;
    FILE* memstream = open_memstream(&result, &size);

    if (memstream == NULL) {
        fprintf(stderr, "Failed to open memory stream\n");
        return NULL;
    }

    fprintf(memstream, "ToDo List in your Terminal!\n");
    fprintf(memstream, "Hey, %s!\n\n", pw->pw_name);
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].is_done) {
            fprintf(memstream, STRIKE_START "%s%d. %s%s\n" STRIKE_END, tasks[i].color,tasks[i].index , tasks[i].name, RESET);
        } else {
            fprintf(memstream, "%s%d. %s%s\n", tasks[i].color,tasks[i].index , tasks[i].name, RESET);
        }
    }
    fprintf(memstream, "\n(A)dd Todo || (R)emove Todo || Mark (D)one || Mark (U)ndone || (E)xit\n>> ");
    
    fclose(memstream);
    return result;
}

void updateDisplay(const char* display) {
    printf(CLEAR_SCREEN);
    printf(CURSOR_HOME);
    printf("%s", display);
    printf(SAVE_CURSOR);
    if (msg[0] != 'n'){
        printf("\n%s", msg);
    }
    printf(RESTORE_CURSOR);
    fflush(stdout);
}

void addDisplay(){
    char name[256];
    int priority;

    printf(CLEAR_LINE);
    printf("Enter the name of the task: ");
    fgets(name, 256, stdin);
    name[strlen(name) - 1] = 0;
    printf("Enter the priority of the task: ");
    printf(SAVE_CURSOR);
    printf("\n(H)igh (M)edium  (L)ow");
    printf(RESTORE_CURSOR);
    priority = getchar();
    while (getchar() != '\n');
    priority = toupper(priority);
    
    if (priority == 'H' || priority == 'M' || priority == 'L') {
        addTodo(name, priority);
        strcpy(msg, "It has been added");
    } else {
        strcpy(msg, "It seems it was an error with the priority");
    }
}

void removeDisplay(){
    int temp = taskCount;
    printf(CLEAR_LINE);
    printf("Enter the ID of the task to remove: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    removeTodo(id);
    if (temp > taskCount) {
        strcpy(msg, "It has been remove");
    } else {
        strcpy(msg, "Index incorrect");
    }
}
void doneDisplay(){
    printf("Enter the ID of the task done: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    markDone(id);

    if (tasks[id - 1].is_done == 1) {
        strcpy(msg, "It has been marked done");
    } else {
        strcpy(msg, "It seem has been an error.");
    }
}

void undoneDisplay(){
    printf("Enter the ID of the task undone: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    markUndone(id);
    strcpy(msg, "It has been marked undone");
}
