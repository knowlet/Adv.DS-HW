#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 20

typedef struct _node *nodePointer;
typedef struct _node {
    int vertex;
    int duration;
    nodePointer link;
} node;
typedef struct {
    int count;
    nodePointer link;
} hdnodes;
hdnodes graph[MAX_VERTICES];
int earliest[MAX_VERTICES] = {};
int latest[MAX_VERTICES] = {};
int order[MAX_VERTICES] = {};

void topSort(int n)
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
            order[i] = j = top;    /* unstack a vertex */
            top = graph[top].count;
            printf("v%d, ", j);
            for (ptr = graph[j].link; ptr; ptr = ptr->link) {
                /* decrease the count of the successor vertices of j */
                k = ptr->vertex;
                if (earliest[k] < earliest[j] + ptr->duration)
                    earliest[k] = earliest[j] + ptr->duration;
                --graph[k].count;
                if (!graph[k].count) {
                    /* add vertex k to the stack */
                    graph[k].count = top;
                    top = k;
                }
            }
        }
}

nodePointer createNode(int vertex, int duration)
{
    nodePointer newNode;
    newNode = malloc(sizeof(node));
    newNode->vertex = vertex;
    newNode->duration = duration;
    newNode->link = NULL;
    return newNode;
}

void insertNode(int k, int vertex, int duration)
{
    nodePointer prev, ptr;
    for (prev = (nodePointer)&graph[k], ptr = graph[k].link; ptr; ptr = ptr->link)
        prev = ptr;
    prev->link = createNode(vertex, duration);
    ++graph[vertex].count;
}

void calcLatestTime(int n)
{
    nodePointer ptr;
    int i, j, k;
    for (i = 0; i < n; ++i)
        latest[i] = earliest[n-1];
    while (i--) {
        j = order[i];
        for (ptr = graph[j].link; ptr; ptr = ptr->link) {
            k = ptr->vertex;
            if (latest[j] > latest[k] - ptr->duration)
                latest[j] = latest[k] - ptr->duration;
        }
    }
}

int main(int argc, const char *argv[])
{
    int i, n, edge, k, vertex, duration;
    scanf("%d %d", &n, &edge);
    for (i = 0; i < edge && scanf("%d %d %d", &k, &vertex, &duration); ++i)
        insertNode(k, vertex, duration);
    topSort(n);
    calcLatestTime(n);

    return 0;
}
