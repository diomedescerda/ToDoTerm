#ifndef MODULES_H
#define MODULES_H
#include <stdio.h>

typedef struct{
    int index;
    char name[256];
    const char* color;
    int is_done;
} Task;

extern Task *tasks;
extern int taskCount;
extern size_t sizeTasks;
extern char msg[256];
extern struct passwd *pw;

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define PURPLE "\x1b[35m"
#define RESET "\x1b[0m"
#define STRIKE_START "\e[9m"
#define STRIKE_END "\e[29m"
#define CLEAR_SCREEN "\033[2J"
#define CLEAR_LINE "\033[2K"
#define CURSOR_HOME "\033[H"
#define SAVE_CURSOR "\033[s"
#define RESTORE_CURSOR "\033[u"

char* generateToDoString(struct passwd *pw);
void updateDisplay(const char* display);
void addDisplay();
void removeDisplay();
void doneDisplay();
void undoneDisplay();
void addTodo(const char* name, int priority);
void removeTodo(int index);
void markDone(int index);
void markUndone(int index);

#endif
