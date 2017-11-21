typedef struct node {
  int value;
  struct node *next;
} node;

typedef struct head {
  int count;
  node *first;
  node *last;
} list;

list* create_list(void);
node* create_node(int value);
int insert(list *lptr, node *nptr, int value);
int delete(list *lptr, node *nptr);
list* merge(list *L1, list *L2);
void print(list *lptr);
