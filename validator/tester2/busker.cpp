#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[] = {2000, 20, 90, 2000};
constexpr int MN_M = 1;
constexpr int MX_M = 8000;
constexpr int MN_C = -100'000'000;
constexpr int MX_C = 100'000'000;
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int n = inf.readInt(MN_N, MX_N[s]);
    inf.readChar(' ');
    int m = inf.readInt(MN_M, MX_M);
    inf.readChar(' ');
    int k = inf.readInt(1, n);
    inf.readChar('\n');

    REP(i,1,n) {
        inf.readInt(MN_C, MX_C);
        inf.readChar('\n');
    }
    std::set<std::pair<int, int>> mp;
    REP(i,1,m) {
        int x = inf.readInt(1, n);
        inf.readChar(' ');
        int y = inf.readInt(1, n);
        ensuref(x != y, "self cycle!");
        auto it = mp.emplace(x, y);
        ensuref(it.second, "duplicate edges!");
        REP(j,1,k) {
            inf.readChar(' ');
            inf.readInt(MN_C, MX_C);
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
