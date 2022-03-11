// accepted 区间dp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int n;
const int N = 310;
int f[N][N];
int a[N], sum[N];
int main()
{
    cin >> n;
    memset(f, 0x3f, sizeof(f)); // INF
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i]; // 前缀和
        f[i][i] = 0;    // 初值
    }
    for(int len = 2; len <= n; len++)   // 阶段
    {
        for(int l = 1; l <= n - len + 1; l++)   // 状态: 左端点
        {
            int r = l + len - 1;    // 状态: 右端点
            for(int k = l; k < r; k++)  // 决策
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
            f[l][r] += sum[r] - sum[l - 1];
        }
    }
    cout << f[1][n] << endl;
    return 0;
}