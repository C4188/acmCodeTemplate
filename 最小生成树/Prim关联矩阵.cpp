#include <stdio.h>
#include <string.h>
const int MAX = 105, INF = 0x3f3f3f3f;
int matrix[MAX][MAX], dist[MAX], n, m;
int FindMinDist()
{
    int minWeight = INF, ret = -1;
    for(int i = 1; i <= m; i++)
        if(dist[i] && dist[i] < minWeight){
            minWeight = dist[i];
            ret = i;
        }

    return ret;
}
int main()
{
    //  m 是点数，n 是边数
    while(scanf("%d", &n) != EOF && n)
    {
        scanf("%d", &m);

        memset(matrix, 0x3f, sizeof(matrix));
        
        int a, b, c;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            matrix[a][b] = matrix[b][a] = c;
        }

        for(int i = 1; i <= m; i++)
        {
            dist[i] = matrix[1][i];
        }

        int totalWeight = 0, count = 0;
        dist[1] = 0;
        count++;
        while(1)
        {
            int v = FindMinDist();
            if(v == -1)
                break;
            totalWeight += dist[v];
            dist[v] = 0;
            count++;
            for(int i = 1; i <= m; i++)
            {
                if(dist[i] && matrix[v][i] < dist[i]){
                    dist[i] = matrix[v][i];
                }
            }
        }
        if(count == m)
            printf("%d\n", totalWeight);
        else
            printf("?\n");
    }
    return 0;
}