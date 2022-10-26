#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <omp.h>

#define SIZE 5

// all-prefix-sums algorithm version which is inherently sequential
/*
void scan(const size_t N, int out[], int in[]){
    size_t i = 0;
    
    for(size_t j = 0; j < N; j++){
        out[j] = in[j];
    }

    for(i = 1; i < N; i++){
        out[i] = in[i] + out[i-1];
    }
}
*/

// void scan(const size_t N, int out[], int in[]){

// }

// Addition-reduction operation (up-sweep)
void reduceOp(const size_t N, int arr[]){
    int depth = (int) ((log(N)/log(2)) - 1);
    int threads = 4;

    for(int d = 0; d <= depth; d++){
        // printf("Step:%d\n",d);

        int num_of_indices_per_node = pow(2,(d+1));
        int max = (int) floor(((N-1)/pow(2,(d+1))));
        int end_index;

        for(int i = 0; i <= max; i++){
            // printf("Node:%d\t",i);
            end_index = (i * num_of_indices_per_node)+(pow(2,d)-1) + pow(2,d);

            // printf("End Index:%d\n",end_index);
            arr[end_index] = arr[end_index] + arr[(int) (end_index - pow(2,d))];

        }
        // printf("\n");
    }    

}

// Parameters:
// N -> Size of the array being passed through
// arr -> Array after reduction operation, before clearing step
void downSweep(const size_t N, int arr[]){

    // Perform the down-sweep
    int depth = (int) ((log(N)/log(2)) - 1);
    // int threads = 4;

    // Make the last (in decrementing order) node's "end_index" equal to 0
    int last_element = arr[N-1];
    arr[N-1] = 0;


    for(int d = depth; d >= 0; d--){
        // printf("Step:%d\n",d);

        // int num_of_indices_per_node = pow(2,(d+1));
        int max = (int) floor(((N-1)/pow(2,(d+1))));

        for(int i = 0; i <= max; i++){
            // printf("Node:%d\t",i);
            // end_index = (i * num_of_indices_per_node)+(pow(2,d)-1) + pow(2,d);

            int left_index = (int) (i*(pow(2,d)+d) + (i + pow(2,d) - 1));
            int right_index = (int) (i*(pow(2,d)+d) + (i + pow(2,(d+1))-1));
            
            // Store the left child in a temporary variable
            // printf("Left index:%d",left_index);
            int temp = arr[left_index];

            // Set the left child
            arr[left_index] = arr[right_index];

            // Set the right child
            arr[right_index] = temp + arr[right_index];

            // printf("End Index:%d\n",end_index);
            // arr[end_index] = arr[end_index] + arr[(int) (end_index - pow(2,d))];

        }
        // printf("\n");
    }    

    // The code below turns the pre-scan to a scan
    // Not sure if this is how we should do the bit-shift to the left?
    for(size_t i = 0; i < N-1; i++){
        arr[i] = arr[i+1];
    }
    arr[N-1] = last_element;

}

void printArr(const size_t N, int arr[]){
    // printf("Values:");
    for(size_t j = 0; j < N; j++){
        printf("%d\t",arr[j]);
    }
    printf("\n");
}

void populateArr(size_t N, int *arr, char *input[]){

    for(size_t i = 1; i <= N; i++){
        arr[i-1] = atoi((input[i]));
    }
    
}

int main(int argc, char *argv[]){

    // Check to see if any arguments were supplied
    if(argc > 1){
        
        // Array size (argc is the size of the input, including the programme name "./main")
        const size_t N = argc - 1;

        // Allocate array space on the heap and populate the allocated buffer with the values passed through main
        int *arr_in = (int*) malloc(sizeof(int) * N);
        populateArr(N, arr_in, argv);

        // Allocate array space on the heap and populate the allocated buffer with 0's
        // Probably not neccesary to assign 0 to all the values, we should be able to just work with the array
        // once the heap space has been allocated, but will assign 0 to all the indices for now
        // int *out = (int*) malloc(sizeof(int) * N);
        // for(size_t i = 0; i < N; i++){
        //     out[i] = 0;
        // }

        // // Before computing the all-prefix-sums, print the input, "arr_in", array (which remains untouched)
        // printf("Input:\n");
        // printArr(N,arr_in);

        // // Perform the all-prefix-scan operation using values in "arr_in" and store the results in "out"
        // scan(N,out,arr_in);

        // // After computing the all-prefix-sums, print the "out" array
        // printf("Output:\n");
        // printArr(N,out);

        printf("Input:\n");
        printArr(N,arr_in);

        reduceOp(N,arr_in);
        
        printf("Output:\n");
        printArr(N,arr_in);

        downSweep(N,arr_in);
        printf("After Down-sweep:\n");
        printArr(N,arr_in);

        // Free the allocated buffer / memory of the 2 arrays on the heap
        free(arr_in);
        // free(out);
    }else{
        printf("Please supply arguments!\n");
    }

    return 0;
}