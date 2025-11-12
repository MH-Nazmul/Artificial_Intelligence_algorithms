#include <bits/stdc++.h>
using namespace std;
int f(int x) { return (x - 3) * (x - 3); }
vector<int> neighbors(int x) { return {x - 1, x + 1}; }
pair<int, int> stochastic_hc(int (*F)(int), vector<int> (*N)(int), int init, int max_steps)
{
    mt19937 rng(123);
    int x = init;
    int fx = F(x);
    for (int step = 0; step < max_steps; step++)
    {
        auto nbr = N(x);
        if (nbr.empty())
            break;
        uniform_int_distribution<int> dist(0, (int)nbr.size() - 1);
        int y = nbr[dist(rng)];
        int fy = F(y);
        if (fy < fx)
        {
            x = y;
            fx = fy;
        }
        else
        {
            int tried = 1;
            bool improved = false;
            while (tried < (int)nbr.size())
            {
                y = nbr[dist(rng)];
                fy = F(y);
                if (fy < fx)
                {
                    x = y;
                    fx = fy;
                    improved = true;
                    break;
                }
                tried++;
            }
            if (!improved)
                break;
        }
    }
    return {x, fx};
}
int main()
{
    auto res = stochastic_hc(f, neighbors, 0, 100);
    cout << res.first << " " << res.second << "\n";
}
