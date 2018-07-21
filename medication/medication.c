/*
Reseptin uusintalaskuri

Laskee reseptin uusintap‰iv‰m‰‰r‰n..


1. ottaa tietoja l‰‰kkeist‰

Error 1 = Can't write into the specified file. 
*/
#include <stdio.h>


#define DATAFILE medication.dat
struct medication {
	//FILE *DATAFILE;
	char drug[30];
	int qty, per_day_qty;
	double prescription_date;

};



/* View medications ----------------------------- */

void view_med() {

   struct medication medicine;
	FILE *file;

	if ( (file=fopen("medication.dat","r")) == NULL) {
		printf("Error 1\n");
	}
  
   while(!feof(file)) {
   
   fread(&medicine, sizeof(medicine), 1, file);
	printf("Medicine name %s \t Quantityt %d\n", medicine.drug, medicine.qty);
   }

   fclose(file);
}

/* Add medications ----------------------------- */

void add_med() {
   struct medication medicine;
	FILE *file;

	if ( (file=fopen("medication.dat","a")) == NULL) {
		printf("Error 1\n");
	}
   printf("Medicine name?\n");
   scanf("%s", &medicine.drug);

   printf("Quantity?\n");
   scanf("%d", &medicine.qty);

   printf("Per day maximium usage?\n");
   scanf("%d", &medicine.per_day_qty);

/*   printf("Prescription date?\n");
   scanf("%lf", &prescription_date); */

   fwrite(&medicine,sizeof(medicine),1, file);

   fclose(file);
}

/* Remove medications ----------------------------- */

void remove_med() {
 //	struct medication medicine;
	FILE *file;

	if ( (file=fopen("medication.dat","a")) == NULL) {
		printf("Error 1\n");
	}

fclose(file);
}



/* Main program */


int main(void) {

  //	struct medication medicine;

	int choice;
	printf("Drug prescription manager v0.1b\nChoose a function\n1 View medicines\n2 Add a medicine\n3 Remove a medicine\n4 Quit\n");
	scanf("%d", &choice);
	fflush(stdin);
	
	if (choice<=4) {
	  
	  if (choice>0) {
	    switch(choice) {
	    case 1:view_med();break;
	    case 2:add_med();break;
	    case 3:remove_med();break;
	    case 4:break;
	    default:printf("A value must be specified\n");
	    }
	  } else {
	    printf("Value too low\n");
	  }
	} else {
	  printf("Value too high\n");
   }
	return 0;
}
