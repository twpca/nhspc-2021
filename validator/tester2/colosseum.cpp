#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[] = {300'000, 1000, 300'000, 300'000, 300'000};
constexpr int MN_M = 0;
constexpr int MX_M = 1'000'000'000;
constexpr int MN_TW = 1;
constexpr int MX_TW = 1000;
constexpr int MN_XY = 0;
constexpr int MX_X[] = {1'000'000'000, 1'000'000'000, 0,             0, 1'000'000'000};
constexpr int MX_Y[] = {1'000'000'000, 1'000'000'000, 0, 1'000'000'000, 1'000'000'000};
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
    inf.readChar('\n');

    REP(i,1,n) {
        int x = inf.readInt(MN_XY, MX_X[s]);
        inf.readChar(' ');
        int y = inf.readInt(MN_XY, MX_Y[s]);
        inf.readChar(' ');
        int t = inf.readInt(MN_TW, MX_TW);
        inf.readChar(' ');
        int w = inf.readInt(MN_TW, MX_TW);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
