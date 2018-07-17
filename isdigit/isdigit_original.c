#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int check_digit (char c) {
	return (c>='0') && (c<='9');
}

int main() {
  
  int i, j;
  for (i=0; i < 25000000; i++) {
    for (j=33; j<127; j++) {
      check_digit(j);
    }
  }
}
