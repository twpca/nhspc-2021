#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_C = 1;
constexpr int MX_C[] = {40, 20, 40, 40};
constexpr int MN_T = 1;
constexpr int MX_T[] = {10'000'000, 30'000, 30'000, 10'000'000};

constexpr int MN_PS = 1;
constexpr int MX_PS = 1000;
constexpr int MN_N = 1;
constexpr int MX_N = 40;
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

    int c = inf.readInt(MN_C, MX_C[s]);
    inf.readChar(' ');
    int t = inf.readInt(MN_T, MX_T[s]);
    inf.readChar('\n');

    // p
    REP(i,1,c) {
        inf.readInt(MN_PS, MX_PS);
        if (i==c) inf.readChar('\n');
        else inf.readChar(' ');
    }

    // s
    REP(i,1,c) {
        inf.readInt(MN_PS, MX_PS);
        if (i==c) inf.readChar('\n');
        else inf.readChar(' ');
    }

    // n
    vector<int> n (c+1);
    REP(i,1,c) {
        n[i] = inf.readInt(MN_N, MX_N);
        if (i==c) inf.readChar('\n');
        else inf.readChar(' ');
    }

    // r
    REP(i,1,c) {
        REP(j,1,i) {
            inf.readInt(0, n[j]);
            if (j==i) inf.readChar('\n');
            else inf.readChar(' ');
        }
    }

    inf.readEof();
    return 0;
}
