#include <stdio.h>
#include <stdlib.h>

struct tip {
	char name[256];
	char author[256];
	char isbn[18];
};


void view_tip() {

   struct tip tip;
   FILE *file;
   
   if ( (file=fopen("tips.dat","r")) == NULL) {
     printf("No tips\n");
	 return;
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
	//printf("got null isbn");
    return 0;
  }
  int digit;
  int digits[18];
  int index = 0;
  
  for (char* p=isbn; *p; *p++) {
    digit = (int) *p;
    if (digit > 47 && digit < 58) {
      digits[index] = digit;
      index = index + 1;
    }
  }
  if (index != 13) {
	//	printf("not 13 long");
    return 0;
  }
  int total = 0;
  int num = 0;
  for (int i = 1; i <= 12; i++) {
	num = digits[i-1] - '0';
	//	int x = digits[i] - '0';
	//    printf("%i digit: %i\n", i, num);
    total += ((i+1) % 2 == 0) ? num * 1 : num * 3; 
  }
  //printf("Total: %i\n", total);
  int chksum = 10 - (total % 10);
  //printf("cheecksum: %i", chksum);
  if (chksum == 10) {
    chksum = 0;
  }
  num = digits[12] - '0';
  if (num == chksum) {
    return 1;
  } else {
    return 0;
  }
  
}


void add_tip() {
   struct tip tip;
   FILE *file;
   
   if ( (file=fopen("tips.dat","a")) == NULL) {
     printf("Error 1\n");
   }
   char name[256];
   char author[256];
   char isbn[18];
   
   
   printf("Name:\n");
   scanf("%256s", &name);

   printf("Author:\n");
   scanf("%256s", &author);

   printf("ISBN:\n");
   scanf("%18s", &isbn);
   
   if (validate_isbn(isbn)==1) {
   
   } else {
	 printf("Invalid ISBN, try again:\n");
	 scanf("%s", &isbn);	 
   }
   strncpy(&tip.name, &name, 256);
   strncpy(&tip.author, &author, 256);
   strncpy(tip.isbn, isbn, 18);
   //tip.name = name;
   //tip.author = author;
   //tip.isbn = isbn;
   
   fwrite(&tip,sizeof(tip),1, file);
   
   fclose(file);
   return;
}

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
   scanf("%i", &choise);
   fclose(file);
   if ( (file=fopen("tips.dat","r")) == NULL) {
     printf("Error 1\n");
   }

   FILE *tmpfile;
   if ( (tmpfile=fopen("tmp.dat","a")) == NULL) {
     printf("Error 1\n");
   }

   int cur = 1;
   while(1) {
     fread(&tip, sizeof(tip), 1, file);
     if (feof(file)) {
       break;
     }
	 printf("read block %i with data: %s, %s, %s", cur, tip.name, tip.author, tip.isbn);
	 if (cur != choise) {
	     fwrite(&tip,sizeof(tip),1, tmpfile);
	 }
	 cur = cur + 1;
   }
   fclose(tmpfile);
   fclose(file);
    if (remove("tips.dat") == 0) {
   	 rename("tmp.dat", "tips.dat");
   	 printf("removed succesfully\n");
    } else {
   	 printf("could not remove old file\n");
   }   
}




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
