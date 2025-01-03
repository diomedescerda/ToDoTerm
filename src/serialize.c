#include "../include/modules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void serializeTasks(const char *filename) {
  char filePath[256];

  if (filename[0] == '~') {
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
      perror("Failed to get home directory");
      return;
    }
    snprintf(filePath, sizeof(filePath), "%s%s", homeDir, filename + 1);
  } else {
    strncpy(filePath, filename, sizeof(filePath));
  }

  char dirPath[256];
  strncpy(dirPath, filePath, sizeof(dirPath));
  char *lastSlash = strrchr(dirPath, '/');
  if (lastSlash != NULL) {
    *lastSlash = '\0';

    struct stat st = {0};
    if (stat(dirPath, &st) == -1) {
      if (mkdir(dirPath, 0700) == -1) {
        perror("Failed to create directory");
        return;
      }
    }
  }

  FILE *file = fopen(filePath, "w");
  if (!file) {
    perror("Failed to open file for writing");
    return;
  }

  for (int i = 0; i < taskCount; ++i) {
    fprintf(file, "%d|%d|%s|%d|%d|%d\n", tasks[i].index, tasks[i].ogIndex,
            tasks[i].name, tasks[i].priority, tasks[i].time, tasks[i].isDone);
  }

  fclose(file);
}

void serializeSchedule(const char *filename) {
  char filePath[256];

  if (filename[0] == '~') {
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
      perror("Failed to get home directory");
      return;
    }
    snprintf(filePath, sizeof(filePath), "%s%s", homeDir, filename + 1);
  } else {
    strncpy(filePath, filename, sizeof(filePath));
  }

  char dirPath[256];
  strncpy(dirPath, filePath, sizeof(dirPath));
  char *lastSlash = strrchr(dirPath, '/');
  if (lastSlash != NULL) {
    *lastSlash = '\0';

    struct stat st = {0};
    if (stat(dirPath, &st) == -1) {
      if (mkdir(dirPath, 0700) == -1) {
        perror("Failed to create directory");
        return;
      }
    }
  }

  FILE *file = fopen(filePath, "w");
  if (!file) {
    perror("Failed to open file for writing");
    return;
  }

  for (int i = 0; i < NUM_DAYS; ++i) {
    fprintf(file, "%s|%d", schedule[i].dayName, schedule[i].nSubjects);
    for (int j = 0; j < schedule[i].nSubjects; ++j) {
      fprintf(file, "|%s", schedule[i].subjects[j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

Task *deserializeTasks(const char *filename, size_t *size) {
  char filePath[256];
  if (filename[0] == '~') {
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
      perror("Failed to get home directory");
      return NULL;
    }
    snprintf(filePath, sizeof(filePath), "%s%s", homeDir, filename + 1);
  } else {
    strncpy(filePath, filename, sizeof(filePath));
  }

  FILE *file = fopen(filePath, "r");
  if (!file) {
    perror("Failed to open file for reading");
    return NULL;
  }

  Task *tasks = NULL;
  *size = 0;

  char line[256];

  while (fgets(line, sizeof(line), file)) {
    Task task;
    char *token = strtok(line, "|");
    if (token)
      task.index = atoi(token);

    token = strtok(NULL, "|");
    if (token)
      task.ogIndex = atoi(token);

    token = strtok(NULL, "|");
    if (token)
      strncpy(task.name, token, 256);

    token = strtok(NULL, "|");
    if (token)
      task.priority = atoi(token);

    token = strtok(NULL, "|");
    if (token)
      task.time = atoi(token);

    token = strtok(NULL, "|");
    if (token)
      task.isDone = atoi(token);

    tasks = realloc(tasks, (*size + 1) * sizeof(Task));
    if (!tasks) {
      perror("Failed to allocate memory");
      fclose(file);
      return NULL;
    }
    tasks[*size] = task;
    (*size)++;
  }

  fclose(file);
  return tasks;
}

Day *deserializeSchedule(const char *filename, size_t *size) {
  char filePath[256];
  if (filename[0] == '~') {
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
      perror("Failed to get home directory");
      return NULL;
    }
    snprintf(filePath, sizeof(filePath), "%s%s", homeDir, filename + 1);
  } else {
    strncpy(filePath, filename, sizeof(filePath));
  }

  FILE *file = fopen(filePath, "r");
  if (!file) {
    perror("Failed to open file for reading");
    return NULL;
  }

  Day *days = NULL;
  *size = 0;

  char line[256];

  while (fgets(line, sizeof(line), file)) {
    Day day;
    char *token = strtok(line, "|");
    if (token)
      strncpy(day.dayName, token, 10);

    token = strtok(NULL, "|");
    if (token)
      day.nSubjects = atoi(token);

    for (int i = 0; i < day.nSubjects; i++) {
      token = strtok(NULL, "|\n");
      if (token) {
        day.subjects[i] = malloc(strlen(token) + 1);
        strncpy(day.subjects[i], token, strlen(token));
        day.subjects[i][strlen(token)] = '\0';
      }
    }

    days = realloc(days, (*size + 1) * sizeof(Day));
    if (!days) {
      perror("Failed to allocate memory");
      fclose(file);
      return NULL;
    }
    days[*size] = day;
    (*size)++;
  }

  fclose(file);
  return days;
}
