#include "bTree.h"
#include <ctype.h>

int main(int argc, const char * argv[])
{
    BTree tree = NULL;
    int i, m;
    keyType key;
    char cmd[5];
    scanf("%d", &m);
    tree = btreeInit(m);
    while (scanf("%s %d", cmd, &key) != EOF) {
        if (tolower(*cmd) == 'i')
            btreeInsert(tree, key);
        if (tolower(*cmd) == 'd')
            btreeRemove(tree, &tree->root, key);
    }
    printf("%d keys in root:\n", tree->root->size);
    for (i = 0; i < tree->root->size; ++i) {
        printf(" %d", tree->root->key[i]);
    }
    puts("\ntraverse:");
    btreeTraverse(tree->root);
    return 0;
}
