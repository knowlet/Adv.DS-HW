#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
    short int bf;
} treeNode;

void avlInsert(treeNode** parent, int key, bool* unbalanced);
void avlErase(treeNode** parent, int key, bool* unbalanced);
void freeTree(treeNode* root);
void infixOrder(treeNode* root);
void prefixOrder(treeNode* root);
void postfixOrder(treeNode* root);