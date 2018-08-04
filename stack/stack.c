#include <stdio.h>
#include <stdlib.h>

struct Stack {
  int size;
  int *arr;
  int top;
};

struct Stack* create_stack(int size) {
  int *arr = malloc(sizeof(int)*size);
  struct Stack *new = malloc(sizeof(struct Stack));
  new->arr = arr;
  new->size = size;
  new->top = 0;
  return new;
}

void destroy_stack(struct Stack *stack) {
  free(stack);
}

int push(struct Stack *stack, int val) {
  if (stack->top < stack->size) {
	stack->arr[stack->top] = val;
	stack->top += 1;
	return 0;
  } else {
	return 1;
  }
}

int pop(struct Stack *stack) {
  if (stack->top == 0) {
	return -1;
  } else {
	stack->top -= 1;
	return stack->arr[stack->top];
  }
}

int main(void) {
  struct Stack *s = create_stack(10);
  push(s, 1);
  printf("pop should be 1: %d, pop should be -1: %d", pop(s), pop(s));
  push(s, 2);
  push(s, 3);
  push(s, 4);
  push(s, 5);
  push(s, 6);
  push(s, 7);
  push(s, 8);
  push(s, 9);
  push(s, 10);
  push(s, 11);
  push(s, 12);
  printf("pop should be 11: %d ", pop(s));
}
