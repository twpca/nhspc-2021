#include<algorithm>
#include<optional>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

struct Arc{
   int to, w, no;
   Arc() = default;
   constexpr Arc(int to, int w, int no) noexcept: to(to), w(w), no(no){}
};

void dfs(vector<Arc> const *g, int x, vector<bool> &vis, int *ra, int &t, int u){
   vis[u] = true;
   for(auto e: g[u]) if(e.w>=x && !vis[e.to]){
      dfs(g, x, vis, ra, t, e.to);
   }
   ra[u] = t++;
}

optional<vector<int>> ok(vector<Arc> const *g, int n, int x){
   vector<bool> vis(n);
   vector<int> ra(n);
   int t = 0;
   for(int u=0; u<n; ++u) if(!vis[u]){
      dfs(g, x, vis, ra.data(), t, u);
   }
   for(int u=0; u<n; ++u) for(auto e: g[u]){
      if(e.w>=x && ra[u]<ra[e.to]){
         return {};
      }
   }
   return move(ra);
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<vector<Arc>> g(n);
   vector<int> x;
   x.reserve(m);
   for(int i=1; i<=m; ++i){
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      --u; --v;
      g[u].emplace_back(v, c, i);
      x.push_back(c);
   }
   sort(x.begin(), x.end());
   x.erase(unique(x.begin(), x.end()), x.end());
   for(auto &gu: g) for(auto &e: gu){
      e.w = lower_bound(x.cbegin(), x.cend(), e.w) - x.cbegin();
   }
   int lb = -1, ub = x.size();
   while(ub-lb > 1){
      int mid = lb + (ub-lb)/2;
      (ok(g.data(), g.size(), mid)? ub: lb) = mid;
   }
   if(lb == -1){
      puts("0 0");
      return 0;
   }
   vector<int> ra = *ok(g.data(), g.size(), ub), ans;
   for(size_t u=0; u<g.size(); ++u) for(auto [v, _, no]: g[u]){
      if(ra[u] < ra[v]){
         ans.push_back(no);
      }
   }
   printf("%d %zu\n", x[lb], ans.size());
   for(int ei: ans){
      printf("%d\n", ei);
   }
}
