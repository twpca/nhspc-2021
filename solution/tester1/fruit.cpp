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
using std::pair;
using std::vector;
using i32 = std::int32_t;
using i64 = std::int64_t;

constexpr bool debug = false;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 c{};
    i32 T{};
    cin >> c >> T;
    vector<i32> p(c + 1);
    vector<i32> s(c + 1);
    vector<i32> n(c + 1);
    vector<vector<i32>> r(c + 1, vector<i32>(c + 1));
    for (int i = 1; i <= c; ++i)
    {
        cin >> p[i];
    }
    for (int i = 1; i <= c; ++i)
    {
        cin >> s[i];
    }
    for (int i = 1; i <= c; ++i)
    {
        cin >> n[i];
    }
    for (int i = 0; i < c; ++i)
    {
        for (int j = 1; j <= i + 1; ++j)
        {
            cin >> r[i][j];
        }
        std::partial_sum(r[i].begin(), r[i].end(), r[i].begin());
    }
    vector<i32> sn(c + 1);
    std::partial_sum(n.begin(), n.end(), sn.begin());
    vector<i32> sp(c + 1);
    std::partial_sum(p.begin(), p.end(), sp.begin());
    vector<i32> dp((c + 1) * (T + 1), -0x7000'0000);
    vector<i32> lc((debug ? (c + 1) * (T + 1) : 0), -1);
    auto index = [T](int x, int y) { return x * (T + 1) + y; };
    dp[index(0, 0)] = 0;
    for (int i = 1; i <= c; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            const int cost = (s[i] + sp[i] - sp[j]) * (sn[c] - sn[j]);
            const int gain = r[i - 1][i] - r[i - 1][j];
            if (debug)
            {
                if (i == 1 && j == 0)
                {
                    cerr << "s[i]: " << s[i] << '\n';
                    cerr << "sp[i]: " << sp[i] << '\n';
                    cerr << "sp[j]: " << sp[j] << '\n';
                    cerr << "sn[c]: " << sn[c] << '\n';
                    cerr << "sn[j]: " << sn[j] << '\n';
                    cerr << "cost: " << cost << " gain: " << gain << '\n';
                }
            }
            for (int k = cost; k <= T; ++k)
            {
                auto &x = dp[index(i, k)];
                auto new_gain = dp[index(j, k - cost)] + gain;
                if (x < new_gain)
                {
                    x = new_gain;
                    if(debug)
                        lc[index(i, k)] = index(j, k - cost);
                }
            }
        }
    }
    if (debug)
    {
        for (int i = 0; i <= T; ++i)
        {
            auto x = dp[index(c, i)];
            cerr << (x < 0 ? -1 : x) << ' ';
        }
        cerr << std::endl;
    }
    i32 ans = -1;
    i32 astate = -1;
    for (int j = 0; j <= c; ++j)
    {
        const int cost = (sp[c] - sp[j]) * (sn[c] - sn[j]);
        const int gain = r[c][c] - r[c][j];
        for (int k = cost; k <= T; ++k)
        {
            auto new_gain = dp[index(j, k - cost)] + gain;
            if (ans < new_gain)
            {
                ans = new_gain;
                astate = index(j, k - cost);
            }
        }
    }
    if (debug)
    {
        for (int i = 0; i < c; ++i)
        {
            cerr << std::setw(10) << astate / (T + 1) << ' ' << std::setw(10)
                 << astate % (T + 1) << ' ' << std::setw(10) << dp[astate]
                 << '\n';
            astate = lc[astate];
        }
        cerr << std::endl;
    }
    cout << ans << std::endl;
}
