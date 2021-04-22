#ifndef _heap_h
#define _heap_h 1

#include <stdio.h>
#include "graph.h"


typedef struct TAG_ELEMENT{
    int vertex;
    float key;  //Changed int to float
}ELEMENT;

typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP{
    int capacity;       // max size of the heap
    int size;           // current size of the heap
    pELEMENT *H;      // array of pointers to elements
}HEAP;

void heapFree(HEAP *heap);

HEAP *heapInit(int capacity);

void heapPrint(HEAP *heap);

void MovingUp (HEAP *heap, int pos);

pELEMENT DeleteMin (HEAP *heap, int *flag, int *count_Heapify)


//void Insert(HEAP , ELEMENT); //edit
//heapInit
//DeleteMIn