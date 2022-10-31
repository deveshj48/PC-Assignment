#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <omp.h>

#define GRAPH_FILE "graph_1.txt"

/// @brief obtain the number of vertices and edges from textfile
/// @return integer array with number of vertices and edges
void getVertEdg(int *numVertices, int *numEdges){ 

    //int VertEdg[2];

    //extracting the numEdges and numVertices from line 0 of textfile
    FILE *textfile;
    char *line = (char*)malloc(30); //have to allocate size, otherwise get segfault
    //char *found;

    textfile = fopen(GRAPH_FILE, "r");

    fgets(line, 30, textfile);
    
    int sepcount = 0;
    char *found = strtok(line, " ");
    while (found != NULL){
        if (sepcount == 0){
            *numVertices = atoi(found);
            //printf("%d\n", VertEdg[0]);
        }
        else if (sepcount == 1){
            *numEdges = atoi(found);
            //printf("%d\n", VertEdg[1]);

        }

        sepcount++;

        found = strtok(NULL, " ");
    }

    fclose(textfile);



}

void setupGraph(int **adjMatrix, int numVertices, int numEdges){

    for (int i = 0; i < numVertices; i++){
        for (int j = 0; j < numVertices; j++){
            adjMatrix[i][j] = -1;
        }
    }

    //printf("%d\n", numEdges);


    //read from text file:
    FILE *textfile;
    char *line  = (char*)malloc(30);
    int linecount = -1;

    textfile = fopen(GRAPH_FILE, "r");


    while (fgets(line, 30, textfile)){

        linecount++;

        //break when we have read all the lines relating to the edges
        if ( linecount > numEdges ){
            break;
        }
        //get the vertices and weights and populate adjacency matrix
        if (linecount != 0){ //skip the first line
            int v1, v2, weight;
            int sepcount = 0;
            char *found = strtok(line, " "); //read a string like 0 1 1 and split by space
            while (found != NULL){
                //there are 3 chunks - v1, v2 and weight
                //printf("%s\n", found);

                if (sepcount == 0){
                    v1 = atoi(found);
                }
                else if (sepcount == 1){
                    v2 = atoi(found);
                }
                else if (sepcount == 2){
                    weight = atoi(found);
                }

                sepcount++;
                found = strtok(NULL, " ");

            }

            // printf("%d\n", weight);

            adjMatrix[v1][v2] = weight;
            adjMatrix[v2][v1] = weight; //due to the symmetry. not sure if needed

        }

    }

    fclose(textfile);

}

void printGraph(int **adjMatrix, int numVertices){
    for (int i = 0; i < numVertices; i++){
        for (int j = 0; j < numVertices; j++){
            printf("%i ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

/// @brief checks whether all nodes are visited
/// @return true if there is a 0 in the visited array (ie, theres an unvisited node)
int Unvisited(int* visited, int numVertices){

    int i = 0;
    
    while (i < numVertices){
        if (visited[i] == 0){
            return 1;
        }
        i++;
    }

    return 0;
    

}

void OmpDijkstra(int **adjMatrix, int numVertices, int source){

    //with openMP, cant explicitely split vertices among processes

    //array of visited vertices. initialied to 0 (false). 1 is true
    int* arrVisited = (int*)malloc(numVertices*sizeof(int));
    

    //array of minimum weights, ie, l (L). initialised to max integer value
    int* l = (int*)malloc(numVertices*sizeof(int));
    
    //the source is visited
    arrVisited[source] = 1;
    l[source] = 0;

    //------------------------------parallel section ------------------------------------------------------

    //omp_set_num_threads(4);
    #pragma omp parallel shared(source)
    {

        //initialise arrays
        #pragma omp for
        for (int i = 0; i<numVertices; i++){
            if (i != source){
                arrVisited[i] = 0;

                if (adjMatrix[i][source] != -1){ //if direct edge between source and current vertex
                    l[i] = adjMatrix[i][source];
                }
                else {
                    l[i] = INT_MAX;
                }
            }

        }


        int u;
        int min;
        //while (Unvisited(arrVisited, numVertices) == 1){ //while there are unvisited nodes
        #pragma omp for ordered
            for (int j=0; j < numVertices-1; j++){

                min = INT_MAX; 

                #pragma omp for reduction(min : l[u]) //looking for minimum l[u] value - but we need the u later. not sure if it will store u
                for (int v = 0; v < numVertices; v++){
                    if (arrVisited[v] == 0){ //if an unvisited vertex
                        if (l[v] <= min){
                            u = v; //u is the vertex such that l[u] = min{l[v] | v is an element of the unvisited nodes}
                            l[u] = l[v];
                            min = l[v];
                        }
                    }
                }

                #pragma omp single //one thread updates this value
                arrVisited[u] = 1; //vertex u is now considered visited
                
                

                #pragma omp for
                for (int v = 0; v < numVertices; v++){
                    if (arrVisited[v] == 0){ //if an unvisited vertex
                        if (adjMatrix[u][v] != -1 && l[u] != -1){
                            if (l[u]+adjMatrix[u][v] < l[v]){
                                l[v] = l[u]+adjMatrix[u][v];

                            }
                        }
                    }
                }
            }
    }

    //------------------------------parallel section end ------------------------------------------------------


    

    for (int h = 0; h < numVertices; h++){
        printf("%i\t", l[h]);
    }
    printf("\n");

    free(arrVisited);
    free(l);
}

int main(){

    //get number of vertices and edges
    int numVertices, numEdges;
    getVertEdg(&numVertices, &numEdges);

    //creating adjacency matrix to store vertices and their edges. eg, adjMatrix[0][3] is the weight of the edge joining vertex 0 and 3
    //using a double pointer to create a dynamic 2d matrix. method 3 -> https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    int** adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++){
        adjMatrix[i] = (int*)malloc(numVertices * sizeof(int));
    }


    setupGraph(adjMatrix, numVertices, numEdges);
    //printGraph(adjMatrix, numVertices);

    double start, finish_p;
     /*Parallel run*/ 
    start = omp_get_wtime();
    OmpDijkstra(adjMatrix, numVertices, 0);
	finish_p = omp_get_wtime() - start;
    printf("\nParallel time: %f\n", finish_p);




    //freeing the dynamically allocated memory
    // for (int i = 0; i < numVertices; i++)
    //     free(adjMatrix[i]);


    return(0);
}