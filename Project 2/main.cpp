//=============================================================================
// Name: Josue Cortez
// ID: 1216953400
// CSE310 T,Th 4:30pm
// Prof. Xue
// Project 2
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "heap.h"


int main()
{
	//========================================
	//	Projet 2 START
	//========================================

	char c;
	int n, flag;

	HEAP* heap;
	ElementT element;
	FILE* ifile, * ofile;
	int j, number;

	heap = NULL;

	while (1) {
		c = nextCommand(&n, &flag);
		switch (c) {
		case 's':
		case 'S':
			//printf("COMMAND: %c\n", c);
			exit(0);

		case 'c':
		case 'C':
			//printf("COMMAND: %c %d\n", c, n);
			heap = heapInit(n);
			break;

		case 'r':
		case 'R':
		{
			//printf("COMMAND: %c\n", c);
			ifile = fopen("HEAPinput.txt", "r");

			if (!ifile) {
				printf("Error: cannot open file for reading\n");
				break;
			}

			fscanf(ifile, "%d", &n);
			// printf("Read in %d\n", n);
			if (heap == NULL || heap->capacity < n) {
				printf("Error: heap overflow\n");
				break;
			}

			heap->size = 0;
			for (j = 1; j <= n; j++) {
				fscanf(ifile, "%d", &number);
				// printf("Read in %d\n", number);
				element = (ElementT)malloc(sizeof(ElementT));
				element->key = number;
				heap->elements[j] = element;
				heap->size++;
			}

			buildHeap(heap, flag);

			break;
		}

		case 'w':
		case 'W':
		{
			//printf("COMMAND: %c\n", c);
			ofile = fopen("HEAPoutput.txt", "w");
			if (!ofile || heap == NULL) {
				printf("Error: cannot write\n");
				break;
			}

			fprintf(ofile, "%d\n", heap->size);
			for (j = 1; j <= heap->size; j++) {
				fprintf(ofile, "%d\n", heap->elements[j]->key);
			}

			fclose(ofile);
			break;
		}

		case 'p':
		case 'P':
		{
			//printf("COMMAND: %c\n", c);
			if (heap == NULL) {
				printf("Error: cannot print\n");
				break;
			}

			heapPrint(heap);
			break;
		}

		case 'd':
		case 'D':
		{
			if (heap == NULL || heap->size == 0) {
				printf("Error: heap is NULL or empty\n");
				break;
			}

			extractMin(heap, flag);

			break;
		}

		case 'i':
		case 'I':
		{
			if (heap == NULL || heap->size == heap->capacity) {
				printf("Error: heap is NULL or full\n");
				break;
			}

			element = (ElementT)malloc(sizeof(ElementT));
			element->key = n;

			insert(heap, element);

			break;
		}

		case 'k':
		case 'K':
		{		
			if (heap == NULL || (n < 1 || n > heap->size) || flag >= heap->elements[n]->key) {
				printf("Error: invalid call to DecreaseKey\n");
				break;
			}

			decreaseKey(heap, n, flag);
			break;
		}

		default:
			// printf("COMMAND: %c\n", c);
			break;
		}
	}
	exit(0);

	//========================================
	//	Projet 2 END
	//========================================
}
//=============================================================================
