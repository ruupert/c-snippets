#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "radix.h"                                                                                         


node* create_node() {
  node *tmp = malloc(sizeof(node));
  tmp->next = NULL;
  tmp->childs = NULL;
  tmp->parent = NULL;
  tmp->key = '\0';
  //  tmp->key = c;
  return tmp;

}

list* create_list(void) {
  list *tmp = malloc(sizeof(list));
  tmp->count = 0;
  tmp->next = malloc(sizeof(node));
  return tmp;
}

int find_char(node *n, char c) {
  printf("\t enter find_char() %c\n", c);
  if (n == NULL) {
	printf("\t - node null\n");
	return 0;
  }
  node* tmp = n;
  do {
	if (tmp->key == c) {
	  return 1;
	} 
	if (tmp->next != NULL) {
	  tmp = tmp->next;
	}
  } while (tmp->next != NULL);

  
  return 0;
}

int find(node *n, char* str) {
  int len = strlen(str);
  node *ptr = n;
  int found;
  for (int i = 0; i < len; i++) {
	found = 0;
	while(ptr->next != NULL) {
	  printf("%c == %c\n", ptr->key, str[i]);
	  if (ptr->key == str[i]) {
		ptr = ptr->childs;
		found = 1;
		break;
	  } else {
		ptr = ptr->next;
	  }
	}
	if (found == 0) {
	  return 0;
	}
  }
  return 1;
}


int insert(node *n, char *str) {
  node *ptr = n;
  node *last = NULL; // since we are in the "head"
  int found;
  for (int i=0; i < strlen(str); i++) {
	found = 0;
	//   	printf("%d,%c, ",i, str[i]);
	if (ptr->key == '\0') {
	  ptr->key = str[i];
	  ptr->next = create_node();
	  ptr->childs = create_node();
	  ptr->childs->parent = ptr;
	  last = ptr;
	  ptr = ptr->childs;
	} else {
	  while (ptr->next != NULL) {
		if (ptr->key == str[i]) {
		  last = ptr;
		  ptr = ptr->childs;
		  found = 1;
		  break; // while loop
		} else {
		  ptr = ptr->next;
		}
	  }
	  if (found == 0) {
		ptr->next = create_node();
		ptr->key = str[i];
		ptr->childs = create_node();
		ptr->childs->parent = last;
		last = ptr;
		ptr = ptr->childs;
	  } 
	}
	
  }
  // printf("\n");
  return 0;
}

char* spaces(int count) {
  char* res = malloc(sizeof(char)*(count+1));
  int i = 0;
  for (; i < count; i++) {
	res[i] = ' ';
  }
  res[i+1] = '\0';
  return res;
}

void print(node *no, int lvl) {
  node *ptr = no;
  node *tmp;
  while (ptr->next != NULL) {
	printf("%c",  ptr->key);
	if (ptr->childs != NULL) {
	  tmp = ptr->childs;
	  if (tmp->key != '\0') {
		printf(" ( " );
		print(tmp, lvl+1);
		printf(" ) ");
	  }
	}
	ptr = ptr->next;
  }
}


int main() {
  list *tree;
  tree = create_list();
  FILE *fp = fopen("words.txt", "r");
  char* buf = malloc(sizeof(char)*128);
  if (!fp) {
	return 0;
  }
  char c;
  size_t i = 0;
	
  while ((c = getc(fp)) != EOF) {
	//	printf("%d, ", i);
	//printf("%c",c);
	if (c == '\n') {
	  char* str = malloc(sizeof(char)*(i));
	  for (size_t j = 0; j < i-1; j++) {
		str[j] = buf[j];
	  }
	  str[i] = '\0';
	  free(buf);
	  char* buf = malloc(sizeof(char)*128);
	  //printf("%s\n", str);
	  
	  insert(tree->next, str);
	  i = 0;
	} else {
	  buf[i] = c;
	  //printf("%c", c);
	  i++;
	}
  
  }
  fclose(fp);


  int res = find(tree->next, "beer");
  printf("found %d", res);
  printf("done, sleeping for 5 secs\n");
  sleep(5);

  //if (tree == NULL) return 0;
  //node *tmp = tree->next;
  
  
  /*  insert(tmp, "jopas");
  insert(tmp, "jotain");
  insert(tmp, "jokin");
  insert(tmp, "jokinen");
  insert(tmp, "jotakuta");
  insert(tmp, "jopa");
  insert(tmp, "jokin");
  */
  print(tree->next, 0);
  return 0;
}
