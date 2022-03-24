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

//====================================================
//		Project 2
//====================================================

void writeHeap(HEAP* H);

void insert(HEAP* H, ElementT element);

void extractMin(HEAP* H, int f);

void decreaseKey(HEAP* H, int index, int value);

void minHeapify(HEAP* H, int index, int &count);

void buildHeap(HEAP* H, int f);

int LEFT(int left);

int RIGHT(int right);

void EXCHANGE(int &a, int &b);

int PARENT(int index);
#endif // !_heap_h
