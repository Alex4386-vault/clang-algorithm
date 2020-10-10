#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_JEWELS 1000

#define MAX_COST 1000
#define MAX_JEWELS_PER_BOX 1000

#define BOX_COUNT 2

typedef struct Box {
  int jewelsPerBox;
  int cost;
} Box;

int recursiveBoxPacker(int leftJewels, Box* boxes, int *boughtBox) {
  if (leftJewels < 0) {
    return 0;
  } else if (leftJewels == 0) {
    return 1;
  }

  double boxEffeciency[BOX_COUNT] = { -1.0, };

  for (int i = 0; i < BOX_COUNT; i++) {
    boxEffeciency[i] = boxes[i].jewelsPerBox / (double) boxes[i].cost;
    if (leftJewels % boxes[i].jewelsPerBox == 0) {
      boxEffeciency[i] += 1000;
    }
  }

  int idx = -1;
  double highestEffeciency = 0;
  for (int i = 0; i < BOX_COUNT; i++) {
    if (idx < 0 || highestEffeciency < boxEffeciency[i]) {
      idx = i;
      highestEffeciency = boxEffeciency[i];
    }
  }

  if (idx >= 0) {
    boughtBox[idx]++;
    return recursiveBoxPacker(leftJewels - boxes[idx].jewelsPerBox, boxes, boughtBox);
  } else {
    return 0;
  }
}

// the main
int main() {
    int isDebug = 0;
    
    FILE *fp;
    
    if (isDebug) {
      fp = stdin;
    } else {
      fp = fopen("input.txt", "r");
    }

    while (1) {

      int leftJewels = 0;
      fscanf(fp, "%d", &leftJewels);

      if (leftJewels == 0) {
        // Moon Hee-jun plays, I!

        // dum-dum-dum-durudumdum! BREAK!
        // https://youtu.be/hLz6vlCdEFk?t=186
        break;
      }

      Box boxes[BOX_COUNT] = { {-1, -1}, };
      double boxEffeciency[BOX_COUNT] = { -1, };

      int boughtBox[BOX_COUNT] = { 0, };

      for (int i = 0; i < BOX_COUNT; i++) {
        fscanf(fp, "%d %d", &(boxes[i].cost), &(boxes[i].jewelsPerBox));
      }

      int success = recursiveBoxPacker(leftJewels, boxes, boughtBox);
      
      if (success) {
        for (int i = 0; i < BOX_COUNT; i++) {
          printf("%d ", boughtBox[i]);
        }
      } else {
        printf("failed");
      }
      printf("\n");
    }

    return 0;
}

