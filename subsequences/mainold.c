#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_STR_LENGTH 10000
#define MAX_SUBSTR_LENGTH 100

const int copyCost = 5;
const int insertCost = 10;
const int deleteCost = 10;

// http://www.siafoo.net/snippet/75#:~:text=fgetstr()%20is%20a%20function,fgets%20is%20safe%20to%20use.&text=14%7D-,fgetstr()%20is%20a%20function%20that%20mimics%20the%20behavior%20of,of%20line%20if%20it%20exists.
char *fgetstr(char *string, int n, FILE *stream) {

 	char *result;
 	result = fgets(string, n, stream);

 	if (result == NULL) {
 		return(result);
  }

	if (string[strlen(string) - 1] == '\n') {
		string[strlen(string) - 1] = 0;
  }

	return string;
}

int getMatrix(int **matrix, char *str, char *substr, int matrixStrIdx, int matrixSubstrIdx) {
  if (matrixStrIdx < 0 || matrixSubstrIdx < 0) {
    return 0;
  }

  if (matrix[matrixStrIdx][matrixSubstrIdx] < 0) {
    if (matrixStrIdx == 0 || matrixSubstrIdx == 0) {
      if (matrixStrIdx == 0) {
        matrix[matrixStrIdx][matrixSubstrIdx] = insertCost * matrixSubstrIdx;
      } else {
        matrix[matrixStrIdx][matrixSubstrIdx] = deleteCost * matrixSubstrIdx;
      }
    } else {
      int strIdx = matrixStrIdx - 1;
      int substrIdx = matrixSubstrIdx - 1;

      int isCopyPossible = 0;
      if (strIdx >= 0 && substrIdx >= 0) {
        if (str[strIdx] == substr[substrIdx]) {
          isCopyPossible = 1;
        }
      }

      int copyBase = getMatrix(matrix, str, substr, matrixStrIdx - 1, matrixSubstrIdx - 1) + copyCost;
      int insertBase = getMatrix(matrix, str, substr, matrixStrIdx, matrixSubstrIdx - 1) + insertCost;
      int deleteBase = getMatrix(matrix, str, substr, matrixStrIdx - 1, matrixSubstrIdx) + deleteCost;

      int lowestCost = 0;

      if (insertBase <= deleteBase) {
        lowestCost = insertBase;
      } else {
        lowestCost = deleteBase;
      }

      if (isCopyPossible) {
        if (copyBase <= lowestCost) {
          lowestCost = copyBase;
        }
      }

      matrix[matrixStrIdx][matrixSubstrIdx] = lowestCost;
    }
  }
  
  return matrix[matrixStrIdx][matrixSubstrIdx];
}

int main() {
  FILE *fp = fopen("input.txt", "r");
  //FILE *fp = stdin;

  if (fp == NULL) {
    printf("File I/O Error\n");
    exit(1);
  }

  int loop = -1;
  fscanf(fp, "%d", &loop);
  fscanf(fp, " ");

  for (int i = 0; i < loop; i++) {
    char mainString[MAX_STR_LENGTH] = {0, };
    char subString[MAX_SUBSTR_LENGTH] = {0, };
    fgetstr(mainString, MAX_STR_LENGTH, fp);
    fgetstr(subString, MAX_SUBSTR_LENGTH, fp);

    int strLength = strlen(mainString);
    int substrLength = strlen(subString);

    int matrixColumnCount = strLength + 1;
    int matrixRowCount = substrLength + 1;

    int** distanceMatrix;
    distanceMatrix = (int **)malloc(sizeof(int *) * matrixColumnCount);
    if (!distanceMatrix) exit(1);

    for (int i = 0; i < matrixColumnCount; i++) {
      distanceMatrix[i] = (int *)malloc(sizeof(int) * matrixRowCount);
      if (!distanceMatrix[i]) exit(1);

      for (int j = 0; j < matrixRowCount; j++) {
        distanceMatrix[i][j] = -1;
      }
    }

    int cost = getMatrix(distanceMatrix, mainString, subString, strLength, substrLength);
    printf("%d\n", cost);

    for (int i = 0; i < strLength; i++) {
      free(distanceMatrix[i]);
    }
    free(distanceMatrix);
  }
}
