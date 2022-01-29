// O(log n)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;
using LL = long long;
constexpr LL MOD = 1000000007;
constexpr LL TRANS[3][3] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 0, 2}
};
struct Mat {
    LL x[3][3];
    Mat () {
        MSET(x, 0);
    }
    Mat operator * (Mat a) {
        Mat res;
        REP(i,0,2) REP(j,0,2) REP(k,0,2) {
            res.x[i][j] += x[i][k] * a.x[k][j];
            res.x[i][j] %= MOD;
        }
        return res;
    }
    Mat pow(LL y) {
        if (y==0) {
            Mat res;
            res.x[0][0] = res.x[1][1] = res.x[2][2] = 1;
            return res;
        }
        if (y==1) {
            return *this;
        }

        Mat tmp = (*this).pow(y/2);
        if (y%2) return tmp*tmp*(*this);
        return tmp*tmp;
    }
}mat;
int main()
{
    REP(i,0,2) REP(j,0,2) mat.x[i][j] = TRANS[i][j];
    LL n;
    while (~scanf("%lld", &n)) {
        n--;
        Mat tmp = mat.pow(n);
        LL ans = tmp.x[0][1] * 1 + tmp.x[0][2] * 3;
        ans %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
