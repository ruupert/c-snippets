#include <stdlib.h>
#include <stdio.h>

void countingsort(int *arr, int max, int len) {
  int *cnt = malloc(sizeof(int)*10);
  int x, y;
  for (int i = 0; i < max; i++) {	cnt[i] = 0; }

  for (int j = 1; j < len; j++) {
	x = arr[j];
	cnt[x] = cnt[x]+1;
  }
  y = 1;
  for (int i = 0; i < max; i++) {
	for (int j = 1; j <= cnt[i]; j++) {
	  arr[y] = i;
	  y = y+1;
	}
  }
  
}

int main(void) {
  int *arr = malloc(sizeof(int)*10);
  arr[0] = 1;
  arr[1] = 4;
  arr[2] = 9;
  arr[3] = 5;
  arr[4] = 2;
  arr[5] = 6;
  arr[6] = 8;
  arr[7] = 8;
  arr[8] = 9;
  arr[9] = 1;
  for (int i = 0; i < 10; i++) {
	printf("%d, ", arr[i]);
  }
  printf("\n");
  countingsort(arr, 10, 10);
  for (int i = 0; i < 10; i++) {
	printf("%d, ", arr[i]);
  }
  printf("\n");
  
}
