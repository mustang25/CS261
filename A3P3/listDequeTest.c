#include "cirListDeque.h"
#include <stdio.h>

int main(){
	struct cirListDeque* q = createCirListDeque();
    printf("Checking if the list is empty %d\n", isEmptyCirListDeque(q));
	addBackCirListDeque(q, (TYPE)1);
    printf("Checking if the list is empty after adding value: %d\n", isEmptyCirListDeque(q));
	addBackCirListDeque(q, (TYPE)2);
	addBackCirListDeque(q, (TYPE)3);
	addFrontCirListDeque(q, (TYPE)4);
	addFrontCirListDeque(q, (TYPE)5);
	addFrontCirListDeque(q, (TYPE)6);
    printf("The list order is:\n");
	printCirListDeque(q);
    printf("The front of the list is: \n");
	printf("%g\n", frontCirListDeque(q));
    printf("The back of the list is: \n");
	printf("%g\n", backCirListDeque(q));
	removeFrontCirListDeque(q);
	removeBackCirListDeque(q);
    printf("The list order after removing front and back is:\n");
	printCirListDeque(q);
	reverseCirListDeque(q);
    printf("The reveresed list order is:\n");
	printCirListDeque(q);
    freeCirListDeque(q);
	return 0;
}
