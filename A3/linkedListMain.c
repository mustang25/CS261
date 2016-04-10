#include "linkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

///* 	VISUAL STUDIO (VS) USERS: COMMENT OUT THE LINE BELOW
//	TO EXCLUDE THE MEMORY TEST CODE.
// */
//#define MEMORY_TEST_INCLUDED
//
//#ifdef MEMORY_TEST_INCLUDED
///* This header is needed for memory usage calculation. */
//#include <sys/resource.h>
//
///* Function to get current memory usage in KB (Max Resident Set Size) */
//long getMemoryUsage() {
//    int who = RUSAGE_SELF;
//    struct rusage usage;
//    int ret;
//    ret = getrusage(who, &usage);
//    return usage.ru_maxrss;
//}
//#endif
//
///*Function to get number of milliseconds elapsed since program started execution*/
//double getMilliseconds() {
//    return 1000.0 * clock() / CLOCKS_PER_SEC;
//}
//
//int main(int argc, char* argv[]){
//    struct linkedList* b;
//    int n, i;
//    double t1, t2;
//    
//#ifdef MEMORY_TEST_INCLUDED
//    /* variables to hold memory used before and after creating LinkedList */
//    long m1, m2;
//    /* memory used BEFORE creating LinkedList */
//    m1 = getMemoryUsage();
//#endif
//    
//    if( argc != 2 ) return 0;
//    
//    b = createLinkedList();
//    n = atoi(argv[1]);/*number of elements to add*/
//    for( i = 0 ; i < n; i++) {
//        addList(b, (TYPE)i);/*Add elements*/
//    }
//    
//#ifdef MEMORY_TEST_INCLUDED
//    /* memory used AFTER creating LinkedList */
//    m2 = getMemoryUsage();
//    printf("Memory used by LinkedList: %ld KB \n", m2-m1);
//#endif
//    
//    t1 = getMilliseconds();/*Time before contains()*/
//    
//    for(i=0; i<n; i++) {
//        containsList(b, i);
//    }
//    
//    t2 = getMilliseconds();/*Time after contains()*/
//    printf("Time for running contains() on %d elements: %g ms\n", n, t2-t1);
//    
//    /* delete the linked list */
//    //deleteLinkedList(b);
//    
//    return 0;
//}

int main(int argc, char* argv[]) {
    int returned = -1;
    struct linkedList* q = createLinkedList(3);
    printf("Checking if the list is empty: %d\n", isEmptyList(q));
    
    printf("Attempting to add to front \n");
    addFrontList(q, 1);
    removeList(q, 1);
    printf("Checking if the list is empty: %d\n", isEmptyList(q));
    addFrontList(q, 2);
    addFrontList(q, 3);
    _printList(q);
    
    printf("Attempting to add to back \n");
    addBackList(q, 4);
    addBackList(q, 5);
    addBackList(q, 6);
    _printList(q);
    
    printf("Attempting to print front \n");
    printf("%d\n", frontList(q));
    
    printf("Attempting to print back \n");
    printf("%d\n", backList(q));
    
    printf("Attempting to remove front \n");
    removeFrontList(q);
    _printList(q);
    
    printf("Attempting to remove back \n");
    removeBackList(q);
    _printList(q);
    
    printf("Attempting to delete 4 \n");
    removeList(q, 4);
    _printList(q);
    
    printf("Attempting to print list \n");
    _printList(q);
    
    printf("Attempting to confirm contains 5 \n");
    returned = containsList(q, 5);
    if (returned == 1)
        printf("true \n");
    else
        printf("false \n");
    
    return 0;
}