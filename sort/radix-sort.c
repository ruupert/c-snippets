#include <stdlib.h>
#include <stdio.h>

struct PunchCard {
  int *r1;
  int *r2;
  int *r3;
};


/* LOL punchcard lol lol lol whoops */
void radixIsort(struct PunchCard p, int col, int len) {
 
  int *ptr;
  switch(col) {
  case 2:
	ptr = p.r3;
	break;
  case 1:
	ptr = p.r2;
	break;
  case 0:
	ptr = p.r1;
	break;
  }

  
  int i, x, y, z;

  for (int j = 1; j < len; j++) {
	x=ptr[j];
	if (col == 2) {
	  y=p.r2[j];
	  z=p.r1[j];
	}
	if (col == 1) {
	  y=p.r3[j];
	  z=p.r1[j];
	}
	if (col == 0) {
	  y=p.r3[j];
	  z=p.r2[j];
	}
	
	i = j-1;
	while ( i > 0 && ptr[i] > x ) {
	  ptr[i+1] = ptr[i];
	  if (col == 2) {
		p.r2[i+1] = p.r2[i];
		p.r1[i+1] = p.r1[i];
	  }
	  if (col == 1) {
		p.r3[i+1] = p.r3[i];
		p.r1[i+1] = p.r1[i];
	  }
	  if (col == 0) {
		p.r3[i+1] =	p.r3[i];
		p.r2[i+1] = p.r2[i];
	  }
	  i = i - 1;
	}
	ptr[i+1] = x;
	if (col == 2) {
	  p.r2[i+1] = y;
	  p.r1[i+1] = z;
	}
	if (col == 1) {
	  p.r3[i+1] = y;
	  p.r1[i+1] = z;
	}
	if (col == 0) {
	  p.r3[i+1] = y;
	  p.r2[i+1] = z;
	}
  }
}


void radixSort(int *r1, int *r2, int *r3, int len) {
  struct PunchCard punch;
  punch.r1 = r1;
  punch.r2 = r2;
  punch.r3 = r3;
  radixIsort(punch,2,len);
  radixIsort(punch,1,len);
  radixIsort(punch,0,len);
  
}

int main(void) {

  // my punch card split in three rows
  
  int *r1 = malloc(sizeof(int)*10);
  int *r2 = malloc(sizeof(int)*10);
  int *r3 = malloc(sizeof(int)*10);
  r1[0] = 0; r2[0] = 9; r3[0] = 7;
  r1[1] = 1; r2[1] = 2; r3[1] = 3;
  r1[2] = 8; r2[2] = 2; r3[2] = 7;
  r1[3] = 3; r2[3] = 1; r3[3] = 3;
  r1[4] = 2; r2[4] = 2; r3[4] = 3;
  r1[5] = 5; r2[5] = 2; r3[5] = 1;
  r1[6] = 2; r2[6] = 1; r3[6] = 5;
  r1[7] = 5; r2[7] = 0; r3[7] = 8;
  r1[8] = 6; r2[8] = 4; r3[8] = 2;
  r1[9] = 1; r2[9] = 5; r3[9] = 1;

  for (int i = 0; i < 10; i++) {
	printf("%d%d%d, ", r1[i],r2[i],r3[i]);
  }
  printf("\n");
  radixSort(r1,r2,r3, 10);
  for (int i = 0; i < 10; i++) {
	printf("%d%d%d, ", r1[i],r2[i],r3[i]);
  }
  printf("\n");
  
}
