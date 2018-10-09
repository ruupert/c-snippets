#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void insert(struct Tree *tree, int key) {
  if (tree == NULL) {
    // printf("got null size tree\n");
    tree = malloc(sizeof(struct Tree));
    struct Node *newnode = malloc(sizeof(struct Node));
    int *new_key = malloc(sizeof(int));
    struct Node *parent = NULL;
    struct Node *left = NULL;
    struct Node *right = NULL;
    newnode->parent = parent;
    newnode->left = left;
    newnode->right = right;
    new_key = &key;
    newnode->key = *new_key;
    tree->root = newnode;				  
  } else if (tree->root == NULL) {
    // printf("got tree but root node is null\n");
    struct Node *newnode = malloc(sizeof(struct Node));
    struct Node *parent = NULL;
    newnode->parent = parent;
    newnode->key = key;
    tree->root = newnode;
  } else {
    // printf("got tree with atleast the root node\n");
    struct Node *newnode = malloc(sizeof(struct Node));
    newnode->key = key;
    struct Node *x;
    x = tree->root;
    struct Node *p;
    while (x != NULL) {
      p = x;
      if (newnode->key < x->key) {
	x = x->left;	
      } else {
	x = x->right;
      }
    }
    newnode->parent = p;
    if (newnode->key < p->key) {
      p->left = newnode;
    } else {
      p->right = newnode;
    }
  }
}




void delete(struct Tree *tree, struct Node *node) {
  struct Node *ptr = tree->root;
  struct Node *old;
  if (node->left == NULL && node->right == NULL) {
    // no children
    if (node->parent == NULL) {
      ptr = NULL;
    } else {
      old = node->parent;
      if (node == old->left) {
	old->left = NULL;
      } else {
	old->right = NULL;
      }
    }
    return;
  }
  // one child
  struct Node *child;
  if (node->left != NULL) {
    child = node->left;
  } else {
    child = node->right;
  }
  old = node->parent;
  child->parent = old;
  if (old == NULL) {
    tree->root = child;
    return;
  }
  if (node == old->left) {
    old->left = child;
    return;
  } else {
    old->right = child;
    return;
  }
  struct Node *next = min_n(node->right);
  node->key = next->key;
  child = next->right;
  old = next->parent;
  if (old->left == next) {
    old->left = child;
  } else {
    old->right = child;
  }
  if (child != NULL) {
    child->parent = old;
  }
  return;
}

struct Node* search(struct Tree *tree, int key) {
  struct Node *tmp = tree->root;
  while (tmp != NULL && tmp->key != key) {
    if (key < tmp->key) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
    }
  }
  return tmp;
}

struct Node* succ(struct Node *node) {
  struct Node *ptr = node;
  struct Node *ptr2;
  if (ptr->right != NULL)
    return min_n(ptr->right);
  ptr2 = ptr->parent;
  while (ptr2 != NULL && ptr == ptr2->right) {
    ptr = ptr2;
    ptr2 = ptr->parent;
  }
  return ptr2;
}

int min(struct Tree *tree) {
  struct Node *tmp = tree->root;
  while (tmp->left != NULL) {
    tmp = tmp->left;
  }
  return tmp->key;
}
int max(struct Tree *tree) {
  struct Node *tmp = tree->root;
  while (tmp->right != NULL) {
    tmp = tmp->right;
  }
  return tmp->key;
}
struct Node* min_n(struct Node *node) {
  struct Node *tmp = node;
  if (tmp->left == NULL) {
    return tmp;
  }
  while (tmp->left != NULL) {
    tmp = tmp->left;
  }
  return tmp;
}
struct Node* max_n(struct Node *node) {
  struct Node *tmp = node;
  while (tmp->right != NULL) {
    tmp = tmp->right;
  }
  return tmp;
}


int max_depth(struct Node *node) {
  if (node==NULL) {
       return 0;
  } else {
    int l_depth = max_depth(node->left);
    int r_depth = max_depth(node->right);
    
    if (l_depth > r_depth)  {
      return(l_depth+1);
    } else {
      return(r_depth+1);
    }
  }
} 

void shuffle(int *arr, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = arr[j];
      arr[j] = arr[i];
      arr[i] = t;
    }
  }
}

void test_tree(int low_val, int high_val) {
  struct Tree *tr;
  int iterations = 0, sum_height = 0;
  size_t sz = high_val-low_val+1;
  int num_arr1[sz];
  int num_arr2[sz];
  int num_arr3[sz];

  for (int i = 0, v = low_val; i <= high_val; i++, v++) {
    num_arr1[i] = v;
    num_arr2[i] = v;
    num_arr3[i] = v;
  }
  printf("testing three times inserting with values between %i and %i in randomized order:\n", low_val, high_val);
  shuffle(num_arr1,sz); 
  tr = malloc(sizeof(struct Tree));
  for (int i = 0; i < sz; i++) {
    insert(tr, num_arr1[i]);
  }
  printf("\t (1) height: %i\n", max_depth(tr->root));

  shuffle(num_arr2,sz); 
  tr = malloc(sizeof(struct Tree));
  for (int i = 0; i < sz; i++) {
    insert(tr, num_arr2[i]);
  }
  printf("\t (2) height: %i\n", max_depth(tr->root));


  shuffle(num_arr3,sz); 
  tr = malloc(sizeof(struct Tree));
  for (int i = 0; i < sz; i++) {
    insert(tr, num_arr3[i]);
  }
  printf("\t (3) height: %i\n", max_depth(tr->root));
 
}

int compare_trees(struct Tree *tree1, struct Tree *tree2) {
  if (tree1 != NULL && tree2 != NULL) {
	struct Node *node1 = tree1->root;
	struct Node *node2 = tree2->root;
	return compare_nodes(node1, node2);	
  } else {
	return 0;
  }

}

int compare_nodes(struct Node *node1, struct Node *node2) {
  if (node1->key == node2->key) {
	int left = -1;
	int right = -5;
	if (node1->left != NULL && node2->right != NULL) {
	  left = compare_nodes(node1->left, node2->left); 
	} else {
	  return 0;
	}
	if (node1->right != NULL && node2->right != NULL) {
	  right = compare_nodes(node1->right, node2->right);
	} else {
	  return 0;
	}
	if (left == right) {
	  return 1;
	} else {
	  return 0;
	}
	
  } else {
	return 0;
  }
}

/*int main(void) {

  //  test_tree(1,100);
  //test_tree(1,1000);
  //test_tree(1,10000);
  //test_tree(1,100000);
  
  // my testing lines

  struct Tree *tr = malloc(sizeof(struct Tree));
  insert(tr, 5);
  printf("my tree root node key is: %i\n", tr->root->key);
  insert(tr, 4);
  insert(tr, 2);
  insert(tr, 9);
  insert(tr, 1);
  struct Node *ptr = malloc(sizeof(struct Node));
  ptr = search(tr, 2);
  printf("searched 2 and its parent is: %i\n", ptr->parent->key);
  printf("my tree min key is: %i\n", min(tr));
  delete(tr, ptr);
  printf("my tree max key is: %i\n", max(tr));
  ptr = search(tr, 1);
  delete(tr, ptr);
  printf("my tree min key is: %i\n", min(tr));

  printf("show root left node is: %i and its parent: %i\n", tr->root->left->key, tr->root->left->parent->key);
  printf("height: %i", max_depth(tr->root));
  
}
*/

