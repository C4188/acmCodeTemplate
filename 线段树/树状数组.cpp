
// 区间查询，单点修改，区间为 [1, N]
const int N = 1e5 + 10;
int c[N];

int ask(int x)
{
    int ans = 0;
    for(; x; x -= x & -x)
        ans += c[x];
    return ans;
}

void add(int x, int y)
{
    for(; x <= N; x += x & -x)  // 注意这里 N 要改一下
        c[x] += y;
}