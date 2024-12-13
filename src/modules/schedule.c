#include "../../include/modules.h"
#include <stdio.h>
#include <time.h>

#define NUM_DAYS 7
#define MAX_SUBJECTS 12
#define MAX_SUBJECT_LENGTH 30

char day[NUM_DAYS][10] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                          "Friday", "Saturday", "Sunday"};

char **subjects[NUM_DAYS];

void printDay() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int d = tm.tm_wday - 1;

  printf("Today is :");
  for (int i = d; i < 7; i++) {
    printf("%s\n", day[i]);
  }
  for (int j = 0; j < d; j++) {
    printf("%s\n", day[j]);
  }
}
