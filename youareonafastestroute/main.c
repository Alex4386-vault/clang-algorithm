#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// YOU ARE ON THE FASTEST AVAILABLE ROUTE

void makeOffset(int *data, int offset, int length) {
  for (int i = length - 1; i >= offset; i--) {
    *(data+i) = *(data+i-offset);
  }

  for (int i = 0; i < offset; i++) {
    *(data+i) = 0;
  }
}

int howManyContent(int *data, int length) {
  if (data == NULL) return 0;

  int i = 0;
  for (i = 0; i < length; i++) {
    if (data[i] < 0) {
      return i;
    }
  }
  
  return length;
}

int getDataSum(int *data, int length) {
  if (data == NULL) return 0;

  int j = 0;
  for (int i = 0; i < length; i++) {
    if (data[i] < 0) {
      return j;
    } else {
      j += data[i];
    }
  }
  
  return j;
}

int *makeCopy(int *data, int length) {
  if (data == NULL) return 0;

  int *a = (int *)malloc(sizeof(int) * length);

  for (int i = 0; i < length; i++) {
    a[i] = data[i];
  }
  
  return a;
}

struct CountMatrixData {
  int count;
  int* route;
};

struct CountMatrixData *getCountMatrixData(int **matrix, struct CountMatrixData **countMatrix, int row, int column, int maxRow, int maxColumn) {
  if (column < 0) {
    return NULL;
  }

  int maxSize = maxRow * maxColumn;

  row = (row + maxRow) % maxRow;

  // check is it precalculated:
  if (countMatrix[row][column].count < 0) {
    int *route = (int *)malloc(sizeof(int) * (maxRow * maxColumn));
    for (int i = 0; i < maxRow * maxColumn; i++) {
      route[i] = -1;
    }

    int temp = -1;
    int offsetTemp = 0;

    for (int offset = -1; offset <= 1; offset++) {
      struct CountMatrixData *thisTemp = getCountMatrixData(matrix, countMatrix, row + offset, column - 1, maxRow, maxColumn);
      if (!thisTemp) continue;

      int count = thisTemp->count + matrix[row][column];
      
      if (temp < 0 || count < temp) {
         temp = count;
         offsetTemp = offset;

         free(route);
         route = thisTemp->route;
      }
    }

    countMatrix[row][column].count = temp;
    route = makeCopy(route, maxRow * maxColumn);
    makeOffset(route, 1, maxRow * maxColumn);

    route[0] = matrix[row][column];

    countMatrix[row][column].route = route;
  }



  return &(countMatrix[row][column]);
}

int main() {
  FILE *fp = fopen("input.txt", "r");
  //FILE *fp = stdin;

  if (fp == NULL) {
    printf("File I/O Error\n");
    exit(1);
  }

  int loop = 2;

  for (int i = 0; i < loop; i++) {
    int row = -1;
    int column = -1;

    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &column);

    int **matrix;
    struct CountMatrixData **countMatrix;

    matrix = (int **)malloc(sizeof(int *) * row);
    countMatrix = (struct CountMatrixData **)malloc(sizeof(struct CountMatrixData *) * row);

    if (!matrix) exit(1);

    for (int i = 0; i < row; i++) {
      matrix[i] = (int *)malloc(sizeof(int) * column);
      countMatrix[i] = (struct CountMatrixData *)malloc(sizeof(struct CountMatrixData) * column);
      if (!matrix[i]) exit(1);
      if (!countMatrix[i]) exit(1);

      for (int j = 0; j < column; j++) {
        matrix[i][j] = -1;
        countMatrix[i][j].count = -1;
        countMatrix[i][j].route = (int *)malloc(sizeof(int) * (row * column));
      }
    }

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++) {
        fscanf(fp, "%d", &(matrix[i][j]));
      }
    }

    int maxLength = row * column;
    struct CountMatrixData *data = getCountMatrixData(matrix, countMatrix, row - 1, column - 1, row, column);

    int length = howManyContent(data->route, maxLength);
    int sum = 0;
    for (int i = length - 1; i >= 0; i--) {
      printf("%d ", data->route[i]);
      sum += data->route[i];
    }
    printf("\n%d\n", sum);

    for (int i = 0; i < row; i++) {
      free(matrix[i]);
      free(countMatrix[i]);
    }
    free(matrix);
    free(countMatrix);
  }
}
