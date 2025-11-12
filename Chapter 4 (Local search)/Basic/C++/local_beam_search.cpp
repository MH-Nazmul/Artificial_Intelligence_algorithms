#include <bits/stdc++.h>
using namespace std;
int f(int x) { return (x - 3) * (x - 3); }
vector<int> neighbors(int x) { return {x - 1, x + 1}; }
pair<int, int> local_beam(int k, int max_steps)
{
    mt19937 rng(123);
    uniform_int_distribution<int> dist(-50, 50);
    vector<int> states(k);
    for (int i = 0; i < k; i++)
        states[i] = dist(rng);
    vector<int> values(k);
    for (int i = 0; i < k; i++)
        values[i] = f(states[i]);
    for (int step = 0; step < max_steps; step++)
    {
        vector<pair<int, int>> pv;
        for (int i = 0; i < k; i++)
            pv.push_back({values[i], states[i]});
        sort(pv.begin(), pv.end());
        int bestv = pv[0].first;
        vector<int> new_states;
        for (int i = 0; i < k; i++)
        {
            int s = pv[i].second;
            auto nbr = neighbors(s);
            for (int y : nbr)
                new_states.push_back(y);
        }
        if (new_states.empty())
            break;
        vector<pair<int, int>> cand;
        for (int s : new_states)
            cand.push_back({f(s), s});
        sort(cand.begin(), cand.end());
        states.clear();
        values.clear();
        for (int i = 0; i < k && i < (int)cand.size(); i++)
        {
            values.push_back(cand[i].first);
            states.push_back(cand[i].second);
        }
        if (values[0] >= bestv)
            break;
    }
    return {states[0], values[0]};
}
int main()
{
    auto res = local_beam(3, 100);
    cout << res.first << " " << res.second << "\n";
}
