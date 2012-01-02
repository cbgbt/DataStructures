#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

typedef struct arraylist_type
{
	void **data;
	int capacity;
	int size;
} arraylist_t;

// Memory management
arraylist_t *new_arraylist();
arraylist_t *new_arraylistWithSize(int initialcapacity);
void delete_arraylist(arraylist_t *list);

// Member functions
void  arraylist_add(arraylist_t *arr, void *data);
void  arraylist_addAt(arraylist_t *arr, void *data, int index);
void  arraylist_clear(arraylist_t *arr);
void *arraylist_get(arraylist_t *arr, int index);
int   arraylist_isEmpty(arraylist_t *arr);
void *arraylist_remove(arraylist_t *arr, int index);
void  arraylist_set(arraylist_t *arr, void *data, int index);
int   arraylist_size(arraylist_t *arr);
void  arraylist_trimToSize(arraylist_t *arr);

// Implementation
// Memory management
arraylist_t *new_arraylist()
{
	arraylist_t *arr = malloc(sizeof(arraylist_t));
	arr->capacity = 10;
	arr->size = 0;
	arr->data = malloc(sizeof(void *) * arr->capacity);
	return arr;
}

arraylist_t *new_arraylistWithSize(int initialcapacity)
{
	arraylist_t *arr = malloc(sizeof(arraylist_t));
	arr->capacity = initialcapacity;
	arr->size = 0;
	arr->data = malloc(sizeof(void *) * arr->capacity);
	return arr;
}

void delete_arraylist(arraylist_t *list)
{
	free(list->data);
	free(list);
}

static void arinccap(arraylist_t *arr)
{
	int i;
	if (arr->capacity < 2)
		arr->capacity += 2;
	arr->capacity = (int) (arr->capacity * 1.5);
	void **data = malloc(sizeof(void *) * arr->capacity);
	for (i = 0; i < arr->size; i++)
		data[i] = arr->data[i];
	free(arr->data);
	arr->data = data;
}

static void arboundchck(arraylist_t *arr)
{
	if (arr->size == arr->capacity)
		arinccap(arr);
}

// Member functions
void  arraylist_add(arraylist_t *arr, void *data)
{
	arboundchck(arr);
	arr->data[arr->size++] = data;
}

void  arraylist_addAt(arraylist_t *arr, void *data, int index)
{
	arboundchck(arr);
	int i;
	for (i = arr->size; i > index; i--)
		arr->data[i] = arr->data[i-1];
	arr->data[index] = data;
	arr->size++;
}

void  arraylist_clear(arraylist_t *arr)
{
	arr->size = 0;
}
void *arraylist_get(arraylist_t *arr, int index)
{
	return (arr->data)[index];
}

int   arraylist_isEmpty(arraylist_t *arr)
{
	return arr->size == 0;
}

void *arraylist_remove(arraylist_t *arr, int index)
{
	int i;
	arr->size--;
	void *data = arr->data[index];
	for (i = index; i < arr->size; i++)
		arr->data[i] = arr->data[i+1];
	return data;
}

void  arraylist_set(arraylist_t *arr, void *data, int index)
{
	arr->data[index] = data;
}

inline int   arraylist_size(arraylist_t *arr)
{
	return arr->size;
}

void  arraylist_trimToSize(arraylist_t *arr)
{
	if (arr->capacity > arr->size)
	{
		int i;
		void **data = malloc(sizeof(void *) * arr->size);
		for (i = 0; i < arr->size; i++)
			data[i] = arr->data[i];
		free(arr->data);
		arr->data = data;
	}
}

#endif
