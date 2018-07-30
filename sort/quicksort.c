#include <stdlib.h>
#include<stdio.h>
 
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, int lo, int hi) {
  int pivot = arr[hi];
  int i = lo - 1;
  for (int j=lo; j <= (hi-1); j++) {
	if (arr[j] < pivot) {
	  i=i+1;
	  swap(&arr[i], &arr[j]);
	}
  }
  swap(&arr[i+1], &arr[hi]);
  return i+1;

}

void quicksort(int *arr, int lo, int hi) {
  if (lo < hi) {
	int p = partition(arr, lo, hi);
	quicksort(arr, lo, p-1);
	quicksort(arr, p+1, hi);
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
  quicksort(arr, 0, 9);
  for (int i = 0; i < 10; i++) {
	printf("%d, ", arr[i]);
  }
  printf("\n");
  
}
