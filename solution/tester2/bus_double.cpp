// O(n)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 105
using namespace std;
using LD = long double;
constexpr LD EPS = 1e-6;
int n, cx, cy;
int xp[M], yp[M];
LD ans;
LD dis(LD x, LD y) {
    return sqrt(x*x + y*y);
}
int main()
{
    while (~scanf("%d %d %d", &cx, &cy, &n)) {
        REP(i,1,n+1) scanf("%d %d", &xp[i], &yp[i]);

        ans = 1e100;
        REP(i,1,n+1) {
            LD tmp =dis(cx - xp[i], cy - yp[i]);
            if (tmp < ans) {
                ans = tmp;
            }
        }
        REP(i,1,n) {
            LD dot = (LD)(xp[i+1] - xp[i]) * (cx - xp[i]) + (LD)(yp[i+1] - yp[i]) * (cy - yp[i]);
            LD ad = dis(xp[i+1] - xp[i], yp[i+1] - yp[i]);
            LD bd = dis(cx - xp[i], cy - yp[i]);

            LD tmp = sqrt(bd*bd - pow(dot/ad, 2));
            if (dot >= 0-EPS && dot <= ad*ad+EPS) {
                if (tmp < ans) ans = tmp;
            }
        }
        printf("%.10f\n", (double)ans);
    }
    return 0;
}
