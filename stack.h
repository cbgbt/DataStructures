#ifndef _STACK_H_
#define _STACK_H_
#include "linkedlist.h"

typedef struct stack_type
{
	llist_t *list;
} stack_t;

// Memory management
stack_t *new_stack();
void delete_stack(stack_t *stack);

//// Member functions
void stack_push(stack_t *stack, void *data);
void *stack_pop(stack_t *stack);
void *stack_getTop(stack_t *stack);
int stack_isEmpty(stack_t *stack);
int stack_size(stack_t *stack);
void stack_clear(stack_t *stack);

// Implementation
// Memory management
stack_t *new_stack()
{
	stack_t *stack = malloc(sizeof(stack_t));
	stack->list = new_llist();
	return stack;
}

void delete_stack(stack_t *stack)
{
	delete_llist(stack->list);
	free(stack);
}

//// Member functions
void stack_push(stack_t *stack, void *data)
{
	llist_addBack(stack->list, data);
}

void *stack_pop(stack_t *stack)
{
	void *data = llist_getBack(stack->list);
	llist_removeBack(stack->list);
	return data;
}

void *stack_getTop(stack_t *stack)
{
	return llist_getBack(stack->list);
}

int stack_isEmpty(stack_t *stack)
{
	return stack->list->size == 0;
}

int stack_size(stack_t *stack)
{
	return stack->list->size;
}

void stack_clear(stack_t *stack)
{
	llist_clear(stack->list);
}

#endif
