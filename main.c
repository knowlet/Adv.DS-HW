//
//  main.c
//  LeftistTree
//
//  Created by KNowlet on 2015/5/17.
//  Copyright (c) 2015年 KNowlet. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "LeftistTree.h"
#define CONSOLEX 80
#define CONSOLEY 24
#define W 5

int maxHeight(leftistTree p)
{
    if (!p) return 0;
    int left_height = maxHeight(p->leftChild);
    int right_height = maxHeight(p->rightChild);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

int _print(leftistTree tree, bool isLeft, int offset, int level, char s[CONSOLEY+1][CONSOLEX+1])
{
    int left, right;
    if (!tree) return 0;
    left  = _print(tree->leftChild, true, offset, level+1, s);
    right = _print(tree->rightChild, false, offset+left+W, level+1, s);
    sprintf(&s[2*level][offset+left], "(%03d)", tree->data.key);
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

void printTree(leftistTree tree)
{
    char s[CONSOLEY+1][CONSOLEX+1];
    int i, j, height = maxHeight(tree) * 2;
    if (!height) {
        puts("Empty!");
        return;
    }
    memset(s, 32, sizeof(s));
    _print(tree, 0, 0, 0, s);
    for (i = 0; i < height; ++i) {
        putchar(10);
        for (j = 0; j < CONSOLEX; ++j)
            putchar(s[i][j]);
    }
    puts("");
}

int main(int argc, char const *argv[])
{
    FILE* streamSrc;
    char cmd[W];
    int key;
    if ((streamSrc=fopen("left tree.txt", "r")) == NULL) {
        perror("\"left tree.txt\" open error");
        exit(EXIT_FAILURE);
    }
    leftistTree tree = NULL;
    while (fscanf(streamSrc, "%s", cmd) != EOF) {
        switch (toupper(*cmd)) {
            case 'I':
                fscanf(streamSrc, "%d", &key);
                insertNode(&tree, key);
                break;
            case 'D':
                deleteNode(&tree);
        }
    }
    leftistTree tree2 = NULL;
    rewind(streamSrc);
    while (fscanf(streamSrc, "%s", cmd) != EOF) {
        switch (toupper(*cmd)) {
            case 'I':
                fscanf(streamSrc, "%d", &key);
                insertNode(&tree2, key);
                break;
            case 'D':
                deleteNode(&tree2);
        }
    }
    return 0;
}