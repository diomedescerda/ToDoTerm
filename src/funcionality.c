#include "../include/modules.h"
#include <string.h>

int found = -1;

void quickSort();
void qs(int lo, int hi);
int partition(int lo, int hi);

void addTodo(const char *name, int priority, int time) {
  tasks[taskCount].index = taskCount + 1;
  tasks[taskCount].ogIndex = taskCount + 1;
  strncpy(tasks[taskCount].name, name, 255);
  tasks[taskCount].name[255] = '\0';
  tasks[taskCount].priority = priority;
  tasks[taskCount].time = time;
  tasks[taskCount].isDone = 0;

  taskCount++;
}

void removeTodo(int id) {
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i].index == id) {
      found = i;
      break;
    }
  }

  if (found != -1) {
    for (int i = found; i < taskCount - 1; i++) {
      tasks[i] = tasks[i + 1];
      tasks[i].index--;
    }
    taskCount--;
  }
}

void markDone(int id) {
  found = -1;
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i].index == id) {
      tasks[i].isDone = 1;
      break;
    }
  }
}

void markUndone(int id) {
  found = -1;
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i].index == id) {
      tasks[i].isDone = 0;
      break;
    }
  }
}

void markUndoneAll() {
  for (int i = 0; i < taskCount; i++) {
    tasks[i].isDone = 0;
  }
}

void updateIndexAsQueue() {
  for (int i = 0; i < taskCount; i++) {
    tasks[i].index = tasks[i].ogIndex;
  }

  taskMode = 'Q';
  quickSort();
}

void updateIndexByTime() {
  int newIndex = 1;
  char periods[] = {'M', 'A', 'E', 'N'};

  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < taskCount; i++) {
      if (tasks[i].time == periods[j]) {
        tasks[i].index = newIndex++;
      }
    }
  }

  taskMode = 'T';
  quickSort();
}

void updateIndexByPriority() {
  int newIndex = 1;
  char priorities[] = {'H', 'M', 'L'};

  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < taskCount; i++) {
      if (tasks[i].priority == priorities[j]) {
        tasks[i].index = newIndex++;
      }
    }
  }

  taskMode = 'P';
  quickSort();
}

void quickSort() { qs(0, taskCount - 1); }

void qs(int lo, int hi) {
  if (lo >= hi) {
    return;
  }

  int pivotIdx = partition(lo, hi);
  qs(lo, pivotIdx - 1);
  qs(pivotIdx + 1, hi);
}

int partition(int lo, int hi) {
  Task pivot = tasks[hi];
  int idx = lo - 1;

  for (int i = lo; i < hi; i++) {
    if (tasks[i].index <= pivot.index) {
      idx++;
      Task tmp = tasks[i];
      tasks[i] = tasks[idx];
      tasks[idx] = tmp;
    }
  }

  idx++;
  tasks[hi] = tasks[idx];
  tasks[idx] = pivot;

  return idx;
}
