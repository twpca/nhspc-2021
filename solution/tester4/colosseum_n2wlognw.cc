// Expect: [AC, TLE, TLE, TLE]
#include<map>
#include<cstdio>
using namespace std;

void my_emplace(map<int, int> &m, int first, int second){
   auto [it, b] = m.emplace(first, second);
   if(!b && it->second > second){
      it->second = second;
   }
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   map<int, int> bst;
   int ans = 0;
   for(int cnt=n; cnt-->0; ){
      int x, y, t, w;
      scanf("%d%d%d%d", &x, &y, &t, &w);
      bst.emplace(0, 0);
      for(auto it=bst.end(); it!=bst.begin(); ){
         if((--it)->first < y){
            break;
         }
         if(it->second >= x){
            if(it->second+t <= m){
               my_emplace(bst, it->first+w, it->second+t);
            }
            it = bst.erase(it);
         }else if(x+t <= m){
            my_emplace(bst, it->first+w, x+t);
         }
      }
      if(!bst.empty()){
         ans = max(ans, bst.crbegin()->first);
      }
   }
   printf("%d\n", ans);
}
