#include "AVLTree.h"

treeNode* newNode(int key)
{
    treeNode* pNode;
    pNode = malloc(sizeof(treeNode));
    pNode->bf = 0;
    pNode->key = key;
    pNode->left = NULL;
    pNode->right = NULL;
    return pNode;
}

void leftRotation(treeNode** parent, bool* unbalanced)
{
    treeNode* grandChild;
    treeNode* child = (*parent)->left;
    if (child->bf == 1) {
        // LL
        (*parent)->left = child->right;
        child->right = *parent;
        (*parent)->bf = 0;
        *parent = child;
    }
    else {
        // LR
        grandChild = child->right;
        child->right = grandChild->left;
        grandChild->left = child;
        (*parent)->left = grandChild->right;
        grandChild->right = *parent;
        switch (grandChild->bf) {
            case 1:
                (*parent)->bf = -1;
                child->bf = 0;
                break;
                
            case 0:
                (*parent)->bf = child->bf = 0;
                break;
                
            case -1:
                (*parent)->bf = 0;
                child->bf = 1;
        }
        *parent = grandChild;
    }
    (*parent)->bf = 0;
    *unbalanced = false;
}

void rightRotation(treeNode** parent, bool* unbalanced)
{
    treeNode* grandChild;
    treeNode* child = (*parent)->right;
    if (child->bf == -1) {
        // RR
        (*parent)->right = child->left;
        child->left = *parent;
        (*parent)->bf = 0;
        *parent = child;
    }
    else {
        // RL
        grandChild = child->left;
        child->left = grandChild->right;
        grandChild->right = child;
        (*parent)->right = grandChild->left;
        grandChild->left = *parent;
        switch (grandChild->bf) {
            case -1:
                (*parent)->bf = 1;
                child->bf = 0;
                break;
                
            case 0:
                (*parent)->bf = child->bf = 0;
                break;
                
            case 1:
                (*parent)->bf = 0;
                child->bf = -1;
        }
        *parent = grandChild;
    }
    (*parent)->bf = 0;
    *unbalanced = false;
}

void avlInsert(treeNode** parent, int key, bool* unbalanced)
{
    if (!*parent) {
        *parent = newNode(key);
        *unbalanced = true;
    }
    else if (key < (*parent)->key) {
        avlInsert(&(*parent)->left, key, unbalanced);
        if (*unbalanced)
            switch ((*parent)->bf) {
                case -1:
                    (*parent)->bf = 0;
                    *unbalanced = false;
                    break;
                    
                case 0:
                    (*parent)->bf = 1;
                    break;
                    
                case 1:
                    leftRotation(parent, unbalanced);
            }
    }
    else if (key > (*parent)->key) {
        avlInsert(&(*parent)->right, key, unbalanced);
        if (*unbalanced)
            switch ((*parent)->bf) {
                case 1:
                    (*parent)->bf = 0;
                    *unbalanced = false;
                    break;
                    
                case 0:
                    (*parent)->bf = -1;
                    break;
                    
                case -1:
                    rightRotation(parent, unbalanced);
            }
    }
    else {
        *unbalanced = false;
        puts("The key is already in the tree!");
    }
}

bool isLeaf(treeNode* p)
{
    return p->left == NULL && p->right == NULL;
}

void delLR(treeNode** parent, bool* unbalanced)
{
    treeNode* grandChild;
    treeNode* child = (*parent)->left;
    if (child->bf == 1) {
        // LL
        (*parent)->left = child->right;
        child->right = *parent;
        (*parent)->bf = 0;
        *parent = child;
        (*parent)->bf = 0;
    }
    else {
        // LR
        grandChild = child->right;
        child->right = grandChild->left;
        grandChild->left = child;
        (*parent)->left = grandChild->right;
        grandChild->right = *parent;
        switch (grandChild->bf) {
            case -1:
                (*parent)->bf = -1;
                child->bf = 0;
                break;
                
            case 1:
                (*parent)->bf = child->bf = 0;
                break;
                
            case 0:
                (*parent)->bf = 0;
                child->bf = 1;
                grandChild->bf = 1;
        }
        *parent = grandChild;
    }
    *unbalanced = false;
}

void delRR(treeNode** parent, bool* unbalanced)
{
    treeNode* grandChild;
    treeNode* child = (*parent)->right;
    if (child->bf == -1) {
        // RR
        (*parent)->right = child->left;
        child->left = *parent;
        (*parent)->bf = 0;
        *parent = child;
        (*parent)->bf = 0;
    }
    else {
        // RL
        grandChild = child->left;
        child->left = grandChild->right;
        grandChild->right = child;
        (*parent)->right = grandChild->left;
        grandChild->left = *parent;
        switch (grandChild->bf) {
            case -1:
                (*parent)->bf = 1;
                child->bf = 0;
                break;
                
            case 1:
                (*parent)->bf = child->bf = 0;
                break;
                
            case 0:
                (*parent)->bf = 0;
                child->bf = -1;
                grandChild->bf = -1;
        }
        *parent = grandChild;
    }
    *unbalanced = false;
}

int delMinNode(treeNode** p, bool* unbalanced)
{
    treeNode* prev = (*p)->right;
    treeNode* node = (*p)->left;
    while (node != NULL){
        prev = node;
        node = node->right;
    }
    avlErase(p, prev->key, unbalanced);
    return prev->key;
}

void avlErase(treeNode** parent, int key, bool* unbalanced)
{
    if (!*parent) {
        *unbalanced = false;
        puts("The key is not in the tree!");
        return;
    }
    else if (key < (*parent)->key) {
        avlErase(&(*parent)->left, key, unbalanced);
        if (*unbalanced)
            switch ((*parent)->bf) {
                case 1:
                    (*parent)->bf = 0;
                    break;
                    
                case 0:
                    (*parent)->bf = -1;
                    *unbalanced = false;
                    break;
                    
                case -1:
                    delRR(parent, unbalanced);
                    *unbalanced = true;
            }
    }
    else if (key > (*parent)->key) {
        avlErase(&(*parent)->right, key, unbalanced);
        if (*unbalanced)
            switch ((*parent)->bf) {
                case -1:
                    (*parent)->bf = 0;
                    break;
                    
                case 0:
                    (*parent)->bf = 1;
                    *unbalanced = false;
                    break;
                    
                case 1:
                    delLR(parent, unbalanced);
                    *unbalanced = true;
            }
    }
    else if (isLeaf(*parent)) {
        free(*parent);
        *parent = NULL;
        *unbalanced = true;
    }
    else
        (*parent)->key = delMinNode(parent, unbalanced);
}

void freeTree(treeNode* root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    root->left = root->right = NULL;
    root->key = 0;
    free(root);
}

void infixOrder(treeNode* root)
{
    if(root==NULL) return;
    infixOrder(root->left);
    printf("%d ", root->key);
    infixOrder(root->right);
}

void prefixOrder(treeNode* root)
{
    if(root==NULL) return;
    printf("%d ", root->key);
    prefixOrder(root->left);
    prefixOrder(root->right);
}

void postfixOrder(treeNode* root)
{
    if(root==NULL) return;
    postfixOrder(root->left);
    postfixOrder(root->right);
    printf("%d ", root->key);
}