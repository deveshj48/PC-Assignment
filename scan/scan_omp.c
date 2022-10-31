#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <omp.h>

#define SIZE 5

// Serial up-sweep
void serialReduceOp(const size_t N, int arr[]){
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

// Serial down-sweep
void serialDownSweep(const size_t N, int arr[]){

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

// Serial Implementation of scan
void serialScan(const size_t N, int arr[]){
    serialReduceOp(N,arr);
    serialDownSweep(N,arr);
}

// Addition-reduction operation (up-sweep)
void reduceOp(const size_t N, int arr[]){
    int depth = (int) ((log(N)/log(2)) - 1);
    // int threads = 4;

    for(int d = 0; d <= depth; d++){
        // printf("Step:%d\n",d);

        int num_of_indices_per_node = pow(2,(d+1));
        int max = (int) floor(((N-1)/pow(2,(d+1))));
        int end_index;

        #pragma omp parallel shared(arr, max, num_of_indices_per_node, d) private(end_index)
        #pragma omp for
            for(int i = 0; i <= max; i++){
                // printf("Node:%d\t",i);
                end_index = (i * num_of_indices_per_node)+(pow(2,d)-1) + pow(2,d);

                // printf("End Index:%d\n",end_index);
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
    // int threads = 4;

    // Make the last (in decrementing order) node's "end_index" equal to 0
    int last_element = arr[N-1];
    arr[N-1] = 0;

    int max, left_index, right_index, temp;

    #pragma omp parallel shared(arr) private(max,left_index,right_index,temp)


    for(int d = depth; d >= 0; d--){

        // int num_of_indices_per_node = pow(2,(d+1));
        max = (int) floor(((N-1)/pow(2,(d+1))));
            
        #pragma omp for
        for(int i = 0; i <= max; i++){

            left_index = (int) (i*(pow(2,d)+d) + (i + pow(2,d) - 1));
            right_index = (int) (i*(pow(2,d)+d) + (i + pow(2,(d+1))-1));
            
            // Store the left child in a temporary variable
            temp = arr[left_index];

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

void validateOutput(size_t N, int serial[], int parallel[]){
    int different = 0;
    size_t i = 0;

    while(i < N && different != 1){
        if(serial[i] != parallel[i]){
            different = 1;
            break;
        }
        i++;
    }

    if(different == 0){
        printf("Validation (Parallel = Sequential): True\n");
    }else{
        printf("Validation (Parallel = Sequential): False\n");
    }
}

int main(int argc, char *argv[]){

    // Check to see if any arguments were supplied
    if(argc > 1){
        double run_time = 0.0;
        double seq_run_time = 0.0;
        
        // Array size (argc is the size of the input, including the programme name "./scan_omp")
        const size_t N = argc - 1;

        // Allocate array space on the heap and populate the allocated buffer with the values passed through main
        int *arr_in = (int*) malloc(sizeof(int) * N);
        populateArr(N, arr_in, argv);

        int *arr_serial = (int*) malloc(sizeof(int) * N);
        populateArr(N, arr_serial, argv);
        seq_run_time = omp_get_wtime();
        serialScan(N,arr_serial);
        seq_run_time = omp_get_wtime() - seq_run_time;
        
        // Before computing the all-prefix-sums, print the input, "arr_in", array (which changes)
        printf("Input:\n");
        printArr(N,arr_in);

        // Start Time
        run_time = omp_get_wtime();
        // Do the up-sweep
        reduceOp(N,arr_in);
        printf("After Reduce Operation:\n");
        printArr(N,arr_in);

        // Perform the all-prefix-sums operation using values in "arr_in"
        downSweep(N,arr_in);

        // Stop Time
        run_time = omp_get_wtime() - run_time;

        // After computing the all-prefix-sums, print the "out" array
        printf("After Down-sweep:\n");
        printArr(N,arr_in);

        printf("\n**Checks\n");
        validateOutput(N, arr_in, arr_serial);

        // Print Performance Metrics
        printf("Run Time:%f s\n",run_time);
        printf("Speedup:%f\n",(seq_run_time/run_time));

        // Free the allocated buffer / memory of the array on the heap
        free(arr_in);
        free(arr_serial);
    }else{
        printf("Please supply arguments!\n");
    }

    return 0;
}