#include <ctype.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include "../include/modules.h"

void tasksByPriority(FILE* memstream, const char* color, int i);
void tasksByTime(FILE* memstream, const char* color, int i);

int id;
int hi, me, lo, mo, af, ev, ni;
int taskMode;

char* generateToDoString(struct passwd *pw) {
    char* result = NULL;
    size_t size = 0;
    FILE* memstream = open_memstream(&result, &size);
    const char* color = "";

    hi = me = lo = mo = af = ev = ni = 0;

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

        switch (taskMode) {
            case 'P':
                tasksByPriority(memstream, color, i);
                break;
            case 'T':
                tasksByTime(memstream, color, i);
                break;
            default:
                break;
        
        }

        if (tasks[i].isDone) {
            fprintf(memstream, STRIKE_START "\t  %s%d. %s%s\n" STRIKE_END, color, tasks[i].index , tasks[i].name, RESET);
        } else {
            fprintf(memstream, "\t  %s%d. %s%s\n", color, tasks[i].index , tasks[i].name, RESET);
        }
    }

    fprintf(memstream, "\n┌────────────────────────────────────────────────────────────────────┐ \n");
    fprintf(memstream, "│ [ (A)dd Todo ] [ (R)emove Todo ] [ Mark (D)one ] [ Mark (U)ndone ] │ \n");
    fprintf(memstream, "│ [ [S]ort By ] [ (C)lear All ] [ (E)xit ]                           │ \n");
    fprintf(memstream, "└────────────────────────────────────────────────────────────────────┘ \n\n>> ");
    
    fclose(memstream);
    return result;
}

void tasksByPriority(FILE* memstream, const char* color, int i ) {
    if(tasks[i].priority == 'H' && hi == 0) {
        fprintf(memstream,"\t%sHIGH%s\n", RED, RESET);
        hi++;
    } else if(tasks[i].priority == 'M' && me == 0) {
        fprintf(memstream,"\t%sMEDIUM%s\n", YELLOW, RESET);
        me++;
    } else if(tasks[i].priority == 'L' && lo == 0) {
        fprintf(memstream,"\t%sLOW%s\n", GREEN, RESET);
        lo++;
    }
}

void tasksByTime(FILE* memstream, const char* color, int i) {
        if(tasks[i].time == 'M' && mo == 0) {
            fprintf(memstream,"\t%sMORNING%s\n", PURPLE, RESET);
            mo++;
        } else if(tasks[i].time == 'A' && af == 0) {
            fprintf(memstream,"\t%sAFTERNOON%s\n", PURPLE, RESET);
            af++;
        } else if(tasks[i].time == 'E' && ev == 0) {
            fprintf(memstream,"\t%sEVENING%s\n", PURPLE, RESET);
            ev++;
        } else if(tasks[i].time == 'N' && ni == 0) {
            fprintf(memstream,"\t%sNIGHT%s\n", PURPLE, RESET);
            ni++;
        }
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

    if (tasks[id - 1].isDone == 1) {
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

void clearDisplay() {
    int op = 0;
    printf(CLEAR_LINE);
    printf("Are you sure you want to clear all (Y/N): ");
    op = getchar();
    while (getchar() != '\n');

    if (toupper(op) == 'Y') {
        taskCount = 0;
        strcpy(msg, "It has been cleared");
    } else {
        strcpy(msg, "It hasn't been cleared");
    }
}

void sortByDisplay() {
    int criteria;

    printf(CLEAR_LINE);
    printf("Specify the sorting criteria: ");
    printf(SAVE_CURSOR);
    printf("\n[Q]ueue [P]riority [T]ime period of the day");
    printf(RESTORE_CURSOR);

    criteria = getchar();
    while (getchar() != '\n');
    criteria = toupper(criteria);

    switch (criteria) {
        case 'Q':
            updateIndexAsQueue();
            strcpy(msg, "It has been sorted as a Queue");
            break;
        case 'P':
            updateIndexByPriority();
            strcpy(msg, "It has been sorted by priority");
            break;
        case 'T':
            updateIndexByTime();
            strcpy(msg, "It has been sorted by time period of the day");
            break;
        default:
            strcpy(msg, "It seems it was an error with the sorting criteria");
            break;
    }
}
