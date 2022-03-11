// LCA最近公共祖先 倍增算法
// accepted
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
const int SIZE = 50010;
int f[SIZE][20], d[SIZE], dist[SIZE], tot, head[SIZE], t, n, m;
struct Edge
{
    int next;
    int v;
    int w;
};
Edge e[SIZE << 1];
queue<int> q;
void addEdge(int x, int y, int z)
{
    e[++tot].v = y;
    e[tot].w = z;
    e[tot].next = head[x];
    head[x] = tot;
}
// 计算树上节点的深度，用数组d存
void bfs()
{
    q.push(1);
    d[1] = 1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = e[i].next)
        {
            int y = e[i].v;
            if (d[y])
                continue;
            d[y] = d[x] + 1;
            dist[y] = dist[x] + e[i].w;
            f[y][0] = x;
            for (int j = 1; j <= t; j++)
                f[y][j] = f[f[y][j - 1]][j - 1];
            q.push(y);
        }
    }
}
int lca(int x, int y)
{
    if (d[x] > d[y])
        swap(x, y);
    for (int i = t; i >= 0; i--)
        if (d[f[y][i]] >= d[x])
            y = f[y][i];
    if (x == y)
        return x;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        t = (int)log(n) / log(2) + 1;
        memset(head, 0, sizeof(int) * (n + 1));
        memset(d, 0, sizeof(int) * (n + 1));
        tot = 0;
        for (int i = 1; i < n; i++)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            addEdge(x, y, z);
            addEdge(y, x, z);
        }
        bfs();
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%d\n", dist[x] + dist[y] - 2 * dist[lca(x, y)]);
        }
    }
    return 0;
}