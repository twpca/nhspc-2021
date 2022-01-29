// Slow O(n log n)
// Expect: AC
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
#define INF (1LL<<61)
using namespace std;
using namespace __gnu_pbds;
using LL = long long;
using P = pair<int,LL>;
struct Metadata {
    LL sum;
    Metadata() {
        sum = 0LL;
    }
};
template<class Const_Node_Iterator,
	 class Node_Iterator,
	 class Cmp_Fn,
	 class Allocator>
class NodesUpdate {
public:
    typedef Metadata metadata_type;
    LL get_sum(int x) {
        LL res = 0;
        auto cur = node_begin();
        while (cur != node_end()) {
            if ((**cur).first <= x) {
                res += (**cur).second;
                res += (cur.get_l_child() == node_end()) ? 0 : cur.get_l_child().get_metadata().sum;
                cur = cur.get_r_child();
            } else {
                cur = cur.get_l_child();
            }
        }
        return res;
    }
protected:
    inline void operator() (Node_Iterator nd_it, Const_Node_Iterator end_nd_it) {
        Metadata l = (nd_it.get_l_child() == end_nd_it)? Metadata() : nd_it.get_l_child().get_metadata();
        Metadata r = (nd_it.get_r_child() == end_nd_it)? Metadata() : nd_it.get_r_child().get_metadata();

        P nd = **nd_it;
        Metadata m;
        m.sum = nd.second + l.sum + r.sum;
        const_cast<Metadata&> (nd_it.get_metadata()) = m;
    }
    virtual Const_Node_Iterator node_begin() const = 0;
    virtual Const_Node_Iterator node_end() const = 0;
    virtual ~NodesUpdate() {}
};
using Tree = tree<P,null_type,less<P>,splay_tree_tag,NodesUpdate>;

int n,s,o,w,id,st[M],ed[M],rd[M],dep[M];
pair<int,int> es[M];
vector<int> e[M];
Tree t;
void init() {
    REP(i,1,n) e[i].clear();
    REP(i,1,n-1) {
        int x, y;
        scanf("%d %d", &x, &y);
        e[x].push_back(y);
        e[y].push_back(x);
        es[i] = make_pair(x, y);
    }
}
void dfs(int cur, int fa, int d) {
    st[cur] = ++id;
    dep[cur] = d;
    rd[st[cur]] = d;
    for (int i: e[cur]) if (i!=fa) {
        dfs(i, cur, d+1);
    }
    ed[cur] = id;
}
void work() {
    id = 0;
    dfs(s, -1, 0);
    t.clear();
    REP(i,1,n) {
        t.insert(make_pair(i, (LL)rd[i] - rd[i-1]));
    }

    auto add_node = [&](int x, int v) {
        auto it = t.lower_bound(make_pair(x, -INF));
        assert(it->first == x);

        LL nv = it->second + v;
        t.erase(it);
        t.insert(make_pair(x, nv));
    };

    int c, x, y;
    REP(i,1,o+w) {
        scanf("%d", &c);
        if (c==1) {
            scanf("%d %d", &x, &y);
            printf("%lld\n", t.get_sum(st[y]) * x);
        } else {
            scanf("%d", &x);
            tie(x, y) = es[x];
            if (dep[x] > dep[y]) swap(x, y);
            add_node(st[y], -1);
            if (ed[y] < n) add_node(ed[y]+1, 1);
        }
    }
}
int main()
{
    while (~scanf("%d %d %d %d", &n, &s, &o, &w)) {
        init();
        work();
    }
    return 0;
}
