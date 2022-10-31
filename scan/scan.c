#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <omp.h>

// all-prefix-sums algorithm version which is inherently sequential (this function is not called anywhere)
void scan(const size_t N, int out[], int in[]){
    size_t i = 0;
    
    for(size_t j = 0; j < N; j++){
        out[j] = in[j];
    }

    for(i = 1; i < N; i++){
        out[i] = in[i] + out[i-1];
    }
}

// Addition-reduction operation (up-sweep)
void reduceOp(const size_t N, int arr[]){
    int depth = (int) ((log(N)/log(2)) - 1);
    int threads = 4;

    for(int d = 0; d <= depth; d++){

        int num_of_indices_per_node = pow(2,(d+1));
        int max = (int) floor(((N-1)/pow(2,(d+1))));
        int end_index;

        for(int i = 0; i <= max; i++){
            end_index = (i * num_of_indices_per_node)+(pow(2,d)-1) + pow(2,d);

            arr[end_index] = arr[end_index] + arr[(int) (end_index - pow(2,d))];

        }
    }    

}

// Parameters:
// N -> Size of the array being passed through
// arr -> Array after reduction operation, before clearing step
void downSweep(const size_t N, int arr[]){

    // Perform the down-sweep
    int depth = (int) ((log(N)/log(2)) - 1);

    // Make the last (in decrementing order) node's "end_index" equal to 0
    int last_element = arr[N-1];
    arr[N-1] = 0;


    for(int d = depth; d >= 0; d--){
        int max = (int) floor(((N-1)/pow(2,(d+1))));

        for(int i = 0; i <= max; i++){

            int left_index = (int) (i*(pow(2,d)+d) + (i + pow(2,d) - 1));
            int right_index = (int) (i*(pow(2,d)+d) + (i + pow(2,(d+1))-1));
            
            // Store the left child in a temporary variable
            int temp = arr[left_index];

            // Set the left child
            arr[left_index] = arr[right_index];

            // Set the right child
            arr[right_index] = temp + arr[right_index];

        }
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
        
        // Array size (argc is the size of the input, including the programme name "./scan")
        const size_t N = argc - 1;

        // Check if the array size is a power of 2
        double whole_check = (log(N)/log(2));
        if(ceil(whole_check) == whole_check || floor(whole_check) == whole_check){
        double run_time = 0.0;
        clock_t start, end;


        // Allocate array space on the heap and populate the allocated buffer with the values passed through main
        int *arr_in = (int*) malloc(sizeof(int) * N);
        populateArr(N, arr_in, argv);

        // Print the input
        printf("Input:\n");
        printArr(N,arr_in);

        // Capture start time and start the reduction operation
        start = clock();
        reduceOp(N,arr_in);
        
        // Print the state of the array after the reduction operation
        printf("After Reduce Operation:\n");
        printArr(N,arr_in);

        // Perform the down-sweep
        downSweep(N,arr_in);

        // Capture the stopping time and calculate the run-time
        end = clock();
        run_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        // Print the final state of the array (i.e. the result of the scan operation)
        printf("After Down-sweep:\n");
        printArr(N,arr_in);

        // Compute and display performance metrics
        printf("\n**Checks\n");
        printf("Run Time:%f s\n",run_time);

        // Free the allocated buffer / memory of the 2 arrays on the heap
        free(arr_in);

        }else{
            printf("**Please ensure the size of your input array is a power of 2.\n");
        }


    }else{
        printf("**Please supply arguments.\n");
    }

    return 0;
}