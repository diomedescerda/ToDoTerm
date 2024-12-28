#ifndef MODULES_H
#define MODULES_H
#include <stdio.h>

#define NUM_DAYS 7
#define MAX_SUBJECTS 12
#define MAX_SUBJECT_LENGTH 30

typedef struct {
  int index;
  int ogIndex;
  char name[256];
  int priority;
  int time;
  int isDone;
} Task;

typedef struct {
  char dayName[10];
  char *subjects[25];
  int nSubjects;
} Day;

extern Task *tasks;
extern int taskCount;
extern char msg[256];
extern struct passwd *pw;
extern int taskMode;

extern Day *schedule;

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

char *generateToDoString(struct passwd *pw);
void updateDisplay(const char *display);
void addDisplay();
void removeDisplay();
void doneDisplay();
void undoneDisplay();
void clearDisplay();
void sortByDisplay();

void addTodo(const char *name, int priority, int period);
void removeTodo(int index);
void markDone(int index);
void markUndone(int index);
void markUndoneAll();
void updateIndexAsQueue();
void updateIndexByTime();
void updateIndexByPriority();

void serializeTasks(const char *filename);
void serializeSchedule(const char *filename);
Task *deserializeTasks(const char *filename, size_t *size);
Day *deserializeSchedule(const char *filename, size_t *size);

void initSchedule();
void printSchedule();
void addSubject();
void removeSubject();
#endif
