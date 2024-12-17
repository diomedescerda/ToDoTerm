#include "../../include/modules.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Day days[NUM_DAYS] = {
    [0] = {.dayName = "Sunday", .nSubjects = 0},
    [1] = {.dayName = "Monday", .nSubjects = 0},
    [2] = {.dayName = "Tuesday", .nSubjects = 0},
    [3] = {.dayName = "Wednesday", .nSubjects = 0},
    [4] = {.dayName = "Thursday", .nSubjects = 0},
    [5] = {.dayName = "Friday", .nSubjects = 0},
    [6] = {.dayName = "Saturday", .nSubjects = 0},
};

void printSchedule() {
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
      n = days[day].nSubjects;
      days[day].subjects[n] = (char *)malloc((strlen(name) + 1) * sizeof(char));
      strcpy(days[day].subjects[n], name);
      days[day].nSubjects++;
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
