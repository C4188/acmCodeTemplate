#include <stdio.h>
const int MAX = 50005;
int head[MAX], tot;
struct Edge{
    int v;
    int next;
    int w;
};
Edge e[MAX << 1];
void addEdge(int u, int v, int w)
{
    e[++tot].v = v;
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot;
}
int findEdge(int u, int v)
{
    for(int i = head[u]; i; i = e[i].next)
        if(e[i].v == v)
            return e[i].w;
    return -1;
}