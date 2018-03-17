#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include "list.h"
#include"queue.h"
#include<stdbool.h>





Queue *new_queue(){
	List *queue =new_list();
	return queue;
}


void free_queue(Queue *queue){
	free_list(queue);
}
void *queue_enqueue(Queue *queue, int data){
	 list_add_end(queue, data);
	 return 0;
}
int queue_dequeue(Queue *queue){
	return list_remove_start(queue);
}
int queue_size(Queue *queue){
	return list_size(queue);
}
bool queue_is_empty(Queue *queue){
	return list_is_empty(queue);
}



















