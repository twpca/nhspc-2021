#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<tuple<int, int, int, int>> E;
vector<vector<int>> G;
vector<int> id;

bool test(int K)
{
    G.clear();
    G.resize(N);
    vector<int> deg(N, 0);
    for (const auto &[w, i, j, _] : E)
    {
        if (w <= K)
            break;
        G[i].emplace_back(j);
        deg[j]++;
    }

    stack<int> st;
    id.resize(N);
    for (int i = 0; i < N; ++i)
    {
        id[i] = -1;
        if (deg[i] == 0)
            st.emplace(i);
    }

    int order = 0;
    while (!st.empty())
    {
        int v = st.top();
        st.pop();
        id[v] = order++;

        for (int w : G[v])
        {
            deg[w]--;
            if (deg[w] == 0)
                st.emplace(w);
        }
    }

    return order == N;
}

int main()
{
    int eid = 0;
    cin >> N >> M;
    E.resize(M);

    vector<int> C;

    for (auto &[w, i, j, id] : E)
    {
        cin >> i >> j >> w;
        i--; j--;
        id = ++eid;
        C.emplace_back(w);
    }

    sort(E.begin(), E.end(), greater<>());
    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());

    int L = 0, R = (int)C.size() - 1;
    if (test(0))
    {
        // no edge reverse required
        cout << 0 << ' ' << 0 << '\n';
    }
    else
    {
        int sol = R;
        while (L < R)
        {
            int M = (L + R) / 2;
            if (test(C[M]))
            {
                sol = min(M, sol);
                R = M - 1;
            }
            else
                L = M + 1;
        }
        if (test(C[L])) {
            sol = min(L, sol);
        }

        test(C[sol]);
        vector<int> revid;

        for (auto [w, i, j, eid] : E)
        {
            if (w > C[sol])
                continue;
            if (id[i] > id[j])
                revid.emplace_back(eid);
        }

        cout << C[sol] << ' ' << revid.size() << '\n';
        for (auto &i : revid)
            cout << i << '\n';
    }
}
