/* CS261- Assignment 1 - Q.2*/
/* Name: Robert Navarro
 * Date: January 16, 2016
 * Solution description: Use pointers to update values for x, y and z.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int retVal;
    /*Print the values of x, y and z*/
    printf("The value of x is: %d\n", x);
    printf("The value of y is: %d\n", y);
    printf("The value of z is: %d\n", z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    retVal = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("The return value of foo is: %d\n", retVal);
    /*Print the values of x, y and z again*/
    printf("The value of x is: %d\n", x);
    printf("The value of y is: %d\n", y);
    printf("The value of z is: %d\n", z);
    /*Is the return value different than the value of z?  Why?*/
    /*Since z was not passed by reference the value was not changed when a + b was assigned to c.
     This is why the return value is different from what value was returned.*/
    return 0;
}
    
    
