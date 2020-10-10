#include <stdio.h>
#include <stdlib.h>

#define MAX_PANCAKE_PER_LINE 30
#define MAX_PANCAKE_DIAMETER_STRLEN 10
#define MAX_CHAR_LINE (MAX_PANCAKE_PER_LINE * MAX_PANCAKE_DIAMETER_STRLEN)

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void flip(int pancakes[], int pancakeHeight, int i) {
    if (i == 0) return;
    if (i > 1) {
        return flip(pancakes, pancakeHeight - (i - 1), 1);
    }

    int swapCount = pancakeHeight / 2;
    for (int i = 0; i < swapCount; i++) {
        swap(pancakes+i, pancakes+(pancakeHeight - i)-1);
    }

    return;
}

int findFlipIndex(int pancakes[], int pancakeHeight) {
    int maxPancakeDiameter = 0;
    int maxPancakeDiameterIndex = 0;
    for (int i = 0; i < pancakeHeight; i++) {
        if (pancakes[i] >= maxPancakeDiameter) {
            maxPancakeDiameter = pancakes[i];
            maxPancakeDiameterIndex = i;
        }
    }

    if (pancakeHeight - 1 == maxPancakeDiameterIndex) {
        return findFlipIndex(pancakes, pancakeHeight - 1) + 1;
    } else if (maxPancakeDiameterIndex == 0 || pancakes[0] == maxPancakeDiameter) {
        return 1;
    } else {
        return (pancakeHeight - maxPancakeDiameterIndex);
    }
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    while (!feof(fp)) {
        char lineBuffer[MAX_CHAR_LINE] = {0,};
        int pancakes[MAX_PANCAKE_PER_LINE] = {0,};

        if (!fgets(lineBuffer, MAX_CHAR_LINE, fp)) {
            break;
        }

        char *currentBufferLocation = lineBuffer;
        int pancakeHeight = 0;

        while (*currentBufferLocation != '\n' && *currentBufferLocation != 0) {
            int value = strtol(currentBufferLocation, &currentBufferLocation, 10);
            printf("%d ", value);

            pancakes[pancakeHeight++] = value;
        }

        printf("\n");

        while (findFlipIndex(pancakes, pancakeHeight)) {
            int wa = findFlipIndex(pancakes, pancakeHeight);
            if (wa >= pancakeHeight) {
                printf("0\n");
                break;
            }
            
            printf("%d ", wa);
            flip(pancakes, pancakeHeight, wa);
        }
    }
}
