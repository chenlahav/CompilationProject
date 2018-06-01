#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct Item {
	int data;
	int key;
};

struct Item* hashArray[SIZE];
struct Item* dummyItem;
struct Item* item;

unsigned int hashCode(char* name)
{
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *)name;

	while (*p != '\0') {
		result = (result << 5) + result + (unsigned int)tolower(*p);
		++p;
	}

	return result;
}

//int hashCode(int key) {
//	return key % SIZE;
//}

struct Item *search(int key) {
	//get the hash 
	int hashIndex = hashCode(key);

	//move in array until an empty 
	while (hashArray[hashIndex] != NULL) {

		if (hashArray[hashIndex]->key == key)
			return hashArray[hashIndex];

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

	return NULL;
}

void insert(int key, int data) {

	struct Item *item = (struct Item*) malloc(sizeof(struct Item));
	item->data = data;
	item->key = key;

	//get the hash 
	int hashIndex = hashCode(key);

	//move in array until an empty or deleted cell
	while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

	hashArray[hashIndex] = item;
}

struct Item* delete(struct Item* item) {
	int key = item->key;

	//get the hash 
	int hashIndex = hashCode(key);

	//move in array until an empty
	while (hashArray[hashIndex] != NULL) {

		if (hashArray[hashIndex]->key == key) {
			struct Item* temp = hashArray[hashIndex];

			//assign a dummy item at deleted position
			hashArray[hashIndex] = dummyItem;
			return temp;
		}

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

	return NULL;
}

void display() {
	int i = 0;

	for (i = 0; i<SIZE; i++) {

		if (hashArray[i] != NULL)
			printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
		else
			printf(" ~~ ");
	}

	printf("\n");
}