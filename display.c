#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include "modules.h"

char* generateToDoString(struct passwd *pw) {
    char* result = NULL;
    char* info = msg;
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
    
    if (info[0] != 'n') {
        fprintf(memstream, "\n%s",info);
    }

    fclose(memstream);
    return result;
}

void updateDisplay(const char* display) {
    printf(CLEAR_SCREEN);
    printf(CURSOR_HOME);
    printf("%s", display);
    if (msg[0] != 'n'){
        printf(CURSOR_UP);
        printf(CURSOR_RIGHT);
    }
    fflush(stdout);
}
