#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX = 1005;
int t, n, Map[MAX][MAX], dist[MAX], visited[MAX];
int FindMinDist()
{
    int minDist = INF + 1, ret = -1;
    for(int i = 1; i <= n; i++)
        if(!visited[i] && dist[i] < minDist){
            minDist = dist[i];
            ret = i;
        }
    return ret;
}
int main()
{
    int a, b, c;
    // t 为边数 n 为点数
    while(scanf("%d%d", &t, &n) != EOF)
    {
        memset(visited, 0, sizeof(visited));
        memset(Map, 0x3f, sizeof(Map));
        for(int i = 0; i < t; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            if(c < Map[a][b])
                Map[a][b] = Map[b][a] = c;
        }
        for(int i = 1; i <= n; i++)
            dist[i] = Map[1][i];
        
        visited[1] = 1;
        while(1)
        {
            int v = FindMinDist();
            if(v == -1) break;
            visited[v] = 1;
            for(int i = 1; i <= n; i++)
                if(!visited[i])
                    dist[i] = min(dist[i], dist[v] + Map[v][i]);
        }
        printf("%d\n", dist[n]);
    }
    return 0;
}