#ifndef MODULES_H
#define MODULES_H

typedef struct{
    int index;
    char name[1000];
    const char* color;
    int is_done;
} Task;

extern Task tasks[10000];
extern int taskCount;
extern char msg[100];
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
#define CURSOR_UP "\033[1F"
#define CURSOR_RIGHT "\033[3C"

char* generateToDoString(struct passwd *pw);
void updateDisplay(const char* display);
void addTodo(const char* name, const char* priority);
void removeTodo(int index);
void markDone(int index);
void markUndone(int index);

#endif
