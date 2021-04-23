#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"

// XUE/01-array-of-structs

extern VERTEX *V;
void printPath(int n, int source, int destination, int s, int t){
    
    PATH *pPATH;
    PATH *pNode;
    int u, v;

    if (V[t].color == 0){
        if (destination < 1 || destination > n || t == destination){
            printf("No %d-%d path exists.\n", s, t);
            return;
        } else{
            printf("No %d-%d path has been computed.\n", s, t);
            return;
        }
    } else if (V[t].color == 1){
        printf("Path not known to be shortest: <%d", s);
    } else if (V[t].color == 2){
        printf("Shortest path: <%d", s);
    }

    // push onto stack
    pNode = (PATH *) malloc(sizeof(PATH));
    pNode->vertex = t;
    pNode->next = NULL;
    pPATH = pNode;
    v = pNode->vertex;
    while(V[v].pi){
        u = V[v].pi;
        pNode = (PATH *) malloc(sizeof(PATH));
        pNode->vertex = u; pNode->next = pPATH;
        pPATH = pNode;
        v = pNode->vertex;
    }

    pNode = pPATH;
    pPATH = pPATH->next;
    free(pNode);
    
    while (pPATH){
        pNode = pPATH;
        printf(", %d", pNode->vertex);;
        pPATH = pPATH->next;
        free(pNode);
    }
    printf(">\n");
    printf("The path weight is: %12.4f\n", V[t].dist);
}

int dijkstra(int n, pNODE *A, int s, int t, int flag){

    pNODE node;
    HEAP *heap;
    ELEMENT *element;

    int u, v, i;
    float w;

    int pos;
    int count_Heapify;

    for (i = 1; i <= n; i++){
        V[i].color = 0;
        V[i].pi = 0;
    }
    V[s].dist = 0;
    V[s].color = 1;

    heap = heapInit(n);
    element = (ELEMENT *) malloc(sizeof(ELEMENT));
    element->vertex = s;
    element->key = 0;
    Insert(heap, element);
    //printf("First insert\n");
//printf("flag=%d\n", flag);
    if (flag == 1){
        // print insertion information
        printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
    }

    while (heap->size){
        element = DeleteMin(heap, &flag, &count_Heapify);
        //printf("DeleteMin\n");
	if (flag == 1){
            // print deletion information
            printf("Delete vertex %d, key=%12.4f\n", element->vertex, element->key);
        }
        u = element->vertex;
        V[u].color = 2;
//printf("fault1\n");
        if (element->vertex == t){  //if u == t? and return 0?
            //return 0;
	    break;
//printf("in\n");
        }
//printf("vertex=%d, t=%d\n", element->vertex, t);
//printf("size=%d\n", heap->size);
        free(element);

        node = A[u];
        while (node){       // for each v in u.adj
            v = node->v;
            w = node->w;
            if (V[v].color == 0){   // if color is white
                V[v].dist = V[u].dist + w;  
                V[v].pi = u;
                V[v].color = 1;
                // printf("V[%d].color to 1\n", v);
                V[v].pos = heap->size + 1;
                element = (ELEMENT *) malloc(sizeof(ELEMENT));
                element->vertex = v;
                element->key = V[v].dist;
                // My code ahead
                Insert(heap, element);      //When do you free? Count to free later?
                //printf("Insert\n");
		if (flag == 1){
			printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
		}
		// free(element);           // ??
                // heapPrint(heap);
            } else if (V[v].dist > V[u].dist + w){
                if (flag == 1){
			printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v, V[v].dist, V[u].dist+w);
		}
		V[v].dist = V[u].dist + w;  
                V[v].pi = u;
                pos = V[v].pos;
		DecreaseKey(heap, pos, V[v].dist);       // do I pass V[v] instead? v?/
        	//printf("DecreaseKey\n");  
	 }
            // How does node get updated for if? Insert?
	    node = node->next;
            // Stack?
            //printf("next\n");
        }
	//printf("next 2\n");
	// free(element);
    }
    if (heap->size == 0){ // or !node ? or !A ?
        return 1;
    } else {
        return 0;
    } 
    // When is return 0 vs return 1? How?
}
