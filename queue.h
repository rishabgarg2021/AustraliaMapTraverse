#include<stdbool.h>
#include "list.h"
typedef struct list Queue;
//creates a new queue and return a pointer to it
Queue *new_queue();
//destroy a queue and free its memory
void free_queue(Queue *queue);
//adds an element to the end of queue always
void *queue_enqueue(Queue *queue, int data);
//removes an element from the staert of the queue
int queue_dequeue(Queue *queue);
//returns the number of elements in queue
int queue_size(Queue *queue);
//returns whether the queue contains no element or some elements
bool queue_is_empty(Queue *queue);


