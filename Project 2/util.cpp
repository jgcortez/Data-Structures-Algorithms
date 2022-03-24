

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

//=============================================================================
int nextCommand(int* n, int* f)
{
	char c;
	//int temp;
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
			scanf("%d", f);
			break;
		}

		if (c == 'P' || c == 'p') {
			break;
		}

		if (c == 'W' || c == 'w') {
			break;
		}

		//===============================================
		//	Projet 2 ADDITIONAL DATA TYPES START
		//===============================================

		if (c == 'I' || c == 'i') {
			scanf("%d", n);
			break;
		}

		if (c == 'D' || c == 'd') {
			scanf("%d", f);
			break;
		}

		if (c == 'K' || c == 'k') {
			scanf("%d", n);
			scanf("%d", f);
			break;
		}


		//===============================================
		//	Projet 2 ADDITIONAL DATA TYPES END
		//===============================================


		//printf("Warning in nextCommand: invalid input \n");
		break;

	}
	return c;
}
//=============================================================================
