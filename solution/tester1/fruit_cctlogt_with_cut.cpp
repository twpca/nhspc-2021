#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>
using std::array;
using std::cerr;
using std::cin;
using std::cout;
using std::map;
using std::pair;
using std::vector;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

constexpr bool debug = false;

struct search_t
{
    int c;
    int T;
    vector<i32> sp;
    vector<i32> s;
    vector<i32> sn;
    vector<vector<i32>> r;
    vector<map<i32, i32>> dp;
    search_t(int c_, int T_)
        : c(c_), T(T_), sp(c + 2), s(c + 2), sn(c + 2), r(c + 1), dp(c + 2)
    {
        int cc = c + 2;
        for (; cc != (cc & -cc); cc += (cc & -cc))
            ;
        for (auto &x : r)
        {
            x = vector<i32>(cc);
        }
    }
    void input(std::istream &is)
    {
        for (int i = 1; i <= c; ++i)
        {
            cin >> sp[i];
        }
        std::partial_sum(sp.begin(), sp.end(), sp.begin());
        for (int i = 1; i <= c; ++i)
        {
            cin >> s[i];
        }
        for (int i = 1; i <= c; ++i)
        {
            cin >> sn[i];
        }
        std::partial_sum(sn.begin(), sn.end(), sn.begin());
        {
            const int x = sn[c];
            for (int i = 0; i <= c + 1; ++i)
            {
                sn[i] = x - sn[i];
            }
        }
        for (int i = 0; i < c; ++i)
        {
            for (int j = 1; j <= i + 1; ++j)
            {
                cin >> r[i][j];
            }
            std::partial_sum(r[i].begin(), r[i].end(), r[i].begin());
            const int x = r[i][i + 1];
            for (int j = 0; j <= c + 1; ++j)
            {
                r[i][j] = x - r[i][j];
            }
        }
    }
    i32 dfs(int last, i32 cost, i32 upper_bound)
    {
        if (last == c + 1)
        {
            return 0;
        }
        auto &cur_map = dp[last];
        auto jt = cur_map.lower_bound(cost);
        if (jt != cur_map.end())
        {
            if (cost < jt->first)
            {
                if (jt->second <= upper_bound)
                {
                    return upper_bound;
                }
            }
            else
            {
                return jt->second;
            }
        }
        auto it = cur_map.insert({cost, -0x3fff'ffff});
        auto &max_gain = it.first->second;
        for (int i = last + 1; i <= c + 1; ++i)
        {
            const i32 cost2 = (sp[i] - sp[last]) * sn[last];
            if (0 > cost - cost2)
                break;
            const i32 new_cost = cost - cost2 - s[i] * (sn[last] - sn[i]);
            if (new_cost >= 0)
            {
                const auto &gain_delta = r[i - 1][last];
                max_gain =
                    std::max(max_gain, dfs(i, new_cost, max_gain - gain_delta) +
                                           gain_delta);
            }
        }
        return max_gain;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 c{};
    i32 T{};
    cin >> c >> T;
    search_t d(c, T);
    d.input(cin);
    i32 ans = d.dfs(0, T, -0x3fff'ffff);
    if (ans < 0)
    {
        ans = -1;
    }
    cout << ans << std::endl;
}
