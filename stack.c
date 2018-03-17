//new_stack, free_stack, stack_push, stack_pop,
//and stack_size,
#include<stdbool.h>
#include "list.h"
#include "stack.h"
#include<stdlib.h>

Stack *new_stack(){
    List *s=new_list() ;
    return s;
}
		
void free_stack(Stack *stack){
	free_list(stack);
}
void stack_push(Stack *stack, int data){
	list_add_start(stack, data);
	
}
int stack_pop(Stack *stack){
	return list_remove_start(stack);
}
int stack_size(Stack *stack){
	return list_size(stack);
}
bool stack_is_empty(Stack *stack){
	return list_is_empty(stack);
}

