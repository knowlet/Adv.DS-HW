#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 20

typedef struct node *nodePointer;
struct node {
    int vertex;
    nodePointer link;
};
typedef struct {
    int count;
    nodePointer link;
} hdnodes;
hdnodes graph[MAX_VERTICES];

void tmpSort(hdnodes graph[], int n)
{
    int i, j, k, top;
    nodePointer ptr;
    /* create a stack of vertices with no predecessors */
    top = -1;
    for (i = 0; i < n; ++i)
        if (!graph[i].count) {
            graph[i].count = top;
            top = i;
        }
    for (i = 0; i < n; ++i)
        if (top == -1) {
            fprintf(stderr, "\n%s\n", "Network has a cycle. Sort terminated.");
            exit(EXIT_FAILURE);
        }
        else {
            j = top;
            top = graph[top].count;
            printf("v%d, ", j);
            for (ptr = graph[j].link; ptr; ptr = ptr->link) {
                /* decrease the count of the successor vertices of j */
                k = ptr->vertex;
                --graph[k].count;
                if (!graph[k].count) {
                    /* add vertex k to the stack */
                    graph[k].count = top;
                    top = k;
                }
            }
        }
}

int main(int argc, const char *argv[])
{
    
    return 0;
}
