// Expect: [AC, AC, TLE, TLE]
#include<vector>
#include<cstdio>
using namespace std;

constexpr int MOD = 1'000'000'007;

int ans_impl(int n, int *dp){
   if(dp[n] != -1) return dp[n];
   if(n == 0) return dp[0] = 1;
   if(n == 1) return dp[1] = 0;
   int res = 0;
   for(int i=0; i<=n-2; ++i){
      res = (res+(2*n-2*i-3ll)*ans_impl(i, dp)) % MOD;
   }
   return dp[n] = res;
}

int ans(int n){
   vector<int> dp(n+1, -1);
   return ans_impl(n, dp.data());
}

int main(){
   int n; scanf("%d", &n);
   printf("%d\n", ans(n));
}
