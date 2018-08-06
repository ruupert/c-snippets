typedef struct node {
  char key;
  struct node *next;
  struct node *childs;
  struct node *parent;
} node;

typedef struct head {
  int count;
  node *next;
} list;


list* create_list(void);
node* create_node();
int insert(node *n, char *str);
//int delete(list *lptr);
//void print(list *L);
