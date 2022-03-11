#include <stdio.h>
#include <string.h>
const int MAX = 10005;
int parent[MAX], mark[MAX], n;
int goUp(int u)
{
    int tmp = u;
    while(u)
    {
        if(mark[u]){
            return u;
        }
        mark[u] = 1;
        u = parent[u];
    }
    return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        memset(parent, 0, sizeof(parent));
        memset(mark, 0, sizeof(mark));
        scanf("%d", &n);
        int a, b;
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d", &a, &b);
            parent[b] = a;
        }
        scanf("%d%d", &a, &b);
        goUp(a);
        printf("%d\n", goUp(b));
    }
    return 0;
}