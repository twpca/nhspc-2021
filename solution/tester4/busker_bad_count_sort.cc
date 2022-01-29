#include<algorithm>
#include<numeric>
#include<queue>
#include<unordered_map>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

struct Arc{
   int to;
   i64 w;
   Arc() = default;
   constexpr Arc(int to, i64 w) noexcept: to(to), w(w){}
};

vector<int> bf(vector<Arc> const *g, int n){
   vector<i64> d(n);
   vector<int> p(n, -1), c(n);
   queue<int> q;
   vector<bool> inq(n, true);
   for(int u=0; u<n; ++u){
      q.push(u);
   }
   while(!q.empty()){
      int u = q.front();
      q.pop(); inq[u] = false;
      for(auto [v, w]: g[u]){
         if(d[v] >= d[u] + w){ // TODO: adjust threashold
            d[v] = d[u] + w;
            p[v] = u;
            if(++c[v] == n/8){
               vector<int> res;
               vector<bool> inres(n);
               for(; !inres[v]; v=p[v]){
                  res.push_back(v);
                  inres[v] = true;
               }
               res.erase(res.cbegin(), find(res.cbegin(), res.cend(), v));
               reverse(res.begin(), res.end());
               return res;
            }
            if(!inq[v]){
               q.push(v);
               inq[v] = true;
            }
         }
      }
   }
   fprintf(stderr, "max count: %d\n", *max_element(c.begin(), c.end()));
   return {};
}

int main(){
   int n, m, k;
   scanf("%d%d%d", &n, &m, &k);
   vector<int> c(n+m*k);
   for(int u=0; u<n; ++u){
      scanf("%d", c.data()+u);
   }
   vector<unordered_map<int, int>> g0(n);
   for(int i=0; i<m; ++i){
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      g0[u].emplace(v, i);
      for(int j=0; j<k; ++j){
         scanf("%d", c.data()+n+i*k+j);
      }
   }
   vector<vector<Arc>> g(2*n);
   for(int u=0; u<n; ++u){
      g[u].emplace_back(n+u, -c[u]);
   }
   for(int u=0; u<n; ++u){
      for(auto vi: g0[u]){
         g[n+u].emplace_back(vi.first, -accumulate(c.cbegin()+n+vi.second*k, c.cbegin()+n+(vi.second+1)*k, 0ll));
      }
   }
   for(auto &gu: g){
      sort(gu.begin(), gu.end(), [](Arc a, Arc b){
         return a.w < b.w;
      });
   }
   auto cyc = bf(g.data(), g.size());
   if(cyc.empty()){
      puts("0");
      return 0;
   }
   vector<int> cyc0;
   vector<i64> w;
   cyc0.reserve(cyc.size()/2*(k+1)+1);
   w.reserve(cyc.size()/2*(k+1));
   for(size_t i=0; i<cyc.size(); ++i){
      int u = cyc[i];
      if(u < n){
         cyc0.push_back(u);
         w.push_back(c[u]);
      }else{
         u -= n;
         int v = cyc[(i+1)%cyc.size()], e = g0[u][v];
         for(int j=0; j<k; ++j){
            cyc0.push_back(n+e*k+j);
            w.push_back(c[cyc0.back()]);
         }
      }
   }
   vector<i64> s(w.size()+1);
   partial_sum(w.cbegin(), w.cend(), s.begin()+1);
   int min_id = min_element(s.cbegin(), s.cend()) - s.cbegin();
   rotate(w.begin(), w.begin()+min_id, w.end());
   rotate(cyc0.begin(), cyc0.begin()+min_id, cyc0.end());
   cyc0.push_back(cyc0[0]);
   partial_sum(w.cbegin(), w.cend(), s.begin()+1);
   int big = 0, small = 0;
   i64 min_back = s.back();
   for(size_t i=s.size(); i-->1; ){
      if(min_back >= s[i]){
         ++(cyc0[i]<n? big: small);
         min_back = s[i];
      }
   }
   printf("%zu\n", cyc0.size());
   for(size_t i=0; i<cyc0.size(); ++i){
      printf("%d%c", cyc0[i]+1, " \n"[i+1==cyc0.size()]);
   }
   printf("%d %d\n", big, small);
}
