#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "modules.h"

Task tasks[10000];
int taskCount = 0;
char msg[100] = "n";
struct passwd *pw;

int main(int argc, char *argv[]) {
    
    uid_t uid;
    int op;

    uid = getuid();
    pw = getpwuid(uid);
    char* display; 
    int id;

    if (pw == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    
    printf("\033[2J");

    do{
        display = generateToDoString(pw); 
        updateDisplay(display);
        op = getchar();
        while (getchar() != '\n');
        switch (toupper(op)) {
            case 'A':
                addDisplay();
                break;
            case 'R':
                removeDisplay();
                break;
            case 'D':
                doneDisplay();
                break;
            case 'U':
                undoneDisplay();
                break;
            case 'E':
                printf(CLEAR_LINE);
                printf("Exiting...\n");
                return 0;
            default:
                strcpy(msg, "Invalid option. Please try again.");
                updateDisplay(display);
        }
    }while(op != 'E');

    return 0;
}
