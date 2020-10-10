#include <stdio.h>
#include <stdlib.h>

struct ElephantIQPseudoMap {
  int weight;
  int iq;
};

typedef struct ElephantIQPseudoMap ElephantIQPseudoMap;

void makeOffset(int *data, int offset, int length) {
  for (int i = length - 1; i >= offset; i--) {
    *(data+i) = *(data+i-offset);
  }

  for (int i = 0; i < offset; i++) {
    *(data+i) = 0;
  }
}

int howManyContent(int *data, int length) {
  int i = 0;
  for (i = 0; i < length; i++) {
    if (data[i] < 0) {
      return i;
    }
  }
  
  return length;
}

void initialize(int *data, int length) {
  for (int i = 0; i < length; i++) {
    data[i] = -1;
  }
}

int* countNearestInadequateElephantMap(ElephantIQPseudoMap *map, int idx, const int length) {
  int baseWeight = map[idx].weight;
  int baseIq = map[idx].iq;

  int* data = (int *)malloc(sizeof(int) * length);
  if (data == NULL) exit(1);
  initialize(data, length);

  int max = 0;

  for (int i = 0; i < length; i++) {
    if (baseWeight < map[i].weight && baseIq > map[i].iq) {
      int *wa = countNearestInadequateElephantMap(map, i, length);
      int thisMax = howManyContent(wa, length);

      if (thisMax > max) {
        free(data);
        data = wa;
        max = thisMax;
      }
    }
  }

  makeOffset(data, 1, length);
  data[0] = idx;

  return data;
}

#define MAX_INPUTS 20

int main() {
  FILE *fp = fopen("input.txt", "r");

  
  int length = 0;
  ElephantIQPseudoMap wa[MAX_INPUTS] = {{0,},};

  while (!feof(fp)) {
    fscanf(fp, "%d %d", &(wa[length].weight), &(wa[length].iq));
    length++;
  }

  /* ElephantIQPseudoMap wa[MAX_INPUTS] = {{1000,2000},{500,3000},{100,4000},{2000,4000}};
  int length = 4;
 */
  int *data = NULL;

  for (int i = 0; i < length; i++) {
    if (data == NULL) {
      data = countNearestInadequateElephantMap(wa, i, length);
    } else {
      int *tmp = countNearestInadequateElephantMap(wa, i, length);
      if (howManyContent(tmp, length) >= howManyContent(data, length)) {
        free(data);
        data = tmp;
      }
    }
  }

  printf("%d\n", howManyContent(data, length));
  for (int i = 0; i < howManyContent(data, length); i++) {
    printf("%d\n", data[i]+1);
  }

  free(data);
  return 0;
}
