// O(n^2 log n) with some reasonable cuts
// expect: TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 300005
using namespace std;
using P = pair<int,int>;
constexpr int INF = 2'000'000'000;
int n, m;
int vx[M], vy[M], w[M], t[M];
set<P> s1, s2;

void add(int k, int v) {
    assert(v >= 0);
    if (k>m) return;

    auto it = s1.upper_bound(P(k+1, -1));
    if (it != s1.begin()) {
        it--;
        if (it->second >= v) {
           return;
        }
    }

    it = s1.lower_bound(P(k, -1));
    while (it!=s1.end() && it->second <= v) {
        int x, y;
        tie(x, y) = *it;
        s1.erase(s1.find(P(x, y)));
        s2.erase(s2.find(P(y, x)));
        it = s1.lower_bound(P(k, -1));
    }
    s1.emplace(k, v);
    s2.emplace(v, k);
}
void add_range(int kr, int vr, int kd, int vd) {
    vector<P> tmp;
    
    // find first
    auto it1 = s1.lower_bound(P(kr, -1));
    if (it1 != s1.end() && it1->second < vr) {
        auto it2 = s2.lower_bound(P(vr, -1));
        if (it2 == s2.end()) {
            it1 = s1.end();
        } else {
            it1 = s1.find(P(it2->second, it2->first));
        }
    }

    for (auto it=it1; it!=s1.end(); it++) {
        tmp.push_back(*it);
    }
    for (auto p: tmp) {
        s1.erase(s1.find(p));
        s2.erase(s2.find(P(p.second, p.first)));
    }
    for (auto p: tmp) {
        add(p.first + kd, p.second + vd);
    }
}
// best value <=k
int get_best(int k) {
    int res = 0;
    auto it = s1.upper_bound(P(k+1, -1));
    if (it != s1.begin()) {
        it--;
        res = it->second;
    }
    return res;
}
void dprint(int i) {
    printf("\n===== i=%d =====\n", i);
    for (auto j: s1) printf("%d %d\n", j.first, j.second);
}
int main()
{
    while (~scanf("%d %d", &n, &m)) {
        s1.clear();
        s2.clear();
        REP(i,1,n) scanf("%d %d %d %d", &vx[i], &vy[i], &t[i], &w[i]);

        int ans = 0;
        REP(i,1,n) {
            add(0, 0);

            int mxv = get_best(vx[i] - 1);
            add_range(vx[i], vy[i], t[i], w[i]);
            if (mxv >= vy[i]) {
                add(vx[i] + t[i], mxv + w[i]);
            }

            //dprint(i);
            ans = max(ans, get_best(m));
        }
        printf("%d\n", ans);
    }
    return 0;
}
