#include "testlib.h"
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
using std::set;
using std::tuple;
using std::vector;
using i32 = std::int32_t;
using i64 = std::int64_t;
constexpr i32 MAXN = 0x7fff'ffff;

struct dddata
{
    i32 n;
    i32 input_k;
    i32 nn;
    vector<i32> shi_w;
    vector<set<i32>> e;
    vector<set<i32>> r_e;
    // Assume file from `is` is validated by the validator.
    void input(InStream &is)
    {
        i32 m{}, k{};
        n = is.readInt(1, MAXN);
        m = is.readInt(1, MAXN);
        k = is.readInt(1, MAXN);
        input_k = k;
        nn = n + m * k;
        shi_w.resize(nn);
        for (int i = 0; i < n; ++i)
        {
            i32 c = is.readInt(-MAXN, MAXN);
            shi_w[i] = c;
        }
        e.resize(n);
        r_e = e;
        for (int i = 0; i < m; ++i)
        {
            const i32 x = is.readInt(1, nn) - 1;
            const i32 y = is.readInt(1, nn) - 1;
            for (int st = n + i * k, ed = st + k; st < ed; ++st)
            {
                shi_w[st] = is.readInt(-MAXN, MAXN);
            }
            e[x].insert(n + i * k);
            r_e[y].insert(n + i * k + k - 1);
        }
    }
    void check_output(InStream &output, InStream &ansx)
    {
        int output_cn = output.readInt(0, nn + 1);
        if (output_cn == 0)
        {
            const int ans_cn = ansx.readInt(0, nn + 1);
            quitif(ans_cn != 0, TResult::_wa,
                   "There is a cycle but output with no cycle.");
            quitf(TResult::_ok, "case 1");
        } else if(output_cn == 1){
            quitf(TResult::_wa, "A valid cycle must have r >= 2");
        }
        vector<i32> fcycle(output_cn);
        for (auto &x : fcycle)
        {
            x = output.readInt(1, nn) - 1;
        }
        quitif(fcycle.front() != fcycle.back(), TResult::_wa,
               "Output is not a cycle.");
        fcycle.pop_back();
        --output_cn;
        const i32 user_big_ans = output.readInt(0, n);
        const i32 user_small_ans = output.readInt(0, nn - n);
        quitif(user_big_ans + user_small_ans == 0, TResult::_wa,
               "Must be at least one valid start point. Save time.");
        i64 sum = 0;
        {
            vector<bool> test_b(nn);
            for (int i = 0; i < output_cn; ++i)
            {
                const i32 x = fcycle[i];
                quitif(test_b[x], TResult::_wa, "%dth city %d repeats ", i,
                       x + 1);
                test_b[x] = true;
                sum += shi_w[x];
                quitif(sum < 0, TResult::_wa, "%dth city %d sum < 0", i, x + 1);
                const i32 j = i + 1 == output_cn ? 0 : i + 1;
                const i32 y = fcycle[j];
                bool connect;
                if (x < n)
                {
                    connect = e[x].find(y) != e[x].end();
                }
                else if (y < n)
                {
                    connect = r_e[y].find(x) != r_e[y].end();
                }
                else
                {
                    const auto k = input_k;
                    connect =
                        x + 1 == y && (y - n) % k != 0 && (x - n) % k != k - 1;
                }
                quitif(!connect, TResult::_wa,
                       "%dth city %d does not connect to %dth city %d", i,
                       x + 1, j, y + 1);
            }
        }
        {
            const int sz = output_cn;
            i32 big_ans = 0;
            i32 small_ans = 0;
            {
                i64 mn = sum;
                for (int i = sz - 1; i >= 0; --i)
                {
                    sum -= shi_w[fcycle[i]];
                    if (sum <= mn)
                    {
                        big_ans += fcycle[i] < n;
                        small_ans += !(fcycle[i] < n);
                    }
                    mn = std::min(mn, sum);
                }
            }
            quitif(user_big_ans != big_ans, TResult::_wa,
                   "user_big_ans: %d != big_ans %d", user_big_ans, big_ans);
            quitif(user_small_ans != small_ans, TResult::_wa,
                   "user_small_ans: %d != small_ans %d", user_small_ans,
                   small_ans);
        }
        quitf(TResult::_ok, "case 2");
    }
};
int main(int argc, char *argv[])
{
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("special judge for busker");
    registerTestlibCmd(argc, argv);
    dddata d{};
    d.input(inf);
    d.check_output(ouf, ans);
}
