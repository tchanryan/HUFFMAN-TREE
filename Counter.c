// Implementation of the Counter ADT by Ryan Tchan z5258155

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"

struct counter {
	struct counter *left;
	struct counter *right;
	char character[MAX_CHARACTER_LEN + 1];
	int freq;
};

static void AddItem(Counter c, struct item *array, int *index);

// creates a new bst of ADT Counter
Counter CounterNew(void) {
	Counter c = malloc(sizeof(struct counter));

	if (c == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	c->left = NULL;
	c->right = NULL;
	c->freq = 0;
	//c->character = NULL;

	return c;
}

// recursively frees all memory of the associated bst Counter
void CounterFree(Counter c) {
	if (c == NULL) {
		return;
	}

	CounterFree(c->left);
	CounterFree(c->right);
	free(c);
}

// adds an occurence of the given character to the counter
void CounterAdd(Counter c, char *character) {
	if (c->freq == 0) {
		c->freq++;
		strcpy(c->character, character);
		return;
	} 

	// adds new character to end
	if (strcmp(c->character, character) > 0 && c->right == NULL) {
		c->right = CounterNew();	
		c->right->freq++;
		strcpy(c->right->character, character);
		return;
	} else if (strcmp(c->character, character) < 0 && c->left == NULL) {
		c->left = CounterNew();
		c->left->freq++;
		strcpy(c->left->character, character);
		return;
	}

	// finds character
	if (strcmp(c->character, character) > 0) {
		CounterAdd(c->right, character);	
	} else if (strcmp(c->character, character) < 0) {
		CounterAdd(c->left, character);
	} else {
		c->freq++;
	}
	return;
}

// Returns the number of distinct characters added to the counter
int CounterNumItems(Counter c) {
	if (c == NULL) {
		return 0;
	}

	return 1 + CounterNumItems(c->left) + CounterNumItems(c->right);
}

// returns the frequency of the given character
int CounterGet(Counter c, char *character) {
	if (c == NULL) {
		return 0;
	} 
	
	if (strcmp(c->character, character) < 0) {
		return CounterGet(c->left, character);
	} else if (strcmp(c->character, character) > 0) {
		return CounterGet(c->right, character);
	} else {
		return c->freq;
	}
}

// Returns a dynamically allocated array containing a copy of each distinct character in the counter
// and its count, and sets *numItems to the number of distinct characters;
struct item *CounterItems(Counter c, int *numItems) {
	if (c == NULL) {
		return NULL;
	}

	*numItems = CounterNumItems(c);
	struct item *array = malloc((*numItems) * (sizeof(struct item)));
	int index = 0;

	AddItem(c, array, &index);

	return array;
}

// Recursive Helper function to allocate a distinct character and its frequency to an array at a 
// particular index -> performs in-order traversal
static void AddItem(Counter c, struct item *array, int *index) {
	if (c == NULL) {
		return;
	}
	AddItem(c->left, array, index);

	strcpy(array[*index].character, c->character);
	array[*index].freq = CounterGet(c, c->character);
	(*index)++;
	
	AddItem(c->right, array, index);
}
