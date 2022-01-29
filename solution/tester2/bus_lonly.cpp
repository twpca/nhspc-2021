// WA: only check distances between given point and lines
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 105
using namespace std;
using I128 = __int128;
int n, cx, cy;
int xp[M], yp[M];
I128 ax, ay;
I128 dis2(I128 x, I128 y) {
    return x*x + y*y;
}
void update_answer(I128 tx, I128 ty) {
    I128 g = abs(__gcd(tx, ty));
    tx /= g;
    ty /= g;
    if (ay == 0 || tx * ay < ax * ty) {
        ax = tx;
        ay = ty;
    }
}
int main()
{
    while (~scanf("%d %d %d", &cx, &cy, &n)) {
        REP(i,1,n+1) scanf("%d %d", &xp[i], &yp[i]);

        ax = 0;
        ay = 0;
        REP(i,1,n) {
            I128 dot = (I128)(xp[i+1] - xp[i]) * (cx - xp[i]) + (I128)(yp[i+1] - yp[i]) * (cy - yp[i]);
            I128 a2 = dis2(xp[i+1] - xp[i], yp[i+1] - yp[i]);
            I128 b2 = dis2(cx - xp[i], cy - yp[i]);

            I128 tx = b2*a2 - dot*dot;
            I128 ty = a2;
            if (dot >= 0 && dot <= a2) {
                update_answer(tx, ty);
            }
        }
        printf("%.10f\n", (double)sqrt((long double)ax/ay));
    }
    return 0;
}
