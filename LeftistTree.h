#include <stdio.h>
#define SWAP(a, b, t) t = a, a = b, b = t

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
void insertNode(leftistTree *a, int key);
void deleteNode(leftistTree *a);