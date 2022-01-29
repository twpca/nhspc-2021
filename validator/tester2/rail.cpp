#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;
constexpr LL MN_N = 1;
constexpr LL MX_N[] = {10'000'000'000, 7, 1'000, 100'000, 10'000'000'000};
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
    inf.readLong(MN_N, MX_N[s]);
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
