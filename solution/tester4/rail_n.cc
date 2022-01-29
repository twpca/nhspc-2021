#include<cstdio>
using namespace std;

constexpr int MOD = 1'000'000'007;

int ans(int n){
   if(n == 1) return 0;
   if(n == 2) return 1;
   int dp[]{1, 0, 1};
   for(int i=3; i<=n; ++i){
      dp[i%3] = (dp[i%3]+2ll*dp[(i-1)%3]) % MOD;
   }
   return dp[n%3];
}

int main(){
   int n; scanf("%d", &n);
   printf("%d\n", ans(n));
}
