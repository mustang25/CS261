/* CS261- Assignment 1 - Q. 0*/
/* Name: Robert Navarro
 * Date: January 14, 2016
 * Solution description: Printer different values using pointers.
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
        /*Print the value pointed to by iptr*/
        printf("The value pointed to by iptr is: %d\n", *iptr);
        /*Print the address pointed to by iptr*/
        printf("The address pointed to by iptr is: %p\n", iptr);
        /*Print the address of iptr itself*/
        printf("The address of iptr is: %p\n", &iptr);
}

int main(){

        /*declare an integer x*/
        int x = 5;

        /*print the address of x*/
        printf("The address of x is: %p\n", &x);

        /*Call fooA() with the address of x*/
        fooA(&x);

        /*print the value of x*/
        printf("The value of x is: %d\n", x);

        return 0;
}
