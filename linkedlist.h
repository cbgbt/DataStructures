#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include<stdlib.h>

typedef struct llnode_type
{
	struct llnode_type *next;
	struct llnode_type *prev;
	void *data;
} lnode_t;

typedef struct linkedlist_type
{
	lnode_t *front;
	lnode_t *back;
	int size;
} llist_t;

typedef struct linkedlistiterator_type
{
	llist_t *over;
	lnode_t *prev;
	lnode_t *next;
	char last;
} lliterator_t;

// linked list
// Memory management
llist_t *new_llist();
void delete_llist(llist_t *list);
// Member functions
void llist_addFront(llist_t *list, void* data);
void llist_addBack(llist_t *list,void *data);
void *llist_getFront(llist_t *list);
void *llist_getBack(llist_t *list);
void llist_removeFront(llist_t *list);
void llist_removeBack(llist_t *list);
void llist_clear(llist_t *list);

// linked list iterator
// Memory management
lliterator_t *llist_iterator(llist_t *list);
lliterator_t *llist_iteratorFront(llist_t *list);
lliterator_t *llist_iteratorBack(llist_t *list);
void delete_lliterator(lliterator_t *iter);
// Member functions
int lliterator_hasNext(lliterator_t *iter);
int lliterator_hasPrev(lliterator_t *iter);
void *lliterator_next(lliterator_t *iter);
void *lliterator_prev(lliterator_t *iter);
void lliterator_set(lliterator_t *iter, void *data);
void lliterator_add(lliterator_t *iter, void *data);
void lliterator_remove(lliterator_t *iter);

lnode_t *new_lnode(void *toHold)
{
	lnode_t *node = malloc(sizeof(lnode_t));
	node->data = toHold;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

llist_t *new_llist()
{
	llist_t *list = malloc(sizeof(llist_t));
	list->front = new_lnode(NULL);
	list->back = new_lnode(NULL);
	list->front->next = list->back;
	list->back->prev = list->front;
	list->size = 0;
	return list;
}

void delete_llist(llist_t *list)
{
	lnode_t *ptr = list->front;
	lnode_t *nxt;
	while (ptr != list->back)
	{
		nxt = ptr->next;
		free(ptr);
		ptr = nxt;
	}
	free(ptr);
}


// Member functions
void llist_addFront(llist_t *list, void* data)
{
	lnode_t *node = new_lnode(data);
	node->prev = list->front;
	node->next = list->front->next;
	node->next->prev = node;
	list->front->next = node;
	list->size++;
}

void llist_addBack(llist_t *list, void *data)
{
	lnode_t *node = new_lnode(data);
	node->next = list->back;
	node->prev = list->back->prev;
	list->back->prev = node;
	node->prev->next = node;
	list->size++;
}

void *llist_getFront(llist_t *list)
{
	return list->front->next->data;
}

void *llist_getBack(llist_t *list)
{
	return list->back->prev->data;
}

void llist_removeFront(llist_t *list)
{
	lnode_t *node = list->front->next;
	if (list->size > 0)
	{
		list->front->next = node->next;
		node->next->prev = list->front;
		free(node);
		list->size--;
	}
}

void llist_removeBack(llist_t *list)
{
	lnode_t *node = list->back->prev;
	if (list->size > 0)
	{
		list->back->prev = node->prev;
		node->prev->next = list->back;
		free(node);
		list->size--;
	}
}
void llist_clear(llist_t *list)
{
	delete_llist(list);
	list = new_llist();
}

// linked list iterator
// Memory management

lliterator_t *llist_iterator(llist_t *list)
{
	return llist_iteratorFront(list);
}

lliterator_t *llist_iteratorFront(llist_t *list)
{
	lliterator_t *itr = malloc(sizeof(lliterator_t));
	itr->prev = list->front;
	itr->next = list->front->next;
	itr->last = 'o';
	itr->over = list;
	return itr;
}

lliterator_t *llist_iteratorBack(llist_t *list)
{
	lliterator_t *itr = malloc(sizeof(lliterator_t));
	itr->prev = list->back->prev;
	itr->next = list->back;
	itr->last = 'o';
	itr->over = list;
	return itr;
}

void delete_lliterator(lliterator_t *iter)
{
	free(iter);
}

// Member functions
int lliterator_hasNext(lliterator_t *iter)
{
	return iter->next != iter->over->back;
}

int lliterator_hasPrev(lliterator_t *iter)
{
	return iter->prev != iter->over->front;
}

void *lliterator_next(lliterator_t *iter)
{
	iter->prev = iter->next;
	iter->next = iter->next->next;
	iter->last = 'p';
	return iter->prev->data;
}

void *lliterator_prev(lliterator_t *iter)
{
	iter->next = iter->prev;
	iter->prev = iter->prev->prev;
	iter->last = 'n';
	return iter->next->data;
}

void lliterator_set(lliterator_t *iter, void *data)
{
	switch(iter->last)
	{
		case 'n':
			iter->next->data = data;
			break;
		case 'p':
			iter->prev->data = data;
			break;
	}
}

void lliterator_add(lliterator_t *iter, void *data)
{
	lnode_t *node = new_lnode(data);
	switch(iter->last)
	{
		case 'n':
			node->next = iter->next;
			node->prev = iter->prev;
			iter->next->prev = node;
			iter->prev->next = node;
			iter->next = node;
			break;
		case 'p':
			node->next = iter->next;
			node->prev = iter->prev;
			iter->next->prev = node;
			iter->prev->next = node;
			iter->prev = node;
			break;
		default:
			free(node);
	}
	iter->last = 'o';
}

void lliterator_remove(lliterator_t *iter)
{
	lnode_t *node;
	if (iter->last != 'o')
	{
		if (iter->last == 'n')
		{
			node = iter->next;
			iter->next = node->next;
		}
		else
		{
			node = iter->prev;
			iter->prev = node->prev;
		}
		node->next->prev = node->prev;
		node->prev->next = node->next;
		free(node);
	}
	iter->last= 'o';
}
#endif
