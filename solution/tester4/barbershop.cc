// Expect: AC
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   vector<int> a(n);
   for(int i=0; i<n; ++i){
      scanf("%d", a.data()+i);
   }
   sort(a.begin(), a.end());
   int s = 0, ans = 0;
   for(int ai: a){
      ans += s += ai;
   }
   printf("%d\n", ans);
}
