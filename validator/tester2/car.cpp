#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using P = pair<int,int>;
constexpr int MN_N = 2;
constexpr int MX_NM[] = {100'000, 20, 100'000, 100'000};
constexpr int MN_M = 0;
constexpr int MN_C = 1;
constexpr int MX_C[] = {1'000'000'000, 1'000'000'000, 100, 1'000'000'000};

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

    int n = inf.readInt(MN_N, MX_NM[s]);
    inf.readChar(' ');
    int m = inf.readInt(MN_M, MX_NM[s]);
    inf.readChar('\n');

    REP(i,1,m) {
        int u = inf.readInt(1, n);
        inf.readChar(' ');
        int v = inf.readInt(1, n);
        inf.readChar(' ');
        int c = inf.readInt(MN_C, MX_C[s]);
        inf.readChar('\n');

        ensuref(u!=v, "no self cycle");
    }
    inf.readEof();
    return 0;
}
