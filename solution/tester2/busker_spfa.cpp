// O(nm + input)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define INF (1LL<<62) // TODO: too small?
using namespace std;
using P = pair<int,int>;
using LL = long long;
struct Edge {
    int t, lid;
    LL w;
    Edge () {}
    Edge (int _t, LL _w, int _lid) {
        t = _t;
        w = _w;
        lid = _lid;
    }
};
int n, m, k;
vector<int> c;
vector<vector<int>> lst;
vector<vector<Edge>> e;
Edge find_edge(int x,int y) {
    for (auto i: e[x]) {
        if (i.t == y) {
            return i;
        }
    }
    fprintf(stderr, "error: %d %d not found\n", x, y);
    assert(0);
    return Edge();
}
void init() {
    c = vector<int> (n + m*k + 1);
    e = vector<vector<Edge>> (n+1);
    lst = vector<vector<int>> (m+1);

    REP(i,1,n) {
        scanf("%d", &c[i]);
    }
    REP(i,1,m) {
        int x, y;
        lst[i].clear();
        scanf("%d %d", &x, &y);

        REP(j, n+1+(i-1)*k, n+i*k) {
            scanf("%d", &c[j]);
            lst[i].push_back(j);
        }

        LL s = c[y];
        for (int j: lst[i]) s += c[j];
        e[x].emplace_back(y, s, i);
    }
}
vector<int> spfa() {
    vector<int> res;
    deque<int> q;
    vector<bool> inq = vector<bool> (n+1, false);
    vector<int> fr = vector<int> (n+1, -1);
    vector<int> cnt = vector<int> (n+1, 0);
    vector<LL> dis = vector<LL> (n+1, -INF);
    vector<LL> dis2 = vector<LL> (n+1, -INF);

    REP(i,1,n) {
        dis[i] = c[i];
        dis2[i] = 0;
        q.push_back(i);
        inq[i] = true;
    }
    int cur;
    int pos = 0;
    while (!q.empty()) {
        if (rand() % 2) {
            cur = q.front();
            q.pop_front();
        } else {
            cur = q.back();
            q.pop_back();
        }
        inq[cur] = false;
        if (pos) break;

        for (auto i: e[cur]) {
            if (make_tuple(dis[i.t], dis2[i.t]) < make_tuple(dis[cur] + i.w, dis2[cur] + 1)) {
                dis[i.t] = dis[cur] + i.w;
                dis2[i.t] = dis2[cur] + 1;
                fr[i.t] = cur;
                if (!inq[i.t] && cnt[i.t] <= n) {
                    cnt[i.t]++;
                    q.push_back(i.t);
                    inq[i.t] = true;
                } else if (!inq[i.t] && cnt[i.t] > n) {
                    pos = i.t;
                    break;
                }
            }
        }
    }

    // no positive cycle
    if (!pos) return res;

    unordered_map<int, bool> vis;
    while (!vis[pos]) {
        vis[pos] = true;
        res.push_back(pos);
        pos = fr[pos];
    }
    reverse(res.begin(), res.end());
    while (res.back() != pos) res.pop_back();

    // check
    find_edge(res.back(), res[0]);
    return res;
}
pair<vector<int>, vector<int>> get_cycle_values(vector<int>& cycle) {
    vector<int> ps, ids;
    REP(i,0,(int)cycle.size()-1) {
        int cur = cycle[i];
        int nxt = cycle[(i+1) % cycle.size()];
        Edge ec = find_edge(cur, nxt);

        ps.push_back(c[cur]);
        ids.push_back(cur);
        for (int j: lst[ec.lid]) {
            ps.push_back(c[j]);
            ids.push_back(j);
        }
    }
    return make_pair(ps, ids);
}
void calc_ans(vector<int>& ps, vector<int>& ids) {
    int sz = ps.size();
    vector<LL> lsum = vector<LL> (sz);
    vector<LL> rsum = vector<LL> (sz);
    vector<LL> lmin = vector<LL> (sz);
    vector<LL> rmin = vector<LL> (sz);

    LL s = 0;
    REP(i,0,sz-1) {
        s += ps[i];
        lsum[i] = s;
        lmin[i] = s;
        if (i != 0) {
            lmin[i] = min(lmin[i], lmin[i-1]);
        }
    }

    s = 0;
    for (int i=sz-1; i>=0; i--) {
        s += ps[i];
        rsum[i] = s;
        rmin[i] = ps[i];
        if (i != sz-1) {
            rmin[i] = min(rmin[i], ps[i] + rmin[i+1]);
        }
    }


    int big=0, small=0, start=-1;
    REP(i,0,sz-1) {
        LL mn = rmin[i];
        if (i != 0) {
            mn = min(mn, rsum[i] + lmin[i-1]);
        }
        if (mn >= 0) {
            if (start == -1) start = i;
            if (i % (k+1) == 0) big++;
            else small++;
        }
    }

    printf("%d\n", sz==0 ? 0 : sz+1);
    if (sz == 0) return;
    rotate(ids.begin(), ids.begin()+start, ids.end());
    REP(i, 0, sz-1) {
        if (i != 0) printf(" ");
        printf("%d", ids[i]);
    }
    printf(" %d", ids[0]);
    puts("");
    printf("%d %d\n", big, small);
}
int main()
{
    srand(514);
    while (~scanf("%d %d %d", &n, &m, &k)) {
        init();

        auto cycle = spfa();
        vector<int> ps, ids;
        tie(ps, ids) = get_cycle_values(cycle);
        calc_ans(ps, ids);
    }
    return 0;
}
