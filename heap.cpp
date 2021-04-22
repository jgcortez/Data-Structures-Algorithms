#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "graph.h"
extern VERTEX *V;

// XUE/01-array-of-structs

void heapFree(HEAP *heap){
    free(heap->H);
    free(heap);
}



//----------------------------------------------
//heapInit
//----------------------------------------------
HEAP* heapInit(int capacity)
{
	HEAP* heap;
	heap = (HEAP*) calloc(1, sizeof(HEAP*));
	heap->capacity = capacity; heap->size = 0;

	heap->H = (pELEMENT*)calloc(capacity + 1, sizeof(pELEMENT*));
	return heap;
}

//----------------------------------------------
//heapPrint (Prov)
//----------------------------------------------

void heapPrint(HEAP *heap){//edit parameters, *heap guessed
    // may be more code here
    int i; //guess
    printf("capacity=%d, size=%d\n", heap->capacity, heap->size);
    for (i = 1; i < heap->size; i++){
        printf("%f, ", heap->H[i]->key);
    }
    if (heap->size > 0){
        printf("%f\n, ", heap->H[heap->size]->key);
    }
    // printf("END heapPrint\n");
}

//minHeapify
//buildHeap
//writeHeap ?
//insert
//extractMin
//decreaseKey
//----------------------------------------------
//HELPER
//----------------------------------------------
//left
//right
//exchange
//parent
//----------------------------------------------
// decreaseKey is movingUp
// heapify is movingDown



void MovingUp(HEAP *heap, int pos){
    pELEMENT temp;
    int parent;

    // print ("BGN MovingUp\n");
    parent = pos/2;
    if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key){
        temp = heap->H[pos];
        heap->H[pos] = heap->H[parent];
        heap->H[parent] = temp;
        V[heap->H[pos]->vertex].pos = pos;          //ADDED (no V or vertex for heap2 Im guessing)
        V[heap->H[parent]->vertex].pos = parent;    //ADDED (no V or vertex for heap2 Im guessing)
        MovingUp(heap, parent);
    }
    // print ("END MovingUp\n");
}

void MovingDown(HEAP *heap, int pos, int *flag, int *count_Heapify){//edit
    //funct //heapify?
}

void BuildHeap(HEAP *heap){//edit parameters?
    int i;
    //printf("BGN BuildHeap\n");
    for (i = heap->size/2; i > 0; i--){
        MovingDown(heap, i, flag, count_Heapify):
    }
    //printf("END BuildHeap %d\n", *count_Heapify);
}

int Insert(HEAP *heap, pELEMENT item){
    if (heap->size >= heap->capacity){
        printf("Error in Insert: Heap full...\n");
        return 1;
    }
    heap->size++;
    heap->H[heap->size] = item;
    V[heap->H[heap->size]->vertex].pos = heap->size;

    MovingUp(heap, heap->size);

    return 0;
}

int DecreaseKey (HEAP *heap, int pos, int newKey){
    if (pos < 1 || pos > heap->size || newKey >= heap->H[pos]->key){
        printf("Error: invalid call to DecreaseKey\n");
        return 1;
    }
    heap->H[pos]->key = newKey;
    MovingUp(heap, pos);
    return 0;
}

pELEMENT DeleteMin (HEAP *heap, int *flag, int *count_Heapify){
    
    pELEMENT min, last;

    if (heap->size <= 0){
        printf("error in DeleteMin: heap empty\n");
        return NULL;
    }
    min = heap->H[1];
    last = heap->H[heap->size--];
    heap->H[1] = last;
    V[heap->H[1]->vertex].pos = 1;                  //Maybe added
    MovingDown(heap, 1, flag, count_Heapify);
    V[min->vertex].pos = 0;                         //Maybe added
    return min;
}