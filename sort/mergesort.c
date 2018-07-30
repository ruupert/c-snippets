#include <stdlib.h>
#include <stdio.h>

void printarr(int *arr, int len) {
  for (int i=0; i<len;i++) {
	printf("%d, ", arr[i]);
  }
}

void merge(int *arr, int lo, int mid, int hi) {
  int left_len = mid - lo + 1;
  int right_len = hi - mid;

  
  int *left_arr = malloc(sizeof(int)*left_len);
  int *right_arr = malloc(sizeof(int)*right_len);

  for (int i=0; i < left_len;i++) {
	left_arr[i] = arr[lo+i];
  }
  for (int j=0; j < right_len;j++) {
	right_arr[j] = arr[j + mid + 1];
  }

  printf("< ");

  printarr(left_arr, left_len);
  printf("> < ");
  printarr(right_arr, right_len);
  printf(">\n");


  int i = 0;
  int j = 0;

  for (int k = lo; k <= hi; k++) {
	if (i == left_len) {
	  arr[k] = right_arr[j];
	  j++;
	  continue;
	}
	if (j == right_len) {
	  arr[k] = left_arr[i];
	  i++;
	  continue;
	}
	if (left_arr[i] <= right_arr[j]) {
	  arr[k] = left_arr[i];
	  i++;
	} else {
	  arr[k] = right_arr[j];
	  j++;
	}
	
  }
  free(right_arr);
  free(left_arr);
  
}
void sort(int *arr, int lo, int hi) {
  if (lo < hi) {
	int mid = (hi+lo) / 2;
	int *ptr = arr;
	sort(ptr, lo, mid);
	sort(ptr, mid+1, hi);
	merge(ptr, lo, mid, hi);
  }

}
void mymergesort(int *arr, int len) {
  sort(arr, 0, len-1);
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

  printarr(arr, 10);
  printf("\n");
  mymergesort(arr, 10);
  printarr(arr, 10);
  printf("\n");
  return 0;
}
