#include <algorithm>
#include <array>
#include <cstdint>
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
            e[x].emplace_back(i, y, sum);
        }
        return true;
    }
    array<i32, 3> get_last_choice(vector<i32> &lc)
    {
        lc.resize(n * n, -1);
        array<i32, 3> ans{};
        {
            vector<i64> we(n * n, 0x7fff'ffff'ffff'ffffll / 3);
            auto index = [this](int x, int y) { return x * n + y; };
            for (int i = 0; i < n; ++i)
            {
                for (auto &nex : e[i])
                {
                    we[index(i, std::get<1>(nex))] =
                        -i64(std::get<2>(nex)) * n - 1;
                }
                we[index(i, i)] = 0;
            }
            for (int k = 0; k < n; ++k)
            {
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        i64 sum = we[index(i, k)] + we[index(k, j)];
                        i64 c2 = sum + we[index(j, i)];
                        if (c2 < 0)
                        {
                            return array<i32, 3>{i, k, j};
                        }
                    }
                }
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        i64 sum = we[index(i, k)] + we[index(k, j)];
                        auto &cur = we[index(i, j)];
                        if (cur > sum)
                        {
                            cur = sum;
                            lc[index(i, j)] = k;
                        }
                    }
                }
            }
        }
        return ans;
    }
    void get_cycle(vector<i32> &out, const vector<i32> &lc, int x, int y)
    {
        auto index = [this](int x, int y) { return x * n + y; };
        int m = lc[index(x, y)];
        if (m == -1)
        {
            out.push_back(x);
            return;
        }
        get_cycle(out, lc, x, m);
        get_cycle(out, lc, m, y);
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
        get_cycle(cycle, lc, ans[0], ans[1]);
        get_cycle(cycle, lc, ans[1], ans[2]);
        get_cycle(cycle, lc, ans[2], ans[0]);
        cycle.erase(std::unique(cycle.begin(), cycle.end()), cycle.end());
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
        i32 mi = 0;
        i32 big_ans = 0;
        i32 small_ans = 0;
        for (int st = 0; st < sz; ++st)
        {
            i64 sum = 0;
            bool fail = false;
            for (int i = 0, j = st; i < sz; ++i)
            {
                sum += c[fcycle[j]];
                if (sum < 0)
                {
                    fail = true;
                    break;
                }
                ++j;
                if (j == sz)
                    j = 0;
            }
            if (!fail)
            {
                big_ans += fcycle[st] < n;
                small_ans += !(fcycle[st] < n);
                mi = st;
            }
        }
        if (sz != 0)
        {
            os << sz + 1 << '\n';
            for (int i = 0; i <= sz; ++i)
            {
                os << fcycle[(i + mi) % sz] + 1 << (i == sz ? '\n' : ' ');
            }
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
    dddata d{};
    d.input(std::cin);
    d.work_nnn(std::cout);
}
