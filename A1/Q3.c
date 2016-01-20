/* CS261- Assignment 1 - Q.3*/
/* Name: Robert Navarro
 * Date: January 16, 2016
 * Solution description: Create an array of 20 values and sort the values. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
    int switched = 0;
    int temp;
    /*If the next number in the array is lower than the current number we will switch values*/
    do {
        switched = 0;
        for (int i = 0; i < (n - 1); i++) {
            if (number[i + 1] < number[i]) {
                temp = number[i];
                number[i] = number[i + 1];
                number[i + 1] = temp;
                switched = 1;
            }
        }
    } while (switched == 1);
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
    int* testArray = (int*)malloc(n*sizeof(int));
    /*Fill this array with random numbers, using rand().*/
    for (int i = 0; i < n; i++){
        testArray[i] = rand();
    }
    
    /*Print the contents of the array.*/
    for (int i = 0; i < n; i++){
        printf("%d\n", testArray[i]);
    }
    /*Pass this array along with n to the sort() function of part a.*/
    sort(testArray, n);
    printf("\n");
    /*Print the contents of the array.*/
    for (int i = 0; i < n; i++){
        printf("%d\n", testArray[i]);
    }
    
    return 0;
}
