#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "heap.h"
#include "graph.h"

extern VERTEX *V;
//----------------------------------------------
// heapFree                                    P
//----------------------------------------------
void heapFree(HEAP *heap)
{
    free(heap->H);
    free(heap);
}

//----------------------------------------------
// heapInit
//----------------------------------------------
HEAP *heapInit(int capacity)
{
    HEAP *heap;
    heap = (HEAP *)calloc(1, sizeof(HEAP *));
    heap->capacity = capacity;
    heap->size = 0;

    heap->H = (pELEMENT *)calloc(capacity + 1, sizeof(pELEMENT *));
    return heap;
}

//----------------------------------------------
// heapPrint                                   P
//----------------------------------------------

void heapPrint(HEAP *heap)
{
    int i; //guess
    printf("capacity=%d, size=%d\n", heap->capacity, heap->size);
    for (i = 1; i < heap->size; i++)
    {
        printf("%f, ", heap->H[i]->key);
    }
    if (heap->size > 0)
    {
        printf("%f\n, ", heap->H[heap->size]->key);
    }
    // printf("END heapPrint\n");
}

//----------------------------------------------
// MovingUp                                    P
//----------------------------------------------
void MovingUp(HEAP *heap, int pos)
{
    pELEMENT temp;
    int parent;

    // print ("BGN MovingUp\n");
    parent = pos / 2;
    if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key)
    {
        temp = heap->H[pos];
        heap->H[pos] = heap->H[parent];
        heap->H[parent] = temp;
        V[heap->H[pos]->vertex].pos = pos;          // Notice use of V[]
        V[heap->H[parent]->vertex].pos = parent;    // Notice use of V[]
        MovingUp(heap, parent);
    }
    // print ("END MovingUp\n");
}

//----------------------------------------------
// MovingDown (minHeapify)
//----------------------------------------------

void MovingDown(HEAP *heap, int pos, int *flag, int *count_Heapify)
{
    int l = left(pos);
    int r = right(pos);
    int smallest;

    if (l <= heap->size && heap->H[l]->key < heap->H[pos]->key)
    {
        smallest = l;
    }
    else
    {
        smallest = pos;
    }

    if (r <= heap->size && heap->H[r]->key < heap->H[smallest]->key)
    {
        smallest = r;
    }

    if (smallest != pos)
    {
        //Exchange heap[pos] and heap[smallest]
        exchange(heap, pos, smallest);
        MovingDown(heap, smallest, flag, count_Heapify);
    }
    count_Heapify++;
    //printf("Calls: %d\n", count);
}

//----------------------------------------------
// BuildHeap
//----------------------------------------------
void BuildHeap(HEAP *heap, int *flag)
{
    int i;
    int *count_Heapify = 0;

    //printf("BGN BuildHeap\n");
    for (i = heap->size / 2; i > 0; i--)
    {
        MovingDown(heap, i, flag, count_Heapify);
    }
    //printf("END BuildHeap %d\n", *count_Heapify);
}

//----------------------------------------------
// Insert                                      P
//----------------------------------------------
int Insert(HEAP *heap, pELEMENT item)
{
    if (heap->size >= heap->capacity)
    {
        printf("Error in Insert: Heap full...\n");
        return 1;
    }
    heap->size++;
    heap->H[heap->size] = item;
    V[heap->H[heap->size]->vertex].pos = heap->size;

    MovingUp(heap, heap->size);

    return 0;
}

//----------------------------------------------
// DecreaseKey                                 P
//----------------------------------------------
int DecreaseKey(HEAP *heap, int pos, int newKey)
{
    if (pos < 1 || pos > heap->size || newKey >= heap->H[pos]->key)
    {
        //printf("Error: invalid call to DecreaseKey\n");
        return 1;
    }
    heap->H[pos]->key = newKey;
    MovingUp(heap, pos);
    return 0;
}

//----------------------------------------------
// DeleteMin (Prov)
//----------------------------------------------
pELEMENT DeleteMin(HEAP *heap, int *flag, int *count_Heapify)
{
    pELEMENT min, last;

    if (heap->size <= 0)
    {
        printf("error in DeleteMin: heap empty\n");
        return NULL;
    }
    min = heap->H[1];
    last = heap->H[heap->size--];
    heap->H[1] = last;
    V[heap->H[1]->vertex].pos = 1;              // Notice use of V[]
    MovingDown(heap, 1, flag, count_Heapify);
    V[min->vertex].pos = 0;                     // Notice use of V[]
    return min;
}

//----------------------------------------------
// HELPER
//----------------------------------------------
int left(int i)
{
    return (2 * i);
}

int right(int i)
{
    return (2 * i + 1);
}

void exchange(HEAP *heap, int &a, int &b)
{
    ELEMENT *temp = heap->H[a];
    heap->H[a] = heap->H[b];
    heap->H[b] = temp;
}
