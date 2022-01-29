// Expect: [AC, TLE, TLE, TLE]
#include<cstdio>
using namespace std;

int ans(int n){
   if(n == 0) return 1;
   if(n == 1) return 0;
   int res = 0;
   for(int i=0; i<=n-2; ++i){
      res += (2*n-2*i-3)*ans(i);
   }
   return res;
}

int main(){
   int n; scanf("%d", &n);
   printf("%d\n", ans(n));
}
