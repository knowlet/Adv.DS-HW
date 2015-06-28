#include "bTree.h"
#include <math.h>

static bTreePtr newNode(int m, short isLeaf)
{
    bTreePtr new = malloc(sizeof(struct bTreeNode));
    new->child = calloc(m, sizeof(bTreePtr));
    new->key = calloc(m - 1, sizeof(keyType));
    new->isLeaf = isLeaf;
    new->size = 0;
    return new;
}

BTree btreeInit(int m)
{
    BTree tree = malloc(sizeof(struct bTree));
    tree->M = m;
    tree->root = newNode(tree->M, 1);
    tree->T = ceil((double)m / 2.0);
    return tree;
}

static void splitChild(BTree tree, bTreePtr parent, int i)
{
    int j, t = tree->T;
    
    bTreePtr node = parent->child[i];
    bTreePtr z = newNode(tree->M, node->isLeaf);
    
    for (j = 0; j < t-1; ++j) {
        z->key[j] = node->key[j+t];
    }
    if (!node->isLeaf) {
        for (j = 0; j < t; ++j) {
            z->child[j] = node->child[j+t];
        }
    }
    node->size = t-1;
    for (j = parent->size; j > i; --j) {
        parent->child[j+1] = parent->child[j];
    }
    parent->child[i+1] = z;
    for (j = parent->size-1; j >= i; --j) {
        parent->key[j+1] = parent->key[j];
    }
    parent->key[i] = node->key[t-1];
    parent->size += 1;
}

static void insertNonFull(BTree tree, bTreePtr node, keyType key)
{
    int i = node->size - 1;
    
    if (node->isLeaf == 1) {
        while(i >= 0 && node->key[i] > key) {
            node->key[i+1] = node->key[i];
            --i;
        }
        node->key[i+1] = key;
        node->size += 1;
    }
    else {
        while (i >= 0 && node->key[i] > key) --i;
        if (node->child[i+1]->size == tree->M-1) {
            splitChild(tree, node, i+1);
            if (key > node->key[i+1]) ++i;
        }
        insertNonFull(tree, node->child[i+1], key);
    }

}

void btreeInsert(BTree tree, keyType key)
{
    bTreePtr root = tree->root;
    if (tree->root->size == tree->M-1) {
        bTreePtr node = newNode(tree->M, 0);
        tree->root = node;
        node->child[0] = root;
        splitChild(tree, node, 0);
        // int i = 0;
        // if (node->key[0] < key) ++i;
        // insertNonFull(tree, node->child[i], key);
        insertNonFull(tree, node, key);
    }
    else {
        insertNonFull(tree, root, key);
    }
}