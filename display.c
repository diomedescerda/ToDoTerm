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
    const char* color = "";

    if (memstream == NULL) {
        fprintf(stderr, "Failed to open memory stream\n");
        return NULL;
    }


    fprintf(memstream, "┌───────────────────────────────────────────────────────────────┐ \n");
    fprintf(memstream, "│                 ToDo List in your Terminal!                   │ \n");
    fprintf(memstream, "└───────────────────────────────────────────────────────────────┘ \n");
    fprintf(memstream, "\n\tHey, ");
    fprintf(memstream, "%s%s!%s\n\n", PURPLE,  pw->pw_name, RESET);

    for (int i = 0; i < taskCount; i++) {
        switch (tasks[i].priority) {
            case 'H':
                color = RED;
                break;
            case 'M':
                color = YELLOW;
                break;
            case 'L':
                color = GREEN;
                break;
        }
        
        if (tasks[i].is_done) {
            fprintf(memstream, STRIKE_START "\t%s%d. %s%s\n" STRIKE_END, color, tasks[i].index , tasks[i].name, RESET);
        } else {
            fprintf(memstream, "\t%s%d. %s%s\n", color, tasks[i].index , tasks[i].name, RESET);
        }
    }

    fprintf(memstream, "\n┌───────────────────────────────────────────────────────────────┐ \n");
    fprintf(memstream, "│ [ (A)dd Todo ] [ (R)emove Todo ] [ Mark (D)one ] [ (U)ndone ] │ \n");
    fprintf(memstream, "│ [ [S]ort By ] [ (C)lear All ] [ (E)xit ]                      │ \n");
    fprintf(memstream, "└───────────────────────────────────────────────────────────────┘ \n\n>> ");
    
    fclose(memstream);
    return result;
}

void updateDisplay(const char* display) {
    printf(CLEAR_SCREEN);
    printf(CURSOR_HOME);
    printf("%s", display);
    printf(SAVE_CURSOR);

    if (msg[0] != 'n') {
        printf("\n%s", msg);
    }

    printf(RESTORE_CURSOR);
    fflush(stdout);
}

void addDisplay() {
    char name[256];
    int priority, period;

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
        printf("Enter the period of the day where you have to do the task: ");
        printf(SAVE_CURSOR);
        printf("\n(M)orning (A)fternoon (E)vening (N)ight");
        printf(RESTORE_CURSOR);

        period = getchar();
        while (getchar() != '\n');
        period = toupper(period);

        if (period == 'M' || period == 'A' || period == 'E' || period == 'N') {
            addTodo(name, priority, period);
            strcpy(msg, "It has been added");
        } else {
            strcpy(msg, "It seems it was an error with the priority");
        }
    } else {
        strcpy(msg, "It seems it was an error with the priority");
    }

}

void removeDisplay() {
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
void doneDisplay() {
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

void undoneDisplay() {
    printf("Enter the ID of the task undone: ");
    scanf("%d", &id);
    while (getchar() != '\n');
    
    markUndone(id);
    strcpy(msg, "It has been marked undone");
}

void sortByDisplay() {
    int criteria;

    printf(CLEAR_LINE);
    printf("Specify the sorting criteria: ");
    printf(SAVE_CURSOR);
    printf("\n[P]riority [T]ime period of the day");
    printf(RESTORE_CURSOR);

    criteria = getchar();
    while (getchar() != '\n');
    criteria = toupper(criteria);

    if (criteria == 'P') {
        updateIndexByPriority();
        strcpy(msg, "It has been sorted by priority");
    } else if (criteria == 'T') {
        updateIndexByTime();
        strcpy(msg, "It has been sorted by time period of the day");
    } else {
        strcpy(msg, "It seems it was an error with the sorting criteria");
    }
}
