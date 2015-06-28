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
        int i = 0;
        if (node->key[0] < key) ++i;
        insertNonFull(tree, node->child[i], key);
        // insertNonFull(tree, node, key);
    }
    else {
        insertNonFull(tree, root, key);
    }
}

static void mergeChild(BTree tree, bTreePtr node, int i)
{
    int j, key = node->key[i];
    bTreePtr prevChild = node->child[i];
    bTreePtr nextChild = node->child[i + 1];
    
    assert(prevChild && prevChild->size == tree->T - 1 && nextChild && nextChild->size == tree->T - 1);
    
    prevChild->key[prevChild->size] = key;
    prevChild->child[prevChild->size + 1] = nextChild->child[0];
    ++prevChild->size;
    
    for (j = 0; j < nextChild->size; ++j) {
        prevChild->key[prevChild->size] = nextChild->key[j];
        prevChild->child[prevChild->size + 1] = nextChild->child[j + 1];
        ++prevChild->size;
    }
    
    for (j = i; j < node->size - 1; ++j) {
        node->key[j] = node->key[j + 1];
        node->child[j + 1] = node->child[j + 2];
    }
    
    node->key[node->size - 1] = 0;
    node->child[node->size] = NULL;
    --node->size;
    
    if (node->size == 0) {
        if (tree->root == node) {
            tree->root = prevChild;
        }
        // free(node);
        node = NULL;
    }
    free(nextChild);
    nextChild = NULL;
}

void btreeRemove(BTree tree, bTreePtr* parent, keyType key)
{
    int i, j, index;
    bTreePtr root =*parent;
    bTreePtr node = root;
    bTreePtr prevChild, nextChild, child;
    keyType prevKey, nextKey;
    
    if (!root) {
        printf("Failed to remove %c, it is not in the tree!\n", key);
        return;
    }
    index = 0;
    while (index < node->size && key > node->key[index]) {
        ++index;
    }
    if (index < node->size && node->key[index] == key) {
        if (node->isLeaf) {
            for (i = index; i < node->size; ++i) {
                node->key[i] = node->key[i + 1];
                node->child[i] = node->child[i + 1];
            }
            --node->size;
            if (node->size == 0) {
                assert(node == *parent);
                free(node);
                parent = NULL;
            }
            return;
        }
        else if (node->child[index]->size >= tree->T) {
            prevChild = node->child[index];
            prevKey = prevChild->key[prevChild->size - 1];
            node->key[index] = prevKey;
            
            btreeRemove(tree, &prevChild, prevKey);
        }
        else if (node->child[index + 1]->size >= tree->T) {
            nextChild = node->child[index + 1];
            nextKey = nextChild->key[0];
            node->key[index] = nextKey;
            
            btreeRemove(tree, &nextChild, nextKey);
        }
        else if (node->child[index]->size == tree->T - 1
                 && node->child[index + 1]->size == tree->T - 1){
            prevChild = node->child[index];
            mergeChild(tree, node, index);
            btreeRemove(tree, &prevChild, key);
        }
    }
    else {
        child = node->child[index];
        if (!child) {
            printf("Failed to remove %d, it is not in the tree!\n", key);
            return;
        }
        
        if (child->size == tree->T - 1) {
            prevChild = NULL;
            nextChild = NULL;
            
            if (index - 1 >= 0) {
                prevChild = node->child[index - 1];
            }
            
            if (index + 1 <= node->size) {
                nextChild = node->child[index + 1];
            }
            if ((prevChild && prevChild->size >= tree->T)
                || (nextChild && nextChild->size >= tree->T)) {
                
                if (nextChild && nextChild->size >= tree->T) {
                    child->key[child->size] = node->key[index];
                    child->child[child->size + 1] = nextChild->child[0];
                    ++child->size;
                    
                    node->key[index] = nextChild->key[0];
                    
                    for (j = 0; j < nextChild->size - 1; ++j) {
                        nextChild->key[j] = nextChild->key[j + 1];
                        nextChild->child[j] = nextChild->child[j + 1];
                    }
                    --nextChild->size;
                }
                else {
                    for (j = child->size; j > 0; --j) {
                        child->key[j] = child->key[j - 1];
                        child->child[j + 1] = child->child[j];
                    }
                    child->child[1] = child->child[0];
                    child->child[0] = prevChild->child[prevChild->size];
                    child->key[0] = node->key[index - 1];
                    ++child->size;
                    
                    node->key[index - 1] = prevChild->key[prevChild->size - 1];
                    --prevChild->size;
                }
            }
            else if ((!prevChild || (prevChild && prevChild->size == tree->T - 1))
                     && ((!nextChild || (nextChild && nextChild->size == tree->T - 1)))) {
                if (prevChild && prevChild->size == tree->T - 1) {
                    mergeChild(tree, node, index - 1);
                    child = prevChild;
                }
                
                else if (nextChild && nextChild->size == tree->T - 1) {
                    mergeChild(tree, node, index);
                }
            }
        }
        btreeRemove(tree, &child, key);
    }
}

static void traverseRecurse(bTreePtr x)
{
    int i;
    for (i = 0; i < x->size; ++i) {
        if (!x->isLeaf) traverseRecurse(x->child[i]);
        printf("%d ", x->key[i]);
    }
    if (!x->isLeaf) traverseRecurse(x->child[i]);
}

void btreeTraverse(bTreePtr x)
{
    traverseRecurse(x);
    puts("");
}