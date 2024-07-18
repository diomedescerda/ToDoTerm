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
#define CLEAR_SCREEN "\033[2J"
#define CURSOR_HOME "\033[H"

typedef struct{
    int index;
    char name[1000];
    const char* color;
    int is_done;
} Task;

Task tasks[10000];
int taskCount = 0;

char* generateToDoString(struct passwd *pw);
void addTodo(const char* name, const char* color);
void removeTodo(int index);
void markDone(int index);
void markUndone(int index);
void updateDisplay(const char* message);


int main(int argc, char *argv[]) {
    
    struct passwd *pw;
    uid_t uid;
    int op;

    uid = getuid();
    pw = getpwuid(uid);
    char* display; 

    if (pw == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    


    addTodo("study", RED);
    addTodo("clean", GREEN);
    addTodo("run", BLUE);

    do{
        display = generateToDoString(pw); 
        updateDisplay(display);
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
                markUndone(1);
                break;
            case 'E':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }while(op != 'E');

    return 0;
}

char* generateToDoString(struct passwd *pw) {
    char* result = NULL;
    size_t size = 0;
    FILE* memstream = open_memstream(&result, &size);

    if (memstream == NULL) {
        fprintf(stderr, "Failed to open memory stream\n");
        return NULL;
    }

    fprintf(memstream, "ToDo List in your Terminal!\n");
    fprintf(memstream, "Hey, %s!\n", pw->pw_name);
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].is_done) {
            fprintf(memstream, STRIKE_START "%s%d. %s%s\n" STRIKE_END, tasks[i].color,tasks[i].index , tasks[i].name, RESET);
        } else {
            fprintf(memstream, "%s%d. %s%s\n", tasks[i].color,tasks[i].index , tasks[i].name, RESET);
        }
    }
    fprintf(memstream, "\n(A)dd Todo || (R)emove Todo || Mark (D)one || Mark (U)ndone || (E)xit");
    fclose(memstream);
    return result;
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
    printf("It has been mark done.\n");
}

void markUndone(int index) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].index == index) {
            tasks[i].is_done = 0;
            break;
        }
    }
    printf("It has been mark undone.\n");
}

void updateDisplay(const char* display) {
    printf(CLEAR_SCREEN);
    printf(CURSOR_HOME);
    printf("%s\n", display);
    fflush(stdout);
}
