#include "../../include/modules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_DAYS 7
#define MAX_SUBJECTS 12
#define MAX_SUBJECT_LENGTH 30

typedef struct {
  char dayName[10];
  char *subjects[15];
  int nSubjects;
} Day;

Day days[NUM_DAYS] = {
    [0] = {.dayName = "Sunday", .nSubjects = 0},
    [1] = {.dayName = "Monday", .nSubjects = 0},
    [2] = {.dayName = "Tuesday", .nSubjects = 0},
    [3] = {.dayName = "Wednesday", .nSubjects = 0},
    [4] = {.dayName = "Thursday", .nSubjects = 0},
    [5] = {.dayName = "Friday", .nSubjects = 0},
    [6] = {.dayName = "Saturday", .nSubjects = 0},
};

void printDay() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int d = tm.tm_wday;
  int end = NUM_DAYS;

  for (int i = d; i < end; i++) {
    printf("%s\n", days[i].dayName);
    for (int j = 0; j < days[i].nSubjects; j++) {
      printf("  - %s\n", days[i].subjects[j]);
    }

    if (i == NUM_DAYS - 1 && d != 0) {
      i = -1;
      end = d;
    }
  }
}

void addSubject(const char *name, int day) {
  int n = days[day].nSubjects;
  days[day].subjects[n] = (char *)malloc((strlen("Math") + 1) * sizeof(char));
  strcpy(days[day].subjects[n], name);
  days[day].nSubjects++;
}

void removeSubject(const char *name) {
  for (int i = 0; i < NUM_DAYS; i++) {
    for (int j = 0; j < days[i].nSubjects; j++) {
      if (strcmp(name, days[i].subjects[j]) == 0) {
        for (int k = j; k < days[i].nSubjects; k++) {
          days[i].subjects[k] = days[i].subjects[k + 1];
        }
        days[i].nSubjects--;
      }
    }
  }
}
