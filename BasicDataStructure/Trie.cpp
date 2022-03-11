#include <string.h>
const int MAX = 1e5 + 10;
int trie[MAX][26], tot = 1, existed[MAX];
void insertTrie(char *str)
{
    int len = strlen(str), p = 1;
    for(int i = 0; i < len; i++)
    {
        int ch = str[i] - 'a';
        if(trie[p][ch] == 0)    trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    existed[p] = 1;
}

int queryTrie(char *str)
{
    int len = strlen(str), p = 1;
    for(int i = 0; i < len; i++)
    {
        p = trie[p][str[i] - 'a'];
        if(p == 0)  return 0;
    }
    return existed[p];
}