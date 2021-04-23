#ifndef _heap_h
#define _heap_h 1

#include <stdio.h>
#include "graph.h"

typedef struct TAG_ELEMENT{
    int vertex;
    float key;      // Float instead of int for format
}ELEMENT;

typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP{
    int capacity;       // max size of the heap
    int size;           // current size of the heap
    pELEMENT *H;        // array of pointers to elements
}HEAP;

void heapFree(HEAP *heap);

HEAP *heapInit(int capacity);

void heapPrint(HEAP *heap);

void MovingUp (HEAP *heap, int pos);

pELEMENT DeleteMin (HEAP *heap, int *flag, int *count_Heapify);

void MovingDown(HEAP *heap, int pos, int *flag, int *count_Heapify);

void BuildHeap(HEAP *heap, int *flag);

int Insert(HEAP *heap, pELEMENT item);

int DecreaseKey (HEAP *heap, int pos, int newKey);

// Helpers

int left(int i);

int right(int i);

void exchange(HEAP *heap, int &a, int &b);

#endif
