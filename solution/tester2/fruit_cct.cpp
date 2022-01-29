// O(c^2T)
// Expect: subtask3 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 45
using namespace std;
int c, t;
int p[M], s[M], n[M], r[M][M];
vector<int> dp[M];
struct Psum {
    vector<int> x;
    Psum() {}
    Psum(int _n, int _x[]) {
        x.clear();
        x.push_back(0);
        REP(i,1,_n) {
            x.push_back(x.back() + _x[i]);
        }
    }
    int sum(int ll,int rr) {
        if (ll > rr) return 0;
        return x[rr] - x[ll-1];
    }
}ps, ns, rs[M];
void init() {
    REP(i,1,c) scanf("%d", &p[i]);
    REP(i,1,c) scanf("%d", &s[i]);
    REP(i,1,c) scanf("%d", &n[i]);
    REP(i,1,c) REP(j,1,i) scanf("%d", &r[i][j]);

    ps = Psum(c, p);
    ns = Psum(c, n);
    REP(i,1,c) rs[i] = Psum(c, r[i]);
}
void work() {
    REP(i,0,c) dp[i] = vector<int> (t+1, -1);
    dp[0][0] = 0;

    REP(i,1,c) REP(j,0,t) REP(k,0,i-1) {
        int dt  = ps.sum(1, i) * ns.sum(k+1, i);
            dt += s[i] * ns.sum(k+1, i);
        int dr = rs[i].sum(k+1, i);

        if (j>=dt && dp[k][j-dt]>=0) {
            dp[i][j] = max(dp[i][j], dp[k][j-dt] + dr);
        }
    }

    int ans = -1;
    // throw remaining fruits
    REP(i,0,c) REP(j,0,t) if (dp[i][j] != -1) {
        int dt = ps.sum(1, c) * ns.sum(i+1, c);
        if (j+dt <= t) {
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
}
int main()
{
    while (~scanf("%d %d", &c, &t)) {
        init();
        work();
    }
    return 0;
}
