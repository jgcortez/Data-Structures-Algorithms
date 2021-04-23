#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"

extern VERTEX *V;
//---------------------------------------------
// printPath                                  P
//---------------------------------------------
void printPath(int n, int source, int destination, int s, int t)
{
    PATH *pPATH;
    PATH *pNode;
    int u, v;

    if (V[t].color == 0)
    {
        if (destination < 1 || destination > n || t == destination)
        {
            printf("No %d-%d path exists.\n", s, t);
            return;
        }
        else
        {
            printf("No %d-%d path has been computed.\n", s, t);
            return;
        }
    }
    else if (V[t].color == 1)
    {
        printf("Path not known to be shortest: <%d", s);
    }
    else if (V[t].color == 2)
    {
        printf("Shortest path: <%d", s);
    }

    // Push onto stack
    pNode = (PATH *)malloc(sizeof(PATH));
    pNode->vertex = t;
    pNode->next = NULL;
    pPATH = pNode;
    v = pNode->vertex;
    while (V[v].pi)
    {
        u = V[v].pi;
        pNode = (PATH *)malloc(sizeof(PATH));
        pNode->vertex = u;
        pNode->next = pPATH;
        pPATH = pNode;
        v = pNode->vertex;
    }

    pNode = pPATH;
    pPATH = pPATH->next;
    free(pNode);

    while (pPATH)
    {
        pNode = pPATH;
        printf(", %d", pNode->vertex);
        ;
        pPATH = pPATH->next;
        free(pNode);
    }
    printf(">\n");
    printf("The path weight is: %12.4f\n", V[t].dist);
}

//---------------------------------------------
// dijkstra variation                        SP
//---------------------------------------------

int dijkstra(int n, pNODE *A, int s, int t, int flag)
{
    pNODE node;
    HEAP *heap;
    ELEMENT *element;

    int u, v, i;
    float w;

    int pos;
    int count_Heapify;

    for (i = 1; i <= n; i++)
    {
        V[i].color = 0;
        V[i].pi = 0;
    }

    // Set distance of s to 0 and color to 1 (grey)
    V[s].dist = 0;
    V[s].color = 1;

    heap = heapInit(n);

    // Allocate memory for new element and insert in heap
    element = (ELEMENT *)malloc(sizeof(ELEMENT));
    element->vertex = s;
    element->key = 0;
    Insert(heap, element);

    if (flag == 1)
    {
        // Print insertion info
        printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
    }

    while (heap->size)
    {
        element = DeleteMin(heap, &flag, &count_Heapify);

        if (flag == 1)
        {
            // Print deletion information
            printf("Delete vertex %d, key=%12.4f\n", element->vertex, element->key);
        }
        u = element->vertex;
        V[u].color = 2;

        if (element->vertex == t)
        {
            //return 0;
            break;
        }

        free(element);

        node = A[u];

        // Perform Relaxation
        while (node)
        { // for each v in u.adj
            v = node->v;
            w = node->w;
            if (V[v].color == 0)
            { // if color is white
                V[v].dist = V[u].dist + w;
                V[v].pi = u;
                V[v].color = 1;         // printf("V[%d].color to 1\n", v);
                V[v].pos = heap->size + 1;

                // Allocate memory for new element and insert in heap
                element = (ELEMENT *)malloc(sizeof(ELEMENT));
                element->vertex = v;
                element->key = V[v].dist;   // SPE
                Insert(heap, element);      

                if (flag == 1)
                {
                    // Print insertion info
                    printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
                }
            }
            else if (V[v].dist > V[u].dist + w)
            {
                if (flag == 1)
                {
                    // Print decrese key info
                    printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v, V[v].dist, V[u].dist + w);
                }
                V[v].dist = V[u].dist + w;
                V[v].pi = u;
                pos = V[v].pos;
                DecreaseKey(heap, pos, V[v].dist);
            }
            node = node->next;
        }
    }
    if (heap->size == 0) // When queue is empty
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
