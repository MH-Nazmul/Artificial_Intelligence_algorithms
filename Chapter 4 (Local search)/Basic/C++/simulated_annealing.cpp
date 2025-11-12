#include <bits/stdc++.h>
using namespace std;
int f(int x) { return (x - 3) * (x - 3); }
vector<int> neighbors(int x) { return {x - 1, x + 1}; }
pair<int, int> simulated_annealing(int init, int max_steps, double t0, double alpha)
{
    mt19937 rng(123);
    uniform_real_distribution<double> ur(0.0, 1.0);
    int x = init;
    int fx = f(x);
    double T = t0;
    for (int step = 0; step < max_steps; step++)
    {
        auto nbr = neighbors(x);
        if (nbr.empty())
            break;
        uniform_int_distribution<int> di(0, (int)nbr.size() - 1);
        int y = nbr[di(rng)];
        int fy = f(y);
        if (fy < fx || ur(rng) < exp(-(double)(fy - fx) / max(T, 1e-12)))
        {
            x = y;
            fx = fy;
        }
        T *= alpha;
        if (T < 1e-12)
            break;
    }
    return {x, fx};
}
int main()
{
    auto res = simulated_annealing(0, 1000, 1.0, 0.995);
    cout << res.first << " " << res.second << "\n";
}
