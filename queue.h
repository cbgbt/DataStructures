#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "linkedlist.h"

typedef struct queue_type
{
	llist_t *list;
} queue_t;

// Memory management
queue_t *new_queue();
void delete_queue(queue_t *queue);

//// Member functions
void queue_enqueue(queue_t *queue, void *data);
void *queue_dequeue(queue_t *queue);
void *queue_getFront(queue_t *queue);
int queue_isEmpty(queue_t *queue);
int queue_size(queue_t *queue);
void queue_clear(queue_t *queue);

// Implementation
queue_t *new_queue()
{
	queue_t *queue = malloc(sizeof(queue_t));
	queue->list = new_llist();
	return queue;
}

void delete_queue(queue_t *queue)
{
	delete_llist(queue->list);
	free(queue);
}

void queue_enqueue(queue_t *queue, void *data)
{
	llist_addBack(queue->list, data);
}

void *queue_getFront(queue_t *queue)
{
	return llist_getFront(queue->list);
}

void *queue_dequeue(queue_t *queue)
{
	void *data = llist_getFront(queue->list);
	llist_removeFront(queue->list);
	return data;
}

int queue_isEmpty(queue_t *queue)
{
	return queue->list->size == 0;
}

int queue_size(queue_t *queue)
{
	return queue->list->size;
}

void queue_clear(queue_t *queue)
{
	llist_clear(queue->list);
}
#endif
