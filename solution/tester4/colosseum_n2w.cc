// Expect: [AC, TLE, TLE, TLE]
#include<unordered_map>
#include<cstdio>
using namespace std;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   unordered_map<int, int> um;
   int ans = 0;
   for(int cnt=n; cnt-->0; ){
      int x, y, t, w;
      scanf("%d%d%d%d", &x, &y, &t, &w);
      um.emplace(0, 0);
      unordered_map<int, int> plus;
      for(auto it=um.begin(); it!=um.end(); ){
         if(it->first >= y){
            if(it->second >= x){
               if(it->second+t <= m){
                  plus.emplace(it->first+w, it->second+t);
               }
               it = um.erase(it);
            }else{
               if(x+t <= m){
                  plus.emplace(it->first+w, x+t);
               }
               ++it;
            }
         }else{
            ++it;
         }
      }
      for(auto [f, s]: plus){
         auto [it, b] = um.emplace(f, s);
         if(!b && it->second > s){
            it->second = s;
         }
      }
      for(auto [f, _]: um){
         ans = max(ans, f);
      }
   }
   printf("%d\n", ans);
}
