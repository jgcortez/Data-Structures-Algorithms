#ifndef _heap_h
#define _heap_h 1

#include <stdio.h>

typedef struct TAG_ELEMENT {
	int key;
}ELEMENT;

typedef ELEMENT* ElementT;

typedef struct TAG_HEAP {
	int capacity; /* max size of the heap */
	int size; /* current size of the heap */
	ElementT* elements; /* pointer to pointers to elements */
}HEAP;


HEAP* heapInit(int capacity);

void heapPrint(HEAP* H);

void PercUp(HEAP* H, int pos);

void PercDown(HEAP* H, int pos);

#endif // !_heap_h
