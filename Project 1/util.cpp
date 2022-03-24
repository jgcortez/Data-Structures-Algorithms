

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

//=============================================================================
int nextCommand(int* n, int* f)
{
	char c;
	while (1) {

		scanf("%c", &c);
		while (c == ' ' || c == '\t' || c == '\n') {
			scanf("%c", &c);
		}

		if (c == 'S' || c == 's') {
			break;
		}

		if (c == 'C' || c == 'c') {
			scanf("%d", n);
			if (*n == 0) {
				printf("Warning in nextCommand: read in int %d\n", *n);
			}
			break;
		}

		if (c == 'R' || c == 'r') {
			break;
		}

		if (c == 'P' || c == 'p') {
			break;
		}

		if (c == 'W' || c == 'w') {
			break;
		}

		printf("Warning in nextCommand: invalid input \n");
		break;

	}
	return c;
}
//=============================================================================