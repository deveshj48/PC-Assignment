// This file is just to test out random code if needed

// Supplies with a structure on how to dynamically allocate an array depending on what has been passed as arguments to the main
// function (the arguments when invoking the executable).

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <omp.h>

#define SIZE 5

// void reduceOp(const size_t N, int arr[]){
//     int depth = (int) ((log(N)/log(2)) - 1);
//     int threads = 4;

//     for(int d = 0; d <= depth; d++){
//         printf("Step:%d\n\n",d);

//         int num_of_indices_per_node = pow(2,(d+1));
//         int max = (int) floor(((N-1)/pow(2,(d+1))));
        
//         for(int i = 0; i <= max; i++){
//             printf("Node:%d\n",i);
//             for(int j = floor((((i*num_of_indices_per_node)+num_of_indices_per_node)/2) - 1); j < ((i*num_of_indices_per_node)+num_of_indices_per_node); j += (num_of_indices_per_node/2)){
//                 printf("Index:%d\n",j);
//                 arr[(int) ((j)+pow(2,(d+1))-1)] = arr[(int) ((j)+pow(2,(d))-1)] + arr[(int) ((j)+pow(2,(d+1))-1)];
//             }
//         }
//         printf("\n");
//     }    

// }

void scan(const size_t N, int out[], int in[]){
    size_t i = 0;
    
    for(size_t j = 0; j < N; j++){
        out[j] = in[j];
    }

    for(i = 1; i < N; i++){
        out[i] = in[i] + out[i-1];
    }
}

void printArr(const size_t N, int arr[]){
    printf("Array:");
    for(size_t j = 0; j < N; j++){
        printf("%d ",arr[j]);
    }
    printf("\n");
}

void populateArr(size_t N, int *arr, char *input[]){

    for(size_t i = 1; i <= N; i++){
        arr[i-1] = atoi((input[i]));
    }
}

void mathFunction(){
    double num = log(8)/log(2);
    printf("Pow function return value:%f",num);
}

int main(int argc, char *argv[]){

    // if(argc > 1){
    //     printf("Number of Arguments:%d\n",argc);
    //     printf("First Argument:%s\n",argv[1]);
    //     const size_t N = argc - 1;

    //     int *arr_in = (int*) malloc(sizeof(int) * N);

    //     populateArr(N, arr_in, argv);

    //     int *out = (int*) malloc(sizeof(int) * N);
    //     for(size_t i = 0; i < N; i++){
    //         out[i] = 0;
    //     }

    //     printArr(N,arr_in);

    //     scan(N,out,arr_in);

    //     printArr(N,out);

    //     free(arr_in);
    //     free(out);
    // }else{
    //     printf("Please supply arguments!\n");
    // }

    mathFunction();

    return 0;
}