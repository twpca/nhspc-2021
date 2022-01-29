#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using P = pair<int,int>;
constexpr int MN_N = 1;
constexpr int MX_N[] = {100, 1, 100, 100};
constexpr int MN_A = 0;
constexpr int MX_A[] = {1'000'000, 100, 1'000'000, 1'000'000};
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
bool check_no_dup(vector<P>& ps) {
    REP(i,1,(int)ps.size()-1) {
        if (ps[i].first == ps[i-1].first && ps[i].second == ps[i-1].second) {
            return false;
        }
    }
    return true;
}
bool check_horizontal_vertical(vector<P>& ps) {
    REP(i,1,(int)ps.size()-1) {
        if (ps[i].first != ps[i-1].first && ps[i].second != ps[i-1].second) {
            return false;
        }
    }
    return true;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int a = inf.readInt(MN_A, MX_A[s]);
    inf.readChar(' ');
    int b = inf.readInt(MN_A, MX_A[s]);
    inf.readChar(' ');
    int n = inf.readInt(MN_N, MX_N[s]);
    inf.readChar('\n');

    vector<P> in;
    REP(i,1,n+1) {
        int x = inf.readInt(MN_A, MX_A[s]);
        inf.readChar(' ');
        int y = inf.readInt(MN_A, MX_A[s]);
        inf.readChar('\n');
        in.push_back(make_pair(x, y));
    }
    inf.readEof();

    ensuref(check_no_dup(in), "Duplicate points");
    if (s==1 || s==2) {
        ensuref(check_horizontal_vertical(in), "Every segmente should be vertical or horizontal");
    }
    return 0;
}
