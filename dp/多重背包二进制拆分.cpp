#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2010;
int f[N];
struct Good {
    int v, w;
};
int main()
{
    vector<Good> goods;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        int v, w, s;
        cin >> v >> w >> s;
        for(int j = 1; j <= s; j *= 2)
        {
            s -= j;
            goods.push_back({v * j, w * j});
        }
        if(s)   goods.push_back({v * s, w * s});
    }
    for(int i = 0; i < goods.size(); i++)
    {
        for(int j = m; j >= goods[i].v; j--)
        {
            f[j] = max(f[j], f[j - goods[i].v] + goods[i].w);
        }
    }
    cout << f[m] << endl;
    return 0;
}