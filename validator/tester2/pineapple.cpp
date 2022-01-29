#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[] = {100'000, 100, 100'000, 100'000};
constexpr int MN_O = 1;
constexpr int MX_O = 100'000;
constexpr int MN_X = 1;
constexpr int MX_X[] = {100'000, 1'000, 100'000, 100'000};
vector<int> e[MX_N[0] + 5];
vector<bool> vis;

int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int dfs(int cur) {
    vis[cur] = true;
    int res = 1;
    for (int i: e[cur]) if (!vis[i]) {
        res += dfs(i);
    }
    return res;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int n = inf.readInt(MN_N, MX_N[s]);
    inf.readChar(' ');
    int st = inf.readInt(1, n);
    inf.readChar(' ');
    int o = inf.readInt(MN_O, MX_O);
    inf.readChar(' ');
    int w = inf.readInt(0, n-1);
    inf.readChar('\n');

    vector<int> deg(n+1, 0);
    REP(i,1,n-1) {
        int u = inf.readInt(1, n);
        inf.readChar(' ');
        int v = inf.readInt(1, n);
        inf.readChar('\n');

        ensuref(u!=v, "u != v");
        e[u].push_back(v);
        e[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<bool> del(n, false);
    int co1 = 0;
    int co2 = 0;
    REP(i,1,o+w) {
        int c = inf.readInt(1, 2);
        inf.readChar(' ');
        if (c == 1) {
            co1++;
            int x = inf.readInt(MN_X, MX_X[s]);
            inf.readChar(' ');
            int y = inf.readInt(1, n);
        } else {
            co2++;
            int z = inf.readInt(1, n-1);
            ensuref(del[z] == false, "z dup");
            del[z] = true;
        }
        inf.readChar('\n');
    }
    inf.readEof();
    ensuref(co1==o && co2==w, "c1==o, c2==w should be satisfied");

    vis = vector<bool>(n+1, false);
    ensuref(dfs(1)==n, "should be a connected tree");

    auto check_line = [&]() {
        int c1 = 0;
        int c2 = 0;
        REP(i,1,n) {
            if (deg[i] == 1) c1++;
            else if (deg[i] == 2) c2++;
            else return false;
        }

        // deg[st] should be 1
        if (deg[st] != 1) return false;

        if (c1!=min(n,2) || c2!=max(n-2,0)) return false;
        return true;
    };
    if (s==2) ensuref(check_line(), "subtask2 should be a line");

    return 0;
}
