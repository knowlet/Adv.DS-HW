#include <stdio.h>
#include <ctype.h>
#include "AVLTree.h"

int maxHeight(treeNode *p) {
    if (!p) return 0;
    int left_height = maxHeight(p->left);
    int right_height = maxHeight(p->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

int _printT(treeNode *tree, bool isLeft, int offset, int level, char s[25][81])
{
    static const int W = 5; // 3 + 2, -99 ~ 999
    char key[W+1];
    if (!tree) return 0;
    sprintf(key, "(%03d)", tree->key);
    int left  = _printT(tree->left, true, offset, level + 1, s);
    int right = _printT(tree->right, false, offset+left+W, level+1, s);
    for (int i = 0; i < W; ++i)
        s[2*level][offset+left+i] = key[i];
    if (level) {
        if (isLeft) {
            for (int i = 0; i < W+right; ++i)
                s[2*level-1][offset+left+W/2+i] = '-';
            s[2*level-1][offset+left+W/2] = '/';    // L
            s[2*level-1][offset+left+W+right+W/2] = '*';
        }
        else {
            for (int i = 0; i < left+W-1; ++i)
                s[2*level-1][offset-W/2+i] = '-';
            s[2*level-1][offset+left+W/2] = '\\';    // R
            s[2*level-1][offset-W/2-1] = '*';
        }
    }
    return left + W + right;
}

void printT(treeNode *tree)
{
    char s[25][81];
    int height = maxHeight(tree) * 2;
    if (!height) {
        puts("Empty!");
        return;
    }
    for (int i = 0; i < 24; i++)
        sprintf(s[i], "%80s", " ");
    _printT(tree, 0, 0, 0, s);
    puts("");
    for (int i = 0; i < height; ++i)
        printf("%s\n", s[i]);
}

void horizonDisplay(treeNode* root, treeNode* ptr, int level)
{
    int i;
    if (ptr!=NULL) {
        horizonDisplay(root, ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
            printf("--> ");
        for (i = 0; i < level && ptr != root; i++)
            printf("\t");
        printf("%d", ptr->key);
        horizonDisplay(root, ptr->left, level + 1);
    }
}

int main(int argc, const char * argv[])
{
    treeNode* avlTree = NULL;
    bool unbalanced = false;
    char code = 0;
    int key = 0;
    while (toupper(code) != 'X') {
        printf("Enter 'I' to insert node, 'E' to erase node, 'C' to clear the tree, 'D' to display tree, 'X' to exit: ");
        scanf("%s", &code);
        switch (toupper(code)) {
            case 'I':
                printf("Enter the value of node: ");
                scanf("%d", &key);
                avlInsert(&avlTree, key, &unbalanced);
                break;
                
            case 'E':
                printf("Enter the value of node: ");
                scanf("%d", &key);
                avlErase(&avlTree, key, &unbalanced);
                break;
                
            case 'C':
                freeTree(avlTree);
                avlTree = NULL;
                unbalanced = false;
                break;
                
            case 'D':
                // horizonDisplay(avlTree, avlTree, 1);
                printT(avlTree);
                // puts("");
                
            default:
                break;
        }
        puts("");
    }
    printf("cleaning up...");
    freeTree(avlTree);
    printf("\nGood bye~\n");
    return 0;
}
