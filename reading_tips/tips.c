#include <stdio.h>


#define DATAFILE tips.dat
struct tip {
	char name[256];
	char author[256];
	char isbn[18];
};



/* View tips ----------------------------- */

void view_tip() {

   struct tip tip;
   FILE *file;
   
   if ( (file=fopen("tips.dat","r")) == NULL) {
     printf("Error 1\n");
   }
   
   while(1) {
     fread(&tip, sizeof(tip), 1, file);
     if (feof(file)) {
       break;
     }
     printf("Tip name %s\tAuthor%s\tISBN: %s\n", tip.name, tip.author, tip.isbn);
     
   }

   fclose(file);
}

int validate_isbn(char* isbn) {
  if (isbn == NULL) {
    return 0;
  }
  int digit;
  int digits[18];
  int index = 0;
  char* p;
  for (p=isbn; *p; p++) {
    digit = (int) p;
    if (digit > 47 && digit < 58) {
      digits[index] = digit;
      index = index + 1;
    }
  }
  if (index != 13) {
    return 0;
  }
  int total = 0;
  for (int i = 1; i < 12; i++) {
    printf("digit: %i\n", digits[i]);
    total += ((i - 1) % 2 == 0) ? digits[i] * 1 : digits[i] * 3; 
  }
  int chksum = 10 - (total % 10);
  if (chksum == 10) {
    chksum = 0;
  }
  if (digits[12] == chksum) {
    return 1;
  } else {
    return 0;
  }
  
}


/* Add tips ----------------------------- */

void add_tip() {
   struct tip tip;
   FILE *file;
   
   if ( (file=fopen("tips.dat","a")) == NULL) {
     printf("Error 1\n");
   }
   
   printf("Name:\n");
   scanf("%s", &tip.name);

   printf("Author:\n");
   scanf("%s", &tip.author);

   printf("ISBN:\n");
   scanf("%s", &tip.isbn);
   if (validate_isbn(tip.isbn)==1) {
   
     // while not valid isbn ask for isbn again

     fwrite(&tip,sizeof(tip),1, file);
   }
   
   fclose(file);
   return;
}

/* Remove tips ----------------------------- */

void remove_tip() {
   struct tip tip;
   FILE *file;
   int choise;
   int i = 1;
   if ( (file=fopen("tips.dat","r")) == NULL) {
     printf("Error 1\n");
   }
   
   while(1) {
     fread(&tip, sizeof(tip), 1, file);
     if (feof(file)) {
       break;
     }
     printf("(%i) Tip name %s\tAuthor%s\tISBN: %s\n", i, tip.name, tip.author, tip.isbn);
     i++;
   }

	  
   printf("Select the number of the tip you wish to remove:\n");
   scanf("%d", &choise);
   
   fclose(file);
}



/* Main program */


int main(void) {

  int choise;
  
  while (1) {
    printf("Choose a function\n1 View tips\n2 Add a tip\n3 Remove a tip\n4 Quit\n");
    scanf("%d", &choise);
    switch(choise) {
    case 1:
      view_tip();
      break;
    case 2:
      add_tip();
      break;
    case 3:
      remove_tip();
      break;
    case 4:
      return 0;
    default:
      printf("A value must be specified\n");
    }
  }
  return 0;
}
