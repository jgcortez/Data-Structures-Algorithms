#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"


HEAP* heapInit(int capacity)
{
	HEAP* heap;
	heap = (HEAP*) calloc(1, sizeof(HEAP*));
	heap->capacity = capacity; heap->size = 0;

	heap->elements = (ElementT*)calloc(capacity + 1, sizeof(ElementT*));
	return heap;
}

void heapPrint(HEAP* H) {
	if (H == NULL) {
		printf("capacity=%d", H->capacity);
		printf(" size=%d\n", H->size);
	}
	else {
		printf("capacity=%d", H->capacity);
		printf(", size=%d\n", H->size);

		printf("%d", H->elements[1]->key);

		for (int i = 2; i <= H->size; i++) {
			printf(", %d", H->elements[i]->key);
		}
		printf("\n");
	}
}