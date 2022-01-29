#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[] = {1'000'000, 10, 100'000, 1'000'000, 1'000'000};
constexpr int MN_K = 2;
constexpr int MN_P = 1;
constexpr int MX_P[] = {1'000'000, 1, 1, 1, 1'000'000};
constexpr int MN_W = 1;
constexpr int MX_W = 1'000'000'000;
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
    int k = inf.readInt(MN_K, n);
    inf.readChar(' ');
    int p = inf.readInt(MN_P, min(MX_P[s], n));
    inf.readChar('\n');
    ensuref((long long)k*p <= n, "k*p should <= n");

    REP(i,1,n) {
        int w = inf.readInt(MN_W, MX_W);
        if (i!=n) inf.readChar(' ');
        else inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
