#include <stdio.h>
#include <stdlib.h>
#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))

typedef struct {
    int key;
    /* other fields */
} element;
typedef struct leftist *leftistTree;
        struct leftist {
            leftistTree leftChild;
            element data;
            leftistTree rightChild;
            int shortest;
        };

void minMeld(leftistTree *a, leftistTree *b);
void minUnion(leftistTree *a, leftistTree *b);
leftistTree newNode(int key);
void insertNode(leftistTree *a, int key);
void delNode(leftistTree *a);
void deleteNode(leftistTree *a);

void minMeldW(leftistTree *a, leftistTree *b);
void minUnionW(leftistTree *a, leftistTree *b);
void insertNodeW(leftistTree *a, int key);
void deleteNodeW(leftistTree *a);