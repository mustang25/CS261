/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */
    DynArr* work;
    work = newDynArr(sizeof(s));
    char testChar = 0;
    
    do{
        testChar = nextChar(s);
        
        if (testChar == '(') {
            pushDynArr(work, ')');
        }
        else if (testChar == ')') {
            if (isEmptyDynArr(work)) {
                return 0;
            }
        else if (testChar != topDynArr(work)) {
                return 0;
            }
        else
            popDynArr(work);
        }
        
        else if (testChar == '[') {
            pushDynArr(work, ']');
        }
        else if (testChar == ']') {
            if (isEmptyDynArr(work)) {
                return 0;
            }
            else if (testChar != topDynArr(work)) {
                return 0;
            }
            else
                popDynArr(work);
        }
        
        else if (testChar == '{') {
            pushDynArr(work, '}');
        }
        else if (testChar == '}') {
            if (isEmptyDynArr(work)) {
                return 0;
            }
            else if (testChar != topDynArr(work)) {
                return 0;
            }
            else
                popDynArr(work);
        }
    } while (testChar != '\0');

    if (!isEmptyDynArr(work))
        return 0;
	return 1;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];
    //char* s = "(x + y,(x + (y + z))\0";
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

