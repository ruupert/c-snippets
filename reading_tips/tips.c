#include <stdio.h>
#include <stdlib.h>

struct tip {
	char name[256];
	char author[256];
	char isbn[18];
};

void clear() {
    char c;
    while ((c = getchar() != '\n') && (c != EOF));
}


void view_tip() {

   struct tip tip;
   FILE *file;
   
   if ( (file=fopen("tips.dat","r")) == NULL) {
     return;
   }
   if (feof(file)) {
     printf("No tips\n");
	 return;
   }
   while(1) {
     fread(&tip, sizeof(tip), 1, file);
     if (feof(file)) {
       break;
     }
     printf("Tip name: %s\tAuthor: %s\tISBN: %s\n", tip.name, tip.author, tip.isbn);
     
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
 	strncpy(&tip.name, &name, 256);
	strncpy(&tip.author, &author, 256);
	strncpy(tip.isbn, isbn, 18);
  
   } else {
	 printf("Invalid ISBN, try again:\n");
	 scanf("%s", &isbn);	 
   }  

   fwrite(&tip,sizeof(tip),1, file);
	
   fclose(file);
   
   return;
}

void remove_tip() {
   struct tip tip;
   FILE *file;
   char choise;
   int i = 1;
   if ( (file=fopen("tips.dat","r")) == NULL) {
     printf("No tip file\n");
	 return;
   }
   if (feof(file)) {
	 printf("No tips to remove");
	 return;
   }
   
   while(1) {
     fread(&tip, sizeof(tip), 1, file);
     if (feof(file)) {
       break;
     }
     printf("(%i) Tip name %s\tAuthor%s\tISBN: %s\n", i, tip.name, tip.author, tip.isbn);
     i++;
   }
   if (i == 1) {
	 printf("No tips for deletion!\n");
	 return;
   }
	  
   printf("Select the number of the tip you wish to remove:\n");
   clear();
   //scanf("%1s", &choise);
   choise = getchar();
   //   printf("choise %c", choise);
   fclose(file);
   int x = choise - '0';
   
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
	 //	 printf("read block %i with data: %s, %s, %s", cur, tip.name, tip.author, tip.isbn);
	 if (cur != x) {
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

  char choise = 0;
    
  while(1) {
	printf("Choose a function: (V)iew tips. (A)dd a tip, (D)elete a tip, (Q)uit\n");
	choise = (char) getchar();
	//	scanf("%1s", &choise);
    switch(choise) {
    case 'v': case 'V':
	  view_tip();
      break;
    case 'a': case 'A':
	  add_tip();
      break;
    case 'd': case 'D':
      remove_tip();
      break;
    case 'q': case 'Q':
      return 0;
    default:
      printf("Invalid input!\n");
	  break;
    }
	clear();
  }
  return 0;
}
