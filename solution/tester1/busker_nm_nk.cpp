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

struct dddata
{
    i32 n;
    i32 input_k;
    vector<i32> c;
    vector<vector<std::tuple<i32, i32, i64>>> e;

    bool input(std::istream &is)
    {
        i32 m{}, k{};
        if (!(is >> n >> m >> k))
            return false;
        input_k = k;
        i32 nn = n + m * k;
        c.resize(nn);
        for (int i = 0; i < n; ++i)
        {
            is >> c[i];
        }
        e.resize(n);
        for (int i = 0; i < m; ++i)
        {
            i32 x, y;
            is >> x >> y;
            x = x - 1;
            y = y - 1;
            i64 sum = c[y];
            for (int j = n + i * k, ed = j + k; j < ed; ++j)
            {
                is >> c[j];
                sum += c[j];
            }
            e[x].emplace_back(i, y, -sum * (n + 1) - 1);
        }
        return true;
    }
    array<i32, 3> get_last_choice(vector<i32> &lc)
    {
        lc.resize(n, -1);
        if (debug)
        {
            std::cout << " i:";
            for (int i = 0; i < n; ++i)
            {
                std::cout << std::setw(10) << i << ' ';
            }
            std::cout << '\n';
        }
        vector<i64> we(n);
        {
            vector<i64> ne(n);
            for (int p = 1; p < n; ++p)
            {
                for (int i = 0; i < n; ++i)
                {
                    for (auto &nex : e[i])
                    {
                        auto &y = std::get<1>(nex);
                        auto &w = std::get<2>(nex);
                        i64 sum = we[i] + w;
                        if (ne[y] > sum)
                        {
                            ne[y] = sum;
                            lc[y] = i;
                        }
                    }
                }
                we = ne;
                if (debug)
                {
                    std::cout << "we:";
                    for (int i = 0; i < n; ++i)
                    {
                        std::cout << std::setw(10) << we[i] << ' ';
                    }
                    std::cout << '\n';
                    std::cout << "lc:";
                    for (int i = 0; i < n; ++i)
                    {
                        std::cout << std::setw(10) << lc[i] << ' ';
                    }
                    std::cout << '\n';
                    std::cout.flush();
                }
            }
        }
        {
            if (debug)
            {
                for (int i = 0; i < n; ++i)
                {
                    for (auto &nex : e[i])
                    {
                        auto &y = std::get<1>(nex);
                        auto &w = std::get<2>(nex);
                        i64 sum = we[i] + w;

                        std::cout << " i:" << std::setw(10) << i << ' ';
                        std::cout << " y:" << std::setw(10) << y << ' ';
                        std::cout << std::setw(10) << we[i] << ' ';
                        std::cout << std::setw(10) << w << ' ';
                        std::cout << std::setw(10) << sum << ' ';
                        std::cout << std::setw(10) << we[y] << '\n';
                    }
                }
            }
            for (int i = 0; i < n; ++i)
            {
                for (auto &nex : e[i])
                {
                    auto &y = std::get<1>(nex);
                    auto &w = std::get<2>(nex);
                    i64 sum = we[i] + w;
                    if (we[y] > sum)
                    {
                        lc[y] = i;
                        return array<i32, 3>{y, i};
                    }
                }
            }
        }
        return array<i32, 3>{};
    }
    auto get_cycle()
    {
        vector<i32> lc{};
        array<i32, 3> ans = get_last_choice(lc);
        vector<i32> cycle{};
        if (ans == decltype(ans)())
        {
            return cycle;
        }
        if (debug)
        {
            for (int i = 0; i < n; ++i)
            {
                std::cout << std::setw(5) << i << ' ' << std::setw(5) << lc[i]
                          << '\n';
            }
        }
        vector<bool> vis(n);
        int y = ans[1];
        if (debug)
        {
            std::cout << "y:" << std::setw(5) << y << '\n';
        }
        for (int i = 0; !vis[y] && i < n; ++i)
        {
            vis[y] = true;
            cycle.push_back(y);
            y = lc[y];
        }
        if (debug)
        {
            std::cout << "y:" << std::setw(5) << y << '\n';
            for (int i = 0; i < int(cycle.size()); ++i)
            {
                std::cout << std::setw(5) << cycle[i] << ' ';
            }
            std::cout << '\n';
            std::cout.flush();
        }
        auto it = std::find(cycle.begin(), cycle.end(), y);
        cycle.erase(cycle.begin(), it);
        std::reverse(cycle.begin(), cycle.end());
        if (debug)
        {
            for (int i = 0; i < int(cycle.size()); ++i)
            {
                std::cout << std::setw(5) << cycle[i] << ' ';
            }
            std::cout << '\n';
            std::cout.flush();
        }
        return cycle;
    }
    auto get_fcycle()
    {
        vector<i32> fcycle{};
        vector<i32> cycle = get_cycle();
        const int sz = cycle.size();
        for (int i = 0; i < sz; ++i)
        {
            int j = i + 1 == sz ? 0 : i + 1;
            fcycle.push_back(cycle[i]);
            for (auto &nex : e[cycle[i]])
            {
                if (cycle[j] == std::get<1>(nex))
                {
                    for (int x = 0; x < input_k; ++x)
                    {
                        fcycle.push_back(n + std::get<0>(nex) * input_k + x);
                    }
                    break;
                }
            }
        }
        return fcycle;
    }
    void work_nnn(std::ostream &os)
    {
        vector<i32> fcycle = get_fcycle();
        const int sz = int(fcycle.size());
        i64 sum = 0;
        {
            i64 mn = 0x7fff'ffff'ffff'ffffll;
            i32 mi = -1;
            for (int i = 0; i < sz; ++i)
            {
                sum += c[fcycle[i]];
                if (mn > sum)
                {
                    mn = sum;
                    mi = i;
                }
            }
            mi = mi + 1 == sz ? 0 : mi + 1;
            std::rotate(fcycle.begin(), fcycle.begin() + mi, fcycle.end());
        }
        i32 big_ans = 0;
        i32 small_ans = 0;
        {
            i64 mn = sum;
            for (int i = sz - 1; i >= 0; --i)
            {
                sum -= c[fcycle[i]];
                if (sum <= mn)
                {
                    big_ans += fcycle[i] < n;
                    small_ans += !(fcycle[i] < n);
                }
                mn = std::min(mn, sum);
            }
        }
        if (sz != 0)
        {
            os << sz + 1 << '\n';
            for (int i = 0; i < sz; ++i)
            {
                os << fcycle[i] + 1 << ' ';
            }
            os << fcycle[0] + 1 << '\n';
            os << big_ans << ' ' << small_ans << '\n';
        }
        else
        {
            os << 0 << '\n';
        }
        os.flush();
    }
};
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    dddata d{};
    d.input(std::cin);
    d.work_nnn(std::cout);
}
