/* CS261- Assignment 1 - Q.4*/
/* Name: Robert Navarro
 * Date: January 16, 2016
 * Solution description: Current students and assign random ids and grades to them. Sort the students by
 * grade.
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
    int switched = 0;
    int tempScore;
    int tempID;
    
    /*This do/while loop checks if the if the score for the next student is higher than the current student.
     *If it is lower we will switch students so that the order is from low to high*/
    do {
        switched = 0;
        for (int i = 0; i < (n - 1); i++) {
            if (students[i + 1].score < students[i].score) {
                tempScore = students[i].score;
                tempID = students[i].id;
                students[i].score = students[i + 1].score;
                students[i].id = students[i + 1].id;
                students[i + 1].score = tempScore;
                students[i + 1].id = tempID;
                switched = 1;
            }
        }
    } while (switched == 1);
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 15;
    
    /*Allocate memory for n students using malloc.*/
    struct student* students = malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/
    int unique = 0;
    /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    for (int i = 0; i < n; i++){
        do {
            students[i].id = (rand()% n + 1);
            unique = 1;
            for (int j = 0; j < i; j++) {
                if (students[i].id == students[j].id ) {
                    unique = 0;
                }
            }
        } while (unique == 0);
        students[i].score = rand() % 101;
    }
    
    /*Print the contents of the array of n students.*/
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", students[i].id, students[i].score);
    }
    /*Pass this array along with n to the sort() function*/
    sort(students, n);
    printf("\n");
    /*Print the contents of the array of n students.*/
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", students[i].id, students[i].score);
    }
    return 0;
}
