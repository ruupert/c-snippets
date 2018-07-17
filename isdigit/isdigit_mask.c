#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int isdigit_mask(int c) {
  int digits[128];
  digits[(int) '0']=1;
  digits[(int) '1']=1;
  digits[(int) '2']=1;
  digits[(int) '3']=1;
  digits[(int) '4']=1;
  digits[(int) '5']=1;
  digits[(int) '6']=1;
  digits[(int) '7']=1;
  digits[(int) '8']=1;
  digits[(int) '9']=1;
  if (digits[c] == 1) {
    return 1;
  }  else {
    return 0;
  }
  

}


int main() {

  
  int i, j;

  for (i=0; i < 25000000; i++) {
    for (j=33; j<127; j++) {
      isdigit_mask(j);
    }
  }
}
