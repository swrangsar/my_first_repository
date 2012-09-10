CFLAGS=-Wall -g -DNDEBUG

all: huffmanTreeTest

huffmanTreeTest: huffmanTree.o

clean:
	rm -f huffmanTreeTest huffmanTree.o
