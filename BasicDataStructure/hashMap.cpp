#include <cstdio>
#define rep(i, a, n) for(int i=a;i<=n;i++)
typedef long long ll;
const int maxsz = 4e6 + 9; //@素数表@:1e7+19,2e7+3,3e7+23
//1e6+3,2e6+3,3e6+7,4e6+9,1e5+3,2e5+3,3e5+7,4e5+9
//@要保证取值的操作次数小于maxsz,maxsz最好为素数@
//@count操作不增加新节点@
class hash_map
{
public:
  struct node
  {
    ll u;
    int v, next;
  } e[maxsz << 1];
  int head[maxsz], nume, numk, id[maxsz];
  bool count(ll u)
  {
    int hs = u % maxsz;
    for (int i = head[hs]; i; i = e[i].next)
      if (e[i].u == u)
        return 1;
    return 0;
  }
  int &operator[](ll u)
  {
    int hs = u % maxsz;
    for (int i = head[hs]; i; i = e[i].next)
      if (e[i].u == u)
        return e[i].v;
    if (!head[hs])
      id[++numk] = hs;
    return e[++nume] = (node){u, 0, head[hs]}, head[hs] = nume, e[nume].v;
  }
  void clear()
  {
    rep(i, 0, numk) head[id[i]] = 0;
    numk = nume = 0;
  }
};

hash_map mp; //定义