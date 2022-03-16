#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAX = 1e5 + 5;
typedef long long ll;
int n, q;
ll a[MAX];
struct SegmentTree {
    int l;
    int r;
    ll dat; // 数据
    ll mark; // 延迟标记
#define l(x) tree[x].l
#define r(x) tree[x].r
#define dat(x) tree[x].dat
#define mark(x) tree[x].mark
}tree[MAX << 2];

void build(int p, int l , int r)
{
    l(p) = l; r(p) = r;
    if(l == r) {
        dat(p) = a[l];
        return ;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    dat(p) = dat(p * 2) + dat(p * 2 + 1);
}

void spread(int p)
{
    if(mark(p)) {
        dat(p * 2) = mark(p) * (r(p * 2) - l(p * 2) + 1);
        dat(p * 2 + 1) = mark(p) * (r(p * 2 + 1) - l(p * 2 + 1) + 1);
        mark(p * 2) = mark(p);
        mark(p * 2 + 1) = mark(p);
        mark(p) = 0;
    }
}

void change(int p, int l, int r, int d)
{
    if(l <= l(p) && r >= r(p)) { // 完全覆盖
        dat(p) = (ll)d * (r(p) - l(p) + 1); // 更新节点信息
        mark(p) += d; // 给节点打上延迟标记
        return ;
    }
    spread(p);  // 下传延迟标记
    int mid = (l(p) + r(p)) / 2;
    if(l <= mid)    change(p * 2, l, r, d);
    if(r > mid) change(p * 2 + 1, l, r, d);
    dat(p) = dat(p * 2) + dat(p * 2 + 1);
}

ll ask(int p, int l, int r)
{
    if(l <= l(p) && r >= r(p))  return dat(p);
    spread(p);
    int mid = (l(p) + r(p)) / 2;
    ll val = 0;
    if(l <= mid)    val += ask(p * 2, l, r);
    if(r > mid) val += ask(p * 2 + 1, l, r);
    return val;
}

int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    build(1, 1, n);
    char op[5];
    int x, y, z;
    for(int i = 1; i <= q; i++)
    {
        scanf("%s%d%d", op, &x, &y);
        if(op[0] == 'Q'){
            printf("%lld\n", ask(1, x, y));
        }
        else{
            scanf("%d", &z);
            change(1, x, y, z);
        }
    }
    return 0;
}