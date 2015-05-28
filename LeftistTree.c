#include "LeftistTree.h"

void minMeld(leftistTree *a, leftistTree *b)
{   /*
    meld the two min leftist trees *a and *b. The resulting min leftist tree
    is returned in *a, and *b is set to NULL
    */
    if (!*a) *a = *b;
    else if (*b) minUnion(a, b);
    *b = NULL;
}

void minUnion(leftistTree *a, leftistTree *b)
{
    /* recursively combine two nonempty min leftist trees */
    leftistTree temp;
    /* set a to be the tree with smaller root */
    if ((*a)->data.key > (*b)->data.key) SWAP(*a, *b, temp);

    /*
    create binary tree such that the smallest key
    in each subtree is in the root
    */
    if (!(*a)->rightChild) (*a)->rightChild = *b;
    else minUnion(&(*a)->rightChild, b);

    /* leftist tree property */
    if (!(*a)->leftChild) {
        (*a)->leftChild = (*a)->rightChild;
        (*a)->rightChild = NULL;
    }
    else if ((*a)->leftChild->shortest < (*a)->rightChild->shortest)
        SWAP((*a)->leftChild, (*a)->rightChild, temp);
    (*a)->shortest = (!(*a)->rightChild) ? 1 : (*a)->rightChild->shortest + 1;
}

void insertNode(leftistTree *a, int key)
{
    leftistTree pNode = malloc(sizeof(struct leftist));
    pNode->leftChild = NULL;
    pNode->data.key = key;
    pNode->rightChild = NULL;
    pNode->shortest = 1;
    minMeld(a, &pNode);
}

void deleteNode(leftistTree *a)
{
    leftistTree pNode = NULL;
    if (*a) {
        minMeld(&(*a)->leftChild, &(*a)->rightChild);
        pNode = (*a)->leftChild;
        printf("%d\n", (*a)->data.key);
        (*a)->leftChild = NULL;
        (*a)->rightChild = NULL;
        (*a)->data.key = 0;
        free(*a);
        *a = pNode;
    } else puts("empty tree!");
}

