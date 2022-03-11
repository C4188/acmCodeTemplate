// 标准模板 prim算法 链式前向星存图 最小堆优化
// accepted
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 305;
const int MAXM = 100005;
int head[MAXN], E_Cnt = 1, dist[MAXN], visited[MAXN], n, m;
struct Edge{
    int v;
    int c;
    int next;
};
Edge e[MAXM];
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > pq;
void addEdge(int u, int v, int c)
{
    e[E_Cnt].next = head[u];
    e[E_Cnt].v = v;
    e[E_Cnt].c = c;
    head[u] = E_Cnt++;
}
int main()
{
    scanf("%d%d", &n, &m);
    int u, v, c;
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &u, &v, &c);
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
    memset(dist, 0x4f, sizeof(dist));

    /*******非模板代码部分*****/
    int maxWeight = 0;
    /************************/

    dist[1] = 0;
    pq.push(make_pair(0, 1));
    while(!pq.empty())
    {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        /*****visited在这里用******/
        if(visited[u])  continue;
        visited[u] = 1;
        /*************************/
        
        /****非模板代码部分****/
        maxWeight = max(maxWeight, d);
        /*********************/

        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v, w = e[i].c;
            if(w < dist[v]){
                dist[v] = w;
                pq.push(make_pair(w, v));
            }
        }
    }
    printf("%d %d\n", n - 1, maxWeight);
    return 0;
}