#include <stdlib.h>


void bubblesort(int *arr, int len) {
  int n = len;
  int newn, tmp;
  while (n > 0) {
	newn = 0;
	for (int i = 1; i < n; i++) {
		if(arr[i-1] > arr[i]) {
		  tmp = arr[i-1];
		  arr[i-1] = arr[i];
		  arr[i] = tmp;
		  newn = i;
		}
	  }
	n = newn;
	
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
  arr[0] = 1;
  for (int i = 0; i < 10; i++) {
	printf("%d, ", arr[i]);
  }
  printf("\n");
  bubblesort(arr, 10);
  for (int i = 0; i < 10; i++) {
	printf("%d, ", arr[i]);
  }
  printf("\n");
  
}
