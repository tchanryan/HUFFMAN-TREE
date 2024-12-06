// Implementation of the Huffman module

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"
#include "Counter.h"
#include "File.h"
#include "huffman.h"

// static helper functions for task 3
static struct huffmanTree *nodeCreateLeaf(char *character, int freq);
static struct huffmanTree *buildHuffmanTree(struct huffmanTree *leaf_array, struct item *array, int numItems);
static void mergeSort(struct item *array, int lo, int high);
static void merge(struct item *array, int lo, int mid, int high);



// Task 1
void decode(struct huffmanTree *tree, char *encoding, char *outputFilename) {
	struct huffmanTree *current = tree;
	struct file *write_decoded = FileOpenToWrite(outputFilename);
	
	int i = 0;
	while (encoding[i] != '\0') {
		
		if (encoding[i] == '0' && current->left != NULL) {
			current = current->left;
		} else if (encoding[i] == '1' && current->right != NULL) {
			current = current->right;
		}  
	
		if (current->left == NULL && current->right == NULL) {
			FileWrite(write_decoded, current->character);
			current = tree;
		
		}
		i++;
	}
	FileClose(write_decoded);
}


// Task 3
struct huffmanTree *createHuffmanTree(char *inputFilename) {
	struct file *read = FileOpenToRead(inputFilename);

	Counter c = CounterNew(); 
	char buffer[MAX_CHARACTER_LEN + 1];
	
	// read and create a sorted counter array of characters + frequency from input
	while ((FileReadCharacter(read, buffer) == true)) {
		CounterAdd(c, buffer);
	}

	int numItems;
	struct item *array = CounterItems(c, &numItems);

	mergeSort(array, 0, numItems - 1); 


	// create huffman leaves from sorted array
	struct huffmanTree *tree = malloc(numItems * sizeof(struct huffmanTree));
	tree = buildHuffmanTree(tree, array, numItems);

	CounterFree(c);
	FileClose(read);

	return tree;
}
//////////////////////////////////// TASK 3 HELPER FUNCTIONS /////////////////////////////////

// creates a huffmanTree leaf for a distinct character + frequency

static struct huffmanTree *nodeCreateLeaf(char *character, int freq) {
	struct huffmanTree *tree = malloc(sizeof(struct huffmanTree));
	if (tree == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	tree->left = NULL;
	tree->right = NULL;
	tree->freq = freq;

	//tree->character = (char *)malloc(MAX_CHARACTER_LEN + 1);
	//strcpy(tree->character, character);
	tree->character = character;

	return tree;
}


// creates leaves from the struct item array and stores the leaf addresses into an array
// pairs the two lowest frequencies to a parent node and inserts the parent frequency back into the array till a tree is made
static struct huffmanTree *buildHuffmanTree(struct huffmanTree *leaf_array, struct item *array, int numItems) {
	int size = numItems;
	if (size == 0) {
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		leaf_array[i] = *nodeCreateLeaf(array[i].character, array[i].freq);
	}

	while (size > 1) {
		struct huffmanTree *left = &leaf_array[0];
		struct huffmanTree *right = &leaf_array[1];
		struct huffmanTree *parent = nodeCreateLeaf(NULL, left->freq + right->freq);

		parent->left = left;
		parent->right = right;

		for (int j = 3; j < size; j++) {
			leaf_array[j - 2] = leaf_array[j];
		}

		leaf_array[0] = *parent;
		size--;

		for (int k = 1; k < size; k++) {
			struct huffmanTree *temp = &leaf_array[k];
			int l = k - 1;
			while (l >= 0 && leaf_array[l].freq > temp->freq) {
				leaf_array[l + 1] = leaf_array[l];
				l--;
			}
			leaf_array[l + 1] = *temp;
		}

	}
	return &leaf_array[0];
}

// helper function that sections an array into two and then merges them
static void mergeSort(struct item *array, int lo, int high) {
	if (lo < high) {
		int mid = lo + (high - lo) / 2;

		mergeSort(array, lo, mid);
		mergeSort(array, mid + 1, high);

		merge(array, lo, mid, high);
	}
}

// // helper function that merges two sections of an array together in-order of frequency
static void merge(struct item *array, int lo, int mid, int high) {
	int first = mid - lo + 1;
	int second = high - mid;

	struct item *left = malloc(first * sizeof(struct item));
	struct item *right = malloc(second * sizeof(struct item));

	// split data into left and right arrays
	for (int i = 0; i < first; i++) {
		left[i] = array[lo + i];
	}
	for (int j = 0; j < second; j++) {
		right[j] = array[mid + 1 + j];
	}

	// bring arrays back together in order of frequency
	int i = 0;
	int j = 0;
	int k = 0;

	while (i < first && j < second) {
		if (left[i].freq <= right[j].freq) {
			array[k] = left[i];
			i++;
		} else {
			array[k] = right[j];
			j++;
		}
		k++;
	}

	// excess numbers merged back in
	while (i < first) {
		array[k] = left[i];
		i++;
		k++;
	}	
	while (j < second) {
		array[k] = right[j];
		j++;
		k++;
	}

	free(left);
	free(right);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////

// // Task 4
char *encode(struct huffmanTree *tree, char *inputFilename) {
	return NULL;
}

