#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
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
		printf("capacity=%d", H->capacity);
		printf(", size=%d\n", H->size);
		if (H->size > 0) {
			printf("%d", H->elements[1]->key);
	
			for (int i = 2; i <= H->size; i++) {
				printf(", %d", H->elements[i]->key);
			}
		printf("\n");
		}
}

void minHeapify(HEAP* H, int index, int &count) {
	int l = LEFT(index);
	int r = RIGHT(index);
	int smallest;

	if (l <= H->size && H->elements[l]->key < H->elements[index]->key) {
		smallest = l;
	}
	else {
		smallest = index;
	}

	if (r <= H->size && H->elements[r]->key < H->elements[smallest]->key) {
		smallest = r;
	}

	if (smallest != index) {
		//Exchange A[i] and A[smallest]
		EXCHANGE(H->elements[index]->key, H->elements[smallest]->key);
		minHeapify(H, smallest, count);
	}
	count++;
	//printf("Calls: %d\n", count);
}

void buildHeap(HEAP* H, int f) {
	int count = 0;
	for (int i = floor(H->size / 2); i >= 1; i--) {
		minHeapify(H, i, count);
	}
	if (f == 1) {
		printf("Number of Heapify calls: %d\n", count);
	}
}

void writeHeap(HEAP* H) {

}

void insert(HEAP* H, ElementT element) {	
	ElementT temp;
	temp = element;
	int newKey = temp->key;
	//printf("value: %d\n", newKey);

	H->size++;
	int i = H->size;

	H->elements[i] = temp;

	H->elements[i]->key = 10000;
	//printf("value: %d\n", newKey);
	decreaseKey(H, i, newKey);
}

void extractMin(HEAP* H, int f) {
	if (H->size < 1) {
		//Nothing, already checked in main
	}
	else {
		int count = 0;
		int min = H->elements[1]->key;
		H->elements[1]->key = H->elements[H->size]->key;
		H->size--;
		minHeapify(H, 1, count);
		printf("Deleted key: %d\n", min);
		if (f == 1) {
			printf("Number of Heapify calls: %d\n", count);
		}
	}
}

void decreaseKey(HEAP* H, int index, int value) {
	if (value > H->elements[index]->key) {
		// Can't decrease
	}
	else {
		H->elements[index]->key = value;
		while (index > 1 && H->elements[PARENT(index)]->key > H->elements[index]->key) {
			EXCHANGE(H->elements[index]->key, H->elements[PARENT(index)]->key);
			index = PARENT(index);
		}
	}
}



//==================
//	HELPER
//==================

int LEFT(int i) {
	return (2 * i);
}

int RIGHT(int i) {
	return (2 * i + 1);
}

void EXCHANGE(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int PARENT(int i) {
	return floor(i / 2);
}
