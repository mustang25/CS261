/* CS261- Assignment 1 - Q.1*/
/* Name: Robert Navarro
 * Date: January 16, 2016
 * Solution description: Assign 10 students a random ID number and a random test score.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student* students = malloc(10 * sizeof(struct student));
     
     /*return the pointer*/
    return students;
}

void generate(struct student* students){
    int unique = 0;
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    for (int i = 0; i < 10; i++){
        do {
            students[i].id = (rand()% 10 + 1);
            unique = 1;
            /*Confirm that ID assigned is unique, if not set unique to false(0) and get new ID.*/
            for (int j = 0; j < i; j++) {
                if (students[i].id == students[j].id ) {
                    unique = 0;
                }
            }
        } while (unique == 0);
        students[i].score = rand() % 101;
    }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    for (int i = 0; i < 10; i++) {
        printf("%d %d\n", students[i].id, students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 100;
    int max = 0;
    int average = 0;
    
    /*Calculate max, min and average*/
    for (int i = 0; i < 10; i++){
        if (students[i].score > max) {
            max = students[i].score;
        }
        if (students[i].score < min) {
            min = students[i].score;
        }
        average += students[i].score;
    }
    average /= 10;
    
    printf("The minimum score is: %d\n", min);
    printf("The maximum score is: %d\n", max);
    printf("The average score is: %d\n", average);
     
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
