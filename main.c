#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define STRIKE_START "\e[9m"
#define STRIKE_END "\e[29m"

typedef struct{
    int index;
    char name[1000];
    const char* color;
    int is_done;
} Task;

Task tasks[10000];
int taskCount = 0;

void printTodo();
void addTodo(const char* name, const char* color);
void removeTodo(int index);
void markDone(int index);
void markUndone(int index);


int main(int argc, char *argv[]) {
    
    struct passwd *pw;
    uid_t uid;
    int op;

    uid = getuid();
    pw = getpwuid(uid);

    if (pw == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    


    addTodo("study", RED);
    addTodo("clean", GREEN);
    addTodo("run", BLUE);
    printf("ToDo List in your Terminal!\n");
    printf("Hey, %s!\n", pw->pw_name);
    printTodo();
    printf("(A)dd Todo || (R)emove Todo || Mark (D)one || Mark (U)ndone || (E)xit\n");
    
    do{
        printf(">>");
        op = getchar();
        while (getchar() != '\n');
        switch (toupper(op)) {
            case 'A':
                addTodo("run", BLUE);
                break;
            case 'R':
                removeTodo(2);
                break;
            case 'D':
                markDone(1);
                break;
            case 'U':
                markUndone(3);
                break;
            case 'E':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
        fflush(stdout);
        printf("\033[1A");
        printf("\033[K");
    }while(op != 'E');

    return 0;
}

void printTodo() {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].is_done) {
            printf(STRIKE_START "%s%d. %s%s\n" STRIKE_END, tasks[i].color,tasks[i].index , tasks[i].name, RESET);
        } else {
            printf("%s%d. %s%s\n", tasks[i].color,tasks[i].index , tasks[i].name, RESET);
        }
    }
}

void addTodo(const char* name, const char* color) {
    if (taskCount < 10000) {
        tasks[taskCount].index = taskCount + 1;
        strncpy(tasks[taskCount].name, name, 999);
        tasks[taskCount].name[999] = '\0';
        tasks[taskCount].color = color;
        taskCount++;
    }
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
        printf("Task %d removed. \n", index);
    } else {
        printf("Task with index %d not found. \n", index);
    }
}

void markDone(int index) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == index) {
            tasks[i].is_done = 1;
            break;
        }
    }
}

void markUndone(int index) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == index) {
            tasks[i].is_done = 0;
            break;
        }
    }
}
