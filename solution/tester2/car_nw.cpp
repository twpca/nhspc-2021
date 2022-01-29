// O(nW)
// Expect: subtask 1,3 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
using namespace std;
struct Edge {
    int t, w, id;
    Edge () {}
    Edge (int _t, int _w, int _id) { t=_t; w=_w; id=_id; }
};
int n, m, mxw;
vector<Edge> e[M];
bool dfs(int X, vector<int>& s, vector<bool>& vis, vector<bool>& ins, int cur) {
    vis[cur] = true;
    ins[cur] = true;
    for (auto i: e[cur]) if (i.w > X) {
        if (!vis[i.t]) {
            if (!dfs(X, s, vis, ins, i.t)) {
                return false;
            }
        } else if (ins[i.t]) {
            return false;
        }
    }
    ins[cur] = false;
    s.push_back(cur);
    return true;
}
void work() {
    vector<int> s;
    vector<bool> vis(n+1, false);
    vector<bool> ins(n+1, false);
    auto check = [&](int X){
        s.clear();
        fill(vis.begin(), vis.end(), false);
        fill(ins.begin(), ins.end(), false);

        REP(i,1,n) if (!vis[i]) {
            if (!dfs(X, s, vis, ins, i)) {
                return false;
            }
        }
        return true;
    };

    int ok = -1;
    REP(i,0,mxw) {
        if (check(i)) {
            ok = i;
            break;
        }
    }

    vector<int> ord(n+1);
    vector<int> ans;
    check(ok);
    REP(i,0,n-1) ord[s[i]] = i;
    REP(i,1,n) for (auto j: e[i]) if (ord[i] < ord[j.t]) {
        ans.push_back(j.id);
    }

    printf("%d %d\n", ok, (int)ans.size());
    for (int i: ans) {
        printf("%d\n", i);
    }
}
int main()
{
    while (~scanf("%d %d", &n, &m)) {
        mxw = -1;
        REP(i,1,n) e[i].clear();
        REP(i,1,m) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            e[x].push_back(Edge(y, z, i));
            mxw = max(mxw, z);
        }

        work();
    }
    return 0;
}
