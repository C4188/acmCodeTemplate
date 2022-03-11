// 点分治
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 4e4 + 10;
int n, k, ans, all_node;
int head[N], tot;
struct Edge{
    int v;
    int next;
    int w;
};
Edge e[N << 1];


void addEdge(int u, int v, int w)
{
    e[++tot].v = v;
    e[tot].w = w;
    e[tot].next = head[u];
    head[u] = tot;
}

int vis[N], sub_tree_cnt[N], max_part[N];
int glob_max_part = 0, root = 0;
void get_root(int u, int fa)    // 获取节点u作为根节点的子树的重心
{
    max_part[u] = 0;
    sub_tree_cnt[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == fa || vis[v])   continue;
        get_root(v, u);
        sub_tree_cnt[u] += sub_tree_cnt[v];
        max_part[u] = max(max_part[u], sub_tree_cnt[v]);
    }
    max_part[u] = max(max_part[u], all_node - sub_tree_cnt[u]);
    if(max_part[u] < max_part[root])    root = u;
}

int d[N], len[N];
void get_dis(int u, int fa) // 求子节点到根节点的路径权值， 并将所有的子节点结果存入len数组
{
    len[++len[0]] = d[u];
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(v == fa || vis[v])   continue;
        d[v] = d[u] + e[i].w;
        get_dis(v, u);
    }
}
int cal(int u, int now) // 计算所有经过根节点的路径中路径小于等于k的个数
{
    d[u] = now, len[0] = 0;
    get_dis(u, 0);
    sort(len + 1, len + len[0] + 1);
    int all = 0;
    for(int l = 1, r = len[0]; l < r; )
    {
        if(len[l] + len[r] <= k) {
            all += r - l;
            ++l;
        }
        else r--;
    }
    return all;
}

void solve(int u)   // 将树的重心作为根节点通过cal()计算所有经过该根节点的路径中权值小于等于k的个数， 然后找到该根节点的子节点，分成多个子树， 找到每个子树的重心， 重新开始这个过程
{
    vis[u] = 1;
    ans += cal(u, 0);
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(vis[v])  continue;
        ans -= cal(v, e[i].w);
        all_node = sub_tree_cnt[v];
        root = 0;
        get_root(v, u);
        solve(root);
    }
}

int main()
{
    while(scanf("%d%d", &n, &k) != EOF && n && k)
    {
        // 初始化
        memset(head, 0, sizeof(head));
        tot = 0;
        memset(max_part, 0, sizeof(max_part));
        memset(sub_tree_cnt, 0, sizeof(sub_tree_cnt));
        memset(vis, 0, sizeof(vis));
        ans = 0;

        // 建树
        int u, v, l;
        for(int i = 0; i < n - 1; i++)
        {
            scanf("%d%d%d", &u, &v, &l);
            addEdge(u + 1, v + 1, l);
            addEdge(v + 1, u + 1, l);
        }

        root = 0;
        all_node = n;
        max_part[0] = n;
        get_root(1, 0);
        solve(root);
        printf("%d\n", ans);
    }
    return 0;
}