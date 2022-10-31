#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 16
#define INCREASE 1
#define DECREASE -1

void printArray(int arr[SIZE]){
    for (int i = 0; i < SIZE; i++){

        printf("%i\t", arr[i]);
    }
    printf("\n");
}


void swap(int arr[], int first_index, int second_index, int operator){
    // If "operator" = 1 then increase, else if "operator" = -1 then decrease
    if((operator)*arr[first_index] > (operator)*arr[second_index]){
        int tmp = arr[first_index];
        arr[first_index] = arr[second_index];
        arr[second_index] = tmp;
    }
}

void bitonicSeq(int unsorted_array[SIZE]){

    // ** Step 1
    for(int i = 0; i < (SIZE); i+=2){
        
        // Starting at index 0, make every second pair an increasing pair
        if(i%4 == 0){
            // Sort pair in increasing order
            // (z)*
            // 3 > 4
            // Increasing -> 
            swap(unsorted_array, i, i+1, INCREASE);

        }
        // Starting at index 2, make every second pair an decreasing pair        
        else{
            // Sort pair in increasing order
            swap(unsorted_array, i, i+1, DECREASE);
        }
        
    }

    // ** Step 2
    for(int i = 0; i < (SIZE); i+=4){
        // Starting at index 0, make every second pair an increasing pair
        if(i%8 == 0){
            // Sort first 4 in increasing order
            swap(unsorted_array, i, i+1, INCREASE);

            swap(unsorted_array, i, i+2, INCREASE);
            swap(unsorted_array, i+1, i+3, INCREASE);
            swap(unsorted_array, i+2, i+3, INCREASE);
        }
        // Starting at index 2, make every second pair an decreasing pair        
        else{
            // Sort pair in increasing order
            swap(unsorted_array, i, i+2, DECREASE);
            swap(unsorted_array, i+1, i+3, DECREASE);
            swap(unsorted_array, i, i+1, DECREASE);
            swap(unsorted_array, i+2, i+3, DECREASE);
        }
        
    }

    // ** Step 3
    for(int i = 0; i < (SIZE); i+=8){
        // Starting at index 0, make every second pair an increasing pair
        if(i%16 == 0){
            // Sort first 4 in increasing order
            swap(unsorted_array, i, i+1, INCREASE); // i + | 2^i

            swap(unsorted_array, i, i+2, INCREASE);
            swap(unsorted_array, i+1, i+3, INCREASE);// i + | 2^(i+1) + 1
            swap(unsorted_array, i+2, i+3, INCREASE);// i + | 2^(i+1) + (i+1)

            swap(unsorted_array, i, i+4, INCREASE);
            swap(unsorted_array, i+1, i+5, INCREASE);
            swap(unsorted_array, i+4, i+5, INCREASE);
            swap(unsorted_array, i+2, i+6, INCREASE);
            swap(unsorted_array, i+4, i+6, INCREASE);
            swap(unsorted_array, i+3, i+7, INCREASE);// i + | 2^(i+2) + (i+3)
            swap(unsorted_array, i+5, i+7, INCREASE);
            swap(unsorted_array, i+6, i+7, INCREASE);


        }
        // Starting at index 2, make every second pair an decreasing pair        
        else{
            // Sort pair in increasing order
            swap(unsorted_array, i, i+4, DECREASE);
            swap(unsorted_array, i+1, i+5, DECREASE);
            swap(unsorted_array, i+2, i+6, DECREASE);
            swap(unsorted_array, i+3, i+7, DECREASE);

            swap(unsorted_array, i, i+2, DECREASE);
            swap(unsorted_array, i+1, i+3, DECREASE);
            swap(unsorted_array, i+4, i+6, DECREASE);
            swap(unsorted_array, i+5, i+7, DECREASE);
            
            swap(unsorted_array, i, i+1, DECREASE);
            swap(unsorted_array, i+2, i+3, DECREASE);
            swap(unsorted_array, i+4, i+5, DECREASE);
            swap(unsorted_array, i+6, i+7, DECREASE);
        }
        
    }

    int increments ;
    for (int k = 0; k < log2(SIZE)-1; k++){ //log2(SIZE)-1 is the number of steps we need to go from unsorted to bitonic sequence

        increments = (int)(pow(2, k+1));

         for (int i = 0; i < SIZE; i+=increments){

         }


    }

}


void bitonicSort(int unsorted_array[SIZE]){
    bitonicSeq(unsorted_array);

    int tmp;

    // ** Step 1
    for(int i = 0; i < (SIZE/2); i++){

        if(unsorted_array[i] > unsorted_array[i+8]){
            tmp = unsorted_array[i];
            unsorted_array[i] = unsorted_array[i+8];
            unsorted_array[i+8] = tmp;
        }        
    }

    // ** Step 2
    
    for(int i = 0; i < (SIZE/4); i++){

        
        if (unsorted_array[i] > unsorted_array[i+4]){
            tmp = unsorted_array[i];
            unsorted_array[i] = unsorted_array[i+4];
            unsorted_array[i+4] = tmp;
        }     

        if (unsorted_array[i+8] > unsorted_array[i+12]){
            tmp = unsorted_array[i+8];
            unsorted_array[i+8] = unsorted_array[i+12];
            unsorted_array[i+12] = tmp;
        }   
    
    }

    for(int i = 0; i < (SIZE/8); i++){

        
        if (unsorted_array[i] > unsorted_array[i+2]){
            tmp = unsorted_array[i];
            unsorted_array[i] = unsorted_array[i+2];
            unsorted_array[i+2] = tmp;
        }     

        if (unsorted_array[i+4] > unsorted_array[i+6]){
            tmp = unsorted_array[i+4];
            unsorted_array[i+4] = unsorted_array[i+6];
            unsorted_array[i+6] = tmp;
        } 

        if (unsorted_array[i+8] > unsorted_array[i+10]){
            tmp = unsorted_array[i+8];
            unsorted_array[i+8] = unsorted_array[i+10];
            unsorted_array[i+10] = tmp;
        }   

        if (unsorted_array[i+12] > unsorted_array[i+14]){
            tmp = unsorted_array[i+12];
            unsorted_array[i+12] = unsorted_array[i+14];
            unsorted_array[i+14] = tmp;
        } 
    
    }

    for(int i = 0; i < (SIZE); i+=2){

        
        if (unsorted_array[i] > unsorted_array[i+1]){
            tmp = unsorted_array[i];
            unsorted_array[i] = unsorted_array[i+1];
            unsorted_array[i+1] = tmp;
        }     

    
    }






}

int main(){

    //int unsorted_array[SIZE] = {5,7,13,15,120,8,6,9,17,36,14,19,20,27,60,100};
    int unsorted_array[SIZE] = {10,20,5,9,3,8,12,14,90,0,60,40,23,35,95,18};
    printf("Unsorted:\n");
    printArray(unsorted_array);
    
    //increasing : 0, 4, 8, 12
    //decreasing : 2, 6, 10, 14


    bitonicSort(unsorted_array);
    


    printf("Sorted:\n");
    printArray(unsorted_array);

    

    return 0;
}