#include "../../include/modules.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void serializeSchedule(const char *filename);
Day *deserializeSchedule(const char *filename, size_t *size);

void initSchedule();
void printSchedule();
void printScheduleSys();
void addSubject();
void removeSubject();

void scheduleMain() {
  size_t size;
  if (!(schedule =
            deserializeSchedule("~/.config/ToDoTerm/schedule.dat", &size))) {
    initSchedule();
  }

  // addSubject();
  //  removeSubject();
  serializeSchedule("~/.config/ToDoTerm/schedule.dat");
  printScheduleSys();
}

void initSchedule() {
  const char *dayNames[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                            "Thursday", "Friday", "Saturday"};
  schedule = malloc(NUM_DAYS * sizeof(Day));

  for (int i = 0; i < NUM_DAYS; i++) {
    strcpy(schedule[i].dayName, dayNames[i]);
    schedule[i].nSubjects = 0;
  }
}

void printSchedule() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int d = tm.tm_wday;
  int end = NUM_DAYS;

  for (int i = d; i < end; i++) {
    printf("%s\n", schedule[i].dayName);
    for (int j = 0; j < schedule[i].nSubjects; j++) {
      printf("  - %s\n", schedule[i].subjects[j]);
    }

    if (i == NUM_DAYS - 1 && d != 0) {
      i = -1;
      end = d;
    }
  }
}

void printScheduleSys() {
  printf(
      "┌───────────────────────────────────────────────────────────────┐ \n");
  printf(
      "│                 Schedule in your Terminal!                    │ \n");
  printf(
      "└───────────────────────────────────────────────────────────────┘ \n\n");
  printSchedule();
  printf("\n┌──────────────────────────────────────────────────────"
         "──────────────┐ \n");
  printf(
      "│ [ (A)dd Subject ] [ (R)emove Subject ] [ (E)xit ]                  │"
      "\n");
  printf("└────────────────────────────────────────────────────────"
         "────────────┘ \n\n>> ");
}

void addSubject() {
  char name[256];
  printf("Insert the name of the subject\n > ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = 0;

  char input[256];
  printf("Which days does it take place? (e.g., 1 3 4)\n");
  printf("[0] Sunday [1] Monday [2] Tuesday [3] Wednesday [4] Thursday [5] "
         "Friday [6] Saturday\n > ");
  fgets(input, 256, stdin);
  input[strlen(input) - 1] = 0;

  int nDays = 0;
  int day;
  int n;
  for (int i = 0; i < strlen(input); i++) {
    if (isdigit(input[i])) {
      day = input[i] - '0';
      n = schedule[day].nSubjects;
      schedule[day].subjects[n] =
          (char *)malloc((strlen(name) + 1) * sizeof(char));
      strcpy(schedule[day].subjects[n], name);
      schedule[day].nSubjects++;
      nDays++;
    }
  }
}

void removeSubject() {
  char name[256];
  printf("Insert the name of the subject\n > ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = 0;

  for (int i = 0; i < NUM_DAYS; i++) {
    for (int j = 0; j < schedule[i].nSubjects; j++) {
      if (strcmp(name, schedule[i].subjects[j]) == 0) {
        for (int k = j; k < schedule[i].nSubjects; k++) {
          schedule[i].subjects[k] = schedule[i].subjects[k + 1];
        }
        schedule[i].nSubjects--;
      }
    }
  }
}
