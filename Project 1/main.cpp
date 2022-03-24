//#include <iostream>
//#include <string>
//#include <sstream>
//#include <fstream>
//
//using namespace std;

//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "heap.h"


int main()
{
	// variables for the parser...
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
				printf("COMMAND: %c\n", c);
				exit(0);

			case 'c':
			case 'C':
				printf("COMMAND: %c %d\n", c, n);
				heap = heapInit(n);
				break;

			case 'r':
			case 'R':
				printf("COMMAND: %c\n", c);
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
					element = (ElementT) malloc(sizeof(ElementT));
					element->key = number;
					heap->elements[j] = element;
					heap->size++;
				}
				break;

			case 'w':
			case 'W':
				printf("COMMAND: %c\n", c);
				if (heap == NULL) {
					printf("Error: heap is NULL\n");
					break;
				}

				ofile = fopen("HEAPoutput.txt", "w");
				if (!ofile) {
					printf("Error: cannot open file for writing\n");
					break;
				}

				fprintf(ofile, "%d\n", heap->size);
				for (j = 1; j <= heap->size; j++) {
					fprintf(ofile, "%d\n", heap->elements[j]->key);
				}

				fclose(ofile);
				break;

			case 'p':
			case 'P':
				printf("COMMAND: %c\n", c);
				if (heap == NULL) {
					printf("Error: heap is NULL\n");
					break;
				}

				heapPrint(heap);
				break;

			default: 
				// printf("COMMAND: %c\n", c);
				break;
		}
	}
	exit(0);
}
//=============================================================================
