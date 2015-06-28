#include <stdio.h>
#include "bTree.h"

int main(int argc, const char * argv[])
{
    char array[] = { 'C', 'N', 'G', 'A', 'H', 'E', 'K', 'Q', 'M', 'F', 'W', 'L', 'T', 'Z', 'D', 'P', 'R', 'X', 'Y', 'S' };
    int length = sizeof(array)/sizeof(char);
    BTree tree = NULL;
    tree = btreeInit(5);
    int i;
    for (i = 0; i < length; ++i) {
        btreeInsert(tree, array[i]);
    }
    for (i = 0; i < tree->root->child[0]->child[0]->size; ++i) {
        printf("%c ", tree->root->child[0]->child[0]->key[i]);
    }
    puts("");
    // for (i = 0; i < bTree.top->items[0].child->size; ++i) {
        // printf("%c ", *(int*)bTree.top->items[0].child->items[i].value);
    // }
    puts("");
    return 0;
}
