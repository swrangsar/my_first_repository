#ifndef _huffmanTree_h
#define _huffmanTree_h

typedef struct {
	char* code;
	int codeLength;
} codeObject;

typedef struct huffmanNode {
	int frequency;
	char symbol;
	struct huffmanNode* leftChild;
	struct huffmanNode* rightChild;
} huffmanNode;


typedef struct {
	huffmanNode* root;
	int numberOfNodes;
} huffmanTree;

huffmanNode* createHuffmanNode();
huffmanNode* huffmanInsert(huffmanTree* HuffmanTree, huffmanNode* HuffmanNode);
codeObject* huffmanEncode(huffmanTree* HuffmanTree, char symbol);
huffmanNode* huffmanDecode(huffmanTree* HuffmanTree, codeObject* CodeObject);
char* analyzeCodeword(huffmanTree* HuffmanTree, char* Codeword);
void clearHuffmanNode(huffmanNode* HuffmanNode);
void clearHuffmanTree(huffmanTree* HuffmanTree);
void clearCodeObject(codeObject* CodeObject);
void showEncode(huffmanTree* HuffmanTree, char symbol);

#endif
