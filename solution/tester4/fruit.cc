#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int c, t;
   scanf("%d%d", &c, &t);
   vector<int> p(c+1), s(c+1), n(c+1), r((c+1)*(c+2)/2);
   for(int i=1; i<=c; ++i){
      scanf("%d", p.data()+i);
   }
   partial_sum(p.cbegin(), p.cend(), p.begin());
   for(int i=1; i<=c; ++i){
      scanf("%d", s.data()+i);
   }
   for(int i=1; i<=c; ++i){
      scanf("%d", n.data()+i);
   }
   partial_sum(n.cbegin(), n.cend(), n.begin());
   auto r_id = [](int i, int j){
      return i*(i+1)/2+j;
   };
   for(int i=1; i<=c; ++i){
      for(int j=1; j<=i; ++j){
         scanf("%d", r.data()+r_id(i, j));
      }
   }
   for(int i=1; i<=c; ++i){
      partial_sum(r.cbegin()+r_id(i, 0), r.cbegin()+r_id(i+1, 0), r.begin()+r_id(i, 0));
   }
   vector<int> dp((c+1)*(n[c]+1), t+1);
   auto id = [N=n[c]](int i, int j){
      return i*(N+1)+j;
   };
   dp[id(0, 0)] = 0;
   for(int i=1; i<=c; ++i){
      for(int j=0; j<=n[c]; ++j){
         for(int k=0; k<=i-1; ++k) if(j >= r[r_id(i, i)]-r[r_id(i, k)]){
            dp[id(i, j)] = min(dp[id(i, j)], dp[id(k, j-r[r_id(i, i)]+r[r_id(i, k)])] + (n[c]-n[k])*(p[i]-p[k]) + (n[i]-n[k])*s[i]);
         }
      }
   }
   int ans = -1;
   for(int i=0; i<=c; ++i){
      for(int j=0; j<=n[c]; ++j) if(dp[id(i, j)] + (n[c]-n[i])*(p[c]-p[i]) <= t){
         ans = max(ans, j);
      }
   }
   printf("%d\n", ans);
}
