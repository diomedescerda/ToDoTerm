#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "../include/modules.h"

Task *tasks;
int taskCount = 0;

char msg[256] = "n";
struct passwd *pw;

int main(int argc, char *argv[]) {
    uid_t uid;
    int op;
    uid = getuid();
    pw = getpwuid(uid);
    char* display; 

    if (pw == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    
    size_t size;
    tasks = deserialize_tasks("data/tasks.dat", &size);
    if (tasks != NULL) {
        taskCount = size;
    } else {
        tasks = calloc(taskCount + 1, sizeof(Task));
        if (tasks == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }

    printf(CLEAR_SCREEN);

    do{
        display = generateToDoString(pw); 
        updateDisplay(display);
        op = getchar();
        while (getchar() != '\n');
        switch (toupper(op)) {
            case 'A':
                tasks = realloc(tasks, taskCount + 1 * sizeof(Task));
                if (tasks == NULL) {
                    fprintf(stderr, "Memory reallocation failed\n");
                    return 1;
                }
                addDisplay();
                break;
            case 'R':
                removeDisplay();
                tasks = realloc(tasks, taskCount + 1 * sizeof(Task));
                if (tasks == NULL) {
                    fprintf(stderr, "Memory reallocation failed\n");
                    return 1;
                }
                break;
            case 'D':
                doneDisplay();
                break;
            case 'U':
                undoneDisplay();
                break;
            case 'C':
                clearDisplay();
                break;
            case 'S':
                sortByDisplay();
                break;
            case 'E':
                printf(CLEAR_LINE);
                printf("Exiting...\n");
                serialize_tasks("data/tasks.dat");
                free(tasks);
                return 0;
            default:
                strcpy(msg, "Invalid option. Please try again.");
                updateDisplay(display);
        }
    }while(op != 'E');
}