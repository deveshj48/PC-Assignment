#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief obtain the number of vertices and edges from textfile
/// @return integer array with number of vertices and edges
void getVertEdg(int *numVertices, int *numEdges){ 

    //int VertEdg[2];

    //extracting the numEdges and numVertices from line 0 of textfile
    FILE *textfile;
    char *line = (char*)malloc(30); //have to allocate size, otherwise get segfault
    //char *found;

    textfile = fopen("graph_0.txt", "r");

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

    textfile = fopen("graph_0.txt", "r");


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
    printGraph(adjMatrix, numVertices);


    //freeing the dynamically allocated memory
    // for (int i = 0; i < numVertices; i++)
    //     free(adjMatrix[i]);


    return(0);
}