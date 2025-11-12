#include <bits/stdc++.h>
using namespace std;
int manhattan(const vector<vector<int>> &s, const vector<vector<int>> &goal)
{
    int n = s.size();
    int d = 0;
    vector<pair<int, int>> pos(n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            pos[goal[i][j]] = {i, j};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int v = s[i][j];
            if (v)
            {
                auto [gi, gj] = pos[v];
                d += abs(gi - i) + abs(gj - j);
            }
        }
    return d;
}
vector<vector<vector<int>>> neighbors(const vector<vector<int>> &s)
{
    int n = s.size();
    int zi = 0, zj = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (s[i][j] == 0)
            {
                zi = i;
                zj = j;
            }
    vector<vector<vector<int>>> res;
    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};
    for (int k = 0; k < 4; k++)
    {
        int ni = zi + di[k], nj = zj + dj[k];
        if (0 <= ni && ni < n && 0 <= nj && nj < n)
        {
            auto t = s;
            swap(t[zi][zj], t[ni][nj]);
            res.push_back(t);
        }
    }
    return res;
}
pair<vector<vector<int>>, int> hill(vector<vector<int>> cur, const vector<vector<int>> &goal, int max_steps)
{
    int h = manhattan(cur, goal);
    for (int step = 0; step < max_steps; step++)
    {
        auto best = cur;
        int besth = h;
        auto nbr = neighbors(cur);
        for (auto &nb : nbr)
        {
            int hb = manhattan(nb, goal);
            if (hb < besth)
            {
                besth = hb;
                best = nb;
            }
        }
        if (besth < h)
        {
            cur = best;
            h = besth;
        }
        else
            break;
    }
    return {cur, h};
}
int main()
{
    vector<vector<int>> goal{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    vector<vector<int>> initial{{1, 2, 3}, {4, 5, 6}, {0, 7, 8}};
    auto res = hill(initial, goal, 100);
    cout << res.second << "\n";
    for (auto &r : res.first)
    {
        for (size_t j = 0; j < r.size(); ++j)
        {
            if (j)
                cout << " ";
            cout << r[j];
        }
        cout << "\n";
    }
}
