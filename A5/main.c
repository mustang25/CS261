#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
    char cmd = ' ';
    char inputFile[100];
    char outputFile[100];
    char newTaskDesc[TASK_DESC_SIZE];
    int priority;
    FILE* inputPointer;
    FILE* outputPointer;
    DynArr* mainList = createDynArr(10);
    struct Task* newTask;
    struct Task* workingTask;

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n"
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');

        /* Load to-do list from file */
        if (cmd == 'l') {
            printf("Enter the name of the input file: ");

            if(fgets(inputFile, sizeof(inputFile), stdin) != 0)
            {
                /*Note: this function was used in reference to a piazza post and 
                 http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input*/
                inputFile[strcspn(inputFile, "\n")] = 0;
            }
            
            /*Set input pointer and confirm that it is not set to 0*/
            inputPointer = fopen(inputFile, "r");
            if(inputPointer == 0) {
                printf("Unable to open %s\n", inputFile);
            }
            else {
                /*Load file into program*/
                printf("Loading the file %s into the program.\n", inputFile);
                loadList(mainList, inputPointer);
                printf("Load Successful!\n");
                fclose(inputPointer);
            }
        }
        
        /*Save to-do list to file*/
        else if (cmd == 's') {
            if (sizeDynArr(mainList) == 0) {
                printf("The list is empty, unable to save!\n");
                break;
            }
            
            printf("Enter the name of the output file: ");
            
            if(fgets(outputFile, sizeof(outputFile), stdin) != 0)
            {
                outputFile[strcspn(outputFile, "\n")] = 0;
            }
            
            /*Set output pointer and open file for writing*/
            outputPointer = fopen(outputFile, "w");
            if (outputPointer == 0) {
                printf("Unable to open %s\n", outputFile);
            }
            
            else {
                /*Write contents of to-do list to output file*/
                printf("Saving the to-do list to the file: %s\n", outputFile);
                saveList(mainList, outputPointer);
                printf("The file has been saved successfully!\n");
                fclose(outputPointer);
            }
        }
        
        /*Add task to to-do list*/
        else if (cmd == 'a') {
            /*Have user enter description of the task*/
            printf("Please enter the description of your task: ");
            if(fgets(newTaskDesc, sizeof(newTaskDesc), stdin) != NULL) {
                newTaskDesc[strcspn(newTaskDesc, "\n")] = 0;
            }
            
            /*Have the user enter priority from 0 - 999*/
            do {
                printf("Please enter a priority for this task (0 - 999): ");
                scanf("%d", &priority);
                while (getchar() != '\n');
                if (priority < 0 || priority > 999) {
                    printf("Invalid priority number, please enter a number between 0 and 999.\n");
                }
            } while (priority < 0 || priority > 999);
            
            /*Create new task and add it to the to-do list*/
            newTask = createTask(priority, newTaskDesc);
            addHeap(mainList, newTask, compare);
            printf("The task '%s' has been successfully added to the list!\n", newTaskDesc);

        }
        
        /*Get the first task from to-do list and display it on screen*/
        else if (cmd == 'g') {
            if (sizeDynArr(mainList) == 0) {
                printf("The list is empty! There are no tasks to display.\n");
            }
            else {
                workingTask = getMinHeap(mainList);
                printf("The first task on the list is: %s\n", workingTask->description);
            }

        }
        
        /*Remove the first task from to-do list*/
        else if (cmd == 'r') {
            if (sizeDynArr(mainList) == 0) {
                printf("The list is empty! There is not a task to remove from the list.\n");
            }
            else {
                workingTask = getMinHeap(mainList);
                removeMinHeap(mainList, compare);
                printf("The first task, %s, has been removed from the list.\n", workingTask->description);
            }
        }
        
        /*Print the to-do list*/
        else if (cmd == 'p') {
            if (sizeDynArr(mainList) == 0) {
                printf("The list is empty! There is nothing to print.\n");
            }
            else {
                printList(mainList);
            }
        }
        
        /*Exit program*/
        else if (cmd == 'e') {
            printf("Exiting program... goodbye!\n");
        }
        
        /*Invalid input*/
        else {
            printf("Invalid user input, please enter a valid option.\n");
        }

      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }
  while(cmd != 'e');
  /* delete the list */
  deleteDynArr(mainList);

  return 0;
}
