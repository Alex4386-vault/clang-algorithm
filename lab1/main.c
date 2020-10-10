#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PANCAKE 1000
#define MAX_INT 0x7FFFFFFF

typedef struct Pancake {
  int weight;
  int withstandWeight;
  int isPancakeWithstandItsWeight;
  int stackable;
} Pancake;

int copyPancakes(Pancake *origin, Pancake *destination, int count) {
  for (int i = 0; i < count; i++) {
    destination[i].weight = origin[i].weight;
    destination[i].withstandWeight = origin[i].withstandWeight;
    destination[i].isPancakeWithstandItsWeight = origin[i].isPancakeWithstandItsWeight;
    destination[i].stackable = origin[i].stackable;
  }
}

int getMaxStack(Pancake *pancakes, int count, int maxWeight) {
  Pancake *tmpPancakes = (Pancake *)malloc(sizeof(Pancake) * count);
  copyPancakes(pancakes, tmpPancakes, count);

  int idx = -1;
  int maxStack = -1;

  for (int i = 0; i < count; i++) {
    if (tmpPancakes[i].stackable) {

      int thisPancakeMax = tmpPancakes[i].withstandWeight - tmpPancakes[i].weight;
      int mostBottomPancakeMax = maxWeight - tmpPancakes[i].weight;

      int minMax = thisPancakeMax > mostBottomPancakeMax ? mostBottomPancakeMax : thisPancakeMax;

      if (thisPancakeMax > 0 && mostBottomPancakeMax > 0 && tmpPancakes[i].stackable) {
        tmpPancakes[i].stackable = 0;

        int stack = getMaxStack(tmpPancakes, count, minMax);
        if (stack > maxStack) {
          idx = i;
          maxStack = stack;
        }

        tmpPancakes[i].stackable = 1;
      } else {
        tmpPancakes[i].stackable = 0;
      }
    }
  }

  return (idx >= 0) ? maxStack + 1 : 0;
}

int main() {
    int isDebug = 0;
    
    FILE *fp;
    
    if (isDebug) {
      fp = stdin;
    } else {
      fp = fopen("input.txt", "r");
    }

    Pancake pancakes[MAX_PANCAKE] = { {0, }, };
    int count = 0;

    while (!feof(fp)) {
      fscanf(fp, "%d %d", &(pancakes[count].weight), &(pancakes[count].withstandWeight));
      count++;
      fscanf(fp, " ");
    }

    for (int i = 0; i < count; i++) {
      int weight = pancakes[i].weight;
      int withstandWeight = pancakes[i].withstandWeight;

      pancakes[i].stackable = (withstandWeight > weight) ? 1 : 0;
    }

    printf("%d\n", getMaxStack(pancakes, count, MAX_INT));
    return 0;
}
