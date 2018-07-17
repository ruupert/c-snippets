#include <ctype.h>
#include <stdio.h>

int main() {
  
  int i, j;
  for (i=0; i < 25000000; i++) {
    for (j=33; j<127; j++) {
      isdigit(j);
    }
  }
}
