#include <bits/stdc++.h>
using namespace std;
int conflicts(const vector<int> &s)
{
    int n = s.size();
    int c = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i] == s[j] || abs(s[i] - s[j]) == abs(i - j))
                c++;
    return c;
}
vector<vector<int>> neighbors(const vector<int> &s)
{
    int n = s.size();
    vector<vector<int>> res;
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
            if (row != s[col])
            {
                auto t = s;
                t[col] = row;
                res.push_back(t);
            }
    return res;
}
pair<vector<int>, int> hill(int n, int max_steps)
{
    mt19937 rng(123);
    vector<int> cur(n);
    for (int i = 0; i < n; i++)
        cur[i] = rng() % n;
    int curc = conflicts(cur);
    for (int step = 0; step < max_steps; step++)
    {
        auto best = cur;
        int bestc = curc;
        auto nbr = neighbors(cur);
        for (auto &nb : nbr)
        {
            int c = conflicts(nb);
            if (c < bestc)
            {
                bestc = c;
                best = nb;
            }
        }
        if (bestc < curc)
        {
            cur = best;
            curc = bestc;
            if (curc == 0)
                break;
        }
        else
            break;
    }
    return {cur, curc};
}
int main()
{
    auto res = hill(8, 10000);
    for (size_t i = 0; i < res.first.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << res.first[i];
    }
    cout << "\n"
         << res.second << "\n";
}
