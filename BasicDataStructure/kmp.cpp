const int MAX = 1e5 + 10;
int next[MAX], n, f[MAX], m;
// 匹配从下标 1 开始
char a[MAX], b[MAX];
void getNext()
{
    next[1] = 0;
    for(int i = 2, j = 0; i <= n; i++)
    {
        while(j > 0 && a[i] != a[j + 1])    j = next[j];
        if(a[i] == a[j + 1])    j++;
        next[i] = j;
    }
}
void getF()
{
    for(int i = 1, j = 0; i <= m; i++)
    {
        while(j > 0 && (j == n || b[i] != a[j + 1]))    j = next[j];
        if(b[i] == a[j + 1])    j++;
        f[i] = j;
        // if(f[i] == n) 此时就是 A 在 B 中的某一次出现
    }
}

