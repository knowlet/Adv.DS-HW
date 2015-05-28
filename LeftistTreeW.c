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
    leftistTree temp, *A = a;
    while (*a) {
        /* set a to be the tree with smaller root */
        if ((*a)->data.key > (*b)->data.key) SWAP(*a, *b, temp);
        /* calc the weight of the node */
        (*a)->shortest += (*b)->shortest;
        if (!(*a)->rightChild) {
            if (!(*a)->leftChild) (*a)->leftChild = *b;
            else {
                (*a)->rightChild = *b;
                if((*a)->leftChild->shortest < (*a)->rightChild->shortest)
                    SWAP((*a)->leftChild, (*a)->rightChild, temp);
            }
            *b = NULL;
            if (!(*A)->leftChild) {
                (*A)->leftChild = (*A)->rightChild;
                (*A)->rightChild = NULL;
            }
            else if ((*A)->rightChild)
                if ((*A)->leftChild->shortest < (*A)->rightChild->shortest)
                    SWAP((*A)->leftChild, (*A)->rightChild, temp);
            break;
        }
        if((*A)->leftChild->shortest < (*A)->rightChild->shortest){
            SWAP((*A)->leftChild, (*A)->rightChild, temp);
            a = &(*A)->leftChild;
        }
        A = a;
        a = &(*a)->rightChild;
    }
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
