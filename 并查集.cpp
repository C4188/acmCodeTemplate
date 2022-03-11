// 判断图的连通性
#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAX = 50005;
int fa[MAX], set_size[MAX], d[MAX];
void prework()
{
    for(int i = 1; i < MAX; i++)
    {
        fa[i] = i;
        set_size[i] = 1;
    }
}
int GetF(int x)
{
    if(x == fa[x])  return x;
    return fa[x] = GetF(fa[x]);
}
int GetF(int x)
{
    if(x == fa[x])  return x;
    int root = GetF(fa[x]); // 递归计算集合代表
    d[x] += d[fa[x]];   // 维护d数组 对边权求和
    return fa[x] = root;    // 路径压缩
}
int Merge(int x, int y)
{
    int fx = GetF(x);
    int fy = GetF(y);
    if(fx == fy)    return 0;   // 如果x, y 属于同一集合
    fa[fx] = fy;    // 将集合fx接在集合fy的后面
    d[fx] = set_size[fy];   
    set_size[fy] += set_size[fx];
    return 1;
}