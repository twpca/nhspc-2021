// Expect: [AC, TLE, TLE, TLE]
#include<omp.h>
#include<algorithm>
#include<atomic>
#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> x(n), y(n), t(n), w(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d%d%d%d", x.data()+i, y.data()+i, t.data()+i, w.data()+i);
   }
   int W = accumulate(w.cbegin(), w.cend(), 0);
   vector<int> a[2];
   a[0].resize(W+1, m+1); a[1].resize(W+1);
   atomic_int n_threads;
#pragma omp parallel
   n_threads = omp_get_num_threads();
   vector<int> max_profit(n_threads.load());
   int ans = 0;
   for(int i=0, s=0; i<=n-1; s+=w[i++]){
      if(y[i] > s) continue;
      a[0][0] = 0;
#pragma omp parallel for
      for(int j=0; j<=W; ++j){
         a[1][j] = m+1;
      }
#pragma omp parallel for
      for(int j=0; j<=W; ++j) if(j>=y[i] && a[0][j]<=m){
         if(a[0][j] >= x[i]){
            if(a[0][j]+t[i] <= m){
               a[1][j+w[i]] = a[0][j]+t[i];
            }
            a[0][j] = m+1;
         }else if(x[i]+t[i] <= m){
            a[1][j+w[i]] = x[i]+t[i];
         }
      }
      fill(max_profit.begin(), max_profit.end(), 0);
#pragma omp parallel for
      for(int j=0; j<=W; ++j){
         a[0][j] = min(a[0][j], a[1][j]);
         if(a[0][j] <= m){
            int k = omp_get_thread_num();
            max_profit[k] = max(max_profit[k], j);
         }
      }
      ans = max(ans, *max_element(max_profit.cbegin(), max_profit.cend()));
   }
   printf("%d\n", ans);
}
