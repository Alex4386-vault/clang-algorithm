#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STUDENT_COUNT 100
#define MAX_STUDENT_PAY 100000

#define MAX_INTEGER 2147483647

int useUnicode = 1;

// utility functions

int getSum(int* data, int count) {
  int sum = 0;
  for (int i = 0; i < count; i++) {
    sum += data[i];
  }
  
  return sum;
}

int getBaseAverage(int* data, int count) {
  int average = (getSum(data, count) / count);
  return (average / 10) * 10;
}

int getMaxIndex(int* data, int count) {
  int max = 0;
  int index = 0;
  for (int i = 0; i < count; i++) {
    if (max < data[i]) {
      max = data[i];
      index = i;
    }
  }
  
  return index;
}

int getNearestIndex(int value, int* data, int* except, int count) {
  int diff = MAX_INTEGER;
  int nearestIdx = -1;
  for (int i = 0; i < count; i++) {
    if (abs(value - data[i]) < diff && !except[i]) {
      diff = abs(value - data[i]);
      nearestIdx = i;
    }
  }
  
  return nearestIdx;
}

int isProper(int data) {
  return (data / 10) * 10 == data;
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

      int tripStudents = 0;
      fscanf(fp, "%d", &tripStudents);

      if (tripStudents == 0) {
        // Moon Hee-jun plays, I!

        // dum-dum-dum-durudumdum! BREAK!
        // https://youtu.be/hLz6vlCdEFk?t=186
        break;
      }

      int pay[MAX_STUDENT_COUNT] = { 0, };

      for (int i = 0; i < tripStudents; i++) {
        fscanf(fp, "%d", pay+i);
      }

      int sum = getSum(pay, tripStudents);
      int baseAverage = getBaseAverage(pay, tripStudents);
      int leftOvers = sum % baseAverage;

      if (!isProper(leftOvers)) {
        printf("Error, Can not divide properly! Terminating session! leftOvers: %d\n", leftOvers);
        return 0;
      }

      int operationAmount = 0;
      int tempOperation = 0;
      int tempLeftOvers = leftOvers;
      int except[MAX_STUDENT_COUNT] = {0,};

      for (int i = 0; i < tripStudents; i++) {
        int toValue = baseAverage;
        int index;

        if (tempLeftOvers != 0) {
          toValue += 10;
          tempLeftOvers -= 10;
          index = getMaxIndex(pay, tripStudents);
        } else {
          index = getNearestIndex(toValue, pay, except, tripStudents);
        }

        int diff = pay[index] - toValue;
        tempOperation += diff;

        int temp = tempOperation + diff;
        pay[index] = toValue;
        except[index] = 1;

        if (diff > 0) {
          operationAmount += diff;
        }
      }

      char *unicodeWonSymbol = "₩";
      char *cp949WonSymbol = "\\";

      printf("%s%d\n", (useUnicode ? unicodeWonSymbol : cp949WonSymbol) ,operationAmount);
    }

    return 0;
}

