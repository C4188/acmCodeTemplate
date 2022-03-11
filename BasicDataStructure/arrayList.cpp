#include <string.h>
const int SIZE = 1e5 + 10;
struct Node
{
    int value;
    int prev;
    int next;
}node[SIZE];
int head, tail, tot;
int initialize()
{
    tot = 2;
    head = 1;
    tail = 2;
    node[head].next = tail;
    node[head].prev = head;
}

// 在下标 p 的下一个位置插入
void insert(int p, int val)
{
    int q = ++tot;
    node[q].value = val;
    node[node[p].next].prev = q;
    node[q].next = node[p].next;
    node[p].next = q;
    node[q].next = p;
}

void remove(int p)
{
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}

void clear()
{
    memset(node, 0, sizeof(node));
    head = tail = tot = 0;
}