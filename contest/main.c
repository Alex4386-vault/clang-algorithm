#include <stdio.h>

int main() {
  FILE *fp;
  fp = fopen("input.txt", "r");

  if (fp == NULL) {
    // get out!
    exit(1);
  }

  
}
