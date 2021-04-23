#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// XUE/01-array-of-structs

//---------------------------------------------
// 
//---------------------------------------------
VERTEX *V;
int main(int argc, char *argv[]){

    FILE *ifile;

    pNODE *A;
    pNODE node;

    char word[256];
    char word2[256];
    int n, m, directed_graph, i;
    int s, s_new, t, t_new, source, source_new, destination, destination_new;
    int u, v, edge_id, flag, flag_new;
    float w;

    int v_scanf, v_fscanf;
    int r_value;


    if (argc != 3){
        printf("Command Format: %s <graph_filel> <direction>\n", argv[0]);
        exit(1);
    }
    if (0 == strcmp(argv[2], "directed\0")){
        directed_graph = 1;
    }
    if (0 == strcmp(argv[2], "undirected\0")){
        directed_graph = 0;
    }

    // open network file for reading
    ifile = fopen(argv[1], "r");
    if (!ifile){
        printf("ErrorGLX1: cannot open fie for reading.\n");
    }

    // read in n = |V| and m = |E|
    v_fscanf = fscanf(ifile, "%d%d", &n, &m);
    if (v_fscanf < 2){
        printf("ErrorGLX2: fscanf returns %d.\n", v_fscanf);
        exit(1);
    }

    // allocate memory for adjacency list
    A = (pNODE *) calloc(n+1, sizeof(pNODE));
    if (!A){
        printf("ERROR: calloc failure.\n");
        exit(1);
    }

    // read in the edges and construct adjacency lists
    for (i = 1; i <= m; i++){
        v_fscanf = fscanf(ifile, "%d%d%d%f", &edge_id, &u, &v, &w);
        if (v_fscanf < 4){
            printf("Error: fscanf returns %d.\n", v_fscanf);
            exit(1);
        }
    
        node = (pNODE) malloc(sizeof(NODE));
        if (!node){
            printf("Error: malloc failure.\n");
            exit(1);
        }

        node->u = u;
        node->v = v;
        node->w = w;
        node->next = A[u];
        A[u] = node;

        if (!directed_graph){
            // BGN for undirected graphs...
            node = (pNODE) malloc(sizeof(NODE));
            if (!node){
                printf("Error: malloc failure.\n");
                exit(1);
            }
            node->u = v;
            node->v = u;
            node->w = w;
            node->next = A[v];
            A[v] = node;
            // END for undirected graphs...
        }
    }

    /*
    // BGN check the adjacency lists
    for (i = 1; i <= n; i++){
        printf("Node %d:", i);
        node = A[i];
        while (node){
            printf("-->|%d %4.1f| ", node->v, node->w);
            node = node->next;
        }
        printf("\n");
    }
    // END check the adjacency list
    */

    // close the input file
     fclose(ifile);

    source = 0;
    destination = 0;
    V = (VERTEX *) calloc(n+1, sizeof(VERTEX));
    if (!V){
       printf("Error: calloc failure:\n");
       exit(1);
    }

//------------------------------------------------
// BGN query part...
//------------------------------------------------
    while (1){
        r_value = nextWord(word);
        if (!r_value){
            printf("ErrorGLX: EOF\n");
            continue;
        }

        if (0 == strcmp(word, "stop")){
            // STOP
            printf("Query: %s\n", word);
            break;
        }

        if (0 == strcmp(word, "find")){
            // FIND
            v_scanf = scanf("%d%d%d", &source_new, &destination_new, &flag_new);
            if (v_scanf != 3){
                printf("ErrorGLX3: wrong return value for scanf\n");
                continue;
            } else{
                printf("Query: %s %d %d %d\n", word, source_new, destination_new, flag_new);
                if (source_new < 1 || source_new > n || flag_new < 0 || flag_new > 1){
                    printf("error: invalid find query\n");
                } else{
                    source = source_new;
                    destination = destination_new;
                    flag = flag_new;
                    dijkstra(n, A, source, destination, flag);;
                }
            }          
        } else if (0 == strcmp(word, "write")){
//print(word);
            r_value = nextWord(word2);
            if (!r_value){
                printf("ErrorGLX4: EOF\n");
                continue;
            }

            if (0 == strcmp(word2, "path")){
//printf(word2);
                v_scanf = scanf("%d%d", &s_new, &t_new);
                if (v_scanf != 2){
                    printf("ErrorGLX5: wrong return value for scanf\n");
                    continue;
                } else{
                    printf("Query: %s %s %d %d\n", word, word2, s_new, t_new);

                    if (source == 0){
                        printf("Error: no path computation done\n");
                    } else if(s_new != source || t_new == s_new || t_new < 1 || t_new > n){
                        printf("Error: invalid source destination pair\n");
                    } else{
                        s = s_new;
                        t = t_new;
                        printPath(n, source, destination, s, t);
                    }
                }
            }
        } else{
            printf("ErrorGLX: Bad input\n");
            continue;
        }
    }

//-------------------------------------------------
    exit(0);
}
