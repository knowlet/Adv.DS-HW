#include "LeftistTree.h"

void minMeldW(leftistTree *a, leftistTree *b)
{   /*
     meld the two min leftist trees *a and *b. The resulting min leftist tree
     is returned in *a, and *b is set to NULL
     */
    if (!*a) *a = *b;
    else if (*b) minUnionW(a, b);
    *b = NULL;
}

void minUnionW(leftistTree *a, leftistTree *b)
{
    /* The shortest here is weight */
    leftistTree temp;
    /* set a to be the tree with smaller root */
    if ((*a)->data.key > (*b)->data.key) SWAP(*a, *b, temp);
    (*a)->shortest += (*b)->shortest;
    /*
     create binary tree such that the smallest key
     in each subtree is in the root
     */
    if (!(*a)->rightChild) (*a)->rightChild = *b;
    else minUnionW(&(*a)->rightChild, b);
    
    /* leftist tree property */
    if (!(*a)->leftChild) {
        (*a)->leftChild = (*a)->rightChild;
        (*a)->rightChild = NULL;
    }
    else if ((*a)->leftChild->shortest < (*a)->rightChild->shortest)
        SWAP((*a)->leftChild, (*a)->rightChild, temp);
}

void insertNodeW(leftistTree *a, int key)
{
    leftistTree pNode = newNode(key);
    minMeldW(a, &pNode);
}

void deleteNodeW(leftistTree *a)
{
    if (*a) {
        minMeldW(&(*a)->leftChild, &(*a)->rightChild);
        delNode(a);
    } else puts("empty tree!");
}
