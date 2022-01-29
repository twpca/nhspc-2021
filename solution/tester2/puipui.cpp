// O(n * log(M))
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 1000005
using namespace std;
using P = pair<int,int>;
int n, k, p;
int in[M], rmx[M];
bool is_ok(int x) {
    int cnt = 0;
    REP(i,k,n) {
        if (rmx[i] <= x) {
            cnt++;
            i += k-1;
        }
    }
    return cnt >= p;
}
void init() {
    REP(i,1,n) scanf("%d", &in[i]);
    sort(in+1, in+n+1);

    multiset<int> s;
    int d = min(k-1, 2); // d>=k-1
    REP(i,1,k-1) {
        if (i-d >= 1) {
            s.insert(in[i] - in[i-d]);
        }
    }
    REP(i,k,n) {
        if (i-d >= 1) {
            s.insert(in[i] - in[i-d]);
        }
        if (i-k >= 1) {
            s.erase(s.find(in[i-k+d] - in[i-k]));
        }
        rmx[i] = *s.rbegin();
    }
}
int main()
{
    while (~scanf("%d %d %d", &n, &k, &p)) {
        init();

        int ok = 1'000'000'000;
        int ng = -1;
        while (abs(ok-ng) > 1) {
            int mid = (ok + ng) / 2;
            if (is_ok(mid)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        printf("%d\n", ok);
    }
    return 0;
}
