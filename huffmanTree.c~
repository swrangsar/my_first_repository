#include <stdio.h>
#include <stdlib.h>
#include "huffmanTree.h"


huffmanNode* createHuffmanNode()
{
	huffmanNode* newHuffmanNode;
	newHuffmanNode = malloc(sizeof(huffmanNode));
	newHuffmanNode->frequency = 0;
	newHuffmanNode->symbol = 0;
	newHuffmanNode->leftChild = NULL;
	newHuffmanNode->rightChild = NULL;
	return newHuffmanNode;
}

huffmanNode* huffmanInsert(huffmanTree* HuffmanTree, huffmanNode* HuffmanNode)
{
	/* This function returns NULL if there is no existing huffmanNode with 
	 * the same symbol, otherwise returns the huffmanNode with the same symbol.
	 * If successful it inserts the new symbol into a new huffmanNode at the
	 * bottom of the tree.
	 */
	
	if (!HuffmanTree) {
		perror("The huffman has not been created.\n");
		exit(1);
	}
	
	if (!HuffmanTree->root) {
		HuffmanTree->root = createHuffmanNode();
		HuffmanTree->root->leftChild = HuffmanNode;
	} else {
		huffmanNode* nextHuffmanNode = HuffmanTree->root->rightChild;
		huffmanNode* thisHuffmanNode = HuffmanTree->root;
		if (thisHuffmanNode->leftChild->symbol == HuffmanNode->symbol) return thisHuffmanNode->leftChild;
		while (nextHuffmanNode) {
			thisHuffmanNode = nextHuffmanNode;
			if (thisHuffmanNode->leftChild->symbol == HuffmanNode->symbol) return thisHuffmanNode->leftChild;
			nextHuffmanNode = thisHuffmanNode->rightChild;
		}
		thisHuffmanNode->rightChild = createHuffmanNode();
		thisHuffmanNode->rightChild->leftChild = HuffmanNode;
	}
	HuffmanTree->numberOfNodes++;
	return NULL; /* meaning successful insertion */
}

codeObject* huffmanEncode(huffmanTree* HuffmanTree, char symbol)
{
	/* This function encodes the given symbol. The encoded form takes a '1' for every
	 * and a '0' for the last left turn taken.
	 */

	if (!HuffmanTree || !HuffmanTree->root) {
		perror("The huffman tree doesn't exist or is empty.\n");
		exit(1);
	}
	
	/* creates a new code object and sets the code to the null character */
	codeObject* newCodeObject = malloc(sizeof(codeObject));
	newCodeObject->code = NULL;
	newCodeObject->codeLength = 0;

	/* initializes the huffmanNode pointers required for traversing the tree */
	huffmanNode* nextHuffmanNode = HuffmanTree->root->rightChild;
	huffmanNode* thisHuffmanNode = HuffmanTree->root;
	while (1) {
		/* if the input symbol matches the symbol in the current node then we 
		 * reallocate memory to the code and append it with a '0' and return the 
		 * code to the caller of this function
		 */
		if (thisHuffmanNode->leftChild->symbol == symbol) {
			newCodeObject->codeLength++;
			int l = newCodeObject->codeLength;
			newCodeObject->code = realloc(newCodeObject->code, (l+1)*sizeof(char));
			newCodeObject->code[l-1] = '0';
			newCodeObject->code[l] = '\0';
			return newCodeObject;
		}
		/* if the input symbol doensn't match the symbol in the current node then we 
		 * reallocate memory to the code and append it with a '1'.
		 */
		newCodeObject->codeLength++;
		int l = newCodeObject->codeLength;
		newCodeObject->code = realloc(newCodeObject->code, (l+1)*sizeof(char));
		newCodeObject->code[l-1] = '1';
		newCodeObject->code[l] = '\0';
		
		/* if the right child of the current node points to NULL then we free the memory
		 * allocated to code and then return a NULL pointer to the caller of this function.
		 */
		if (!nextHuffmanNode) {
//			if (newCodeObject->code) free(newCodeObject->code);
			if (newCodeObject) clearCodeObject(newCodeObject);

			return NULL;
		}
		thisHuffmanNode = nextHuffmanNode;
		nextHuffmanNode = thisHuffmanNode->rightChild;
	}
}
		
huffmanNode* huffmanDecode(huffmanTree* HuffmanTree, codeObject* CodeObject)
{
	/* This function takes a code and then returns the huffmanNode containing the corresponding
	 * symbol or else returns a NULL pointer which only means no symbol has been assigned such a
	 * code.
	 */
	
	if (!HuffmanTree || !HuffmanTree->root) {
		/* the huffman tree is either undefined or empty. */
		perror("The huffman tree is either undefined or empty.\n");
		exit(1);
	}
	
	if (!CodeObject || !CodeObject->code || !CodeObject->codeLength) {
		perror("The code is either undefined or empty.\n");
		exit(1);
	}
	
	if (CodeObject->code[CodeObject->codeLength]) {
		perror("The code is not null terminated.\n");
		exit(1);
	}
	
	int i = 0;
	huffmanNode* nextHuffmanNode = HuffmanTree->root->rightChild;
	huffmanNode* thisHuffmanNode = HuffmanTree->root;
	for (; i < CodeObject->codeLength; i++) {
		if (CodeObject->code[i] == '0') {
			thisHuffmanNode = thisHuffmanNode->leftChild;
			break;
		}
		if (CodeObject->code[i] == '1') {
			thisHuffmanNode = nextHuffmanNode;
			nextHuffmanNode = thisHuffmanNode->rightChild;
		} else {
			perror("The code has a number other than 0 or 1.\n");
			exit(1);
		}
	}


	if (thisHuffmanNode && thisHuffmanNode->symbol) {
		return thisHuffmanNode;
	} else {
		return NULL;
	}
}

char* analyzeCodeword(huffmanTree* HuffmanTree, char* Codeword)
{
	/* This function breaks up the codeword into codes which end with a 0 and
	 * transform them into a codeObject and then decode them using the decode function
	 * and then return the whole decoded codeword as a string.
	 */
	if (!HuffmanTree || !HuffmanTree->root) {
		perror("The huffman tree is either undefined or empty.\n");
		exit(1);
	}
	
	char* decodedWord = NULL;
	/* continue analyzing as long as a NULL is not found in the codeword */
	int i = 0, j, k = 0;

	while (Codeword[i] != '\0') {
		char* codePart = NULL;
		j = 0;
		while (Codeword[i] != '\0') {
			codePart = realloc(codePart, (sizeof(char)*(j+2)));
			codePart[j] = Codeword[i];
			i++;j++;
			if (codePart[j-1] == '0') break;
		}
		if (codePart[j-1] != '0') {
			perror("A code part ending with a non-zero number was found.\n");
			break; /* the code doesn't end with a zero so we break out of the loop */
		}
		codePart = realloc(codePart, sizeof(char)*(j+2));
		codePart[j] = '\0';
		codeObject* newCodeObject = malloc(sizeof(codeObject));
		newCodeObject->code = codePart;
		newCodeObject->codeLength = j;

		huffmanNode* HuffmanNode = huffmanDecode(HuffmanTree, newCodeObject);
		clearCodeObject(newCodeObject);
		if (HuffmanNode && HuffmanNode->symbol) {
			decodedWord = realloc(decodedWord, sizeof(char)*(k+2));
			decodedWord[k] = HuffmanNode->symbol;
			k++;
		} else {
			decodedWord = realloc(decodedWord, sizeof(char)*(k+2));
			decodedWord[k] = '?';
			k++;
		}
	}
	decodedWord = realloc(decodedWord, sizeof(char)*(k+2));
	decodedWord[k] = '\0';
	return decodedWord;
}


void clearHuffmanNode(huffmanNode* HuffmanNode)
{
	if (HuffmanNode) {
		if (HuffmanNode->leftChild) clearHuffmanNode(HuffmanNode->leftChild);
		if (HuffmanNode->rightChild) clearHuffmanNode(HuffmanNode->rightChild);
		free(HuffmanNode);
	}
}

void clearHuffmanTree(huffmanTree* HuffmanTree)
{
	if (HuffmanTree) {
		if (HuffmanTree->root) {
			clearHuffmanNode(HuffmanTree->root);
		}
		free(HuffmanTree);
	}
}

void clearCodeObject(codeObject* CodeObject)
{
	if (CodeObject) {
		if (CodeObject->code) free(CodeObject->code);
		free(CodeObject);
	}
}
	
void showEncode(huffmanTree* HuffmanTree, char symbol)
{
	codeObject* new = NULL;
	new = huffmanEncode(HuffmanTree, symbol);
	if (new) {
		if (new->code) {
			printf("The encoded form of symbol %c is %s\n", symbol, new->code);
		}
		clearCodeObject(new);

	} else {
		printf("The encoded form of symbol %c is unknown\n", symbol);
	}
}
