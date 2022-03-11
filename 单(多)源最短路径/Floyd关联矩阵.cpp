#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int Map[305][305];
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            scanf("%d", &Map[i][j]);
    // 核心代码块
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                Map[i][j] = min(Map[i][j], Map[i][k] + Map[k][j]);
    return 0;
}