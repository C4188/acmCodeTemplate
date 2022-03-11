// 标准模板 dijkstra算法 链式前向星存图 最小堆优化
// accepted
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX = 100005;
typedef pair<int, int> pii;
struct Edge{
    int v;
    int w;
    int next;
};
Edge e[MAX << 1];
int head[MAX], E_Cnt = 1, visited[MAX], n, m, s, dist[MAX];
priority_queue<pii, vector<pii>, greater<pii> > pq;
void add(int u, int v, int w)
{
    e[E_Cnt].next = head[u];
    e[E_Cnt].v = v;
    e[E_Cnt].w = w;
    head[u] = E_Cnt++;
}
int main()
{
    /*n 个点 m 条边 s 点到任一点最短路*/
    scanf("%d%d%d", &n, &m, &s);


    int u, v, w;
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    memset(dist, 0x4f, sizeof(int) * (n + 1));

    
    //dijkstra
    pq.push(make_pair(0, s));
    dist[s] = 0;
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(visited[u])  continue;
        visited[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            if(e[i].w + dist[u] < dist[e[i].v]){
                dist[e[i].v] = e[i].w + dist[u];
                pq.push(make_pair(dist[e[i].v], e[i].v));
            }
        }
    }



    int i;
    for(i = 1; i < n; i++)
        printf("%d ", dist[i]);
    printf("%d\n", dist[i]);
    return 0;
}