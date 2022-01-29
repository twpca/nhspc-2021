#include "testlib.h"
#include <cassert>
#include <vector>
constexpr int MN_C = 1;
constexpr int MX_C[] = {40, 20, 40, 40};
constexpr int MN_N = 1;
constexpr int MX_N = 40;
constexpr int MN_PI = 1;
constexpr int MX_PI = 1000;
constexpr int MN_T = 1;
constexpr int MX_T[] = {10'000'000, 30'000, 30'000, 10'000'000};

int subtask(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp("--testcase", argv[i - 1]))
        {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    const int s = subtask(argc, argv);

    const int c = inf.readInt(MN_C, MX_C[s]);
    inf.readChar(' ');
    inf.readInt(MN_T, MX_T[s]);
    inf.readChar('\n');

    for (int i = 1; i <= c; ++i)
    {
        inf.readInt(MN_PI, MX_PI);
        inf.readChar(i != c ? ' ' : '\n');
    }
    for (int i = 1; i <= c; ++i)
    {
        inf.readInt(MN_PI, MX_PI);
        inf.readChar(i != c ? ' ' : '\n');
    }
    {
        std::vector<int> n(c);
        for (int i = 1; i <= c; ++i)
        {
            n[i - 1] = inf.readInt(MN_N, MX_N);
            inf.readChar(i != c ? ' ' : '\n');
        }
        for (int i = 0; i <= c; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                inf.readInt(0, n[j]);
                inf.readChar(j + 1 != i ? ' ' : '\n');
            }
        }
    }
    inf.readEof();
}
