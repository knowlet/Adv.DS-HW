#include <ctype.h>
#include <string.h>
#include "AVLTree.h"
#define consoleX 80
#define consoleY 24
#define W 5

int maxHeight(treeNode *p)
{
    if (!p) return 0;
    int left_height = maxHeight(p->left);
    int right_height = maxHeight(p->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

int _printT(treeNode* tree, bool isLeft, int offset, int level, char s[consoleY+1][consoleX+1])
{
    int left, right;
    if (!tree) return 0;
    left  = _printT(tree->left, true, offset, level+1, s);
    right = _printT(tree->right, false, offset+left+W, level+1, s);
    sprintf(&s[2*level][offset+left], "(%03d)", tree->key);
    s[2*level][offset+left+W] = 32;
    if (level) {
        int y = 2 * level - 1, w = W / 2;
        if (isLeft) {
            memset(&s[y][offset+left+w], '-', W+right);
            s[y][offset+left+w] = '/';
            s[y][offset+left+W+right+w] = '*';
        }
        else {
            memset(&s[y][offset-w], '-', left+W);
            s[y][offset+left+w] = '\\';
            s[y][offset-w-1] = '*';
        }
    }
    return left + W + right;
}

void printT(treeNode *tree)
{
    char s[consoleY+1][consoleX+1];
    int i, j, height = maxHeight(tree) * 2;
    if (!height) {
        puts("Empty!");
        return;
    }
    memset(s, 32, sizeof(s));
    _printT(tree, 0, 0, 0, s);
    for (i = 0; i < height; ++i) {
        putchar(10);
        for (j = 0; j < consoleX; ++j)
            putchar(s[i][j]);
    }
    puts("");
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
        // printf("Enter 'I' to insert node, 'D' to delete node, 'C' to clear the tree, 'S' to show tree, 'X' to exit: ");
        scanf("%s", &code);
        switch (toupper(code)) {
            case 'I':
                // printf("Enter the value of node: ");
                scanf("%d", &key);
                avlInsert(&avlTree, key, &unbalanced);
                break;
                
            case 'D':
                // printf("Enter the value of node: ");
                scanf("%d", &key);
                avlErase(&avlTree, key, &unbalanced);
                break;
                
            case 'C':
                freeTree(avlTree);
                avlTree = NULL;
                unbalanced = false;
                break;
                
            // case 'S':
                // horizonDisplay(avlTree, avlTree, 1);
                // puts("");
                
            default:
                break;
        }
        printT(avlTree);
    }
    // printf("cleaning up...");
    freeTree(avlTree);
    // puts("\nGood bye~");
    return 0;
}
