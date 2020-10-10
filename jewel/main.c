#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_COUNT 1000
#define MAX_COMMISSION_DEADLINE 1000
#define MAX_COMMISSION_FINE 10000

typedef struct Commission {
  int workDay;
  int finePerDay;
  int completeDay;
} Commission;

int isCommissionComplete(Commission *commissions, int length) {
  int complete = 1;

  for (int i = 0; i < length; i++) {
    complete = (commissions[i].completeDay > 0) && complete;
  }

  return complete;
}

int calculateFine(Commission *commissions, int length) {
  int sum = 0;

  for (int i = 0; i < length; i++) {
    if (commissions[i].completeDay > 0) {
      sum += commissions[i].finePerDay * ( commissions[i].completeDay - 1);
    }
  }

  return sum;
}


void findCommissions(int days, Commission *commissions, int length) {
  if (isCommissionComplete(commissions, length)) return;

  int idx = -1;
  int minFine = 0;

  int originalFine = 0;
  for (int i = 0; i < length; i++) {
    if (commissions[i].completeDay <= 0) {
      int tmp = commissions[i].completeDay;
      commissions[i].completeDay = days + commissions[i].workDay;
      int fine = calculateFine(commissions, length);
      if (fine < minFine || idx < 0) {
        idx = i;
        minFine = fine;
      }
      commissions[i].completeDay = tmp;
    } else {
    }
  }

  if (idx < 0) {

    return;
  } else {
    int dayAfterCompletion = days + commissions[idx].workDay;
    commissions[idx].completeDay = dayAfterCompletion;
    printf("%d ", idx + 1);

    return findCommissions(dayAfterCompletion, commissions, length);
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

    int count = -1;
    fscanf(fp, "%d", &count);
    fscanf(fp, " ");

    for (int i = 0; i < count; i++) {
      int commissionsCount = -1;

      fscanf(fp, "%d", &commissionsCount);
      fscanf(fp, " ");
      
      Commission* commissions = NULL;
      commissions = (Commission *)malloc(sizeof(Commission) * commissionsCount);

      for (int i = 0; i < commissionsCount; i++) {
        commissions[i].completeDay = 0;
        fscanf(fp, "%d %d", &(commissions[i].workDay), &(commissions[i].finePerDay));
      }

      findCommissions(0, commissions, commissionsCount);
      free(commissions);
    }

    return 0;
}

