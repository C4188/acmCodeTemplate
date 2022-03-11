#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1010;
const int mod = 1000000007;
int f[N], g[N];
int main()
{
    // n 是物品个数, m 是背包的体积
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        f[i] = -0x3f3f3f3f;
    g[0] = 1;
    for(int i = 0; i < n; i++)
    {
        int v, w;
        cin >> v >> w;
        for(int j = m; j >= v; j--)
        {
            int t = max(f[j], f[j - v] + w);
            int s = 0;
            if(t == f[j])   s += g[j];
            if(t == f[j - v] + w)   s += g[j - v];
            if(s >= mod)    s -= mod;
            f[j] = t;
            g[j] = s;
        }
    }
    
    int maxw = 0;
    for(int i = 0; i <= m; i++) maxw = max(maxw, f[i]);
    int res = 0;
    for(int i = 0; i <= m; i++)
    {
        if(maxw == f[i]) {
            res += g[i];
            if(res >= mod)  res -= mod;
        }
    }
    cout << res << endl;
    return 0;
}