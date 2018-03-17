//new_stack, free_stack, stack_push, stack_pop,
//and stack_size,
#include "list.h"
#include<stdbool.h>
typedef struct list Stack;
//creates new stack and return pointer to it.
Stack *new_stack();
//destroy a stack and free its memory
void free_stack(Stack *stack);
//adds an element to the front of stack everytime.
//this is O(1)
void stack_push(Stack *stack, int data);
//pops an element from front of the stack everytime 
//this is O(1).
int stack_pop(Stack *stack);
//returns number of elements contained in a stack
int stack_size(Stack *stack);
bool stack_is_empty(Stack *stack);

