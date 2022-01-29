// Expect: WA in subtask 2 and 3
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct Pt{
   int x, y;
   Pt() = default;
   constexpr Pt(int x, int y) noexcept: x(x), y(y){}
};

constexpr int dist2(Pt a, Pt b) noexcept{
   return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

int area2(Pt a, Pt b, Pt c) noexcept{
   return abs(a.x*b.y-a.y*b.x+b.x*c.y-b.y*c.x+c.x*a.y-c.y*a.x);
}

int main(){
   Pt o; int n;
   scanf("%d%d%d", &o.x, &o.y, &n);
   vector<Pt> p(n+1);
   for(int i=0; i<=n; ++i){
      scanf("%d%d", &p[i].x, &p[i].y);
   }
   int op2 = dist2(o, p[0]);
   double ans = sqrt(op2);
   for(int i=1; i<=n; ++i){
      int oq2 = dist2(o, p[i]), pq2 = dist2(p[i-1], p[i]);
      if(auto [x, y] = minmax(op2, oq2); y > x+pq2){
         ans = min(ans, sqrt(x));
      }else{
         ans = min(ans, area2(o, p[i-1], p[i])/sqrt(pq2));
      }
      op2 = oq2;
   }
   printf("%.16g\n", ans);
}
