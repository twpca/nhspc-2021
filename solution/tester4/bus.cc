// Expect: AC
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
using namespace std;
using i64 = long long;

struct Pt{
   int x, y;
   Pt() = default;
   constexpr Pt(int x, int y) noexcept: x(x), y(y){}
};

constexpr i64 dist2(Pt a, Pt b) noexcept{
   return ((i64)a.x-b.x)*(a.x-b.x) + ((i64)a.y-b.y)*(a.y-b.y);
}

i64 area2(Pt a, Pt b, Pt c) noexcept{
   return abs((i64)a.x*b.y-(i64)a.y*b.x+(i64)b.x*c.y-(i64)b.y*c.x+(i64)c.x*a.y-(i64)c.y*a.x);
}

int main(){
   Pt o; int n;
   scanf("%d%d%d", &o.x, &o.y, &n);
   vector<Pt> p(n+1);
   for(int i=0; i<=n; ++i){
      scanf("%d%d", &p[i].x, &p[i].y);
   }
   i64 op2 = dist2(o, p[0]);
   double ans = sqrt(op2);
   for(int i=1; i<=n; ++i){
      i64 oq2 = dist2(o, p[i]), pq2 = dist2(p[i-1], p[i]);
      if(auto [x, y] = minmax(op2, oq2); y > x+pq2){
         ans = min(ans, sqrt(x));
      }else{
         ans = min(ans, area2(o, p[i-1], p[i])/sqrt(pq2));
      }
      op2 = oq2;
   }
   printf("%.16g\n", ans);
}
