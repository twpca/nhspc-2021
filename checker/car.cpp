#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int N, M, ANSK;
vector<tuple<int, int, int>> E;

bool isDAG()
{
    vector<vector<int>> G(N);
    vector<int> deg(N);
    for (auto [i, j, w] : E)
    {
        G[i].emplace_back(j);
        deg[j]++;
    }
    int SZ = 0;

    stack<int> st;
    for (int i = 0; i < N; ++i)
        if (deg[i] == 0)
            st.emplace(i);
    while (!st.empty())
    {
        int v = st.top();
        st.pop();
        SZ++;

        for (int w : G[v])
        {
            deg[w]--;
            if (deg[w] == 0)
                st.push(w);
        }
    }
    return SZ == N;
}

int main(int argc, char *argv[])
{
    registerTestlibCmd(argc, argv);

    N = inf.readInt();
    M = inf.readInt();
    E.resize(M);
    for (auto &[i, j, w] : E)
    {
        i = inf.readInt();
        i--;
        j = inf.readInt();
        j--;
        w = inf.readInt();
    }

    ANSK = ans.readInt();

    int USERK = ouf.readInt();
    int USERN = ouf.readInt(0, M);

    if (USERK != ANSK)
    {
        quitf(_wa, "K not correct, expect %d, found %d.", ANSK, USERK);
    }

    vector<int> RevFlag(M + 1, -1);
    for (int i = 0; i < USERN; ++i)
    {
        int eid = ouf.readInt(1, M);
        if (RevFlag[eid] != -1)
        {
            quitf(_wa, "eid '%d' duplicated at line %d and %d.", eid, RevFlag[eid] + 1, i + 1);
        }
        RevFlag[eid] = i;

        int a, b, w;
        tie(a, b, w) = E[eid - 1];

        if (w > USERK)
        {
            quitf(_wa, "eid '%d' can not be used because it has level %d, it should be no more than %d", eid, w, USERK);
        }

        E[eid - 1] = make_tuple(b, a, w);
    }

    if (isDAG())
        quitf(_ok, "ok, the graph is DAG.");
    else
        quitf(_wa, "wa, it is not a DAG.");
}
