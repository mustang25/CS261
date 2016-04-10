#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{
    int i;
    hashLink* current;
    hashLink* next;
    
    for (i = 0; i < ht->tableSize; i++) {
        current = ht->table[i];
        
        while (current != 0) {
            next = current->next;
            current->value = 0;
            free(current->key);
            free(current);
            current = next;
        }
        ht->table[i] = 0;
    }
    
    free(ht->table);
    ht->tableSize = 0;
    ht->count = 0;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
    /*creat a pointer to reference the old data*/
    hashLink** oldTable = ht->table;
    int oldSize = ht->tableSize;
    int i;
    hashLink *current;
    hashLink *next;
    
    /*init a new hash table with the new size*/
    _initMap(ht, newTableSize);
    
    /*store the old data in the new table. Data from the old table is freed
     as it is copied over to the new table*/
    for (i = 0; i < oldSize; i++)
    {
        current = oldTable[i];
        while(current != 0)
        {
            insertMap(ht, current->key, current->value);
            next = current->next;
            current = next;
        }
    }
    free(oldTable);
    
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
    int index;

    /*This function and several other functions in the future reference HASHING_FUNCTION,
     which is defined in hashMap.h. This allows to easily change between hashing method 1 and 2.*/
    if (HASHING_FUNCTION == 1) {
        index = stringHash1(k) % capacity(ht);
    }
    else {
        index = stringHash2(k) % capacity(ht);
    }
    
    /*This check ensures that the index is not less than 0*/
    if (index < 0) {
        index += capacity(ht);
    }
    
    /*If the hash table already contains the value we are looking to add, we will simply
     update the value to reflect the addition of one more. Note - since value is an int
     I was unable to "free" the value before reassigning it to a new value*/
    if (containsKey(ht, k)) {
        ht->table[index]->value = v;
    }
    
    /*If the value is not found we will create a new link and insert it at the front of the index
     Count is only updated here since in the option above we are not adding a new hashLink*/
    else {
        struct hashLink* newLink = malloc(sizeof(struct hashLink));
        assert(newLink != 0);
        newLink->key = k;
        newLink->value = v;
        newLink->next = ht->table[index];
        
        ht->table[index] = newLink;
        ht->count++;
    }

    
    /*After adding a new value or updating a value we will check to see if the load factor is 
     greater than or equal to the LOAD_FACTOR_THRESHOLD*/
    if(tableLoad(ht) >= LOAD_FACTOR_THRESHOLD) {
        _setTableSize(ht, ht->tableSize * 2);
    }
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
    int index;
    struct hashLink* current;
    
    if (HASHING_FUNCTION == 1) {
        index = stringHash1(k) % capacity(ht);
    }
    else {
        index = stringHash2(k) % capacity(ht);
    }
    
    if (index < 0) {
        index += capacity(ht);
    }
    
    current = ht->table[index];
    
    /*if we find the value we are looking for we will return the reference to the value (aka count) of that word*/
    while (current != 0) {
        if (strcmp(current->key, k) == 0) {
            return &(current->value);
        }
        current = current->next;
    }
    
    /*If nothing is found we return null*/
    return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
    int index;
    struct hashLink* current;
    
    if (HASHING_FUNCTION == 1) {
        index = stringHash1(k) % capacity(ht);
    }
    else {
        index = stringHash2(k) % capacity(ht);
    }
    
    if (index < 0) {
        index += capacity(ht);
    }
    
    current = ht->table[index];
    
    /*If we find the key we are looking for we exit the function and return 1*/
    while (current != 0) {
        if (strcmp(current->key, k) == 0) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  

    int index;
    int found = 0;
    struct hashLink* current;
    struct hashLink* previous;
    
    if (HASHING_FUNCTION == 1) {
        index = stringHash1(k) % capacity(ht);
    }
    else {
        index = stringHash2(k) % capacity(ht);
    }
    
    if (index < 0) {
        index += capacity(ht);
    }
    
    current = ht->table[index];
    previous = current;
    
    /*We are scanning through the list to find the value that we want to remove. If found we will update the pointers and free the value we removed. "found" is used to determine if we print the unable to find key statement.*/
    while (current != 0 && found != 1) {
        if (strcmp(current->key, k) == 0) {
            if (current == previous) {
                ht->table[index] = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current->key);
            free(current);
            ht->count--;
            found = 1;
        }
        previous = current;
        current = current->next;
    }
    if (found != 1) {
        printf("Unable to find key, no values removed\n");
    }
    
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
	return ht->count;	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this*/
    int emptyCount = 0;
    int i;
    
    for (i = 0; i < capacity(ht); i++) {
        if (ht->table[i] == 0) {
            emptyCount++;
        }
    }
    
	return emptyCount;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*returns a float for the load factor. Size and capacity are both cast to float so that we can get an accurate representation of the table load.*/
	return ((float)(size(ht)) / (float)(capacity(ht)));
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


