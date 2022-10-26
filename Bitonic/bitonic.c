#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 16

void printArray(int arr[SIZE]){
    for (int i = 0; i < SIZE; i++){

        printf("%i\t", arr[i]);
    }
    printf("\n");
}

int main(){

    int unsorted_array[SIZE] = {5,7,13,15,120,8,6,9,17,36,14,19,20,27,60,100};
    printf("Unsorted:\n");
    printArray(unsorted_array);
    
    //increasing : 0, 4, 8, 12
    //decreasing : 2, 6, 10, 14
    
    // ** Step 1
    for(int i = 0; i < (SIZE); i+=2){
        
        // Starting at index 0, make every second pair an increasing pair
        if(i%4 == 0){
            // Sort pair in increasing order
            // (z)*
            // 3 > 4
            // Increasing -> 
            if(unsorted_array[i] > unsorted_array[i+1]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+1];
                unsorted_array[i+1] = tmp;
            }
        }
        // Starting at index 2, make every second pair an decreasing pair        
        else{
            // Sort pair in increasing order
            if(unsorted_array[i] < unsorted_array[i+1]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+1];
                unsorted_array[i+1] = tmp;
            }
        }
        
    }

    // ** Step 2
    for(int i = 0; i < (SIZE); i+=4){
        // Starting at index 0, make every second pair an increasing pair
        if(i%8 == 0){
            // Sort first 4 in increasing order
            if(unsorted_array[i] > unsorted_array[i+2]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+2];
                unsorted_array[i+2] = tmp;
            }

            if(unsorted_array[i+1] > unsorted_array[i+3]){
                int tmp = unsorted_array[i+1];
                unsorted_array[i+1] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }

            if(unsorted_array[i] > unsorted_array[i+1]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+1];
                unsorted_array[i+1] = tmp;
            }

            if(unsorted_array[i+2] > unsorted_array[i+3]){
                int tmp = unsorted_array[i+2];
                unsorted_array[i+2] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }
        }
        // Starting at index 2, make every second pair an decreasing pair        
        else{
            // Sort pair in increasing order
            if(unsorted_array[i] < unsorted_array[i+2]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+2];
                unsorted_array[i+2] = tmp;
            }

            if(unsorted_array[i+1] < unsorted_array[i+3]){
                int tmp = unsorted_array[i+1];
                unsorted_array[i+1] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }

            if(unsorted_array[i] < unsorted_array[i+1]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+1];
                unsorted_array[i+1] = tmp;
            }

            if(unsorted_array[i+2] < unsorted_array[i+3]){
                int tmp = unsorted_array[i+2];
                unsorted_array[i+2] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }
        }
        
    }

    // ** Step 3
    for(int i = 0; i < (SIZE); i+=8){
        // Starting at index 0, make every second pair an increasing pair
        if(i%16 == 0){
            // Sort first 4 in increasing order
            if(unsorted_array[i] > unsorted_array[i+4]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+4];
                unsorted_array[i+4] = tmp;
            }

            if(unsorted_array[i+1] > unsorted_array[i+5]){
                int tmp = unsorted_array[i+1];
                unsorted_array[i+1] = unsorted_array[i+5];
                unsorted_array[i+5] = tmp;
            }

            if(unsorted_array[i+2] > unsorted_array[i+6]){
                int tmp = unsorted_array[i+2];
                unsorted_array[i+2] = unsorted_array[i+6];
                unsorted_array[i+6] = tmp;
            }

            if(unsorted_array[i+3] > unsorted_array[i+7]){
                int tmp = unsorted_array[i+3];
                unsorted_array[i+3] = unsorted_array[i+7];
                unsorted_array[i+7] = tmp;
            }

            if(unsorted_array[i] > unsorted_array[i+2]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+2];
                unsorted_array[i+2] = tmp;
            }

            if(unsorted_array[i+1] > unsorted_array[i+3]){
                int tmp = unsorted_array[i+1];
                unsorted_array[i+1] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }

            if(unsorted_array[i+4] > unsorted_array[i+6]){
                int tmp = unsorted_array[i+4];
                unsorted_array[i+4] = unsorted_array[i+6];
                unsorted_array[i+6] = tmp;
            }

            if(unsorted_array[i+5] > unsorted_array[i+7]){
                int tmp = unsorted_array[i+5];
                unsorted_array[i+5] = unsorted_array[i+7];
                unsorted_array[i+7] = tmp;
            }


            if(unsorted_array[i] > unsorted_array[i+1]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+1];
                unsorted_array[i+1] = tmp;
            }

            if(unsorted_array[i+2] > unsorted_array[i+3]){
                int tmp = unsorted_array[i+2];
                unsorted_array[i+2] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }

            if(unsorted_array[i+4] > unsorted_array[i+5]){
                int tmp = unsorted_array[i+4];
                unsorted_array[i+4] = unsorted_array[i+5];
                unsorted_array[i+5] = tmp;
            }

            if(unsorted_array[i+6] > unsorted_array[i+7]){
                int tmp = unsorted_array[i+6];
                unsorted_array[i+6] = unsorted_array[i+7];
                unsorted_array[i+7] = tmp;
            }
        }
        // Starting at index 2, make every second pair an decreasing pair        
        else{
            // Sort pair in increasing order
            if(unsorted_array[i] < unsorted_array[i+4]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+4];
                unsorted_array[i+4] = tmp;
            }

            if(unsorted_array[i+1] < unsorted_array[i+5]){
                int tmp = unsorted_array[i+1];
                unsorted_array[i+1] = unsorted_array[i+5];
                unsorted_array[i+5] = tmp;
            }

            if(unsorted_array[i+2] < unsorted_array[i+6]){
                int tmp = unsorted_array[i+2];
                unsorted_array[i+2] = unsorted_array[i+6];
                unsorted_array[i+6] = tmp;
            }

            if(unsorted_array[i+3] < unsorted_array[i+7]){
                int tmp = unsorted_array[i+3];
                unsorted_array[i+3] = unsorted_array[i+7];
                unsorted_array[i+7] = tmp;
            }

            if(unsorted_array[i] < unsorted_array[i+2]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+2];
                unsorted_array[i+2] = tmp;
            }

            if(unsorted_array[i+1] < unsorted_array[i+3]){
                int tmp = unsorted_array[i+1];
                unsorted_array[i+1] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }

            if(unsorted_array[i+4] < unsorted_array[i+6]){
                int tmp = unsorted_array[i+4];
                unsorted_array[i+4] = unsorted_array[i+6];
                unsorted_array[i+6] = tmp;
            }

            if(unsorted_array[i+5] < unsorted_array[i+7]){
                int tmp = unsorted_array[i+5];
                unsorted_array[i+5] = unsorted_array[i+7];
                unsorted_array[i+7] = tmp;
            }


            if(unsorted_array[i] < unsorted_array[i+1]){
                int tmp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[i+1];
                unsorted_array[i+1] = tmp;
            }

            if(unsorted_array[i+2] < unsorted_array[i+3]){
                int tmp = unsorted_array[i+2];
                unsorted_array[i+2] = unsorted_array[i+3];
                unsorted_array[i+3] = tmp;
            }

            if(unsorted_array[i+4] < unsorted_array[i+5]){
                int tmp = unsorted_array[i+4];
                unsorted_array[i+4] = unsorted_array[i+5];
                unsorted_array[i+5] = tmp;
            }

            if(unsorted_array[i+6] < unsorted_array[i+7]){
                int tmp = unsorted_array[i+6];
                unsorted_array[i+6] = unsorted_array[i+7];
                unsorted_array[i+7] = tmp;
            }
        }
        
    }


    printf("Sorted:\n");
    printArray(unsorted_array);

    

    return 0;
}