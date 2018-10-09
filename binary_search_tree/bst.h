#include <stdio.h>


struct Node {
  int key;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
} Node;

struct Tree {
  struct Node *root;
  int height;
} Tree;


//void print(struct Tree *tree, int key);
void insert(struct Tree *tree, int key);
void delete(struct Tree *tree, struct Node *node);
//struct Node* search_recursive(struct Tree *tree, int key);
struct Node* search(struct Tree *tree, int key);
struct Node* succ(struct Node *node);
struct Node* min_n(struct Node *node);
struct Node* max_n(struct Node *node);
int max_depth(struct Node *node);
int compare_trees(struct Tree *tree1, struct Tree *tree2);
int compare_nodes(struct Node *node1, struct Node *node2);
int min(struct Tree *tree);
int max(struct Tree *tree);

