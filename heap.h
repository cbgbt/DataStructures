#ifndef _HEAP_H_
#define _HEAP_H_
#include<stdlib.h>
#include"arraylist.h"

typedef struct heap_type
{
	arraylist_t *heap;
	int (*comparator)(void *, void *);
	int (*inorder)(void *, void *, int (*comparator)(void *, void *));
} heap_t;

// Natural order funcs

// Is a < b?
static int minheap_ordering(void *a, void *b, int (*comparator)(void *, void *))
{
	return comparator(a,b) < 0;
}
// a > b?
static int maxheap_ordering(void *a, void *b, int (*comparator)(void *, void *))
{
	return comparator(a,b) > 0;
}

// Private Members
static void h_percolateDown(heap_t *,int hole);
static void h_percolateUp(heap_t *,int hole);
static void h_swapEl(heap_t *,int el1, int el2);

// Memory Management
heap_t *new_minheap(int (*comparator)(void *, void *));
heap_t *new_maxheap(int (*comparator)(void *, void *));
void   delete_heap(heap_t *heap);

// Public Members
int heap_size(heap_t *heap);
int heap_isEmpty(heap_t *heap);
void heap_clear(heap_t *heap);
void *heap_pop(heap_t *heap);
void *heap_top(heap_t *heap);
void heap_insert(heap_t *heap, void *data);

// Implementation
// Private Members
void h_percolateDown(heap_t *heap, int hole)
{
	int size = heap_size(heap);
	int near = 2 * hole;
	int smallest = hole;
	int left = near+1; int right = near+2;
	void *le = arraylist_get(heap->heap, left);
	void *re = arraylist_get(heap->heap, right);
	void *sme = arraylist_get(heap->heap, hole);
	if (left < size)
	{
		if (heap->inorder(le, sme, heap->comparator))
			smallest = left;
	}
	if (right < size)
	{
		void *sme = arraylist_get(heap->heap, smallest);
		if (heap->inorder(re, sme, heap->comparator))
			smallest = right;
	}
	if (smallest != hole)
	{
		h_swapEl(heap, hole, smallest);
		h_percolateDown(heap, smallest);
	}
}

void h_percolateUp(heap_t *heap, int hole)
{
	void *hle = arraylist_get(heap->heap, hole);
	int cmpi = (hole-1)/2;
	if (cmpi < heap_size(heap))
	{
		void *cmp = arraylist_get(heap->heap, cmpi);
		if (heap->inorder(hle, cmp, heap->comparator))
		{
			h_swapEl(heap, hole, cmpi);
			h_percolateUp(heap, cmpi);
		}
	}
}
inline void h_swapEl(heap_t *heap, int el1, int el2)
{
	void *ela = arraylist_get(heap->heap, el1);
	void *elb = arraylist_get(heap->heap, el2);
	arraylist_set(heap->heap, elb, el1);
	arraylist_set(heap->heap, ela, el2);
}

// Memory Management
heap_t *new_minheap(int (*comparator)(void *, void *))
{
	heap_t *heap = malloc(sizeof(heap_t));
	heap->heap = new_arraylist();
	heap->inorder = minheap_ordering;
	heap->comparator = comparator;
	return heap;
}

heap_t *new_maxheap(int (*comparator)(void *, void *))
{
	heap_t *heap = malloc(sizeof(heap_t));
	heap->heap = new_arraylist();
	heap->inorder = maxheap_ordering;
	heap->comparator = comparator;
	return heap;
}

void   delete_heap(heap_t *heap);

// Public Members
inline int heap_size(heap_t *heap)
{
	return arraylist_size(heap->heap);
}

int heap_isEmpty(heap_t *heap)
{
	return arraylist_isEmpty(heap->heap);
}

void heap_clear(heap_t *heap)
{
	arraylist_clear(heap->heap);
}

void *heap_pop(heap_t *heap)
{
	h_swapEl(heap, 0, heap_size(heap) - 1);
	void *ret = arraylist_remove(heap->heap, heap_size(heap) - 1);
	h_percolateDown(heap, 0);
	return ret;
}

void *heap_top(heap_t *heap)
{
	return arraylist_get(heap->heap, 0);
}

void heap_insert(heap_t *heap, void *data)
{
	arraylist_add(heap->heap, data);
	h_percolateUp(heap, heap_size(heap) - 1);
}
#endif
