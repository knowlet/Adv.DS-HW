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
int path[MAX_VERTICES] = {};

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

void traversal(int start, int end, int n)
{
    nodePointer ptr;
    int i;
    if (start == end) {
        for (i = 0; i < n; ++i) printf("%d ", path[i]);
        printf("%d\n", start);
    }
    else
        for (path[n] = start, ptr = graph[start].link; ptr; ptr = ptr->link)
            if (earliest[start] == latest[ptr->vertex] - ptr->duration)
                traversal(ptr->vertex, end, n + 1);
}

int CriticalPath(int n)
{
    nodePointer ptr;
    int i;
    for (i = 1; i < n; ++i)
        if (!earliest[i]){
            fprintf(stderr, "\n%s\n", "Network Unreacheable.");
            exit(EXIT_FAILURE);
        }
    printf("\netv:");
    for (i = 0; i < n; ++i) printf("%3d", earliest[i]);
    puts("");
    for (i = 0; i < n; ++i)
        latest[i] = earliest[n-1];
    while (i--)
        for (ptr = graph[order[i]].link; ptr; ptr = ptr->link)
            if (latest[order[i]] > latest[ptr->vertex] - ptr->duration)
                latest[order[i]] = latest[ptr->vertex] - ptr->duration;
    printf("ltv:");
    for (i = 0; i < n; ++i) printf("%3d", latest[i]);
    puts("");
    traversal(0, n - 1, 0);
    return earliest[n-1];
}

int main(int argc, const char *argv[])
{
    int i, n, edge, k, vertex, duration;
    scanf("%d %d", &n, &edge);
    for (i = 0; i < edge && scanf("%d %d %d", &k, &vertex, &duration); ++i)
        insertNode(k, vertex, duration);
    topSort(n);
    printf("Critical Length: %d\n", CriticalPath(n));
    return 0;
}
