#include <stdlib.h>
#include <stdio.h>

void isort(int *arr, int len) {
  int i, x;
  
  for (int j = 1; j < len; j++) {
	x=arr[j];
	i = j-1;
	while ( i > 0 && arr[i] > x ) {
	  arr[i+1] = arr[i];
	  i = i - 1;
	  
	}
	arr[i+1] = x;
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
  isort(arr, 10);
  for (int i = 0; i < 10; i++) {
	printf("%d, ", arr[i]);
  }
  printf("\n");
  
}
