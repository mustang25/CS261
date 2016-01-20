/* CS261- Assignment 1 - Q.5*/
/* Name: Robert Navarro
 * Date: January 14, 2016
 * Solution description: This program takes a user inputted word a makes it have sticky caps
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
    int test;
    int currentChar = 0;
     /*Convert to sticky caps*/
    do {
        test = word[currentChar];
        /*Test if a char is upper or lower case*/
        /*If char is even it must be upper case*/
        if (currentChar % 2 == 0 && test != 0) {
            if (test > 96 && test < 123) {
                word[currentChar] = toUpperCase(word[currentChar]);
            }
        }
        /*If char is odd it must be lower case*/
        else {
            if (test > 64 && test < 91) {
                word[currentChar] = toLowerCase(word[currentChar]);
            }
        }
        /*Increase current char if char is not 0*/
        if (test != 0) {
            currentChar++;
        }
    } while (test != 0);
}

int main(){
    char userInput[50];
    /*Read word from the keyboard using scanf*/
    printf("Enter a string and I will turn it into sticky caps: ");
    scanf("%s" , userInput);
    /*Call sticky*/
    sticky(userInput);
    /*Print the new word*/
    printf("%s\n", userInput);
    return 0;
}
