#include <stdio.h>
#include <stdlib.h>

typedef int keyType;
typedef struct bTreeNode *bTreePtr;
struct bTreeNode {
    keyType *key;
    int size;
    bTreePtr *child;
    short isLeaf;
};

typedef struct bTree {
    bTreePtr root;
    int M;
    int T;
} *BTree;

BTree btreeInit(int t);
void btreeInsert(BTree tree, keyType key);
