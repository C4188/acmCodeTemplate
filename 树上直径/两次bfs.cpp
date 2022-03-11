// 水图 两次bfs可以用来求树的直径
// accepted
#include <stdio.h>
#include <queue>
// #include <vector>
#include <string.h>
using namespace std;
typedef unsigned long long ull;
const int MAXN = 5e4 + 5;
int head[MAXN], E_Cnt = 1, n, x, visited[MAXN];
struct Edge{
    int v;
    ull w;
    int next;
};
Edge e[MAXN << 1];
void addEdge(int u, int v, ull w)
{
    e[E_Cnt].next = head[u];
    e[E_Cnt].v = v;
    e[E_Cnt].w = w;
    head[u] = E_Cnt++;
}
typedef pair<ull, int> pii;
// priority_queue<pii> pq;
queue<pii> pq;
ull maxlen;
int bfs(int m)
{
    int maxIndex;
    maxlen = 0;
    memset(visited, 0, sizeof(visited));
    pq.push(make_pair(0, m));
    while(!pq.empty())
    {
        ull d = pq.front().first;
        int u = pq.front().second;
        pq.pop();
        if(visited[u])    continue;
        visited[u] = 1;
        if(maxlen < d){
            maxlen = d;
            maxIndex = u;
        }
        for(int i = head[u]; i; i = e[i].next)
        {
            pq.push(make_pair(e[i].w + d, e[i].v));
        }
    }
    return maxIndex;
}
int main()
{
    // n 为边数 x 为起始点(求树上直径起始点无所谓)
    scanf("%d%d", &n, &x);
    int u, v;
    ull w, sum = 0;
    for(int i = 0; i < n - 1; i++)
    {
        scanf("%d%d%llu", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        sum += w;
    }
    sum <<= 1;
    bfs(x);
    // 两次bfs  bfs(bfs(x));
    // maxlen即为直径 w 为一条边的长度
    printf("%llu\n", sum - maxlen);
    return 0;
}