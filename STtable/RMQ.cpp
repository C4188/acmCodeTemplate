#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAX = 2e5 + 5;
int n, k, f[MAX][19], Logn[MAX];
void pre()
{
    Logn[1] = 0;
    Logn[2] = 1;
    for(int i = 3; i <= MAX; i++)
        Logn[i] = Logn[i >> 1] + 1;
}
int ST_query(int l, int r)
{
    int tmp = Logn[r - l + 1];
    return max(f[l][tmp], f[r - (1 << tmp) + 1][tmp]);
}
int main()
{
    pre();
    while(scanf("%d%d", &n, &k) != EOF)
    {
        for(int i = 1; i <= n; i++)
            scanf("%d", &f[i][0]);

        for(int j = 1; j <= Logn[n]; j++)
            for(int i = 1; i <= n - (1 << j) + 1; i++)
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        
    }
    return 0;
}

// 二维RMQ 注意内存
// #include <stdio.h>
// #include <algorithm>
// using namespace std;
// const int MAX = 255;
// int f[MAX][MAX][17][17], g[MAX][MAX][17][17], val[MAX][MAX];
// int RMQ_MAX(int x1, int y1, int x2, int y2)
// {
//     int kx = 0, ky = 0;
//     while((1 << (1 + kx)) <= x2 - x1 + 1)   kx++;
//     while((1 << (1 + ky)) <= y2 - y1 + 1)   ky++;
//     int m1 = f[x1][y1][kx][ky];
//     int m2 = f[x2 - (1 << kx) + 1][y1][kx][ky];
//     int m3 = f[x1][y2 - (1 << ky) + 1][kx][ky];
//     int m4 = f[x2 - (1 << kx) + 1][y2 - (1 << ky) + 1][kx][ky];
//     return max(max(m1, m2), max(m3, m4));
// }
// int RMQ_MIN(int x1, int y1, int x2, int y2)
// {
//     int kx = 0, ky = 0;
//     while((1 << (1 + kx)) <= x2 - x1 + 1)   kx++;
//     while((1 << (1 + ky)) <= y2 - y1 + 1)   ky++;
//     int m1 = g[x1][y1][kx][ky];
//     int m2 = g[x2 - (1 << kx) + 1][y1][kx][ky];
//     int m3 = g[x1][y2 - (1 << ky) + 1][kx][ky];
//     int m4 = g[x2 - (1 << kx) + 1][y2 - (1 << ky) + 1][kx][ky];
//     return min(min(m1, m2), min(m3, m4));
// }
// int main()
// {
//     int n, b, k;
//     scanf("%d%d%d", &n, &b, &k);
//     for(int i = 1; i <= n; i++)
//         for(int j = 1; j <= n; j++)
//         {
//             scanf("%d", &val[i][j]);
//             f[i][j][0][0] = g[i][j][0][0] = val[i][j];
//         }
//     for(int i = 0; (1 << i) <= n; i++)
//         for(int j = 0; (1 << j) <= n; j++)
//         {
//             if(i == 0 && j == 0)    continue;
//             for(int row = 1; row + (1 << j) - 1 <= n; row++)
//                 for(int col = 1; col + (1 << j) - 1 <= n; col++)
//                 {
//                     if(j == 0){
//                         f[row][col][i][j] = max(f[row][col][i - 1][j], f[row + (1 << (i - 1))][col][i - 1][j]);
//                         g[row][col][i][j] = min(g[row][col][i - 1][j], g[row + (1 << (i - 1))][col][i - 1][j]);
//                     }
//                     else{
//                         f[row][col][i][j] = max(f[row][col][i][j - 1], f[row][col + (1 << (j - 1))][i][j - 1]);
//                         g[row][col][i][j] = min(g[row][col][i][j - 1], g[row][col + (1 << (j - 1))][i][j - 1]);
//                     }
//                 }
//         }
//     int x, y;
//     while(k--)
//     {
//         scanf("%d%d", &x, &y);
//         printf("%d\n", RMQ_MAX(x, y, x + b - 1, y + b - 1) - RMQ_MIN(x, y, x + b - 1, y + b - 1));
//     }
//     return 0;
// }