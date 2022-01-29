#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[] = {200, 200, 200, 200};
constexpr int MN_T = 1;
constexpr int MX_T[] = {200, 3, 100, 200};
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
    inf.readChar('\n');

    vector<int> in;
    REP(i,1,n) {
        int x = inf.readInt(MN_T, MX_T[s]);

        if (i==n) {
            inf.readChar('\n');
        } else {
            inf.readChar(' ');
        }
        in.push_back(x);
    }
    inf.readEof();
    return 0;
}
