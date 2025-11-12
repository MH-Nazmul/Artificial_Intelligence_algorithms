#include <bits/stdc++.h>
using namespace std;
int f(int x) { return (x - 3) * (x - 3); }
vector<int> neighbors(int x) { return {x - 1, x + 1}; }
pair<int, int> hill(int init, int max_steps)
{
    int x = init;
    int fx = f(x);
    for (int step = 0; step < max_steps; step++)
    {
        int best = fx;
        int bestx = x;
        auto nbr = neighbors(x);
        for (int y : nbr)
        {
            int fy = f(y);
            if (fy < best)
            {
                best = fy;
                bestx = y;
            }
        }
        if (best < fx)
        {
            x = bestx;
            fx = best;
        }
        else
            break;
    }
    return {x, fx};
}
pair<int, int> random_restart(int max_steps, int restarts)
{
    mt19937 rng(123);
    uniform_int_distribution<int> dist(-50, 50);
    pair<int, int> best = {0, INT_MAX};
    for (int r = 0; r < restarts; r++)
    {
        auto res = hill(dist(rng), max_steps);
        if (res.second < best.second)
            best = res;
    }
    return best;
}
int main()
{
    auto res = random_restart(50, 20);
    cout << res.first << " " << res.second << "\n";
}
