#include <stdio.h>                                                                                             
#include <stdlib.h>                                                                                            
#include "linkedlist.h"                                                                                         
node* create_node(int value) {
  node *tmp = malloc(sizeof(node));
  tmp->next = NULL;
  tmp->value = value;
  return tmp;

}

list* create_list(void) {
  list *tmp = malloc(sizeof(list));
  tmp->count = 0;
  tmp->first = NULL;
  tmp->last = NULL;
  return tmp;
}

void print(list *lptr) {
  node *n = lptr->first;
  printf("---\n");
  while (n) {
    printf("%i\n", n->value);
    n = n->next;
  }
}

int insert(list *L, node *nodepos, int value) {
  if (L == NULL) {
    return -1;
  }
  if (L->first == NULL && L->last == NULL) {
    // printf("got a list with no elements");
    node *tmp = create_node(value);
    L->count += 1;
    L->last = tmp;
    L->first = tmp;
    return 0;
  } else {
    if (nodepos == NULL) {
      // replace first and attach tail to the snake head
      node *tmp = L->first;
      node *new = create_node(value);
      new->next = tmp;
      L->first = new;
      L->count += 1;
      return 0;
    } else {
      // find the position and replace
      if (nodepos->value == L->first->value) {
	node *tmp = L->first;
	node *tmp2;
	node *new = create_node(value);
	tmp2 = tmp->next;
	new->next = tmp2;
	if (new->next == NULL) {
	  L->last = new;
	}
	tmp->next = new;
	L->count += 1;
	return 0;
      }
      if (nodepos->value == L->last->value) {
	node *tmp = L->last;
	node *tmp2;                                                                                
	node *new = create_node(value);                                                           
        tmp2 = tmp->next;                                                                               
        new->next = tmp2;                                                                               
        tmp->next = new;                                                                                
        L->last = new;                                                                                  
        L->count += 1;                                                                                  
        return 0;                                                                                       
      }                                                                                                   

      node *tmp = L->first;                                                                          
      node *new = create_node(value);                                                               
      node *tmp2;                                                                                    

      while (tmp->next != NULL) {                                                                         
	if (tmp->next->value == nodepos->value) {                                                             
	  tmp2 = tmp->next;                                                                           
          new->next = tmp2;                                                                           
	  tmp->next = new;
          L->count += 1;                                                                              
          return 0;                                                                                   
	}                                                                                               
      }                                                                                                   
    }
  }
  return 0;
}

int delete(list *L, node *p) {
  if (L == NULL) {
    return 1;
  }
  if (p == L->first && L->count == 1) {
    return 1;
  }
  if (L->first == NULL) {
    return 1;
  }
  if (L == NULL) {
    return -1;
  }

  if (L->first == NULL && L->last == NULL) {
    L->count = 0;
    return 0;
  } else {
    if (p == NULL) {
      // replace first and attach tail to the snake head. 
      if (L->first != L->last) {
	node *tmp = L->first->next;
	L->first = tmp;
	L->count -= 1;
      } else {
	L->first = NULL;
	L->last = NULL;
	L->count = 0;
      }
      return 0; 
    } else {
      // find the position and replace
      if (p == L->first) {
	node *tmp = L->first; 
	node *tmp2 = tmp->next;
	L->count -= 1;
	if (tmp2->next == NULL) {
	  tmp->next = NULL;
	  L->last = tmp; 
	  L->first = tmp;
	} else {
	  tmp->next = tmp2->next;
	  L->first = tmp;
	} 
	return 0; 
      } 
      node *tmp = L->first;
      node *tmp2;

      while (tmp->next != NULL) {
	if (tmp->next->value == p->value) {
	  if (tmp->next->next == NULL) {
	    tmp->next = NULL;
	    L->count -= 1;
	    L->last = tmp;
	  } else {
	    tmp2 = tmp->next->next;
	    tmp->next = tmp2;
	    L->count -= 1;
	  }
	  return 0;
	}
      }
    }
  }
  return 0;
}

list* merge(list *L1, list *L2) {

  list *list = create_list();
  
  if ((L1->first) == NULL && (L2->first) == NULL) {
    return list;
  }
  if ((L1->first) == NULL && (L2->first) != NULL) {
    return L2;
  }
  if ((L1->first) != NULL && (L2->first) == NULL) {
    return L1;
  }
  
  node *l1 = L1->first;
  node *l2 = L2->first;

  while (l1->next != NULL) {
    if (l1->value == l2->value && list->first == NULL) {
      // first element exception
      insert(list, NULL, l1->value);
    } else if (l1->value < l2->value && list->first == NULL) {
      insert(list, NULL, l1->value);
      insert(list, list->last, l2->value);
    }
    if (l1->value == l2->value) {
      // first element exception
      insert(list, list->last, l1->value);
    } else if (l1->value < l2->value) {
      insert(list, list->last, l1->value);
      insert(list, list->last, l2->value);
    }
    l1 = l1->next;
    l2 = l2->next;
  }                                                                                                           
  
  return list;

}


int main() {
  list *tlist1, *tlist2;
  tlist1 = create_list();
  //  tlist2  = create_list();
  if (tlist1 == NULL) return 0;
  //  if (tlist2 == NULL) return 0;
  if (insert(tlist1, NULL, 1) == 0) {
    for (int i = 2; i < 8; i++) {
      insert(tlist1, NULL, i);
      printf("added %i to list\n", i);
    }
    delete(tlist1, tlist1->first);
    return 0;
  } else {
    return -1;
  }
  return 0;
}
