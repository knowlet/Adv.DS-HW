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

leftistTree newNode(int key)
{
    leftistTree node = malloc(sizeof(struct leftist));
    node->leftChild = NULL;
    node->data.key = key;
    node->rightChild = NULL;
    node->shortest = 1;
    return node;
}

void insertNode(leftistTree *a, int key)
{
    leftistTree pNode = newNode(key);
    minMeld(a, &pNode);
}

void delNode(leftistTree *a)
{
    leftistTree pNode = (*a)->leftChild;
    printf("%d\n", (*a)->data.key);
    (*a)->leftChild = NULL;
    (*a)->rightChild = NULL;
    (*a)->data.key = 0;
    free(*a);
    *a = pNode;
}

void deleteNode(leftistTree *a)
{
    if (*a) {
        minMeld(&(*a)->leftChild, &(*a)->rightChild);
        delNode(a);
    } else puts("empty tree!");
}

