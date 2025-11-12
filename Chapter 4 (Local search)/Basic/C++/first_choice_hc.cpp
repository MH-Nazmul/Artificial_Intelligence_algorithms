#include <bits/stdc++.h>
using namespace std;
int f(int x) { return (x - 3) * (x - 3); }
vector<int> neighbors(int x) { return {x - 1, x + 1}; }
pair<int, int> first_choice_hc(int (*F)(int), vector<int> (*N)(int), int init, int max_steps)
{
    mt19937 rng(123);
    int x = init;
    int fx = F(x);
    for (int step = 0; step < max_steps; step++)
    {
        auto nbr = N(x);
        shuffle(nbr.begin(), nbr.end(), rng);
        bool improved = false;
        for (int y : nbr)
        {
            int fy = F(y);
            if (fy < fx)
            {
                x = y;
                fx = fy;
                improved = true;
                break;
            }
        }
        if (!improved)
            break;
    }
    return {x, fx};
}
int main()
{
    auto res = first_choice_hc(f, neighbors, 0, 100);
    cout << res.first << " " << res.second << "\n";
}
