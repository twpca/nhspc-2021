#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

int dfs(vector<int> const *g, int u, int p, int *pos, vector<int> &d, vector<int> &subsz, int depth){
   int res = 1, i = d.size();
   pos[u] = i;
   d.push_back(depth);
   subsz.push_back(0);
   for(auto v: g[u]) if(v != p){
      res += dfs(g, v, u, pos, d, subsz, depth+1);
   }
   return subsz[i] = res;
}

int sum(int const *bit, int i){
   int s = 0;
   for(; i>0; i-=i&-i){
      s += bit[i];
   }
   return s;
}

void update(int *bit, int n, int i, int x){
   for(; i<=n; i+=i&-i){
      bit[i] += x;
   }
}

int main(){
   int n, s, o, w;
   scanf("%d%d%d%d", &n, &s, &o, &w);
   --s;
   vector<pair<int, int>> koro;
   koro.reserve(n-1);
   vector<vector<int>> g(n);
   for(int i=n-1; i-->0; ){
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      koro.emplace_back(u, v);
      g[u].push_back(v);
      g[v].push_back(u);
   }
   vector<int> bit, pos(n), subsz;
   bit.reserve(n);
   subsz.reserve(n);
   dfs(g.data(), s, s, pos.data(), bit, subsz, 0);
   for(int i=n-1; i>=1; --i){
      bit[i] -= bit[i-(i&-i)];
   }
   for(auto &p: koro) if(pos[p.first] < pos[p.second]){
      swap(p.first, p.second);
   }
   int q = o + w;
   while(q-- > 0){
      int type; scanf("%d", &type);
      if(type == 1){
         int x, y;
         scanf("%d%d", &x, &y);
         printf("%lld\n", (i64)x*sum(bit.data(), pos[--y]));
      }else{
         int z;
         scanf("%d", &z);
         int i = pos[koro[--z].first];
         update(bit.data(), n-1, i, -1);
         update(bit.data(), n-1, i+subsz[i], 1);
      }
   }
}
